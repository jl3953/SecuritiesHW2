#ifndef ADDQUEUE_H
#define ADDQUEUE_H
#include <string>

using namespace std;

/**
 * Returns the counter to a unique id for files.
 */
string extractCounter();

/**
 * Adds a file to the protected directory. Returns 0 on success,
 * non-zero value otherwise.
 */
int addqueue(string directory, string filename);

#endif
