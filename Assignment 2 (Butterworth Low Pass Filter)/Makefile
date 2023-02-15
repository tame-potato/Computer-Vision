# Computer Vision Fall 2022
# Assignment 2
# Author: Pablo Ruiz

all: Assignment2

Four2.o: Four2.c Four2_Private.h cplx.h
	g++ -g -Wall Four2.c -c -lm

Assignment2: Assignment_2.cpp Four2.h Four2.o cplx.h
	g++ -g -Wall Assignment_2.cpp -o Assignment_2.o Four2.o -lm