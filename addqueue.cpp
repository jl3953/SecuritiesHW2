#include "addqueue.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <fstream>
#include <sstream>

int counter = 1;

using namespace std;

string extractCounter()
{
    ostringstream convert;
    convert << counter++;
    return convert.str();
}

int addqueue(string directory, string filename)
{
    //open file in new directory
    string name = directory + string("/file") + extractCounter();
    ofstream fullpath (name.c_str());

    //open original file for reading
    ifstream original (filename.c_str());
    string line;
    if (original.is_open())
    {   
        //copy header
        char userid[1000] = {'\0'};
        getlogin_r(userid, 1000);
        string header = string("header========\n")
            + string("userid: ") + string(userid)
            + string("\n==================\n");
        fullpath << header;
        //copy original file into protected directory
        while (getline(original, line))
            fullpath << line << "\n";
        original.close();
        fullpath.close();
        return 0;
    }
    else
    {
        cerr << "addqueue.c, addqueue(), unable to open "
            "original file: " << filename << endl;
        fullpath.close();
        return -1;
    }

    return 0;
}
int main(int argc, char** argv)
{
    string directory = "./test";
    cout << directory << endl;

    //TIME OF CHECK VS TIME OF ACCESS--PERMISSIONS MAY CHANGE
    int i;
    for (i = 1; i < argc; i++)
    {
        cout << argv[i] << endl;
        assert(addqueue(directory, argv[i]) == 0);
    }

    return 0;
}

