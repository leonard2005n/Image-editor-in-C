//Neacsa Leonard 315CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "image.h"
#include "function.h"
#include "error_utils.h"
#define MAX 100

//Gets 4 numbers from a string
int get_numbers_4(char *s, int *a, int *b, int *c, int *d)
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
	if (!p) {
		invalid_command();
		return 0;
	}
	if (check_numbers(p))
		*c = atoi(p);
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
		*d = atoi(p);
	else {
		invalid_command();
		return 0;
	}

	return 1;
}

//Seclectes the pixels of the image
void select(image_rgb *pic_rgb, image_gray *pic_g,
			int *x1, int *y1, int *x2, int *y2, char *command)
{
	//a and b is for the first point and
	//c and d is for the second one
	int a, b, c, d, n, m;
	char s[MAX];

	strcpy(s, command + 7);
	//Determit if a image is loaded into the program
	if (!test_memory(pic_rgb, pic_g))
		return;

	//Chose which values to put in the function
	if (pic_rgb) {
		n = pic_rgb->n;
		m = pic_rgb->m;
	}
	if (pic_g) {
		n = pic_g->n;
		m = pic_g->m;
	}

	//Determine if the selctio needs to select all the pixels
	if (strstr(s, "ALL")) {
		*x1 = 0;
		*y1 = 0;
		*x2 = n;
		*y2 = m;

		printf("Selected ALL\n");
		return;
	}

	//extracts the values of the coordinates
	if (!get_numbers_4(s, &a, &b, &c, &d))
		return;

	if (b > d) {
		int aux = d;
		d = b;
		b = aux;
	}
	if (a > c) {
		int aux = a;
		a = c;
		c = aux;
	}
	// printf("%d %d %d %d", b, d, a, c);
	if (a < 0 || b < 0 || c < 0 || d < 0 || a > m ||
		b > n || c > m || d > n || b == d || a == c) {
		inval_coordinates();
		return;
	}

	*x1 = b;
	*y1 = a;
	*x2 = d;
	*y2 = c;

	printf("Selected %d %d %d %d\n", a, b, c, d);
}
