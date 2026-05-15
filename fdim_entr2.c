
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
	

    // Optional: Standardize format to 8-bit RGBA
	/*
    png_set_expand(png_ptr);
    png_set_strip_16(png_ptr);
    png_set_tRNS_to_alpha(png_ptr);
    png_read_update_info(png_ptr, info_ptr);
	*/

	//printf( "%d %d %d\n", width, height, png_get_rowbytes(png_ptr, info_ptr) );

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

int main( int argc, char **argv )
{
	int w, h;
	uc **image;
	int *hist;
	int nt, nr;
	int p0, p1, p2, p3, p4;
	long wmin, s, d;
	int tmin;
	float p, ent;
	int i, ii, j, jj, k, kk;
	
	read_png_file( argv[1], &w, &h, &image );
	nt = ( w / 8 ) * ( h / 8 );
	nr = 4 * nt;
	hist = calloc( nt, sizeof( int ) );
	for ( i = 0; i < w / 4; i++ )
	{
		for ( ii = 0; ii < h / 4; ii++ )
		{
			for ( j = 0; j < w / 8; j++ )
			{
				for ( jj = 0; jj < h / 8; jj++ )
				{
					s = 0;
					for ( k = 0; k < 4; k++ )
					{
						for ( kk = 0; kk < 4; kk++ )
						{
							p1 = image[ 8 * jj + 2 * kk ][ 8 * j + 2 * k ];
							p2 = image[ 8 * jj + 2 * kk + 1 ][ 8 * j + 2 * k ];
							p3 = image[ 8 * jj + 2 * kk ][ 8 * j + 2 * k + 1 ];
							p4 = image[ 8 * jj + 2 * kk + 1 ][ 8 * j + 2 * k + 1 ];
							p0 = image[ 4 * ii + kk ][ 4 * i + k ];
							
							d = sqr( p1 - p0 ) + sqr( p2 - p0 ) + sqr( p3 - p0 ) + sqr( p4 - p0 );
							s += d;
						}
					}
					if ( j == 0 && jj == 0 || s < wmin )
					{
						wmin = s;
						tmin = ( w / 8 ) * jj + j;
					}
				}
			}
			hist[ tmin ]++;
		}
	}
	ent = 0;
	for ( i = 0; i < nt; i++ )
	{
		if ( hist[i] == 0 ) continue;
		p = (float)hist[i] / nr;
		ent -= p * log( p );
	}
	printf( "%g\n", ent / log( nt ) );
}