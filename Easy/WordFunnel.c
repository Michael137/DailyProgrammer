#include "../Utils/trie.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void build_trie( Trie** trie, FILE* fp )
{
	char* in_str;
	t_create( trie );

	while( !feof( fp ) ) {
		read_input_file( &in_str, fp );
		t_insert( trie, in_str );
		free( in_str );
	}

	rewind( fp );
}

bool check_strings( char* str1, char const* str2 )
{
	uint64_t const len = strlen( str1 );
	for( uint64_t i = 0; i < len; ++i ) {
		// Remove character from string
		char tmp[len + 1];
		strncpy( tmp, str1, sizeof( tmp ) );
		memmove( &tmp[i], &tmp[i + 1], len - i );

		if( strcmp( tmp, str2 ) == 0 ) return true;
	}

	return false;
}

int funnel_trie( Trie const* trie, char* str )
{
	int count = 0;
	uint64_t const len = strlen( str );
	for( uint64_t i = 0; i < len; ++i ) {
		// Remove character from string
		char tmp[len + 1];
		strncpy( tmp, str, sizeof( tmp ) );
		memmove( &tmp[i], &tmp[i + 1], len - i );

		if( t_search( trie, tmp ) && !( ( i > 0 && str[i] == str[i - 1] ) ) )
			count++;
	}

	return count;
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

// Find all words in enable1.txt that yield
// check_strings( word, another word in enable1.txt ) for five
// words in the enable1.txt list
//
// e.g. boats
int bonus2( bool print )
{
	FILE* fp;
	int num_found = 0;
	char* in_str;

	fp = fopen( "enable1.txt", "r" );

	Trie* trie;
	build_trie( &trie, fp );

	while( !feof( fp ) ) {
		read_input_file( &in_str, fp );
		if( funnel_trie( trie, in_str ) == 5 ) {
			if( print ) printf( "%s\n", in_str );
			num_found++;
		}
		free( in_str );
	}

	t_free( trie );
	fclose( fp );

	return num_found;
}

int main()
{
//	challenge();
	printf( "Found %d words funnelling 5 other words.\n", bonus2( false ) );

	return 0;
}
