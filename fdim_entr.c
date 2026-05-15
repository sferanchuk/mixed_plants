
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int read_pnm( const char *fname, int *w, int *h, unsigned char **bytes )
{
	FILE *f;
	char buf[4096];
	char *p;
	int i, j, k;
	
	f = fopen( fname, "rt" );
	fgets( buf, 4096, f );
	fgets( buf, 4096, f );
	if ( buf[0] == '#' ) fgets( buf, 4096, f );
	sscanf( buf, "%d %d", w, h );
	fgets( buf, 4096, f );
	*bytes = malloc( *w * *h );
	memset( buf, 0, 4096 );
	for ( i = 0; i < *w * *h; i++ )
	{
		for ( j = 0; j < 1; j++ ) 
		{
			k = 0;
			do { buf[k] = fgetc( f ); if ( !isspace( buf[k] ) ) break; } while( 1 );
			k++;
			do { buf[k] = fgetc( f ); if ( isspace( buf[k] ) ) break; k++; } while( 1 );
			buf[k] = 0;
		}
		(*bytes)[i] = atoi( buf );
	}
	fclose( f );
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
	int M1, M2, M_min, M_max;
	int L;
	int L_step;
	int h, height;
	float r;
	float N_r;
	float *ra, *Nra;
	unsigned char *bytes;
	unsigned char *row;
	int pixel;
	int *hist;
	float fr, s0;
	float sum, nb, emax;
	float ss1, ss2;
	int n, np;
	int i, ii, j, jj, k, kk, k1, k2;
	
	srand( 1 );
	read_pnm( argv[1], &M1, &M2, &bytes );
	M_min = min_macro( M1, M2 );
	M_max = max_macro( M1, M2 );
	
	G_min = 256;
	G_max = 0;
	for ( i = 0; i < M1 * M2; i++ )
	{
		G_min = min_macro( G_min, bytes[i] );
		G_max = max_macro( G_max, bytes[i] );
	}
	G = G_max - G_min + 1;
	ra = malloc( M_max * sizeof( float ) );
	Nra = malloc( M_max * sizeof( float ) );
	np = 0;
	
	hist = malloc( 256 * sizeof( int ) );
	for ( L = 2; L < M_min / 2 && L < 150; )
	{
		L_step = sqrt( L );
		N_r = 0;
		r = (float) L;
		n = L * L;
		emax = log( G * ( 1 - pow( 1 - 1. / G, n ) ) );
		//emax = max_entr( G, L );
		s0 = 0;
		for ( i = 0; i < M2 - L; i += L_step )
		{
			for ( j = 0; j < M1 - L; j += L_step )
			{
				memset( hist, 0, 256 * sizeof( int ) );
				for ( ii = 0; ii < L; ii++ )
				{
					row = bytes + M1 * ( i + ii );
					for ( jj = 0; jj < L; jj++ )
					{
						pixel = row[ j + jj ];
						hist[ pixel ]++;
					}
				}
				sum = 0;
				nb = 0;
				for ( k = G_min; k < G_max; k++ )
				{
					fr = (float)hist[k] / n;
					if ( fr != 0 ) 
					{
						sum -= fr * log( fr );
						nb += 1;
					}
				}
				if ( sum / emax < 0.2 ) continue;
				//N_r += sum / log( nb );
				N_r += sum / emax;
				s0 += 1;
			}
		}
		N_r /= s0;
		ra[np] = r;
		Nra[np] = N_r;
		np++;
		L += L_step;
	}

	//quadratic_regression( np, ra, Nra, &ss1, &ss2 );
	//printf( "%g %g\n", ss1, ss2 );
	for ( i = 0; i < np; i++ ) printf( "[%g,%g],", ra[i], Nra[i] );
}

