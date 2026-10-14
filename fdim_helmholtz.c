
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <png.h>
#include <gsl/gsl_sf_bessel.h>


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
		
#define min_macro( a, b ) ((a)<(b))?(a):(b)
#define max_macro( a, b ) ((a)>(b))?(a):(b)
#define abs_macro( a ) ((a)>=0)?(a):(-(a))

/*
double b_fit( int n, float *vect, float *p0, float *p1 );
double g_fit( int n, float *vect, float *p );
double bb_fit( int n, float *vect, float *p, float *diff );
*/

void calc_laplas( int w, int h, double *field, double *laplas )
{
	int i, j, k;

	for ( i = 1; i < h - 1; i++ )
	{
		for ( j = 1; j < w - 1; j++ )
		{
			laplas[ i * w + j ] = 4 * field[ i * w + j ] 
				- field[ ( i + 1 ) * w + j ]
				- field[ ( i - 1 ) * w + j ]
				- field[ i * w + j + 1 ]
				- field[ i * w + j - 1 ];
		}
	}
	for ( i = 1; i < h - 1; i++ )
	{
		laplas[ i * w ] = 3 * field[ i * w ] - field[ ( i + 1 ) * w ] - field[ ( i - 1 ) * w ] - field[ i * w + 1 ];
		laplas[ i * w + w - 1 ] = 3 * field[ i * w + w - 1 ] 
			- field[ ( i + 1 ) * w + w - 1 ] - field[ ( i - 1 ) * w + w - 1 ] - field[ i * w + w - 2 ];
	}
	for ( j = 1; j < w - 1; j++ )
	{
		laplas[ j ] = 3 * field[j] - field[ j - 1 ] - field[ j + 1 ] - field[ w + j ];
		k = ( h - 1 ) * w;
		laplas[ k + j ] = 3 * field[ k + j ] - field[ k + j - 1 ] - field[ k + j + 1 ] - field[ k - w + j ];
	}
	laplas[0] = 2 * field[0] - field[1] - field[w];
	laplas[ w - 1 ] = 2 * field[ w - 1 ] - field[ w - 2 ] - field[ 2 * w - 1 ];
	k = ( h - 1 ) * w;
	laplas[ k ] = 2 * field[k] - field[ k + 1 ] - field[ k - w ];
	k = h * w - 1;
	laplas[ k ] = 2 * field[k] - field[ k - 1 ] - field[ k - w ];
}
	
void fdim_field_multi( int w, int h, double *field )
{
	double s0, ss0, ss, v, avg, sd;
	int nn, i0, j0, ii, jj;
	int i, j, k;
	
	for ( k = 2; k < h / 2; k *= 2 )
	{
		ss = 0;
		nn = 0;
		for ( i = 0; i < h - k; i += k )
		{
			for ( j = 0; j < w - k; j += k )
			{
				s0 = 0;
				ss0 = 0;
				for ( i0 = 0; i0 < 2; i0++ )
				{
					for ( j0 = 0; j0 < 2; j0++ )
					{
						v = 0;
						for ( ii = i; ii < i + k; ii++ )
						{
							for ( jj = j; jj < j + k; jj++ )
							{
								v += field[ ( ii + i0 * k ) * w + ( jj + j0 * k ) ];
							}
						}
						v /= ( k * k );
						s0 += v;
						ss0 += v * v;
					}
				}
				avg = s0 / 4;
				sd = sqrt( ss0 / 4 - avg * avg );
				if ( sd != sd ) continue;
				ss += sd;
				nn++;
			}
		}
		printf( "%g,", ss / nn );
	}
	printf( "\n" );
}

