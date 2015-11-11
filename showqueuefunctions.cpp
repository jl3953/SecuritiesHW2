#include "showqueue.h"
#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include "constants.h"
#include "showqueueObject.h"
#include <vector>

using namespace std;
typedef string filename;
typedef string user;

int convertToMap(map<filename, user>& fileToOwner)
{
    //open file
    ifstream input(USERFILENAME);
    if (input.is_open())
    {
        //read file line by line
        string line;
        while (getline(input, line))
        {
            //parse each line for owner and filename
            istringstream ss(line);
            //char owner[100] = {'\0'};
            string owner, fname;
            getline(ss, owner, ' ');
            getline(ss, fname, ' ');

            //insert owner and filename into map
            fileToOwner.insert(pair<filename, user> (fname, owner));
        }
    }
    else
    {
        cerr << "showqueue.c, convertToMap(), could not "
            "open users to files: " << USERFILENAME << endl;
        input.close();
        return -1;
    }
    
    input.close();
    return 0;
}

int showqueue(vector<ShowqueueObject>& sq,
        const map<string, string>& fileToOwner)
{
    DIR *dir;
    if ((dir = opendir (DIRECTORY))) 
    {
        struct dirent *ent;
        struct stat file;
        struct tm clock;
        while ((ent = readdir (dir))) 
        {
            //get filename and owner
            string fname = string(ent->d_name);
            if (fileToOwner.find(fname) == fileToOwner.end())
            {
                //other random files in the directory not added
                //by one of the users
                continue;
            }
            string owner = fileToOwner.find(fname)->second;

            //get timestamp
            string fullname = string(DIRECTORY) + "/" + fname;
            assert(stat(fullname.c_str(), &file) == 0);
            localtime_r(&(file.st_mtime), &clock);
            int sec = clock.tm_sec;
            int min = clock.tm_min;
            int hour = clock.tm_hour;
            int day = clock.tm_mday;
            int month = clock.tm_mon + 1;
            int year = clock.tm_year + 1900;

            //unique id
            string uniqueID = fname;

            ShowqueueObject o(fname, owner, year, month, day,
                    hour, min, sec, uniqueID);
            sq.push_back(o);
        }
    } 
    else {
        cerr << "showqueue.cpp, showqueue(), could not open "
            "directory: " << DIRECTORY << endl;
        return -1;
    }
    
    closedir (dir);
    return 0;
}


