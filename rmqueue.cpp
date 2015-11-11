#include "rmqueue.h"
#include "showqueue.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "constants.h"
#include <cassert>

using namespace std;

int main(int argc, char** argv)
{

    //lower privilege
    assert(seteuid(getuid()) == 0);

    //read in list of files and their owners
    map<filename, user> fileToOwner;
    assert(convertToMap(fileToOwner) == 0);

    //for every file, check whether this user is the one who
    //added it to the queue
    vector<filename> validFiles;
    int i;
    for (i = 1; i < argc; i++)
    {
        string fname = string(argv[i]);
        //check if filename is accurate / file exists
        if (!checkFileExistence(fileToOwner, fname))
        {
            cerr << fname << ":\tX\tFile does not exist in"
               " printspooler." << endl;
            continue;
        }

        //check if user has the right to remove file
        if (canRemove(fileToOwner, fname))
            validFiles.push_back(fname);
        else
            cerr << fname << "\tX\tUser " << getuid() << 
                " was not the user who added file." << endl;
    }

    assert(removeFiles(fileToOwner, validFiles) == 0);

    return 0;
}

