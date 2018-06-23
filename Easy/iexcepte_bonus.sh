#!/bin/bash
if [ ! -f enable1.txt ]; then
	wget https://norvig.com/ngrams/enable1.txt
fi

cat enable1.txt | xargs -n1 ./a.out | grep false | wc -l
