# Huffman-Coding

> In computer science and information theory, a Huffman code is a particular type of optimal
  prefix code that is commonly used for lossless data compression. The process of finding or using such a code proceeds by means of Huffman coding, an algorithm developed by David A. Huffman while he was a Sc.D. student at MIT, and published in the 1952 paper "A Method for the Construction of Minimum-Redundancy Codes".
  [from wikipedia](https://en.wikipedia.org/wiki/Huffman_coding)
  
Simply, it compresses and decompresses text files without lossing any data.

## how it works
encode.c file converts "text.txt" into huffman code.
decode.c file converts huffman code into "output.txt".

you need to compile all .c files in the utils folder as well as common.c to run encode or decode file.