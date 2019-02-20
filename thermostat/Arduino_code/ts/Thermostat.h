//
// Created by B. Korzhak on 20.02.2019.
//

#ifndef Thermostat_h
#define Thermostat_h

#include "Arduino.h"


class Thermostat {
    public:
        Thermostat(int cooling_pin, int heating_pin, int fans_pin_1, fans_pin_2);
        void cooling(float temperature);
        void heating(float temperature);

    private:
        void _fans_manage()

        unsigned long _fans_preview_millis;

        int _cooling_pin,  _heating_pin, _fans_pin_1, _fans_pin_2;
};


#endif //Thermostat_h
