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


#include "src/event/Loop.hpp"
#include "src/RingBuffer.hpp"


namespace lr {
namespace Buttons {


/// The number of attached buttons.
///
const uint8_t cButtonCount = 2;

/// The pin numbers where the buttons are attached.
///
const uint8_t cButtonPins[cButtonCount] = {5, 21};

/// Initial delay.
///
const uint8_t cRepeatDelay = 12;

/// Repeat speed.
///
const uint8_t cRepeatSpeed = 5;


/// The button state.
///
struct State {
    bool last;
    uint8_t repeatCount;
};

/// The button states.
///
State gState[cButtonCount];

/// A buffer to store the button presses.
///
RingBuffer<uint8_t, Button> gButtonBuffer(16);


/// The event call to poll the buttons.
///
void eventCall()
{
    for (uint8_t i = 0; i < cButtonCount; ++i) {
        const bool newState = digitalRead(cButtonPins[i]);
        const auto button = static_cast<Button>(i);
        auto &state = gState[i];
        if (state.last != newState) {
            state.last = newState;
            if (!newState) {
                gButtonBuffer.write(&button, 1);
            } else {
                state.repeatCount = cRepeatDelay;
            }
        }
        if (!state.last) {
            state.repeatCount -= 1;
            if (state.repeatCount == 0) {
                gButtonBuffer.write(&button, 1);                
                state.repeatCount = cRepeatSpeed;
            }
        }
    }
}


void initialize()
{
    for (uint8_t i = 0; i < cButtonCount; ++i) {
        gState[i] = State {true, cRepeatDelay};
        pinMode(cButtonPins[i], INPUT_PULLUP);
    }
    event::mainLoop().addRepeatedEvent(&eventCall, 100_ms);
}


Button getNextButtonPress()
{
    Button button;
    if (gButtonBuffer.read(&button, 1) == 0) {
        return None;
    }
    return button;
}


}
}