double fdim_field( int w, int h, double *field )
{
	double s0, ss0, ss, v, avg, sd;
	double s[5] = { 0 }, slope;
	int nn, i0, j0, ii, jj;
	int l;
	int i, j, k;
	
	l = 0;
	for ( k = 2; k < h / 2; k *= 2, l++ )
	{
		nn = 0;
		s0 = 0;
		ss0 = 0;
		for ( i = 0; i < h; i += k )
		{
			for ( j = 0; j < w; j += k )
			{
				ss = 0;
				for ( ii = i; ii < i + k; ii++ )
				{
					for ( jj = j; jj < j + k; jj++ )
					{
						ss += field[ ii * w + jj ];
					}
				}
				v = ss / ( k * k );
				s0 += v;
				ss0 += v * v;
				nn++;
			}
		}
		avg = s0 / nn;
		sd = sqrt( ss0 / nn - avg * avg );
		
		s[0] += l;
		s[1] += sd;
		s[2] += l * l;
		s[3] += sd * sd;
		s[4] += l * sd;
	}
	slope = ( l * s[4] - s[0] * s[1] ) / ( l * s[2] - s[0] * s[0] );
	return -slope / log( 2 );
}

int main( int argc, char **argv )
{
	double s0 = 0, ss0 = 0, avg, sd;
	int w, h, n;
	unsigned char **bytes;
	unsigned char *row;
	int pixel;
	double *field;
	double *laplas;
	double *perturb;
	double v, sx, sy, ss;
	double coeff;
	double sigma;
	double delta;
	double fdim;
	double *corrfun;
	double *cfnorm;
	double rcorr;
	int i, j, k;
	
	srand( 1 );
	read_png_file( argv[1], &w, &h, &bytes );
	n = w * h;
	
	for ( i = 0; i < h; i++ )
	{
		for ( j = 0; j < w; j++ )
		{
			s0 += bytes[i][j];
			ss0 += sqr( bytes[i][j] );
		}
	}
	avg = s0 / n;
	sd = sqrt( ss0 / n - avg * avg );
	
	field = calloc( w * h, sizeof( double ) );
	laplas = calloc( w * h, sizeof( double ) );
	perturb = calloc( w * h, sizeof( double ) );
	for ( i = 0; i < h; i++ )
	{
		row = bytes[ i ];
		for ( j = 0; j < w; j++ )
		{
			pixel = row[ j ];
			field[ i * w + j ] = ( (float)pixel - avg ) / sd;
		}
	}
	calc_laplas( w, h, field, laplas );
	s0 = 0;
	avg = s0 / ( h * w );
	sx = 0;
	sy = 0;
	ss = 0;
	for ( i = 0; i < h; i++ )
	{
		for ( j = 0; j < w; j++ )
		{
			sx += field[ i * w + j ] * field[ i * w + j + 1 ];
			sy += field[ i * w + j ] * laplas[ i * w + j + 1 ];
			ss += field[ i * w + j ] * laplas[ i * w + j  ];
		}
	}
	coeff = sy / sx;
	sigma = ss / ( h * w ) - coeff;
	ss = 0;
	for ( i = 0; i < h; i++ )
	{
		for ( j = 0; j < w; j++ )
		{
			perturb[ i * w + j ] = laplas[ i * w + j ] - field[ i * w + j ] * coeff;
			ss += perturb[ i * w + j ] * perturb[ i * w + j ];
		}
	}
	delta = ss / ( h * w );
	v = sqrt( delta );
	for ( i = 0; i < h * w; i++ ) perturb[i] /= v;
	/*
	corrfun = calloc( w, sizeof( double ) );
	cfnorm = calloc( w, sizeof( double ) );
	for ( i = 0; i < h; i++ )
	{
		for ( j = 0; j < w / 2; j++ )
		{
			for ( k = 0; k + j < w; k++ )
			{
				corrfun[ j ] += perturb[ i * w + k ] * perturb[ i * w + k + j ] / sigma;
				cfnorm[ j ] += 1;
			}
		}
	}
	ss = 0;
	for ( i = 0; i < 5; i++ ) 
	{
		v = corrfun[i] / cfnorm[i];
		printf( "%g ", v );
		if ( v < 0 ) continue;
		ss += v * i * i;
	}
	printf( "\n" );
	rcorr = sqrt( ss );
	*/
	fdim = fdim_field( w, h, perturb );
	printf( "[%g,%g,%g,%g],\n", coeff, sigma, delta, fdim );
}

