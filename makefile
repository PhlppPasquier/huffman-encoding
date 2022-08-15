all: 
	gcc -o encode src/encode.c src/bitstream/bitstream.c src/heapq/heapq.c src/huffman/huffman.c
	gcc -o decode src/decode.c src/bitstream/bitstream.c src/heapq/heapq.c src/huffman/huffman.c