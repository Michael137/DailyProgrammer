#ifndef TRIE_H_IN
#define TRIE_H_IN

#include <stdbool.h>

#define ALPHABET_SZ 26
#define ASSERT_WORD( container, str )                                          \
	if( t_search( container, str ) ) printf( "Found %s!\n", str );

typedef struct TrieNode_
{

	struct TrieNode_* children[ALPHABET_SZ];
	bool is_word_end;

} TrieNode;

typedef struct Trie_
{
	TrieNode* root;
} Trie;

void t_insert( Trie** trie, char const* str );
void t_free( Trie* trie );
bool t_search( Trie const* trie, char const* str );
void t_create( Trie** trie );

#endif // TRIE_H_IN
