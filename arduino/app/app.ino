#include "Arduino.h"

// Libs
#include "ArduinoHardware/led.hpp"

// Namespaces
namespace ah = ArduinoHardware;

// Function prototypes
void SerialPortHandleData();
void SerialPortHandleCommands(String a_command);
void SerialPortCommandOn();
void SerialPortCommandOff();

// Globals
ah::LED blueLed = ah::LED(2);

// Sketch
void setup()
{
    Serial.begin(19200);
    Serial.println("Serial communication is working");
}

void loop()
{
    SerialPortHandleData();
}

/*

    --- Serial port data handling ---

*/

void SerialPortHandleData()
{
    if(Serial.available() > 0)
    {
        // Read the incoming data
        String data = Serial.readString();

        // Handle potential commands
        SerialPortHandleCommands(data);
    }
}

void SerialPortHandleCommands(String a_command)
{
    if(a_command == "on")
    {
        SerialPortCommandOn();
    }
    else if(a_command == "off")
    {
        SerialPortCommandOff();
    }
}

void SerialPortCommandOn()
{
    Serial.println("Turned LED on");
    blueLed.SetHigh();
}

void SerialPortCommandOff()
{
    Serial.println("Turned LED off");
    blueLed.SetLow();
}