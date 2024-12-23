//Neacsa Leonard 315CA
#pragma once
#include <stdio.h>

//A struct that defines a pixel
typedef struct {
	int R, G, B;
} pixels;

//Struct that dfines a inage that is colored
typedef struct {
	char name[3];
	int max_value, n, m;
	pixels **pixel;
} image_rgb;

//Struct that defines a image that is grayscale
typedef struct {
	char name[3];
	int max_value, n, m;
	int **pixel;
} image_gray;
