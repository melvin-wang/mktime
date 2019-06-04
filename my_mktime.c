
#define IS_LEAP_YEAR(year) ((((year) % 4 == 0 && (year) % 100 != 0) || (year) % 400 == 0) ? 1 : 0)

typedef struct
{
    u_int16_t year; /*年:2019,2020,2021,...*/
    u_int8_t mon;   /*月[1,12]*/
    u_int8_t day;   /*日[1,31]*/
    u_int8_t hour;  /*时[0,23]*/
    u_int8_t min;   /*分[0,59]*/
    u_int8_t sec;   /*秒[0,59]*/
    u_int16_t ms;   /*毫秒[0,999]*/
} TIME;

typedef struct
{
    int32_t second;      /*从1970到现在的秒数*/
    int16_t millisecond; /*毫秒*/
} TIME_STAMP;

void _mktime(TIME *ptm, TIME_STAMP *pts)
{
    static int16_t mon_yday[2][12] = {
        {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
        {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335},
    };

    int32_t epoch_sec;
    int32_t y;

    epoch_sec = (ptm->year - 1970) * 365 * 24 * 3600 +
                (mon_yday[IS_LEAP_YEAR(ptm->year)][ptm->mon - 1] + (ptm->day - 1)) * 24 * 3600 + ptm->hour * 3600 +
                ptm->min * 60 + ptm->sec;

    for (y = 1970; y < ptm->year; y++)
    {
        if (IS_LEAP_YEAR(y))
        {
            epoch_sec += 24 * 3600;
        }
    }

    pts->second = epoch_sec;
    pts->millisecond = ptm->ms;
}
