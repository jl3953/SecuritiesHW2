#include "addqueue.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <fstream>
#include <sstream>

#define DIRECTORY "/home/tinyvm/test"
#define USERFILENAME "/home/tinyvm/test/test/usersfiles"

int counter = 1;

using namespace std;

string extractCounter()
{
    ostringstream convert;
    convert << counter++;
    return convert.str();
}

int userfiles(string filename)
{
    //get login
    char userid[1000] = {'\0'};
    if (getlogin_r(userid, 1000) != 0) return -1;
    cout << string(userid) << endl;
    
    //write to file
    std::ofstream outfile (USERFILENAME, ios_base::app);
    outfile << string(userid) << " " << filename << "\n";
    outfile.close();
    return 0;
}

int addqueue(string directory, string filename)
{
    //open original file for reading
    ifstream original (filename.c_str());
    string line;
    if (original.is_open())
    {   
        //open file in new directory
        string name = directory + string("/file") + extractCounter();
        ofstream fullpath (name.c_str());

        //keep track of which user is adding which file
        if (userfiles(name) != 0)
        {
            cerr << "addqueue.cpp, addqueue(), filename + user "
                "could not be added to " << USERFILENAME << endl;
            return -1;
        }

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
        return -1;
    }

    return 0;
}
int main(int argc, char** argv)
{
    //TIME OF CHECK VS TIME OF ACCESS--PERMISSIONS MAY CHANGE
    int i;
    for (i = 1; i < argc; i++)
    {
        cout << argv[i] << endl;
        assert(addqueue(DIRECTORY, argv[i]) == 0);
    }

    return 0;
}

