// DateTime.h ... interface to simply Date/Time ADT
// Written by John Shepherd, Feb 2019

#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <stdbool.h>

// External view of DateTime

typedef struct DateTimeRep *DateTime;

// create new timestamp object
DateTime newDateTime (void);

// free up memory associated with timestamp
void dropDateTime (DateTime);

// convert a string into a timestamp value
DateTime scanDateTime (char *);

// write DateTime to stdout
void showDateTime (DateTime);

// check whether one timestamp precedes another
bool DateTimeBefore (DateTime, DateTime);

// check whether one timestamp follows another
bool DateTimeAfter (DateTime, DateTime);

#endif
