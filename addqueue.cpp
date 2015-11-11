#include "addqueue.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "constants.h"

using namespace std;

int main(int argc, char** argv)
{
    //TIME OF CHECK VS TIME OF ACCESS--PERMISSIONS MAY CHANGE

    //lower privilege to uid before running program.
    seteuid(getuid());

    int i;
    for (i = 1; i < argc; i++)
    {
        if (!checkPermissions(argv[i]))
        {
            cerr << argv[i] << ": X user " << getuid() << 
                " has insufficient permissions on file"
               ". Cannot add to queue." << endl;
        }
        else {
            addqueue(DIRECTORY, argv[i]);
        }
    }

    return 0;
}

