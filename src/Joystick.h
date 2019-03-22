#ifndef FIRST_CAMERACONTROL_JOYSTICK2_H
#define FIRST_CAMERACONTROL_JOYSTICK2_H

#include <SDL2/SDL_joystick.h>
#include <memory>
#include <vector>

struct SDLJoystickDeleter {
    inline void operator()(SDL_Joystick *joy) {
        if(SDL_JoystickGetAttached(joy)) {
            SDL_JoystickClose(joy);
        }
    }
};

class Joystick {
public:
    Joystick(int index);

    bool is_open() const;

    void update();

    double axis(int index);

    bool button(int index);

    void set_deadzone(int index, double value);

    void set_all_deadzones(double value);

    int num_axes() const;

    int num_buttons() const;

    int num_hats() const;

    enum class HatDirection : int {
        CENTERED = 0,
        UP = 1,
        RIGHT = 2,
        DOWN = 4,
        LEFT = 8
    };

    HatDirection hat(int index);

    static void Init();

    static int NumberOfConnectJoysticks();

private:
    std::unique_ptr<SDL_Joystick, SDLJoystickDeleter > _joystick;

    std::vector<double> _deadzones;

    SDLJoystickDeleter _joy_deleter;

    static constexpr int16_t axis_max = 32767;
    static constexpr int16_t axis_min = -32767;
};

inline Joystick::HatDirection operator & (const Joystick::HatDirection &a, const Joystick::HatDirection &b) {
    return static_cast<Joystick::HatDirection>(static_cast<int>(a) & static_cast<int>(b));
}

inline Joystick::HatDirection operator | (const Joystick::HatDirection &a, const Joystick::HatDirection &b) {
    return static_cast<Joystick::HatDirection>(static_cast<int>(a) | static_cast<int>(b));
}

#endif //FIRST_CAMERACONTROL_JOYSTICK2_H
