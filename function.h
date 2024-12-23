//Neacsa Leonard 315CA
#pragma once
#include "image.h"

//Function that loads a image into memory
void load(image_rgb * *rgb, image_gray  * *gray,
		  int *x1, int *y1, int *x2, int *y2, char *command);

//Function that saves the image to a specific file in
//binary or ascii
void save(image_rgb *pic_rgb, image_gray *pic_g, char *command);

//Seclectes the pixels of the image
void select(image_rgb *pic_rgb, image_gray *pic_g,
			int *x1, int *y1, int *x2, int *y, char *command);

//A function that crops the image that is saved into the memmory
void crop(image_rgb **pic_rgb, image_gray **pic_g,
		  int *x1, int *y1, int *x2, int *y2);

//Function that rotates the sleceted pixels
void rotate(image_rgb **pic_rgb, image_gray **pic_g, int *x1,
			int *y1, int *x2, int *y2, char *command);

//Function that apply the specific algorithm on the image
void apply(image_rgb **rgb, image_gray **gray,
		   int *x1, int *y1, int *x2, int *y2, char *command);

//Function that equalize a gray image
void equalize(image_rgb **rgb, image_gray **gray);

//Function that shows the historgram of a image
void histogram(image_rgb **rgb, image_gray **gray, char *command);
