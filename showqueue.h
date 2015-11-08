#ifndef SHOWQUEUE_H
#define SHOWQUEUE_H

#include <map>
#include <string>
using namespace std;

/**
  * Converts a file listing users and their filenames to a map
  * mapping the filenames to their users.
  * Returns 0 on success, non-zero otherwise.
  */
int convertToMap(map<string, string>&);

/**
  * Prints out all files in a directory.
  * Returns 0 on success, non-zero otherwise.
  */
int showqueue(const map<string, string>&);

#endif
