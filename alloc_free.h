//Neacsa Leonard 315CA
#pragma once
#include "image.h"

//Function that frees a rgb image
void free_image_rgb(image_rgb * *aux);

//Function that frees a gray iamge
void free_image_gray(image_gray **aux);

//Function that allocates memory for a rgb image
image_rgb *alloc_image_rgb(int const n, int const m);

//Function that allocates memory for a gray image
image_gray *alloc_image_gray(int const n, int const m);

//Function that allocs a array of pixles_rgb
pixels **alloc_pixles_rgb(int n, int m);

//Function that alloc memory for a matrix int
int **alloc_matrix(int n, int m);
