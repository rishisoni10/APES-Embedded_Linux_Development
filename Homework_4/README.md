**Problem Statement:**

***Part 1:***
Write a character driver to send commands from user space to set frequency and time period of an LEDs (on board) blinking.
- All operations to set/clear LED must happen in the kernel space
- Make use of a private variable of the driver to store current state information
    * Rate (period), duty cycle, on & off
    * The char driver will be the point of communication to the kernel space GPIO functions to set clear the LEDs
- Implement the routines of char driver to support your capabilities
- You can use the software timers to generate PWM for LEDs

***Part 2:***
Write an application that communicates with the char driver developed above to
- Set state variables for the LEDs
    * On/Off
    * Frequency
    * Duty cycle
- Read the state variables from the char driver
    * Read all
    * Query single

***Part 3:***
Write code to implement sockets to communicate between two processes
- Support bi-directional communications
- Make use of sockets on your laptop/PC to send commands to the user space application on the beaglebone that you made in the previous question


***Implemetation:***
* Part 1: filenames -> led_driver_Rishi.c, Makefile
* Part 2: filename -> beaglebone_server.c
* Part 3: filename -> pc_client.c
* Compile and load the kernel module with the driver functionality
* Connect the PC and the BeagleBone to a network router. 
* Run *beaglebone_server.c* on the BeagleBone and *pc_client.c* on your PC.
* Before this, modify the port numbers on both the server and the client code, and the static IP of the client , if required.
* Select the menu item options from the client (PC) side and observe the corresponding changes on server (BeagleBone)
