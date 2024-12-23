//Neacsa Leonard 315CA
#pragma once
#include "image.h"

//Function that shows the message for a invalid commnad
void invalid_command(void);

//Test if the image is loaded in the memory
int test_memory(image_rgb *pic_rgb, image_gray *pic_g);

//Function that prints a invalid the message for the invalid
//set of coordinates for the select fucntion
void inval_coordinates(void);

//Function that prints the message for the selection is not square
void selection_not_square(void);

//Function that prints the message if the angle is not valid
void invalid_angle(void);

//Functio that aproximate the values of a rgb pixel
void aprox_pixel_rgb(pixels **tmp, int i, int j);

//Functio that aproximate the values of a gray pixel
void apox_pixel_gray(int **tmp, int i, int j);

//Function taht prints he message if the parameter of the apply is not
//supported
void apply_inval_parameter(void);

//Function that prints the message for the error of image type
void invalid_image_type(void);

//Countes the times each value apperes in the image
void frequency(image_gray *pic, int a[]);

//Check if the string is contains only numbers
int check_numbers(char *p);
