//Neacsa Leonard 315CA
#include <stdio.h>
#include <stdlib.h>
#include "alloc_free.h"
#include "image.h"

//Function that allocs a array of pixles_rgb
pixels **alloc_pixles_rgb(int n, int m)
{
	pixels **tmp = (pixels **)malloc(n * sizeof(pixels *));

	if (!tmp) {
		tmp = NULL;
		return tmp;
	}

	//Allocs memory for pixels
	for (int i = 0; i < n; i++) {
		tmp[i] = (pixels *)malloc(m * sizeof(pixels));
		if (!tmp[i]) {
			for (int j = i - 1; j >= 0; j--) {
				free(tmp);
			}
			fprintf(stderr, "alloc_pixels()error\n");
			free(tmp);
			tmp = NULL;
			return tmp;
		}
	}
	return tmp;
}

//Function that alloc memory for a matrix int
int **alloc_matrix(int n, int m)
{
	int **tmp = (int **)malloc(n * sizeof(int *));

	if (!tmp) {
		tmp = NULL;
		return tmp;
	}

	//Allocs memory for pixels
	for (int i = 0; i < n; i++) {
		tmp[i] = (int *)malloc(m * sizeof(int));
		if (!tmp[i]) {
			for (int j = i - 1; j >= 0; j--) {
				free(tmp);
			}
			fprintf(stderr, "alloc_matrix()error\n");
			free(tmp);
			tmp = NULL;
			return tmp;
		}
	}
	return tmp;
}

//Function that allocates memory for a rgb image
image_rgb *alloc_image_rgb(int const n, int const m)
{
	image_rgb *pic = (image_rgb *)malloc(sizeof(image_rgb));
	pic->pixel = alloc_pixles_rgb(n, m);
	if (!pic->pixel) {
		free(pic);
		pic = NULL;
	}
	return pic;
}

//Function that allocates memory for a gray image
image_gray *alloc_image_gray(int const n, int const m)
{
	image_gray *pic = (image_gray *)malloc(sizeof(image_gray));
	pic->pixel = alloc_matrix(n, m);
	if (!pic->pixel) {
		free(pic);
		pic = NULL;
	}
	return pic;
	return pic;
}

//Function that frees a gray iamge
void free_image_gray(image_gray **aux)
{
	image_gray *pic = *aux;
	for (int i = 0; i < pic->n; i++)
		free(pic->pixel[i]);
	free(pic->pixel);
	free(pic);
	aux = NULL;
}

//Function that frees a rgb image
void free_image_rgb(image_rgb **aux)
{
	image_rgb *pic = *aux;
	for (int i = 0; i < pic->n; i++)
		free(pic->pixel[i]);
	free(pic->pixel);
	free(pic);
	aux = NULL;
}
