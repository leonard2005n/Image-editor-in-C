//Neacsa Leonard 315CA
#include <stdio.h>
#include <stdlib.h>
#include "error_utils.h"
#include "alloc_free.h"
#include "image.h"

//A function that crops the image that is saved into the memmory
void crop(image_rgb **pic_rgb, image_gray **pic_g,
		  int  *x1, int *y1, int *x2, int *y2)
{
	//Determite if a image is loaded into the program
	if (test_memory(*pic_rgb, *pic_g) == 0)
		return;

	if ((*pic_rgb)) {
		image_rgb *pic = *pic_rgb;
		pixels **a;
		int n = *x2 - *x1, m = *y2 - *y1;

		a = alloc_pixles_rgb(n, m);
		if (!a) {
			return;
		}

		//Copies the values to an auxilar matrix
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				a[i][j] = pic->pixel[*x1 + i][*y1 + j];
			}
		}

		//Frees the old memmory
		for (int i = 0; i < pic->n; i++)
			free(pic->pixel[i]);
		free(pic->pixel);

		//Replace with the cropped version of the image
		pic->pixel = a;
		pic->n = n;
		pic->m = m;
		*x1 = 0;
		*y1 = 0;
		*x2 = n;
		*y2 = m;
	} else {
		image_gray *pic = *pic_g;
		int **a;
		int n = *x2 - *x1, m = *y2 - *y1;
		a = alloc_matrix(n, m);
		if (!a) {
			return;
		}

		//Copies the values to an auxilar matrix
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				a[i][j] = pic->pixel[*x1 + i][*y1 + j];
			}
		}

		//Frees the old memmory
		for (int i = 0; i < pic->n; i++)
			free(pic->pixel[i]);
		free(pic->pixel);

		//Replace with the cropped version of the image
		pic->pixel = a;
		pic->n = n;
		pic->m = m;
		*x1 = 0;
		*y1 = 0;
		*x2 = n;
		*y2 = m;
	}

	printf("Image cropped\n");
}
