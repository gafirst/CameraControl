#include <iostream>
#include <SDL2/SDL.h>
#include "Joystick.h"

using namespace std;

Joystick::Joystick(int index)
    : _joystick(nullptr, _joy_deleter)
{
    auto joystickCount = NumberOfConnectJoysticks();

    if(joystickCount <= index || index < 0) {
        throw out_of_range{"Index " + to_string(index) + " is invalid with only " + to_string(joystickCount)
                           + " connected."};
    }

    _joystick.reset(SDL_JoystickOpen(index));

    if(_joystick == nullptr) {
        cerr << "Could not open joystick " + to_string(index) << endl;
    }

    auto num_axes = SDL_JoystickNumAxes(_joystick.get());

    if(num_axes < 0) {
        throw runtime_error{SDL_GetError()};
    }

    _deadzones.resize(static_cast<size_t>(num_axes));
}

bool Joystick::is_open() const {
    return SDL_JoystickGetAttached(_joystick.get());
}

void Joystick::update() {
    SDL_JoystickUpdate();
}

double Joystick::axis(int index) {
    auto value = ( static_cast<double>(SDL_JoystickGetAxis(_joystick.get(), index)) / axis_max );

    return (fabs(value) > _deadzones[index]) ? value : 0.0;
}

bool Joystick::button(int index) {
    return (SDL_JoystickGetButton(_joystick.get(), index) == 1);
}

void Joystick::set_deadzone(int index, double value) {
    _deadzones[index] = value;
}

void Joystick::set_all_deadzones(double value) {
    fill(_deadzones.begin(), _deadzones.end(), value);
}

int Joystick::num_axes() const {
    return SDL_JoystickNumAxes(_joystick.get());
}

int Joystick::num_buttons() const {
    return SDL_JoystickNumButtons(_joystick.get());
}

int Joystick::num_hats() const {
    return SDL_JoystickNumHats(_joystick.get());
}

Joystick::HatDirection Joystick::hat(int index) {
    return static_cast<HatDirection>(SDL_JoystickGetHat(_joystick.get(), index));
}

void Joystick::Init() {
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
}

int Joystick::NumberOfConnectJoysticks() {
    auto count = SDL_NumJoysticks();
    if(count < 0) {
        throw runtime_error{SDL_GetError()};
    }
    return count;
}


