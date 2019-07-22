#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"
#include "HuffmanTree.hpp"
#include "FileIO.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    //requires additional command line arguments
    if (argc == 1){
        cout << "Command line arguments required";
        return 1;
    }
    
    string mode = argv[1], filename = argv[2], buffer;
    FileIO fio;
    HuffmanTree tree;

    if(mode == "compress"){
        fio.fileToString(filename, buffer);   //fill buffer with file contents
        buffer = tree.compress(buffer);   //compress buffer using Huffman Tree
        cout << "Compressed: " << buffer << endl;   //log to conslole
        fio.stringToFile(filename, buffer); //rewrite origninal file with compressed code
        buffer = tree.serializeTree();  //create a serialized key to decompress later
        cout << "SerializedKey: " << buffer << endl;    //log to console
        fio.stringToFile("serializedKey_"+filename, buffer);    //create a new file with the serialized key
    }

    else if (mode == "decompress"){
        string key;
        fio.fileToString(filename, buffer); //fill buffer with compressed code
        fio.fileToString("serializedKey_"+filename, key);   //fill key using the serialized key file
        buffer = tree.decompress(buffer, key);  //decode using the encoded string and the key
        cout << buffer; //log to console
        fio.stringToFile(filename, buffer); //rewrite to file after decoding the original text
    }
    //invalid arguments
    else{
        cout << "Invalid arguments!";
        return 1;
    }
}
