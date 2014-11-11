Total Hours Spent: 1.5/1.5
		   Actual/Expect

4357 Embedded Firmware Essentials
- Program Assignment #2

1. Login to mbed web site, export the "Hello World" program to all of the following targets.
   How many text files and how many lines of text code in the exported offline code package?
   How many binary (library or object) files?

Zero

   How many files are different between (a) and (b)? (Use linux commands: find, wc, diff) (10 points)

a) Has 1 unique (text) file - Makefile
b) Has 2 unique (text) files - HelloWorld.uvproj and HelloWorld.uvopt
So 3 different files total.

Other files looks the same between (a) and (b).

   What is the "Entry point address:" of your program?  (hint: using readelf)

   a.	Exporting to uVision
   b.	Exporting to GCC ARM Embedded

   Note: Right Click your program, then select "export ..."

2. binwalk, objdump, nm to Analysis binaries files
   http://binwalk.org/

3. Optional: git clone https://github.com/mbedmicro/mbed

