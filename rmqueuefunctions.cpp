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
        assert(seteuid(PRIVILEGEDUSER) == 0);
        if (remove(fullname.c_str()) != 0)
        {
            cerr << fname << ": X Could not remove file from " 
                << DIRECTORY << endl;
            assert(seteuid(getuid()) == 0);
            continue;
        }
        assert(seteuid(getuid()) == 0);

        //remove file from map to prevent a duplicate name from
        //looking up the same filename and coming up positive
        fileToOwner.erase(fname);
        cout << fname << ": Y " << endl;

    }

    //remove file from usersfiles
    assert(seteuid(PRIVILEGEDUSER) == 0);
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
    assert(seteuid(getuid()) == 0);

    return 0;


}

