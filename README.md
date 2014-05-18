mini-search
===========

Mini-Search-Engine

This project contains the files required to parse and create an index for searching terms in Wikipedia. There are 2 python files and one C++ file. The file 1_parse_python.py takes as input the wikipedia xml to be parsed. 
It creates two files with mapping as follows:
1) tuple.txt: contains (word,id) tuples as word --> wikipedia_id
2) urls.txt: contains (id, wikipedia_url) tuples as wikipedia_id --> wikipedia_url

The second file 2_writeIndexToFile.py reads the contents of tuple.txt and combines them to create posting lists for words in a file index.txt as follows:
word --> wikipedia_id1, wikipedia_id2,...

The third file 3_constructIndex.cpp reads the posting lists from index.txt and loads the index into memory. The user can enter a query of any number of words and this program fetches the relevant documents containing all these words. 
