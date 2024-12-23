//Neacsa Leonard 315CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "function.h"
#include "error_utils.h"
#define MAX 100

//Gets 2 numbers from a string
int get_numbers_2(char *s, int *a, int *b)
{
	//extracts the values of the coordinates
	char *p = strtok(s, "\n ");
	if (!p) {
		invalid_command();
		return 0;
	}
	if (check_numbers(p))
		*a = atoi(p);
	else {
		invalid_command();
		return 0;
	}

	p = strtok(0, "\n ");
	if (!p) {
		invalid_command();
		return 0;
	}
	if (check_numbers(p))
		*b = atoi(p);
	else {
		invalid_command();
		return 0;
	}

	p = strtok(0, "\n ");
	if (p) {
		invalid_command();
		return 0;
	}
	return 1;
}

//Function that shows the historgram of a image
void histogram(image_rgb **rgb, image_gray **gray, char *command)
{
	//Determit if a image is loaded into the program
	if (test_memory(*rgb, *gray) == 0)
		return;

	char s[MAX];
	int x, y;

	strcpy(s, command + 9);

	if (!get_numbers_2(s, &x, &y))
		return;

	//Determit if the image in memory is gray or rgb
	if (*rgb) {
		invalid_image_type();
		return;
	}

	//This matrix retains the number of apperances of
	//the specific values and group means the number of values that
	//need to be in a group
	int a[256], group = 256 / y;
	image_gray *pic = *gray;

	frequency(pic, a);

	//max reperesent the max frequency of a value
	double max = 0;

	for (int i = 0; i < 256; i = i + group) {
		int sum = 0;
		for (int j = i; j < i + group; j++) {
			sum += a[j];
		}
		a[i] = sum;
		if (max < sum)
			max = sum;
	}

	//Prints the historgram of the image
	for (int i = 0; i < 256; i = i + group) {
		double new_value = 1.0 * a[i] / max;
		new_value *= x;
		a[i] = floor(new_value);
		printf("%d\t|\t", a[i]);
		for (int j = 0; j < a[i]; j++)
			printf("*");
		printf("\n");
	}
}
