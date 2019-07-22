#ifndef FILE_IO_H
#define FILE_IO_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//struct for file handling
struct FileIO {
    void fileToString(string filename, string& str);
    void stringToFile(string filename, string str);
};

void FileIO::fileToString(string filename, string& str){
    ifstream in(filename);
    string line;
    str.clear();
    //unable to find file in directory
    if(!in){
        cout << "Unable to find file: " << filename << '\n';
        return;
    }
    //append each line of file into the buffer string 'str'
    while(!in.eof()){
        getline(in,line);
        str += line + '\n';
    }
    in.close(); //close file
    str.pop_back(); //remove unneccesary last newline
}

void FileIO::stringToFile(string filename,string str){
    ofstream out(filename); //open or create file
    out << str; //copy buffer string 'str' into the file
}

#endif
