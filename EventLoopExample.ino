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


#include "Buttons.hpp"
#include "Display.hpp"

#include "src/event/Loop.hpp"


using namespace lr;


/// The event loop.
///
event::BasicLoop<event::StaticStorage<16>> gEventLoop;


/// Process all button presses.
///
void processButtonPresses()
{
    switch (Buttons::getNextButtonPress()) {
    case Buttons::Left:
        Display::decreaseNumber();
        break;
    case Buttons::Right:
        Display::increaseNumber();
        break;
    default:
        break;
    }
}


void setup()
{
    // Initialise all modules.
    Buttons::initialize();
    Display::initialize();
    
    // Register the button press processor.
    event::mainLoop().addPollEvent(&processButtonPresses);
}


void loop()
{
    gEventLoop.loopOnce();
}
