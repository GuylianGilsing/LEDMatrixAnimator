// Library by Guylian Gilsing
// Github: https://github.com/GuylianGilsing/ArduinoLibs

#ifndef ARDUINO_HARDWARE_FILE_BUTTON
#define ARDUINO_HARDWARE_FILE_BUTTON

namespace ArduinoHardware
{
    // Using an enum class makes it more clear to which enum you are referring
    enum class ButtonType
    {
        PULL_UP = 0,
        PULL_DOWN = 1,
        RAW_READING = 2
    };

    class Button
    {
    private:
        unsigned int pin = 0;
        ButtonType buttonState = ButtonType::RAW_READING;

        bool buttonClickRegistered = false;

        // Debouncing (Removing voltage interference)
        const int debounceTime = 50;
        int lastTimeStateChanged = 0;
        int lastBtnState = 0;

    public:
        // Normal constructor
        Button(int a_pin, ButtonType a_buttonType = ButtonType::RAW_READING)
        {
            this->pin = a_pin;
            this->buttonState = a_buttonType;

            pinMode(this->pin, INPUT);   
        }

        bool IsPressed()
        {
            bool pressed = false;

            int buttonReading = digitalRead(this->pin);

            if(buttonReading != this->lastBtnState)
                this->lastTimeStateChanged = millis();

            if((millis() - this->lastTimeStateChanged) >= this->debounceTime)
            {
                switch(this->buttonState)
                {
                    // A pullup button returns true once when a high voltage has been detected
                    case ButtonType::PULL_UP:
                        if(buttonReading == HIGH && this->buttonClickRegistered == false)
                        {
                            pressed = true;
                            this->buttonClickRegistered = true;
                        }

                        if(this->buttonClickRegistered && buttonReading == LOW)
                            this->buttonClickRegistered = false;
                    break;

                    // A pulldown button returns true once when a high voltage has been let go off
                    case ButtonType::PULL_DOWN:
                        if(!this->buttonClickRegistered && buttonReading == HIGH)
                            this->buttonClickRegistered = true;

                        if(this->buttonClickRegistered && buttonReading == LOW)
                        {
                            pressed = true;
                            this->buttonClickRegistered = true;
                        }
                    break;

                    // a RAW_READING button returns true when a high voltage is detected
                    default:
                        if(buttonReading == HIGH)
                            pressed = true;
                    break;
                }
            }

            this->lastBtnState = buttonReading;

            return pressed;
        }
    };
}

#endif