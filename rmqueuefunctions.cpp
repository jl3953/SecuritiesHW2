#include "rmqueue.h"
#include "showqueue.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "constants.h"
#include <cassert>
#include <sstream>
#include <stdio.h>
#include <fstream>

using namespace std;

int checkFileExistence(const map<filename, user>& fileToOwner,
        const string& fname)
{
    //check if this filename exists as a key in the map
    cout << "rmqueuefunctions.cpp, checkFileExistence, filename: "
        << fname << endl;
    return fileToOwner.count(fname) > 0;
}

int canRemove(const map<filename, user>& fileToOwner, 
        const string& fname)
{
    ostringstream convert;
    convert << getuid();
    string program_user = convert.str();

    string owner = fileToOwner.find(fname)->second;

    return (program_user.compare(owner) == 0);
}

int removeFiles(map<filename, user>& fileToOwner, 
        const vector<filename>& validFiles)
{
    for (int i = 0; i < validFiles.size(); i++)
    {
        string fname = validFiles[i];
        string fullname = string(DIRECTORY) + string("/") + fname;

        //remove file from directory
        if (remove(fullname.c_str()) != 0)
        {
            cerr << "rmqueue.cpp, removeFiles(), could not remove"
                " file " << fname << " from " << DIRECTORY
                << endl;
            continue;
        }

        //remove file from map to prevent a duplicate name from
        //looking up the same filename and coming up positive
        fileToOwner.erase(fname);

        cout << "test, should be 0. result: " << fileToOwner.count(fname) << endl;
    }

    //remove file from usersfiles
    ofstream output(USERFILENAME);
    if (!output.is_open())
    {
        cerr << "rmqueue.cpp, removeFiles(), could not open file "
            << USERFILENAME << " for writing." << endl;
        return -1;
    }
    map<string,string>::iterator it;
    for(it = fileToOwner.begin(); it != fileToOwner.end(); it++)
    {
        output << it->second << " " << it->first << endl;
    }
    output.close();

    return 0;


}

