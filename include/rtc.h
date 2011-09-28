#pragma once

typedef struct {
  uint16_t year;
  uint16_t month;
  uint16_t day;
  uint16_t hour;
  uint16_t minute;
  uint16_t second;
  uint32_t microsecond;
} rtc_datetime;


typedef struct {
  uint64_t tick;
} rtc_tick;

void rtc_convert_time_to_datetime(rtc_datetime *out, time_t in);

void rtc_convert_utc_to_localtime(const rtc_tick *in, rtc_tick *out);

void rtc_convert_tick_to_datetime(rtc_datetime *out, const rtc_tick *in);

void rtc_convert_datetime_to_tick(const rtc_datetime *in, rtc_tick *out);

