1.0
Library as downloaded 02Feb2012 22:55 UTC from http://srmonk.blogspot.com/2012/01/arduino-timer-library.html

1.1
Changed data types of variables and functions:
 o event types and indexes changed from int to int8_t.
 o periods and durations changed from lon to unsigned long.
 o update() and stop() functions typed as void, since they return nothing.
 o pin numbers and pin values changed from int to uint8_t, this agrees with digitalWrite().
 o added return values to Timer::pulse() and Timer::oscillate(uint8_t, unsigned long, uint8_t).
 o changed test in Event::update() to use subtraction to avoid rollover issues.
Updated keywords.txt file to include all functions.
