/*
    Computer Vision
    Assignment 3
    Author: Pablo Ruiz
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

/// @brief Reads an image from a file
/// @param image output array of the image intensities
/// @param fileName full name of the image to read, ie. "image1.pgm"
/// @param pgmType output representing type of pgm encoding used P1-P6
/// @param sizeX output x dimension of the image intensity array
/// @param sizeY output y dimension of the image intensity array
/// @return If succesful return 0, otherwise return error code
unsigned Read_PGM (const char *fileName,
                   unsigned char *&image,
                   char *&pgmType,
                   unsigned &sizeX,
                   unsigned &sizeY,
                   unsigned normal=255)
{
    unsigned levels, size;
    pgmType = (char*)malloc(sizeof(char) * 3);

    // Read Image
    FILE *iFile = fopen(fileName,"r");
    if(iFile == 0) return 1; //return read failure error code
    if(4 != fscanf(iFile, "%s %u %u %u ", pgmType, &sizeX, &sizeY, &levels)) return 2; //return scan error code
    size = sizeX * sizeY;
    image = (unsigned char *) malloc(size);
    fread(image,sizeof(unsigned char),size,iFile);
    fclose(iFile);
    return 0;
}


/// @brief normalize an array of floats with a known max value (upper limit)
/// @param data input array of floats, they will be normalized in place
/// @param size size of the input array
/// @param max current max value of the data in the array
/// @param norm upper limit of the output array, defaults to 255
void Norm(int *data, unsigned char **out, float max, unsigned size, int norm = 255)
{
    // Normalize intensity values
    *out = (unsigned char*)calloc(sizeof(unsigned char), size);
    float factor = norm / max;
    for (unsigned i = 0; i < size; ++i)
    {
        (*out)[i] = data[i] * factor;
    }
}

/// @brief normalize an array of floats with an unknown max value
/// @param data input array of floats, they will be normalized in place
/// @param size size of the input array
/// @param norm upper limit of the output array, defaults to 255
void Norm(int *data, unsigned char **out, unsigned size, int norm = 255)
{
    float max = data[0];
    //find max
    for (unsigned i = 0; i < size; ++i)
    {
        max = data[i] > max ? data[i] : max;
    }
    Norm(data, out, max, size, norm);
}

/// @brief Combine two int 1D input arrays into a single int 1D output array. 
///        Each element in the output array is the magnitude of the corresponding 
///        elements in the two input arrays.
/// @param a Input 1D int array 1. 
/// @param b Input 1D int array 2.
/// @param out Output 1D int array.
/// @param size Length of the input and output arrays.
void Combine(int *a, int *b, int **out, unsigned size)
{
    *out = (int*)calloc(sizeof(int), size);
    for (unsigned i = 0; i < size; ++i)
    {
        (*out)[i] = sqrt(pow(a[i],2) + pow(b[i],2));
    }
}

/// @brief Combine two unsigned char 1D input arrays into a single unsigned char 1D output array. 
///        If either of the input arrays has an element larger than 0 the matching element in the
///        output array is mapped to 255.
/// @param a Input 1D unsigned char array 1. 
/// @param b Input 1D unsigned char array 2.
/// @param out Output 1D unsigned char array.
/// @param size Length of the input and output arrays.
void Combine(unsigned char *a, unsigned char *b, unsigned char **out, unsigned size)
{    
    *out = (unsigned char*)calloc(sizeof(unsigned char), size);
    for (unsigned i = 0; i < size; ++i)
    {
        (*out)[i] = (b[i] || b[i]) ? 255 : 0;
    }

}

/// @brief Filters an input int array according to a given threshold and returns it as an unsigned char array
/// @param a Input int 1D array to filter
/// @param size Size of the input array
/// @param out Output unsigned char 1D array pointer
/// @param thresh Threshold at which to filter the input values. Anything larger than this value is mapped to 
///               255 in the output, everything else is mapped to 0.
void Threshold(int *a, unsigned size, unsigned char **out, int thresh)
{
    *out = (unsigned char*)calloc(sizeof(unsigned char), size);
    for (unsigned i = 0; i < size; ++i)
    {
        (*out)[i] = a[i] > thresh ? 255 : 0;   
    }
}

/// @brief Converts an array of ints to an array of unsigned chars 
/// @param a Input 1D int array 
/// @param size Length of input array
/// @return Pointer to the converted 1D unsigned char array output.
unsigned char *Int_2_Char(int *a, unsigned size)
{
    unsigned char* out = (unsigned char*)calloc(sizeof(unsigned char), size);
    for (unsigned i = 0; i < size; ++i)
    {
        out[i] = a[i] > 255 ? 255 : (a[i] < 0 ? 0 : a[i]);
    }
    return out;
}

/// @brief Creates a .pgm image file with the passed name and writes
///        the passed image data to it
/// @param fileName full name of the image to write, ie. "image1.pgm"
/// @param image image data
/// @param pgmType type of pgm encoding used P1-P6
/// @param sizeX x dimension of the image data passed
/// @param sizeY y dimension of the image data passed
/// @param level max level range of the image data passed
/// @return If successful return 0, otherwise return error code
unsigned Write_PGM (const char *fileName,
                    unsigned char *image,
                    char *pgmType,
                    unsigned sizeX,
                    unsigned sizeY,
                    unsigned level=255)
{
    //Write image to file
    FILE *iFile = fopen(fileName,"w");
    if(iFile==0) return 1; //return error code failed to open
    fprintf(iFile, "%s\n%u %u\n%u\n", pgmType,sizeX,sizeY,level);//write header
    fwrite(image, sizeof(unsigned char), sizeX * sizeY, iFile); //write binary image
    fclose(iFile);
    return 0;
}

/// @brief Adds random noise to the image up to a limit
/// @param image 1D image array to add noise to 
/// @param size length of image array
/// @param limit maximum absolute limit for the added noise
void Add_Noise(unsigned char *image, unsigned size, int limit)
{
    float noisyPixel, noise; 
    for (unsigned i = 0; i < size; ++i)
    {
        noise = ((2*(float)rand() - RAND_MAX) / RAND_MAX) * limit;
        noisyPixel =  noise + image[i];
        if (noisyPixel > 255)
            image[i] = 255;
        else if (noisyPixel < 0)
            image[i] = 0;
        else
            image[i] = noisyPixel;
    }
}

/// @brief find the percentage difference between the pixels in two images
/// @param a First 1D array to compare
/// @param b Second 1D array to compare
/// @param size Size of the arrays
/// @return The percentage difference
float Diff(unsigned char *a, unsigned char *b, unsigned size)
{
    unsigned diffCount = 0;
    for (unsigned i = 0; i < size; ++i)
    {
        a[i] != b[i] ? ++diffCount : 0;
    }
    return ((float)diffCount/size) * 100;
} 

/// @brief Creates a Gaussian low pass filter (smoothing kernel) 
/// @param kernel Kernel output 1D array
/// @param size Dimension for the square kernel (odd preferred) 
/// @param K Gaussian factor
/// @param sd Gaussian Standard Deviation
void Gauss_Kernel(float **kernel, unsigned size, int K = 1, int sd = 1)
{
    unsigned index;
    float sum = 0;
    *kernel = (float *)calloc(sizeof(float), size*size);

    //Calculate the factor for every element of the filter
    for (unsigned i = 0; i < size; ++i)
    {
        for (unsigned j = 0; j < size; ++j)
        {
            index = i * size + j;
            (*kernel)[index] = (float)K * exp(-(pow(i,2)+pow(j,2))/((float)2*pow(sd,2)));
            sum += (*kernel)[index];
        }

    }

    //Divide every element by the total so that together they all add up to one
    for (unsigned i = 0; i < size*size; ++i)
    {
        (*kernel)[i] /= sum;        
    }

}

/// @brief Performs a convolution with a 2D mask on an image
/// @param in The input image as a 1D array.
/// @param sizeX The X dimension of the image.
/// @param sizeY The Y dimension of the image.
/// @param filter The 2D filter mask as a 1D array.
/// @param filterX The X dimension of the filter mask.
/// @param filterY The Y dimension of the filter mask.
/// @param out The output filtered image as a 1D array of length sizeX*sizeY
/// @param normalize If true normalize the output to either 0 or 255, if false
///                  return the raw values. False by default.
/// @param threshold The threshold above which its returned as 255 when normalizing.
///                  0 by default.
void Convolution_2D(unsigned char *in, 
                    unsigned sizeX, 
                    unsigned sizeY, 
                    float *filter, 
                    unsigned filterX, 
                    unsigned filterY, 
                    int **out, 
                    bool binary=false, 
                    int threshold=0)
{
    unsigned index,
    indexFilter,
    centerX = filterX/2,
    centerY = filterY/2;
    int filteredOrigin,
        indexCorrected,
        offsetX,
        offsetY,
        max;

    *out = (int*)calloc(sizeof(int), sizeX*sizeY); //allocate space for the output array

    for (unsigned i = 0; i < sizeY; ++i)
    {
        for (unsigned j = 0; j < sizeX; ++j)
        {
            index = sizeX * i + j; //calculate the index for the current image intensity value
            filteredOrigin = 0; //reset the output value for the current origin
            for (unsigned k = 0; k < filterY; ++k)
            {
                for (unsigned l = 0; l < filterX; ++l)
                {
                    indexFilter = filterX * k + l; //calculate the index for the current filter value
                    offsetX = l - centerX; //calculate the X offset relative to the center of the filter
                    offsetY = k - centerY; //calculate the Y offset relative to the center of the filter
                    indexCorrected = index + offsetX + offsetY*sizeX;

                    // If the corrected index is:
                    //  -negative
                    //  -larger than the end of the array
                    //  -larger than the current end of row
                    //  -smaller than the beginning of current row
                    // Add 0 otherwise add the product of filter times the intensity
                    if  (
                        indexCorrected < 0 ||
                        indexCorrected > (int)(sizeX * sizeY) ||
                        (l > centerX ? indexCorrected > (int)((i+1)*sizeX) : false) ||
                        (l < centerX ? indexCorrected < (int)(i*sizeX) : false)
                        )
                        filteredOrigin += 0;
                    else
                        filteredOrigin += filter[indexFilter] * in[indexCorrected];

                }
            }
            max = (filteredOrigin > max) ? filteredOrigin : max;
            (*out)[index] = (binary) ? ((abs(filteredOrigin) > threshold) ? 255 : 0) : abs(filteredOrigin); //if binary is enabled and the output is above the threshhold save as 255
        }
    }
}

int main(int argc, char *argv[]){

    unsigned sizeX, sizeY, size; //image width, height, size
    unsigned char *image; //image array
    char *pgmType;
    char *nameRead = argv[1];
    int threshold = atoi(argv[2]);
    int thresholdNoisy = atoi(argv[3]);
    int thresholdSmooth = atoi(argv[4]);
    int limit = atoi(argv[5]);
    int *filteredX, *filteredY, *filteredFull, *noisyFull, *smoothFull, *imageSmooth;
    unsigned char *noisyChar, *filteredChar, *smoothChar;
    float sobelFilterX[] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    float sobelFilterY[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    float *smoothFilter;// = {0.0751, 0.1238, 0.0751, 0.1238, 0.2042, 0.1238, 0.0751, 0.1238, 0.0751};

    //Read image and normalize the values
    Read_PGM(nameRead, image, pgmType, sizeX, sizeY);
    size = sizeX*sizeY;

#pragma region Clean
    //Apply sobel filter and return filtered normalized array
    Convolution_2D(image, sizeX, sizeY, sobelFilterX, 3, 3, &filteredX, false);
    Convolution_2D(image, sizeX, sizeY, sobelFilterY, 3, 3, &filteredY, false);

    //Combine X and Y filtered edge images
    Combine(filteredX, filteredY, &filteredFull, size);

    //Normalize filtered results
    Norm(filteredFull, &filteredChar, size);

    //Save the filtered edge image
    Write_PGM("Sobel_Clean.pgm", filteredChar, pgmType, sizeX, sizeY);

    //Threshold filtered results
    Threshold(filteredFull, size, &filteredChar, threshold);

    //Save the binary edge image
    Write_PGM("Binary_Clean.pgm", filteredChar, pgmType, sizeX, sizeY);
#pragma endregion

#pragma region Noise
    //Add noise to image
    Add_Noise(image, size, limit);

    //Save noisy image for reference
    Write_PGM("Source_Noisy.pgm", image, pgmType, sizeX, sizeY);

    //Apply sobel filter to noisy image
    Convolution_2D(image, sizeX, sizeY, sobelFilterX, 3, 3, &filteredX);
    Convolution_2D(image, sizeX, sizeY, sobelFilterY, 3, 3, &filteredY);

    //Combine X and Y filtered edge images
    Combine(filteredX, filteredY, &noisyFull, size);

    //Normalize filtered results
    Norm(noisyFull, &noisyChar, size);

    //Save the filtered edge image
    Write_PGM("Sobel_Noisy.pgm", noisyChar, pgmType, sizeX, sizeY);

    //Threshold filtered results
    Threshold(noisyFull, size, &noisyChar, thresholdNoisy);

    //Save the binary edge image
    Write_PGM("Binary_Noisy.pgm", noisyChar, pgmType, sizeX, sizeY);
#pragma endregion

#pragma region Smooth
    //Smooth
    Gauss_Kernel(&smoothFilter, 3);
    Convolution_2D(image, sizeX, sizeY, smoothFilter, 3, 3, &imageSmooth);

    //Replace original image with smoothed image
    image = Int_2_Char(imageSmooth, size);

    //Save smooth image for reference
    Write_PGM("Source_Smooth.pgm", image, pgmType, sizeX, sizeY);

    //Apply sobel filter to noisy smoothed image
    Convolution_2D(image, sizeX, sizeY, sobelFilterX, 3, 3, &filteredX);
    Convolution_2D(image, sizeX, sizeY, sobelFilterY, 3, 3, &filteredY);

    //Combine X and Y filtered edge images
    Combine(filteredX, filteredY, &smoothFull, size);

    //Normalize filtered results
    Norm(smoothFull, &smoothChar, size);

    //Save the filtered edge image
    Write_PGM("Sobel_Smooth.pgm", smoothChar, pgmType, sizeX, sizeY);

    //Threshold filtered results
    Threshold(smoothFull, size, &smoothChar, thresholdSmooth);

    //Save the binary edge image
    Write_PGM("Binary_Smooth.pgm", smoothChar, pgmType, sizeX, sizeY);
#pragma endregion

    //Print the percentage change between noisy and not
    std::cout << "Difference between clean and noisy binary edges: " << Diff(filteredChar, noisyChar, size) << "%" << std::endl;
    std::cout << "Difference between clean and smooth binary edges: " << Diff(filteredChar, smoothChar, size) << "%" << std::endl;

    return 0;
}
