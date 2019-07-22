#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"
#include "HuffmanTree.hpp"
#include "FileIO.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if (argc == 1){
        cout << "Command line arguments required";
        return 1;
    }

    string mode = argv[1], filename = argv[2], buffer;
    FileIO fio;
    HuffmanTree tree;

    if(mode == "compress"){
        
        fio.fileToString(filename, buffer); 
        buffer = tree.compress(buffer);
        cout << "Compressed: " << buffer << endl;
        fio.stringToFile(filename, buffer);
        buffer = tree.serializeTree();
        cout << "SerializedKey: " << buffer << endl;
        fio.stringToFile("serializedKey_"+filename, buffer);
    }

    else if (mode == "decompress"){
        string key;
        fio.fileToString(filename, buffer);
        fio.fileToString("serializedKey_"+filename, key);
        buffer = tree.decompress(buffer, key);
        cout << buffer;
        fio.stringToFile(filename, buffer);
    }

    else{
        cout << "Invalid arguments!";
        return 1;
    }
}