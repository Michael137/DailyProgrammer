#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void read_input( char** str, FILE* in_stream )
{
	uint64_t buf_sz = 255;
	*str = malloc( buf_sz );

	if( *str != NULL ) {
		int input;
		uint64_t ctr = 0;
		while( ( input = fgetc( in_stream ) ) != '\n' && input != EOF ) {
			( *str )[ctr++] = input;

			if( ctr == buf_sz ) {
				buf_sz *= 2;
				*str = realloc( *str, buf_sz );
			}
		}

		( *str )[ctr] = '\0';
	} else {
		fprintf( stderr, "Failed to allocate memory at %s:%d:%s()", __FILE__,
				 __LINE__, __func__ );
	}
}

void read_input_prompt( char** str ) { read_input( str, stdin ); }

void read_input_file( char** str, FILE* fp ) { read_input( str, fp ); }

bool check_strings( char* str1, char const* str2 )
{
	uint64_t const len = strlen( str1 );
	for( uint64_t i = 0; i < len; ++i )
	{
		char tmp[len + 1];
		strncpy( tmp, str1, len );
		memmove( &tmp[i], &tmp[i + 1], len - i );

		if( strncmp( tmp, str2, len ) == 0 )
			return true;
	}

	return false;
}

void challenge()
{
	char *mut_str, *fin_str;
	read_input_prompt( &mut_str );
	read_input_prompt( &fin_str );

	if( check_strings( mut_str, fin_str ) )
		printf( "Works\n" );
	else
		printf( "Doesn't work\n" );

	free( mut_str );
	free( fin_str );
	mut_str = NULL;
	fin_str = NULL;
}

void bonus()
{
	char *mut_str, *fin_str;
	FILE* fp;
	fp = fopen( "enable1.txt", "r" );

	read_input_file( &mut_str, fp );
	read_input_file( &fin_str, fp );

	fclose( fp );

	check_strings( mut_str, fin_str );

	free( mut_str );
	free( fin_str );
	mut_str = NULL;
	fin_str = NULL;
}
int main()
{
	challenge();
//	bonus();

	return 0;
}
