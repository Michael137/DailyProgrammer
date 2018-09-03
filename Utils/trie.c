#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./trie.h"

// ASCII: 97-122 (a-z)
// 'a' -> 97 - 97 == 0
int t_idx_from_char( char letter ) { return tolower( letter ) - 'a'; }

void t_create_node( TrieNode** node )
{
	( *node ) = malloc( sizeof( TrieNode ) );
	for( int i = 0; i < ALPHABET_SZ; ++i )
		( *node )->children[i] = NULL;
	( *node )->is_word_end = false;
}

void t_insert_node( TrieNode** node, char const* str )
{
	TrieNode* trav = *node;
	for( int i = 0; str[i] != '\0'; ++i ) {
		int idx = t_idx_from_char( str[i] );

		if( trav->children[idx] == NULL )
			t_create_node( &( trav->children[idx] ) );

		trav = trav->children[idx];
	}

	trav->is_word_end = true;
}

bool t_search_from_node( TrieNode* node, char const* str )
{
	TrieNode* tmp = node;
	for( int i = 0; str[i] != '\0'; ++i ) {
		int idx = t_idx_from_char( str[i] );

		if( tmp->children[idx] == NULL ) return false;

		tmp = tmp->children[idx];
	}

	return tmp->is_word_end;
}

void t_create( Trie** trie )
{
	( *trie ) = malloc( sizeof( Trie ) );
	t_create_node( &( ( *trie )->root ) );
}

void t_insert( Trie** trie, char const* str )
{
	t_insert_node( &( ( *trie )->root ), str );
}

bool t_search( Trie* trie, char const* str )
{
	t_search_from_node( trie->root, str );
}

void t_free_node( TrieNode* node )
{
	if( node == NULL ) return;

	for( int i = 0; i < ALPHABET_SZ; ++i )
		t_free_node( node->children[i] );

	free( node );
	node = NULL;
}

void t_free( Trie* trie )
{
	t_free_node( trie->root );
	free( trie );
	trie = NULL;
}
