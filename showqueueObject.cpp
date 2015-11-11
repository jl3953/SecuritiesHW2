#include "showqueueObject.h"

ShowqueueObject::ShowqueueObject(string fname, string owner,
        int year, int month, int day, int hour, int min,
        int sec, string uniqueID)
: d_fname(fname)
, d_owner(owner)
, d_sec(sec)
, d_min(min)
, d_hour(hour)
, d_day(day)
, d_month(month)
, d_year(year)
, d_uniqueID(uniqueID) {}

ostream& operator<<(ostream& os, const ShowqueueObject& o)
{
    os << o.d_fname << " " << o.d_owner << " " <<
        o.d_year << "-" << o.d_month << "-" << o.d_day << "_" <<
        o.d_hour << ":" << o.d_min << ":" << o.d_sec << " " <<
        o.d_uniqueID;
    return os;
}

bool ShowqueueObject::operator<(const ShowqueueObject& o2) const
{
    if (d_year < o2.d_year)  return true;
    else if (d_year > o2.d_year) return false;
    else if (d_month < o2.d_month) return true;
    else if (d_month > o2.d_month) return false;
    else if (d_day < o2.d_day) return true;
    else if (d_day > o2.d_day) return false;
    else if (d_hour < o2.d_hour) return true;
    else if (d_hour > o2.d_hour) return false;
    else if (d_min < o2.d_min) return true;
    else if (d_min > o2.d_min) return false;
    else if (d_sec < o2.d_sec)
        return true;
    else if (d_sec > o2.d_sec) return false;
    else
        return false;
}
