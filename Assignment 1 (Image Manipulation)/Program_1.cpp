/*
    Computer Vision 
    Assignment 1 Program 1
    Author: Pablo Ruiz
*/
 
//Sample Program to Read/Write Image
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
  unsigned sizeX; //image width
  unsigned sizeY; //image height
  unsigned char *image; //image array
  unsigned levels;
  char pgmType[3];

  /* Read Image */
  FILE *iFile = fopen("mri.pgm","r");
  if(iFile==0) return 1;
  if(4!=fscanf(iFile, "%s %d %d %d ", pgmType, &sizeX, &sizeY, &levels)) return 1;
  image=(unsigned char *) malloc(sizeX*sizeY);
  fread(image,sizeof(unsigned char),sizeX*sizeY,iFile);
  fclose(iFile);

  /*write image to file*/
  iFile = fopen("mri2.pgm","w");
  if(iFile==0) return 1; //error handling
  fprintf(iFile, "%s\n%d %d\n%d\n", pgmType, sizeX,sizeY,255);//write header
  fwrite(image, sizeof(unsigned char), sizeX*sizeY, iFile); //write binary image
  fclose(iFile);
  return 0;
}