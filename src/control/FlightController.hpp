#ifndef FLIGHT_CONTROLLER_HPP
#define FLIGHT_CONTROLLER_HPP

#include <ArduinoSTL.h>

#include "IController.hpp"

#include "command/IReceiver.hpp"
#include "sensing/imu/IIMU.hpp"
#include "sensing/voltage/ISensor.hpp"
#include "esc/ESCManager.hpp"

#include "PID.hpp"
#include "ExponentialFilter.hpp"

namespace control
{

class FlightController : public IController
{
public:

    FlightController();

    ~FlightController();

    void Init() override;

    void Control() override;


private:

    template <typename T>
    struct MotionData {
        T thrust;
        T yaw;
        T pitch;
        T roll;
    };

    template <typename T>
    struct EulerAngles {
        T yaw;
        T pitch;
        T roll;
    };

    template <typename T>
    struct Axes {
        T x;
        T y;
        T z;
    };

    struct IMUData {
        EulerAngles<float> angles;
        Axes<float> angular_rate;
    };

    IMUData imu_data2_;

    void InitFilter();
    void InitPID();
    void ReadReceiverData();
    void MapReceiverData();
    void ReadIMUData();
    void PIDCalculation();
    void CalculateMotorsSpeeds();
    void WriteMotorsSpeeds();

private:

    sensing::voltage::ISensor* voltage_sensor_;
    sensing::voltage::ISensor* current_sensor_;      /////////////////
    sensing::imu::IIMU* imu_;
    command::IReceiver* receiver_;

    MotionData<ExponentialFilter<float>* > filter_;

    ExponentialFilter<float>* yaw_filter_;
    ExponentialFilter<float>* current_filter_;       /////////////////
    ExponentialFilter<float>* voltage_filter_;       /////////////////
    uint32_t prev_time;                              /////////////////
    uint32_t seconds_ = 0;

    MotionData<int16_t> receiver_data_;
    MotionData<float> imu_data_;
    MotionData<float> pid_data_;
    MotionData<PID*> pid_controller_;

    esc::ESCManager* esc_manager_;
    std::vector<int16_t> motors_speeds_;

    bool init_;
};

}

#endif
