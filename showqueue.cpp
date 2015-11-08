#include "showqueue.h"
#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <fstream>
#include <sstream>

#define USERFILENAME "/home/tinyvm/test/usersfiles"

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


int main()
{
    map<filename, user> fileToOwner;
    assert(convertToMap(fileToOwner) == 0);

    //test
    /*map<string, string>::iterator it;
    for (it = fileToOwner.begin(); it != fileToOwner.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }*/

    return 0;
}
