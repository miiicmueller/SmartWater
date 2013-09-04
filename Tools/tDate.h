#ifndef T_DATE_H
#define T_DATE_H

#include <string>
#include <assert.h>
#include <../Def/def.h>

class tDate
    {
public:
    UInt16 year;
    UInt8 month;
    UInt8 day;
    UInt8 dayOfWeek;
    UInt8 hour;
    UInt8 minute;
    UInt8 second;

    tDate();

    };
#endif
