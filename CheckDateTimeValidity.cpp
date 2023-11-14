
void CheckPeriodValidity(int value, const string& period, int min_value, int max_value){
    if (value > max_value )
        throw domain_error(period + " is too small"s);
    if (value < min_value) {
        throw domain_error(period + " is too big"s);
    }
}

void CheckDateTimeValidity(const DateTime& day_time) {
    CheckPeriodValidity(day_time.year, "year", 1, 9999);
    CheckPeriodValidity(day_time.month, "month", 1, 12);

    const bool is_leap_year = (day_time.year % 4 == 0) && !(day_time.year % 100 == 0 && day_time.year % 400 != 0);
    const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    CheckPeriodValidity(day_time.day, "day", 1, month_lengths[day_time.month - 1]);
    CheckPeriodValidity(day_time.hour, "hour", 0, 23);
    CheckPeriodValidity(day_time.minute, "minute", 0, 59);
    CheckPeriodValidity(day_time.second, "second", 0, 59);
}