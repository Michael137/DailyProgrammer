word_funnel: trie
	gcc WordFunnel.c trie.o

trie:
	gcc -c ../Utils/trie.c -o trie.o

.PHONY:
clean:
	rm -f a.out
	rm -f trie.o

all: clean word_funnel
