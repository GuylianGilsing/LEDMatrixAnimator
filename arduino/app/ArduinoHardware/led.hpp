// Library by Guylian Gilsing
// Github: https://github.com/GuylianGilsing/ArduinoLibs

#ifndef ARDUINO_HARDWARE_FILE_LED
#define ARDUINO_HARDWARE_FILE_LED

namespace ArduinoHardware
{
    class LED
    {
    private:
        int pin = 0;

    public:
        LED(int a_pin)
        {
            this->pin = a_pin;
            pinMode(this->pin, OUTPUT);
        }

        void SetHigh()
        {
            digitalWrite(this->pin, HIGH);
        }

        void SetLow()
        {
            digitalWrite(this->pin, LOW);
        }
    };
}

#endif