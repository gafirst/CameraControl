#include <iostream>
#include <bitset>
#include <iomanip>
#include "Controller.h"

using namespace std;

Controller::Controller(std::shared_ptr<Joystick> joystick, std::shared_ptr<Camera> camera)
    : _joystick(joystick),
      _camera(camera)
{
}

void Controller::update() {
    if(_joystick != nullptr && _camera != nullptr) {
        _joystick->update();

        attempt_axis_control();

        button_control();

        set_prev_buttons();
    }
}

void Controller::change_joystick(std::shared_ptr<Joystick> joystick) {
    _joystick = joystick;
}

void Controller::chage_camera(std::shared_ptr<Camera> camera) {
    _camera = camera;
}

void Controller::attempt_axis_control() {
    // Emergency stop button
    if(_joystick->button(0)){
        if (!_prev_button[0]) {
            _camera->stop();
            cout << setw(12) << _camera->name() << "\tStop\n";
            _prev_pan = 0;
            _prev_tilt = 0;
            _prev_speed = 0;
        }
    } else {
        axis_control();
    }
}

void Controller::axis_control() {
    auto pan = _joystick->axis(0);
    auto tilt = _joystick->axis(1);

    auto speed = ((-1.0 * _joystick->axis(3)) + 1.0) / 2.0;

    if(pan != _prev_pan || tilt != _prev_tilt || speed != _prev_speed) {
        Camera::RotateType type;

        if(pan < 0) {
            if(tilt < 0) {
                type = Camera::RotateType::DOWN_LEFT;
            } else if(tilt > 0) {
                type = Camera::RotateType::UP_LEFT;
            } else {
                type = Camera::RotateType::LEFT;
            }
        } else if(pan > 0) {
            if(tilt < 0) {
                type = Camera::RotateType::DOWN_RIGHT;
            } else if(tilt > 0) {
                type = Camera::RotateType::UP_RIGHT;
            } else {
                type = Camera::RotateType::RIGHT;
            }
        } else {
            if(tilt < 0) {
                type = Camera::RotateType::DOWN;
            } else if(tilt > 0) {
                type = Camera::RotateType::UP;
            } else {
                type = Camera::RotateType::STOP;
            }
        }

        _camera->rotate(type, speed);
    }

    _prev_pan = pan;
    _prev_tilt = tilt;
    _prev_speed = speed;

    auto hat_state =_joystick->hat(0);

    if(hat_state != _prev_hat) {
        if (static_cast<int>(hat_state & Joystick::HatDirection::UP) > 0) {
            _camera->zoom(Camera::ZoomType::TELE);
        } else if (static_cast<int>(hat_state & Joystick::HatDirection::DOWN) > 0) {
            _camera->zoom(Camera::ZoomType::WIDE);
        } else {
            _camera->zoom(Camera::ZoomType::STOP);
        }
    }

    _prev_hat = hat_state;
}

std::shared_ptr<Joystick> Controller::joystick() const {
    return _joystick;
}

std::shared_ptr<Camera> Controller::camera() const {
    return _camera;
}

void Controller::button_control() {
    if (_joystick->button(1) && !_prev_button[1]) {
        cout << "*** reinit camera: " << _camera->name() << "\n";
        _camera->reconnect();
        cout << "*** reinit camera: " << _camera->name() << " complete!\n";
	return;
    }

    // Go to a preset (button pressed down)
    if (_joystick->button(3)) {
        if(_joystick->button(2) && !_prev_button[2]) {
            _camera->save_preset(0);
            cout << setw(12) << _camera->name() << "\tSaving preset 0\n";
        } else if(_joystick->button(4) && !_prev_button[4]) {
            _camera->save_preset(2);
            cout << setw(12) << _camera->name() << "\tSaving preset 2\n";
        } else if(_joystick->button(5) && !_prev_button[5]) {
            _camera->save_preset(3);
            cout << setw(12) << _camera->name() << "\tSaving preset 3\n";
        } else if(_joystick->button(6) && !_prev_button[6]){
            _camera->save_preset(4);
            cout << setw(12) << _camera->name() << "\tSaving preset 4\n";
        } else if(_joystick->button(7) && !_prev_button[7]){
            _camera->save_preset(5);
            cout << setw(12) << _camera->name() << "\tSaving preset 5\n";
        } else if(_joystick->button(8) && !_prev_button[8]){
            _camera->save_preset(6);
            cout << setw(12) << _camera->name() << "\tSaving preset 6\n";
        } else if(_joystick->button(9) && !_prev_button[9]){
            _camera->save_preset(7);
            cout << setw(12) << _camera->name() << "\tSaving preset 7\n";
        } else if(_joystick->button(10) && !_prev_button[10]){
            _camera->save_preset(8);
            cout << setw(12) << _camera->name() << "\tSaving preset 8\n";
        } else if(_joystick->button(11) && !_prev_button[11]){
            _camera->save_preset(9);
            cout << setw(12) << _camera->name() << "\tSaving preset 9\n";
        }
    } else {
        if(_joystick->button(2) && !_prev_button[2]) {
            _camera->recall_preset(0);
            cout << setw(12) << _camera->name() << "\tRecalling preset 0\n";
        } else if(_joystick->button(4) && !_prev_button[4]) {
            _camera->recall_preset(2);
            cout << setw(12) << _camera->name() << "\tRecalling preset 2\n";
        } else if(_joystick->button(5) && !_prev_button[5]) {
            _camera->recall_preset(3);
            cout << setw(12) << _camera->name() << "\tRecalling preset 3\n";
        } else if(_joystick->button(6) && !_prev_button[6]){
            _camera->recall_preset(4);
            cout << setw(12) << _camera->name() << "\tRecalling preset 4\n";
        } else if(_joystick->button(7) && !_prev_button[7]){
            _camera->recall_preset(5);
            cout << setw(12) << _camera->name() << "\tRecalling preset 5\n";
        } else if(_joystick->button(8) && !_prev_button[8]){
            _camera->recall_preset(6);
            cout << setw(12) << _camera->name() << "\tRecalling preset 6\n";
        } else if(_joystick->button(9) && !_prev_button[9]){
            _camera->recall_preset(7);
            cout << setw(12) << _camera->name() << "\tRecalling preset 7\n";
        } else if(_joystick->button(10) && !_prev_button[10]){
            _camera->recall_preset(8);
            cout << setw(12) << _camera->name() << "\tRecalling preset 8\n";
        } else if(_joystick->button(11) && !_prev_button[11]){
            _camera->recall_preset(9);
            cout << setw(12) << _camera->name() << "\tRecalling preset 9\n";
        }
    }
}

void Controller::set_prev_buttons() {
    for(size_t i = 0; i < _prev_button.size(); ++i) {
        _prev_button[i] = _joystick->button(i);
    }
}
