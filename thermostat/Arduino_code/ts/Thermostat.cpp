//
// Created by navch on 20.02.2019.
//

#include "Arduino.h"
#include "Thermostat.h"

Thermostat::Thermostat(int cooling_pin, int heating_pin, int temp_pin_1, int temp_pin_2 = 0,
                       int thermistor_R=49900, float nominal_t=18, float coef_thermistor=269, int serial_R=10000,
                       int B_coef=3950) {
    pinMode(cooling_pin, OUTPUT);
    pinMode(heating_pin, OUTPUT);
    pinMode(temp_pin_1, INPUT);

    if (temp_pin_2) pinMode(temp_pin_2, INPUT);

    _cooling_pin = cooling_pin;
    _heating_pin = heating_pin;
    _temp_pin_1 = temp_pin_1;
    _temp_pin_2 = temp_pin_2;

    // Const for calculate temperature into thermistor
    _thermistor_R = thermistor_R;
    _nominal_t = nominal_t;
    _coef_thermistor = coef_thermistor;
    _serial_R = serial_R;
    _B_coef = B_coef;

}

void Thermostat::_fans_manage() {

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
