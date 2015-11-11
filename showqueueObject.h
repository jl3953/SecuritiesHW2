#ifndef SHOWQUEUEOBJECT_H
#define SHOWQUEUEOBJECT_H

#include <string>
#include <iostream>

using namespace std;

/**
  * Represents an object that groups together all attributes of 
  * a file that must be printed to the user.
  */
class ShowqueueObject{

    private:
        string d_fname, d_owner;
        int d_sec, d_min, d_hour, d_day, d_month, d_year;
        string d_uniqueID;

    public:
        ShowqueueObject(string fname, string owner,
                int sec, int min, int hour, int day, int month,
                int year, string uniqueID);

        //allows the file's name, owner, timestamp, and uniqueID
        //to be printed together
        friend ostream& operator<<(ostream& os, 
                const ShowqueueObject& sq);

        //allows files to be sorted by timestamp
        bool operator< (const ShowqueueObject& o2) const;
};

#endif
