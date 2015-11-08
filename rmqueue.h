#ifndef RMQUEUE_H
#define RMQUEUE_H

#include "constants.h"
#include <map>
#include <vector>

/**
  * Checks whether a file actually exists in the directory.
  * Returns 1 on true, 0 on false.
  */
int checkFileExistence(const map<filename, user>&, 
        const filename&);

/**
  * Checks whether a user has permission to remove a file from
  * the directory.
  * Returns 1 on true, 0 on false.
  */
int canRemove(const map<filename, user>&, const filename&);

/**
  * Removes files from the printspooler.
  * Returns 0 on success, non-zero on failure.
  */
int removeFiles(map<filename, user>&, const vector<filename>&);

#endif
