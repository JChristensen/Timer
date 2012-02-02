
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

#ifndef Timer_h
#define Timer_h

#include <inttypes.h>
#include "Event.h"

#define MAX_NUMBER_OF_EVENTS 10


class Timer
{

public:
  Timer(); 

  int every(long period, void (*callback)()); 
  int every(long period, void (*callback)(), int repeatCount); 
  int after(long duration, void (*callback)());
  int oscillate(int pin, long period, int startingValue);
  int oscillate(int pin, long period, int startingValue, int repeatCount);
  int pulse(int pin, long period, int startingValue);
  int stop(int id);
  int update(); 
	
  
protected:
  Event _events[MAX_NUMBER_OF_EVENTS];
  int findFreeEventIndex();

};

#endif
