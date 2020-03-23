// DateTime.c ... implementation of a simple Date/Time ADT
// Written by John Shepherd, Feb 2019

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <time.h>

#include "DateTime.h"

// data structures to represent DateTime (timestamp) values

typedef struct DateTimeRep {
	time_t timestamp;
} DateTimeRep;

// create new timestamp object
// only needed if you want to build the timestamp yourself
// otherwise use scanDate() which creates/fills a DateTime object
DateTime newDateTime ()
{
	DateTimeRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate DateTime");

	struct tm epoch;
	strptime ("1970-01-01 00:00:00", "%F %T", &epoch);
	new->timestamp = mktime (&epoch);
	return new;
}

// free up memory associated with timestamp
void dropDateTime (DateTime dt)
{
	assert (dt != NULL);
	free (dt);
}

// convert a string into a timestamp value
// formats seen in email:
//   Wed, 30 Nov 2011 23:27:34  == "%a, %e %b %Y %T"
//   27 April 2011 9:48:28 AM   == "%e %B %Y %r"
DateTime scanDateTime (char *str)
{
	struct tm time;
	char *result;

	// clear time struct
	memset (&time, 0, sizeof (time));

	// try parsing with day-of-week
	result = strptime (str, "%a, %e %b %Y %T", &time);

	// if fails, try parsing without day-of-week
	if (result == NULL) result = strptime (str, "%e %B %Y %r", &time);

	// if fails again, try ISO date format
	if (result == NULL) result = strptime (str, "%F", &time);

	// if fails again, give up
	if (result == NULL)
		return NULL;

	DateTime new = newDateTime ();
	new->timestamp = mktime (&time);
	return new;
}

// print formatted DateTime value to stdout
void showDateTime (DateTime dt)
{
	assert (dt != NULL);
	printf ("%s", ctime (&(dt->timestamp)));
}

// check whether one timestamp precedes another
bool DateTimeBefore (DateTime dt1, DateTime dt2)
{
	assert (dt1 != NULL);
	assert (dt2 != NULL);
	double diff = difftime (dt1->timestamp, dt2->timestamp);
	return (diff < 0.0) ? 1 : 0;
}

// check whether one timestamp follows another
bool DateTimeAfter (DateTime dt1, DateTime dt2)
{
	assert (dt1 != NULL);
	assert (dt2 != NULL);
	double diff = difftime (dt1->timestamp, dt2->timestamp);
	return (diff > 0.0) ? 1 : 0;
}
