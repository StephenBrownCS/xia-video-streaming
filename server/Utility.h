
#ifndef UTILITY_H_
#define UTILITY_H_

/**
 * Utilty class for the CidDirectoryServer and the Content Serer
*/

#include <iostream>

extern const int LVL_INFO;
extern const int LVL_DEBUG;
extern bool VERBOSE;

/**
 * Prints the local host information (AD, HID, 4IP)
*/
    void printHostInformation();

/*
** write the message to stdout unless in quiet mode
*/
    void say(std::string msg, int priorityLevel = LVL_INFO);

/*
** always write the message to stdout
*/
    void warn(const char *fmt, ...);


/*
** write the message to stdout, and exit the app
*/
    void die(int ecode, const char *fmt, ...);

#endif
