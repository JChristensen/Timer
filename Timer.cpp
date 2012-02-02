/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */



/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 Code by Simon Monk
 http://www.simonmonk.org
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// For Arduino 1.0 and earlier
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Timer.h"


Timer::Timer()
{
}

int Timer::every(long period, void (*callback)(), int repeatCount)
{
	int i = findFreeEventIndex();
	if (i == -1) return -1;

	_events[i].eventType = EVENT_EVERY;
	_events[i].period = period;
	_events[i].repeatCount = repeatCount;
	_events[i].callback = callback;
	_events[i].lastEventTime = millis();
	_events[i].count = 0;
	return i;
}

int Timer::every(long period, void (*callback)())
{
	return every(period, callback, -1); // - means forever
}

int Timer::after(long period, void (*callback)())
{
	return every(period, callback, 1);
}

int Timer::oscillate(int pin, long period, int startingValue, int repeatCount)
{
	int i = findFreeEventIndex();
	if (i == -1) return -1;

	_events[i].eventType = EVENT_OSCILLATE;
	_events[i].pin = pin;
	_events[i].period = period;	
	_events[i].pinState = startingValue;
	digitalWrite(pin, startingValue);
	_events[i].repeatCount = repeatCount * 2; // full cycles not transitions
	_events[i].lastEventTime = millis();
	_events[i].count = 0;
	return i;
}

int Timer::oscillate(int pin, long period, int startingValue)
{
	oscillate(pin, period, startingValue, -1); // forever
}

int Timer::pulse(int pin, long period, int startingValue)
{
	oscillate(pin, period, startingValue, 1); // once
}

int Timer::stop(int id)
{
	_events[id].eventType = EVENT_NONE;
}

int Timer::update()
{
	for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		if (_events[i].eventType != EVENT_NONE)
		{
			_events[i].update();
		}
	}
}

int Timer::findFreeEventIndex()
{
	for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		if (_events[i].eventType == EVENT_NONE)
		{
			return i;
		}
	}
	return -1;
}

