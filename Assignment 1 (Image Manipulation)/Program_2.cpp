/*
    Computer Vision 
    Assignment 1 Program 2
    Author: Pablo Ruiz
*/

//Takes an image and removes the 4th quadrant
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    unsigned sizeX; //image width
    unsigned sizeY; //image height
    unsigned char *image; //image array
    unsigned char *imageTemp; //temporary image array
    unsigned int k; //iterator for storing image data from a matrix
    unsigned levels;
    char pgmType[3];

    /* Read Image */
    FILE *iFile = fopen("Porche.pgm","r");
    if(iFile==0) return 1;
    if(4!=fscanf(iFile, "%s %d %d %d ", pgmType, &sizeX, &sizeY, &levels)) return 1;
    image=(unsigned char *) malloc(sizeX*sizeY);
    fread(image,sizeof(unsigned char),sizeX*sizeY,iFile);
    fclose(iFile);

    //The new image
    imageTemp = (unsigned char *) malloc(sizeX*sizeY);

    //Convert image array into a matrix
    unsigned char processMatrix [sizeY][sizeX];
    //This line copies a 1D array into an 2D array 
    memcpy(processMatrix, image, sizeX*sizeY*sizeof(unsigned char));

    k = 0;
    //Copy only quadrants 1, 2, and 3. Set 4th quadrant to black
    for(unsigned int i=0; i<sizeY; i++){
        for(unsigned int j=0; j<sizeX; j++){
            
            if (!(i > sizeY/2 && j > sizeX/2)){
                imageTemp[k] = processMatrix[i][j];
                //imageTemp[k] = image[k];
            }
            else{
                imageTemp[k] = 0;
            }
            k++;
        }
    }

    /*write image to file*/
    iFile = fopen("Porche2.pgm","w");
    if(iFile==0) return 1; //error handling
    fprintf(iFile, "%s\n%d %d\n%d\n", pgmType,sizeX,sizeY,255);//write header
    fwrite(imageTemp, sizeof(unsigned char), sizeX*sizeY, iFile); //write binary image
    fclose(iFile);

    return 0;
}
