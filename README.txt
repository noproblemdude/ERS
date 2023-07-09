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

The Project has been split in 3 Branches. Each one represents teh code to be uploaded to each Node. This is the Code for the ECU carrying the monitor hardware.
This branch includes the "Application" directory which contains the code that interafces with the user, p.e code that runs after pressing a button connected to the Board.
