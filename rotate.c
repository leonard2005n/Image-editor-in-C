//Neacsa Leonard 315CA
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "error_utils.h"
#include "alloc_free.h"

//Function that rotates the hole rgb image
void rotate_all_image_rbg(image_rgb **rgb, int count)
{
	image_rgb *pic = *rgb;

	//Rotates the selected pixels by the numvber of the value count
	while (count) {
		int aux;
		pixels **a = alloc_pixles_rgb(pic->m, pic->n);
		if (!a) {
			return;
		}
		count--;
		//Rotates the selected pixels by 90 degrees
		for (int i = 0; i < pic->n; i++) {
			for (int j = 0; j < pic->m; j++) {
				a[j][pic->n - i - 1] = pic->pixel[i][j];
			}
		}
		for (int i = 0; i < pic->n; i++)
			free(pic->pixel[i]);
		free(pic->pixel);

		pic->pixel = a;
		aux = pic->n;
		pic->n = pic->m;
		pic->m = aux;
		a = NULL;
	}
}

//Function that rotates the hole gray image
void rotate_all_image_gray(image_gray **gray, int count)
{
	image_gray *pic = *gray;

	//Rotates the selected pixels by the numvber of the value count
	while (count) {
		int **a = alloc_matrix(pic->m, pic->n), aux;
		if (!a) {
			return;
		}
		count--;
		//Rotates the selected pixels by 90 degrees
		for (int i = 0; i < pic->n; i++) {
			for (int j = 0; j < pic->m; j++) {
				a[j][pic->n - i - 1] = pic->pixel[i][j];
			}
		}
		for (int i = 0; i < pic->n; i++)
			free(pic->pixel[i]);
		free(pic->pixel);

		pic->pixel = a;
		aux = pic->n;
		pic->n = pic->m;
		pic->m = aux;
		a = NULL;
	}

}

//Rotate a portion of the image rgb
void rotate_image_rgb(image_rgb *pic, int *x1, int *y1,
					  int *x2, int *y2, int count)
{
		pixels **a;
		int n = *x2 - *x1, m = *y2 - *y1;

		a = alloc_pixles_rgb(n, m);
		if (!a) {
			return;
		}

		//Rotates the selected pixels by the numvber of the value count
		while (count) {
			count--;

		//Rotates the selected pixels by 90 degrees and copies
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					a[j][n - i - 1] = pic->pixel[*x1 + i][*y1 + j];
				}
			}

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					pic->pixel[*x1 + i][*y1 + j] = a[i][j];
				}
			}
		}

		for (int i = 0; i < n; i++)
			free(a[i]);
		free(a);
}

//Rotate a portion of the gray image
void rotate_image_gray(image_gray *pic, int *x1, int *y1,
					   int *x2, int *y2, int count)
{
		int **a;
		int n = *x2 - *x1, m = *y2 - *y1;

		a = alloc_matrix(n, m);
		if (!a) {
			return;
		}
		//Rotates the selected pixels by 90 degrees
		while (count) {
			count--;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					a[j][n - i - 1] = pic->pixel[*x1 + i][*y1 + j];
				}
			}

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					pic->pixel[*x1 + i][*y1 + j] = a[i][j];
				}
			}
		}

		for (int i = 0; i < n; i++)
			free(a[i]);
		free(a);
}

//Function that rotates the sleceted pixels
void rotate(image_rgb **pic_rgb, image_gray **pic_g,
			int *x1, int *y1, int *x2, int *y2, char *command)
{
	int angle, n = *x2 - *x1, m = *y2 - *y1, initial_angle;
	command = command + 6;

	//Determit if a image is loaded into the program
	if (!test_memory(*pic_rgb, *pic_g))
		return;
	angle = atoi(command);
	initial_angle = angle;

	int line = 0, row = 0;
	if (*pic_rgb) {
		line = (*pic_rgb)->n;
		row = (*pic_rgb)->m;
	}
	if (*pic_g) {
		line = (*pic_g)->n;
		row = (*pic_g)->m;
	}

	//Verifies if an angle i
	if (angle < -360 && 360 < angle) {
		invalid_angle();
		return;
	}

	if (angle < 0)
		angle = 360 + angle;

	if ((angle % 90) != 0) {
		invalid_angle();
		return;
	}

	//Count represent the number of times it needs to be rotated
	int count = angle / 90 % 4;

	if (n == line && row == m) {
		if (*pic_rgb) {
			rotate_all_image_rbg(pic_rgb, count);
			*x2 = (*pic_rgb)->n;
			*y2 = (*pic_rgb)->m;
			printf("Rotated %d\n", initial_angle);
			return;
			return;
		}
		if (*pic_g) {
			// printf("wow");
			rotate_all_image_gray(pic_g, count);
			*x2 = (*pic_g)->n;
			*y2 = (*pic_g)->m;
			printf("Rotated %d\n", initial_angle);
			return;
		}
	}

	//Test if the selection is square
	if (n != m) {
		selection_not_square();
		return;
	}

	if ((*pic_rgb)) {
		rotate_image_rgb(*pic_rgb, x1, y1, x2, y2, count);
	} else {
		rotate_image_gray(*pic_g, x1, y1, x2, y2, count);
	}

	printf("Rotated %d\n", initial_angle);
}
