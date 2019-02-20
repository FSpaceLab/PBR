//
// Created by navch on 20.02.2019.
//

#include "Arduino.h"
#include "Thermostat.h"

Thermostat::Thermostat(int cooling_pin, int heating_pin, int fans_pin_1, int fans_pin_2) {
    pinMode(cooling_pin, OUTPUT);
    pinMode(heating_pin, OUTPUT);
    pinMode(fans_pin_1, OUTPUT);
    pinMode(fans_pin_2, OUTPUT);


    _cooling_pin = cooling_pin;
    _heating_pin = heating_pin;
    _fans_pin_1 = fans_pin_1;
    _fans_pin_2 = fans_pin_2;
}

void Thermostat::_fans_manage(bool on, int time_after_off) {

}

float Thermostat::get_temperature(int pin) {
    int t = analogRead(pin);

    // R (Om) into thermistor
    float tr = _serial_R / (1023.0 / t - 1);

    // Themperature calculation (in *C)
    return (1.0 / (log(tr / _thermistor_R) / _B_coef + 1.0 / (_nominal_t + 273.15))) - _coef_thermistor;
}

float Thermostat::avg_temp() {
    float avg = 0;

    if (temp_i == 5) temp_i = 0;

    temp_data[temp_i++] = this->get_temperature(_temp_pin_1);

    for (int i = 0; i < 5; i++) avg += temp_data[i];

    return avg / temp_data_size;
}

void Thermostat::cooling(float temperature) {
    if (temperature < this->get_temperature(_temp_pin_1))

}
