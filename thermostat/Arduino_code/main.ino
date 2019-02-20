#include "DHT.h"

#define DHTTYPE DHT11

#define B 3950 // B-коэффициент
#define SERIAL_R 10000 // сопротивление последовательного резистора, 102 кОм
#define THERMISTOR_R 49900 // номинальное сопротивления термистора, 100 кОм
#define NOMINAL_T 18 // номинальная температура (при которой TR = 50 кОм)
#define COEF_THERMISTOR 269

// ALL PINS
#define THERMISTOR_PIN A0
#define DHTPIN 2
#define COOLER_COLD_PIN 4
#define COOLER_HEAT_PIN 3
#define PELTIER_PIN 6
#define HEAT_BED_PIN 7


DHT dht(DHTPIN, DHTTYPE);

unsigned long cooling_previous_millis = 0;
const long cooling_interval = 60000; 

int temp_i = 0;
const byte temp_data_size = 5;
float temp_data[temp_data_size];

void setup() {
    Serial.begin( 9600 );
    pinMode(THERMISTOR_PIN, INPUT);
    pinMode(DHTPIN, INPUT);
    
    pinMode(COOLER_COLD_PIN, OUTPUT);
    pinMode(COOLER_HEAT_PIN, OUTPUT);
    pinMode(PELTIER_PIN, OUTPUT);
    pinMode(HEAT_BED_PIN, OUTPUT);
}


float get_temp_from_thermistor() {
    int t = analogRead( THERMISTOR_PIN );
    // R (Om) from thermistor
    float tr = SERIAL_R / (1023.0 / t - 1);
    // Themperature calculation (in *C)
    return (1.0 / (log(tr / THERMISTOR_R) / B + 1.0 / (NOMINAL_T + 273.15))) - COEF_THERMISTOR;
}


float get_temp_from_dht() {
    return dht.readTemperature();
}


void cooling(float temp, float current_temp) {
    unsigned long current_millis = millis();

    if (current_millis - cooling_previous_millis >= cooling_interval) {
        cooling_previous_millis = current_millis;

        if (temp < get_temp_from_thermistor()) {
            digitalWrite(COOLER_COLD_PIN, HIGH);
            digitalWrite(COOLER_HEAT_PIN, HIGH);
            digitalWrite(PELTIER_PIN, HIGH);
        } else {
            digitalWrite(COOLER_COLD_PIN, LOW);
            digitalWrite(COOLER_HEAT_PIN, LOW);
            digitalWrite(PELTIER_PIN, LOW);
        }
    }
}


void heating(int temp) {
    if (temp > avg_temp()) {
        digitalWrite(HEAT_BED_PIN, HIGH);
    } else {
        digitalWrite(HEAT_BED_PIN, LOW);
    }
}


float avg_temp() {
    float avg = 0;

    if (temp_i == temp_data_size) temp_i = 0;

    temp_data[temp_i++] = get_temp_from_thermistor();
    for (int i = 0; i < temp_data_size; i++) avg += temp_data[i];
    
    return avg / temp_data_size;  
}


void loop() {
    float temp = avg_temp();
    cooling(10, temp);
//    Serial.print(get_temp_from_dht());
//    Serial.print(F("   "));
    
    Serial.println(temp);
  
    delay(100);
}
