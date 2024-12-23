//Neacsa Leonard 315CA
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "alloc_free.h"
#include "image.h"
#include "error_utils.h"
#include "function.h"

//Function that applyes the blur algorithm on a rgb image
void apply_rgb(image_rgb *pic, int const x1,
			   int const y1, int const x2, int const y2,
			   int center, int cross, int diag, double exp)
{
	int n = x2 - x1, m = y2 - y1;
	pixels **tmp = alloc_pixles_rgb(n, m);

	//Gnereting the image with the algorithm
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (x1 + i == 0 || y1 + j == 0 ||
				x1 + i == pic->n - 1 || y1 + j == pic->m - 1) {
				tmp[i][j].R = pic->pixel[x1 + i][y1 + j].R;
				tmp[i][j].G = pic->pixel[x1 + i][y1 + j].G;
				tmp[i][j].B = pic->pixel[x1 + i][y1 + j].B;
			} else {
				double sum_R = 0, sum_G = 0, sum_B = 0;
				sum_R = exp * (pic->pixel[x1 + i][y1 + j].R * center);
				sum_G = exp * (pic->pixel[x1 + i][y1 + j].G * center);
				sum_B = exp * (pic->pixel[x1 + i][y1 + j].B * center);

				sum_R += exp * (pic->pixel[x1 + i - 1][y1 + j].R * cross);
				sum_R += exp * (pic->pixel[x1 + i][y1 + j - 1].R * cross);
				sum_R += exp * (pic->pixel[x1 + i + 1][y1 + j].R * cross);
				sum_R += exp * (pic->pixel[x1 + i][y1 + j + 1].R * cross);

				sum_R += exp * (pic->pixel[x1 + i + 1][y1 + j + 1].R * diag);
				sum_R += exp * (pic->pixel[x1 + i + 1][y1 + j - 1].R * diag);
				sum_R += exp * (pic->pixel[x1 + i - 1][y1 + j - 1].R * diag);
				sum_R += exp * (pic->pixel[x1 + i - 1][y1 + j + 1].R * diag);

				sum_G += exp * (pic->pixel[x1 + i - 1][y1 + j].G * cross);
				sum_G += exp * (pic->pixel[x1 + i][y1 + j - 1].G * cross);
				sum_G += exp * (pic->pixel[x1 + i + 1][y1 + j].G * cross);
				sum_G += exp * (pic->pixel[x1 + i][y1 + j + 1].G * cross);

				sum_G += exp * (pic->pixel[x1 + i + 1][y1 + j + 1].G * diag);
				sum_G += exp * (pic->pixel[x1 + i + 1][y1 + j - 1].G * diag);
				sum_G += exp * (pic->pixel[x1 + i - 1][y1 + j - 1].G * diag);
				sum_G += exp * (pic->pixel[x1 + i - 1][y1 + j + 1].G * diag);

				sum_B += exp * (pic->pixel[x1 + i - 1][y1 + j].B * cross);
				sum_B += exp * (pic->pixel[x1 + i][y1 + j - 1].B * cross);
				sum_B += exp * (pic->pixel[x1 + i + 1][y1 + j].B * cross);
				sum_B += exp * (pic->pixel[x1 + i][y1 + j + 1].B * cross);

				sum_B += exp * (pic->pixel[x1 + i + 1][y1 + j + 1].B * diag);
				sum_B += exp * (pic->pixel[x1 + i + 1][y1 + j - 1].B * diag);
				sum_B += exp * (pic->pixel[x1 + i - 1][y1 + j - 1].B * diag);
				sum_B += exp * (pic->pixel[x1 + i - 1][y1 + j + 1].B * diag);

				//aproximate the value
				tmp[i][j].R = round(sum_R);
				tmp[i][j].G = round(sum_G);
				tmp[i][j].B = round(sum_B);

				aprox_pixel_rgb(tmp, i, j);
			}
		}
	}

	//Replace the genereted section into the image
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			pic->pixel[x1 + i][y1 + j] = tmp[i][j];
		}
	}

	//Frees the tmp matrix for the algortihm to work
	for (int i = 0 ; i < n; i++)
		free(tmp[i]);
	free(tmp);
}

//Function that apply the specific algorithm on the image
void apply(image_rgb **rgb, image_gray **gray,
		   int *x1, int *y1, int *x2, int *y2, char *command)
{
	image_rgb *pic_rgb = *rgb;
	image_gray *pic_g = *gray;

	//Determit if a image is loaded into the program
	if (!test_memory(pic_rgb, pic_g))
		return;

	if (strlen(command) < 6) {
		invalid_command();
		return;
	}

	if (strstr(command, "SHARPEN"))	{
		if (pic_rgb) {
			apply_rgb(pic_rgb, *x1, *y1, *x2, *y2, 5, -1, 0, 1);
		} else {
			printf("Easy, Charlie Chaplin\n");
			return;
		}
		printf("APPLY SHARPEN done\n");
	} else if (strstr(command, "EDGE")) {
		if (pic_rgb) {
			apply_rgb(pic_rgb, *x1, *y1, *x2, *y2, 8, -1, -1, 1);
		} else {
			printf("Easy, Charlie Chaplin\n");
			return;
		}
		printf("APPLY EDGE done\n");
	} else if (strstr(command, "BLUR")) {
		if (!strstr(command, "GAUSSIAN")) {
			if (pic_rgb) {
				apply_rgb(pic_rgb, *x1, *y1, *x2, *y2, 1, 1, 1, 1.0 / 9);
			} else {
				printf("Easy, Charlie Chaplin\n");
				return;
			}
			printf("APPLY BLUR done\n");
		} else {
			if (pic_rgb) {
				apply_rgb(pic_rgb, *x1, *y1, *x2, *y2, 4, 2, 1, 1.0 / 16);
			} else {
				printf("Easy, Charlie Chaplin\n");
				return;
			}
			printf("APPLY GAUSSIAN_BLUR done\n");
			}
	} else {
		apply_inval_parameter();
	}
}
