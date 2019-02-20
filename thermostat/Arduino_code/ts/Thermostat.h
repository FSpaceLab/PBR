//
// Created by B. Korzhak on 20.02.2019.
//

#ifndef Thermostat_h
#define Thermostat_h

#include "Arduino.h"


class Thermostat {
    public:
        Thermostat(int cooling_pin, int heating_pin, int temp_pin_1, int temp_pin_2,
                   int thermistor_R, float nominal_t, float coef_thermistor, int serial_R,
                   int B_coef);
        void cooling(float temperature);
        void heating(float temperature);
        float avg_temp();
        float get_temperature(int pin);

    private:
        void _fans_manage()
        unsigned long _fans_preview_millis;

        int _cooling_pin,  _heating_pin, _temp_pin_1, _temp_pin_2,_thermistor_R, _serial_R;

        float _nominal_t, _coef_thermistor;
};


#endif //Thermostat_h
