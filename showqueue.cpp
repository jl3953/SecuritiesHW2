#include "showqueue.h"
#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include "constants.h"

using namespace std;
int main()
{
    map<filename, user> fileToOwner;
    assert(convertToMap(fileToOwner) == 0);

    cout << "File\tOwner\tTimestamp\tUnique ID" << endl;
    cout << "====\t=====\t=========\t=========" << endl;
    assert(showqueue(fileToOwner) == 0);

    return 0;
}
