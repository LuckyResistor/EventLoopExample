//
// Event Loop Example
// ---------------------------------------------------------------------------
// (c)2019 by Lucky Resistor. See LICENSE for details.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#include "Display.hpp"


namespace lr {
namespace Display {


/// The number of attached LEDs
///
const uint8_t cLedCount = 6;

/// The pin numbers for the LEDs.
///
const uint8_t cLeds[cLedCount] = {13, 12, 11, 10, 9, 6};


/// The current light LED.
///
uint8_t gCurrentLed = 0;


void initialize()
{
    for (const auto pinNumber : cLeds) {
        pinMode(pinNumber, OUTPUT);
    }
    setNumber(0);
}


void setNumber(uint8_t number)
{
    for (uint8_t i = 0; i < cLedCount; ++i) {
        digitalWrite(cLeds[i], ((i == number) ? HIGH : LOW));
    }
}


void increaseNumber()
{
    if ((gCurrentLed+1) < cLedCount) {
        gCurrentLed += 1;
        setNumber(gCurrentLed);
    }
}


void decreaseNumber()
{
    if (gCurrentLed > 0) {
        gCurrentLed -= 1;
        setNumber(gCurrentLed);
    }
}


}
}

