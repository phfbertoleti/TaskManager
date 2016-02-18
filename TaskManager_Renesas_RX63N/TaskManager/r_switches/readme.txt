PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

Switches
========

Document Number 
---------------
N/A

Version
-------
v1.0

Overview
--------
Configures port pins for switches and calls user defined function on switch press. The callback functions are called
straight from the interrupt service routine associated with the switch press. This means that users should keep their
callback functions short to make sure it does not hold up the rest of their system.

Features
--------
* Call one function to setup switches.
* Define function to call when switch is pressed.

Supported MCUs
--------------
* RX610 Group
* RX621, RX62N Group
* RX62T Group
* RX630 Group
* RX631, RX63N Group 

Limitations
-----------
* None

Peripherals Used Directly
-------------------------
* None

Required Packages
-----------------
* None

How to add to your project
--------------------------
*  Add src\r_switches.c to your project.
*  Add an include path to the 'r_switches' directory. 
*  Add an include path to the 'r_switches\src' directory.
*  Configure middleware through r_switches_config.h.

File Structure
--------------
r_switches
|
|--->src (contains package source)  
|
|--->r_switches_config.h (used for configuring middleware)
|
|--->readme.txt
                
Boards Tested On
----------------
* RSKRX610
* RSK+RX62N
* RSKRX62T
* RDKRX62N
* RSKRX630
* RSKRX63N
* RDKRX63N
