#ifndef FIRST_CAMERACONTROL_CAMERA_H
#define FIRST_CAMERACONTROL_CAMERA_H

#include <cstdint>
#include <vector>
#include <boost/asio.hpp>

class Camera {
public:
    Camera(std::string name, std::string ip_address, uint8_t default_preset, boost::asio::io_service &io_service);

    ~Camera();

    void save_preset(uint8_t number);

    void recall_preset(uint8_t number);

    inline uint8_t default_preset() const {
        return _default_preset;
    }

    enum class RotateType {
        STOP,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        UP_LEFT,
        UP_RIGHT,
        DOWN_LEFT,
        DOWN_RIGHT
    };

    void rotate(double pan = 0, double tilt = 0);

    void rotate(Camera::RotateType type, double speed_factor = 0.5);

    enum class ZoomType {
        STOP,
        TELE,
        WIDE
    };

    void zoom(double speed = 0);

    void zoom(ZoomType type);

    void stop();

    void reconnect();

    inline std::string name() const {
        return _name;
    }

    inline std::string address() const {
	return _address;
    }

    static inline uint8_t pan_max() {
        return 24;
    }

    static inline uint8_t tilt_max() {
        return 20;
    }

    static inline uint8_t zoom_max() {
        return 7;
    }

private:

    std::string _name;
    std::string _address;

    uint8_t _default_preset;

    boost::asio::io_service& _io_service;
    boost::asio::ip::tcp::socket _socket;

    void send_command(std::vector<uint8_t> command);

    void tcp_connect_with_timeout(const std::string& host, const std::string& service,
                                  boost::posix_time::time_duration timeout);

};

inline Camera::RotateType operator & (const Camera::RotateType  &a, const Camera::RotateType  &b) {
    return static_cast<Camera::RotateType >(static_cast<int>(a) & static_cast<int>(b));
}

inline Camera::RotateType  operator | (const Camera::RotateType  &a, const Camera::RotateType  &b) {
    return static_cast<Camera::RotateType >(static_cast<int>(a) | static_cast<int>(b));
}

#endif //FIRST_CAMERACONTROL_CAMERA_H
