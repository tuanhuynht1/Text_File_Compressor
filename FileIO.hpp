#ifndef FILE_IO_H
#define FILE_IO_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct FileIO {
    void fileToString(string filename, string& str);
    void stringToFile(string filename, string str);
};

void FileIO::fileToString(string filename, string& str){
    ifstream in(filename);
    string line;
    str.clear();

    if(!in){
        cout << "Unable to find file: " << filename << '\n';
        return;
    }

    while(!in.eof()){
        getline(in,line);
        str += line + '\n';
    }
    in.close();
    str.pop_back();
}

void FileIO::stringToFile(string filename,string str){
    ofstream out(filename);
    out << str;
}

#endif