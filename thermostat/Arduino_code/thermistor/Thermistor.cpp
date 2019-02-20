//
// Created by navch on 20.02.2019.
//

#include "Thermistor.h"

#define B 3950 // B-коэффициент
#define SERIAL_R 10000 // сопротивление последовательного резистора, 102 кОм
#define THERMISTOR_R 49900 // номинальное сопротивления термистора, 100 кОм
#define NOMINAL_T 18 // номинальная температура (при которой TR = 50 кОм)
#define COEF_THERMISTOR 269

float get_t(uint_8 pin) {

    int t = analogRead(pin);

    // R (Om) from thermistor
    float tr = SERIAL_R / (1023.0 / t - 1);

    // Themperature calculation (in *C)
    return (1.0 / (log(tr / THERMISTOR_R) / B + 1.0 / (NOMINAL_T + 273.15))) - COEF_THERMISTOR;
}
