-------- Text File Compressor ------
by Tuan Huynh, 2019

files provided by the University of South Florida, Willam Oropallo, Ph.D, include:
HeapQueue.hpp
HuffmanBase.hpp
HuffmanBase.cpp




-------- Description and Compilation ------

This is a Text File Compression program that uses a Huffman Tree Algorithm.
Download all files included and compile using *.cpp




--------- Command Line Arguments ---------

This program uses command line arguments to compress or decompress text files

To compress a text file:

    Run the executable along with the keyword "compress" as the second argument and the filename as the third argument.
    Ex--    a.exe compress text.txt 

    After the program executes, it will compress the original text file, and  
    create a new file named "serializedKey_"+filename in the same directory. 
    DO NOT DELETE, ALTER, OR RENAME this text file.

To decompress a text file:

    Run the executable along with the keyword "decompress" as the second argument and the filename as the third argument.
    Make sure you have the unaltered serializedKey file in the same directory
    Ex--    a.exe decompress text.txt

    After the program executes, it will decompress the text file into its original contents.
