# The-Huffmans-Algorithm
-The Huffman algorithm is a lossless, data-compression algorithm. 

-Given an input text file, the program must do the following:
  - The program should perform a linear scan to gather the frequencies of all the letters in a file. Letters with zero frequencies should not be considered. The frequencies should then be saved in a list L of binary tree nodes. Here, each node should contain a letter and its frequency. 
  - The list L should be sorted according to frequencies in increasing order.
  - The first 2 nodes N1 and N2 with the lowest frequencies should then be removed from the list L. A new node N should be built with a hypothetical letter (a dummy) and a frequency from the sum of the frequences of nodes N1 and N2. Node N1 should then be the left child of N and N2 the right child of N. Node N shoud then be inserted into L to keep the list in sorted order. This process should be repeated until L has only one node T. 
  - The node T is the Huffman code tree. For any node in the tree, its edge pointing to its left child (if there is one), can be interpreted as 0 and its right edge pointing to its right child (if there is one), can be interpreted as 1. The binary string along the edge path from the root to a letter at a leaf node is the Huffman code for the letter. 
  - The program should use the Huffman code to encode the input text file and output a coded file (encoded file).
  - The program should then input the encoded file, decode it using the Huffman code, and save the result in another output file (decoded file). 

Test Run: The program should be tested by first encoding and decoding the following text:
- In computer science and information theory, a Huffman code is an optimal prefix code found using the algorithm developed by David A. Huffman while he was a Ph.D. student at MIT, and published in the 1952 paper "A Method for the Construction of Minimum-Redundancy Codes". The process of finding and/or using such a code is called Huffman coding and is a common technique in entropy encoding, including in lossless data compression. The algorithm's output can be viewed as a variable-length code table for encoding a source symbol (such as a character in a file). Huffman's algorithm derives this table based on the estimated probability or frequency of occurrence (weight) for each possible value of the source symbol. As in other entropy encoding methods, more common symbols are generally represented using fewer bits than less common symbols. Huffman's method can be efficiently implemented, finding a code in linear time to the number of input weights if these weights are sorted. However, although optimal among methods encoding symbols separately, Huffman coding is not always optimal among all compression methods.













