
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <png.h>

typedef unsigned char uc;

#define sqr(x) ((x)*(x))

int read_png_file( const char *filename, int *_w, int *_h, uc ***data ) 
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) return 0;

    // 1. Initialize PNG structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);

    // 2. Set up Error Handling
    if (setjmp(png_jmpbuf(png_ptr))) 
	{
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return 0;
    }

    // 3. Initialize I/O, Get Metadata, and Read Pixel Data
    png_init_io(png_ptr, fp);
    png_read_info(png_ptr, info_ptr);
    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
	

    // Read rows
    png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
    png_read_image(png_ptr, row_pointers);

    // 4. Cleanup
    //for (int y = 0; y < height; y++) free(row_pointers[y]);
    //free(row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
	
	*_w = width;
	*_h = height;
	*data = (uc**) row_pointers;
	
	return 1;
}
	
float max_entr( int G, int L )
{
	int ni = 100;
	int *hist;
	int n = L*L;
	float sum, entr;
	float st = 0;
	int i, j, k;
	
	hist = malloc( G * sizeof( int ) );
	for ( i = 0; i < ni; i++ )
	{
		memset( hist, 0, G * sizeof( int ) );
		for ( j = 0; j < n; j++ )
		{
			k = rand() % G;
			hist[k]++;
		}
		sum = n;
		entr = 0;
		for ( j = 0; j < G; j++ )
		{
			if ( hist[j] != 0 ) entr -= ( hist[j] / sum ) * log( hist[j] / sum );
		}
		st += entr;
	}
	return st/ni;
}
	
#define min_macro( a, b ) ((a)<(b))?(a):(b)
#define max_macro( a, b ) ((a)>(b))?(a):(b)

void solve3( float *m, float *rp, float *sol )
{
	float det;
	float rm[9];
	int i, j;
	
	det = ( m[0] * m[4] - m[1] * m[3] ) * m[8] - ( m[0] * m[5] - m[2] * m[3] ) * m[7] + ( m[1] * m[5] - m[2] * m[4] ) * m[6];
	rm[0] = ( m[4] * m[8] - m[5] * m[7] ) / det;
	rm[3] = -( m[3] * m[8] - m[5] * m[6] ) / det;
	rm[6] = ( m[3] * m[7] - m[4] * m[6] ) / det;
	rm[1] = -( m[1] * m[8] - m[2] * m[7] ) / det;
	rm[4] = ( m[0] * m[8] - m[2] * m[6] ) / det;
	rm[7] = -( m[0] * m[7] - m[1] * m[6] ) / det;
	rm[2] = ( m[1] * m[5] - m[2] * m[4] ) / det;
	rm[5] = -( m[0] * m[5] - m[2] * m[3] ) / det;
	rm[8] = ( m[0] * m[4] - m[1] * m[3] ) / det;
	
	for ( i = 0; i < 3; i++ )
	{
		sol[i] = 0;
		for ( j = 0; j < 3; j++ ) sol[i] += rm[ 3 * i + j ] * rp[j];
	}
}

void quadratic_regression( int ng, float *xx, float *yy, float *s1, float *s2 )
{
	float m[9] = { 0 }, rp[3] = { 0 }, sol[3];
	float x, y;
	float dd, yp, sum, rms;
	int i, j;
	
	for ( i = 0; i < ng; i++ )
	{
		x = log( xx[i] );
		y = log( yy[i] );
		m[0] += 1;
		m[1] += x;
		m[2] += x * x;
		m[3] += x;
		m[4] += x * x;
		m[5] += x * x * x;
		m[6] += x * x;
		m[7] += x * x * x;
		m[8] += x * x * x * x;
		rp[0] += y;
		rp[1] += y * x;
		rp[2] += y * x * x;
	}
	solve3( m, rp, sol );
	sum = 0;
	for ( i = 0; i < ng; i++ )
	{
		x = log( xx[i] );
		y = log( yy[i] );
		yp = sol[0] + sol[1] * x + sol[2] * x * x;
		dd = y - yp;
		sum += dd * dd;
	}
	rms = sqrt( sum / ng );
	*s1 = sol[1];
	*s2 = sol[2];
}

int main( int argc, char **argv )
{
	int G_min, G_max, G;
	int w, h, M_min, M_max;
	int L;
	int L_step;
	float r;
	float N_r;
	float *ra, *Nra;
	float N_min;
	unsigned char **bytes;
	unsigned char *row;
	int pixel;
	int *hist;
	float fr, s0;
	float sum, nb, emax;
	float ss1, ss2;
	int n, np;
	int i, ii, j, jj, k, kk, k1, k2;
	
	srand( 1 );
	read_png_file( argv[1], &w, &h, &bytes );
	
	G_min = 256;
	G_max = 0;
	for ( i = 0; i < h; i++ )
	{
		for ( j = 0; j < w; j++ )
		{
			G_min = min_macro( G_min, bytes[i][j] );
			G_max = max_macro( G_max, bytes[i][j] );
		}
	}
	G = G_max - G_min + 1;
	hist = malloc( 256 * sizeof( int ) );
	n = w * h;
	emax = log( G * ( 1 - pow( 1 - 1. / G, n ) ) );
	memset( hist, 0, 256 * sizeof( int ) );
	for ( ii = 0; ii < h; ii++ )
	{
		row = bytes[ ii ];
		for ( jj = 0; jj < w; jj++ )
		{
			pixel = row[ jj ];
			hist[ pixel ]++;
		}
	}
	sum = 0;
	for ( k = G_min; k < G_max; k++ )
	{
		fr = (float)hist[k] / n;
		if ( fr != 0 ) 
		{
			sum -= fr * log( fr );
		}
	}

	printf( "%g\n", sum / emax );
}

