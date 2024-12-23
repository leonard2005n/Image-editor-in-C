//Neacsa Leonard 315CA
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "error.h"
#include "image.h"

//Function that shows the message for a invalid commnad
void invalid_command(void)
{
	printf("Invalid command\n");
}

//Function that prints a invalid the message for the invalid
//set of coordinates for the select fucntion
void inval_coordinates(void)
{
	printf("Invalid set of coordinates\n");
}

//Function that prints the message for the selection is not square
void selection_not_square(void)
{
	printf("The selection must be square\n");
}

//Function that prints the message if the angle is not valid
void invalid_angle(void)
{
	printf("Unsupported rotation angle\n");
}

//Function taht prints he message if the parameter of the apply is not
//supported
void apply_inval_parameter(void)
{
	printf("APPLY parameter invalid\n");
}

//Function that prints the message for the error of image type
void invalid_image_type(void)
{
	printf("Black and white image needed\n");
}

//Functio that aproximate the values of a rgb pixel
void aprox_pixel_rgb(pixels **tmp, int i, int j)
{
	//Aprox the value if it is below 0
	if (tmp[i][j].R < 0)
		tmp[i][j].R = 0;

	if (tmp[i][j].G < 0)
		tmp[i][j].G = 0;

	if (tmp[i][j].B < 0)
		tmp[i][j].B = 0;

	// Aporx the value if it is above 255
	if (tmp[i][j].R > 255)
		tmp[i][j].R = 255;

	if (tmp[i][j].G > 255)
		tmp[i][j].G = 255;

	if (tmp[i][j].B > 255)
		tmp[i][j].B = 255;
}

//Function that aproximate the values of a gray pixel
void apox_pixel_gray(int **tmp, int i, int j)
{
	//Aprox the value if it is below 0
	if (tmp[i][j] < 0)
		tmp[i][j] = 0;

	// Aporx the value if it is above 255
	if (tmp[i][j] > 255)
		tmp[i][j] = 255;

}

//Countes the times each value apperes in the image
void frequency(image_gray *pic, int a[])
{
	//Makes the vector full of 0
	for (int i = 0; i < 256; i++)
		a[i] = 0;

	for (int i = 0; i < pic->n; i++)
		for (int j = 0; j < pic->m; j++)
			a[pic->pixel[i][j]]++;
}

//Check if the string is contains only numbers
int check_numbers(char *p)
{
	int start = 0, n = strlen(p);
	if (p[0] == '-')
		start++;
	for (int i = start; i < n; i++) {
		if (!isdigit(p[i]))
			return 0;
	}
	return 1;
}

//Test if the image is loaded in the memory
int test_memory(image_rgb *pic_rgb, image_gray *pic_g)
{
	if (!pic_rgb && !pic_g) {
		printf("No image loaded\n");
		return 0;
	}
	return 1;
}
