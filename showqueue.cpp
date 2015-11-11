#include "showqueue.h"
#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include "constants.h"
#include "showqueueObject.h"
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
    //lower privilege
    assert(seteuid(getuid()) == 0);

    map<filename, user> fileToOwner;
    assert(convertToMap(fileToOwner) == 0);

    cout << "File\t\tOwner\tTimestamp\t\tUnique ID" << endl;
    cout << "====\t\t=====\t=========\t\t=========" << endl;

    vector<ShowqueueObject> sq;
    assert(showqueue(sq, fileToOwner) == 0);

    //sort by time
    sort(sq.begin(), sq.end());

    for (int i = 0; i < sq.size(); i++)
        cout << sq[i] << endl;

    return 0;
}
