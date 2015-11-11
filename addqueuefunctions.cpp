#include "addqueue.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "constants.h"

using namespace std;

string extractCounter()
{
    //read in current counter from counter file
    ifstream counter(COUNTERFILE);
    string s_number;
    getline(counter, s_number);
    counter.close();
    int number = atoi(s_number.c_str());

    //convert incremented counter to string
    ostringstream convert;
    convert << ++number;
    string incremented = convert.str();

    //overwrite old counter with new one
    assert(seteuid(PRIVILEGEDUSER) == 0);
    ofstream outfile(COUNTERFILE);
    outfile << incremented;
    outfile.close();
    assert(seteuid(getuid()) == 0);

    //return incremented counter
    return incremented;
}

int userfiles(string originalFname)
{
    //write to file
    ofstream outfile (USERFILENAME, ios_base::app);
    outfile << getuid() << " " << originalFname << "\n";
    outfile.close();

    return 0;
}

int addqueue(string directory, string originalFname)
{
    //open original file for reading
    ifstream original (originalFname.c_str());
    string line;
    if (original.is_open())
    {   
        //open file in protected directory
        string fname = string("fileid") + extractCounter();
        string name = string(DIRECTORY) + string("/") + fname;
        
        //setting umask to protect file--raising privilege
        //to owner of directory in order to write
        assert(seteuid(PRIVILEGEDUSER) == 0);
        mode_t prev_umask = umask(077);
        ofstream fullpath (name.c_str());

        //keep track of which user is adding which file
        if (userfiles(fname) != 0)
        {
            cerr << "addqueue.cpp, addqueue(), filename + user "
                "could not be added to " << USERFILENAME << endl;
            return -1;
        }

        //copy original file into protected directory
        while (getline(original, line))
        {
            fullpath << line << "\n";
        }
        fullpath.close();

        //lowering privilege again to original user and
        //resetting original mask
        seteuid(getuid());
        umask(prev_umask); 

        original.close();

        //printing success message
        cout << originalFname << ":\tY\t" << fname << endl;
        return 0;
    }
    else
    {
        cerr << originalFname <<":\tX\tunable to open file." << 
            endl;
        return -1;
    }

    return 0;
}

int checkPermissions(const char* originalFname)
{
    struct stat result;
    stat(originalFname, &result);

    //if owner, check owner bits for read permissions
    if ( getuid() == result.st_uid)
        return result.st_mode & S_IRUSR;
    //if group, check group bits
    else if ( getgid() == result.st_gid)
        return result.st_mode & S_IRGRP;
    //else, check other bits
    else
        return result.st_mode & S_IROTH;
    
}

