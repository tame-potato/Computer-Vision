Purpose:
This project aims to obtain the FFT and inverse FFT of a .pgm image and implement a Butterworth low pass filter
which outputs a smoothed image.  

Source Code: 
-Assignment_2.cpp 
-cplx.h
-Four2.c
-Four2.h 
-Four2_Private.h
-clover.pgm
-other square .pgm image files

How to Run:
-Open a command line terminal and navigate to the directory where this file is contained.

-Type in "make" and hit return, a new file will appear in the directory: Assignment_2.o.

-The executable takes three arguments separated by spaces. The first is the name of the image to target, ie. "clover.pgm". 
 The second is the degree of the filter (n). The third is the radius of the filter (Do).

-Run the file by typing the following into the terminal, this example would apply a filter to image clover.pgm with n=2, Do=10:
    "./Assignment_2.o clover.pgm 2 10"

-The program will return the total power of the FFT before the filter, the total power after the filter, and the percentage
 of the total power remaining after the filter. 

-Additionally the program will ouput three new images:

    -Magnitude.pgm
        The magnitude of the FFT before the filter.

    -Magnitude_Filtered.pgm 
        The magnitude of the FFT after the filter.

    -Butterworth.pgm
        The Butterworth filter used on the image.

    -Output.pgm
        The filtered image.