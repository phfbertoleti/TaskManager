r_bsp Package
=============

Document Number: 
----------------
N/A

Version:
--------
v1.10

Overview
--------
The r_bsp package provides a foundation for code to be built on top of. It provides startup code, iodefines, and MCU
information for different boards. There are 2 folders that make up the r_bsp package. The 'mcu' folder has iodefine
files for each MCU group. The 'board' folder has a folder with startup code and MCU information for each supported
board. Inside each board folder is a file named 'mcu_info.h' which has information about the MCU on the board. This 
information is used to help configure Renesas middleware that uses the r_bsp package. Which MCU and board is chosen
is decided by the settings in 'platform.h'. The user can choose which board they are using by uncommenting the include
path that applies to their board. For example, if you are using the RSK+RX62N then you would uncomment the 
#include "./board/rskrx62n/r_bsp.h" include path. Users are encouraged to add their own boards to the 'board' directory.

Features
--------
* Provides foundation to build code on top of.
* Provides MCU startup code.
* Provides SFR access through iodefine.h
* Stores details of MCU in 'mcu_info.h' to help configure Renesas middleware.
 
Limitations:
------------
N/A

Peripherals Used Directly:
--------------------------
N/A

Required Packages:
------------------
N/A

How to add to your project:
---------------------------
* Copy the r_bsp folder to your project.
* Add an include path to the 'r_bsp' directory. 
* Add all of the source files for your board from the 'r_bsp\board\--YOUR_BOARD--' directory to your project. 
* Uncomment the include path for your board in 'platform.h' which is located in the 'r_bsp' directory.

File Structure:
---------------
r_bsp
|
|--->board (contains supported boards)
|  |
|  |--->rskrx62n (example)
|  |
|  |--->*Other supported boards*
|  
|--->mcu (contains iodefine.h files for different MCU groups)
|  |
|  |--->rx62n (example)
|  |
|  |--->*Other supported MCUs*
|
|--->platform.h (choose which board to use)
|
|--->readme.txt


