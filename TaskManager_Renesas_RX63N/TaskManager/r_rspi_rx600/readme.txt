PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

RSPI Driver
===========

Document Number: 
----------------
N/A

Version:
--------
v1.0

Overview
--------
Basic RSPI Master Mode driver. 

Features
--------
* Functions to init, read, and write the RSPI channels
* Ability to lock channels to a task to ensure no other tasks try to use 
  peripheral while it is already being used.
 
Limitations:
------------
* This code is not re-entrant but does protect against multiple concurrent
  function calls.

Peripherals Used Directly:
--------------------------
* RSPI0
* RSPI1

Required Packages:
------------------
* none

How to add to your project:
---------------------------
*  Add src\r_rspi_rx600.c to your project.
*  Add an include path to the 'r_rspi_rx600' directory. 
*  Add an include path to the 'r_rspi_rx600\src' directory.
*  Configure middleware through r_rspi_rx600_config.h.

File Structure:
---------------
r_rspi_rx600
|
|--->src (contains package source)  
|
|--->r_rspi_rx600_config.h (used for configuring middleware)
|
|--->readme.txt
                
