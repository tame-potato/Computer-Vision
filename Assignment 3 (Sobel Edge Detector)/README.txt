Purpose:
This project aims to apply a 3x3 Sobel edge detection mask to a .pgm image in order to obtain a filtered image which only shows the edges 
or sudden intensity changes in the original image. Additionally noise will be purposefully added to the image and the Sobel filter will 
be applied again. Finally, a 3x3 Gaussian smoothing filter will be applied to the noisy image and the Sobel filter will be applied again.
The edge detection on all three images (clean, noisy, smooth)

Source Code: 
-Assignment_3.cpp 
-mri.pgm
-cake.pgm

How to Run:
-Open a command line terminal and navigate to the directory where this file is contained.

-Type in "make" and hit return, a new file will appear in the directory: Assignment_3.o.

-The executable takes five arguments separated by spaces. 
    -The first is the name of the image to target, ie. "mri.pgm". 
    -The second is the threshold for the clean image filter values, any output from the convolution larger or equal to this value will be converted to 255 all other outputs will be 0.
    -The third is the threshold for the noisy image.
    -The fourth is the threshold for the smooth image.
    -The fifth is the limit for the random noise added to the clean image to create the noisy image.

-Run the file by typing the following into the terminal, this example would apply edge detection to image cake.pgm with a threshold of 0 for the clean image, 
 120 for the noisy image, 45 for the smooth image, and a noise limit of +-20:
    "./Assignment_3.o cake.pgm 0 90 35 20"

-The program will output eight new images:

    -Sobel_Clean.pgm
        The raw normalized results from the sobel edge detection masks applied to the original image.

    -Binary_Clean.pgm
        The binary results using the clean image threshold (second argument) from the sobel edge detection masks applied to the original image.

    -Source_Noisy.pgm 
        The image after having artificial noise added using the noise limit specified (fifth argument).

    -Sobel_Noisy.pgm
        The raw normalized results from the sobel edge detection masks applied to the noisy image.

    -Binary_Noisy.pgm
        The binary results using the noisy image threshold (third argument) from the sobel edge detection masks applied to the noisy image.
    
    -Source_Smooth.pgm 
        The image after having artificial noise added using the noise limit specified (fifth argument) and being smoothed by a 3x3 Gaussian low pass kernel with K=1 and sigma=1.

    -Sobel_Smooth.pgm
        The raw normalized results from the sobel edge detection masks applied to the smooth image.

    -Binary_Smooth.pgm
        The binary results using the smooth image threshold (fourth argument) from the sobel edge detection masks applied to the smooth image.

- Additionally the program will output the pixel percentage difference between the clean binary image, the noisy binary image, and the smooth binary image respectively.
    
