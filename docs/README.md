# raster_meta
(Only PNG and BMP formats are available)<br>
At the moment the project is in the development stage, but the main functions are already working.

Technical requirements and dependencies:
1. Works only on Linux (tested on Ubuntu).
2. Requires CMake.<br>
To install: ```sudo apt install cmake```.<br>
3. Makefile is supported by most systems by default, but if yours does not support it, you will need to install it too.<br>
To install: ```sudo apt install make```.

Instructions for use:
1. Copy the repository and open the terminal in the copied folder.
2. Create a new folder ```mkdir binary_tmp``` and go to it ```cd binary_tmp```.
3. Compile the program as follows ```cmake ..```, then ```make```.
4. If everything went well, the main file should have appeared in the "binary_tmp" folder.
6. Run the program as follows: ```./main <path_to_file/filename>```.