ERS- Environment Recognition System

This Project implements an ultrasonic radar system based on arduino Hardware.
3 ECUs(Arduino boards) shall be connected through a CAN bus, with each ECU respectively being
connected to an LCD display, a Servo motor and an ultrasonic range senor.

Regarding Software this project is mainly structured in the following directories:

-Include:
This is where all the header files are stored to be included

-lib:
Here the premade libraries which this project are stored

-src:
Contains the Main loop file, where the execution begins after the ECU is powered on

    -BSW:
    The source code for the lower level Hardware interaction functionality is implemented here

    -Application:
    Functionality regarding how the user interfaces with the system lies here

-test:
Unit tests (Not yet implemented)

The build wont work while the source code for motor, monitor and sensor are present in the Project (like MonitorHW.h and sensor.h) 
since they have identical functions. To build one has to remove the source files which wont be needed for the specific ECU.
A better arrangement is to be found, per example creating one repo for each ECU.