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

#define DIRECTORY "/home/tinyvm/test"
#define USERFILENAME "/home/tinyvm/test/usersfiles"
#define COUNTERFILE "/home/tinyvm/test/counter"

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
    ofstream outfile(COUNTERFILE);
    outfile << incremented;
    outfile.close();

    //return incremented counter
    return incremented;
}

int userfiles(string filename)
{
    //write to file
    ofstream outfile (USERFILENAME, ios_base::app);
    outfile << getuid() << " " << filename << "\n";
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
        //open file in protected directory
        string fname = string("file") + extractCounter();
        string name = directory + string("/") + fname;
        
        //setting umask to protect file
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
            fullpath << line << "\n";
        fullpath.close();
        umask(prev_umask); //resetting umask to original mask

        original.close();
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

int checkPermissions(const char* filename)
{
    struct stat result;
    stat(filename, &result);

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

int main(int argc, char** argv)
{
    //TIME OF CHECK VS TIME OF ACCESS--PERMISSIONS MAY CHANGE
    int i;
    for (i = 1; i < argc; i++)
    {
        cout << argv[i] << endl;
        if (!checkPermissions(argv[i]))
        {
            cerr << getuid() << " has insufficient "
               "permissions on " << argv[i] <<
               ". Cannot add to queue." << endl;
        }
        else {
            if (addqueue(DIRECTORY, argv[i]) != 0)
            {
                cerr << "addqueue.c, main(), failed to add " << 
                    argv[i] <<"to queue." << endl;
            }
        }
    }

    return 0;
}

