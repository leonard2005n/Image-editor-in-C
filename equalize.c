//Neacsa Leonard 315CA
#include <stdio.h>
#include <math.h>
#include "function.h"
#include "error_utils.h"

//Function that returns the sum of the values
//in the array <= n
int sum_vector(int a[], int n)
{
	int sum = 0;

	for (int i = 0; i <= n; i++)
		sum += a[i];

	return sum;
}

//Function that equalize a gray image
void equalize(image_rgb **rgb, image_gray **gray)
{
	//Determit if a image is loaded into the program
	if (test_memory(*rgb, *gray) == 0)
		return;

	//Determit if the image in memory is gray or rgb
	if (*rgb) {
		invalid_image_type();
		return;
	}

	image_gray *pic = *gray;

	//This matrix retains the number of apperances of
	//the specific values
	int a[256];
	double area = pic->n * pic->m;

	frequency(pic, a);
	//Determine the value that it needs to be replaced
	for (int i = 0; i < pic->n; i++) {
		for (int j = 0; j < pic->m; j++) {
			double new_value = 0;
			int h = sum_vector(a, pic->pixel[i][j]);

			new_value = 255.0 / area * h;
			pic->pixel[i][j] = round(new_value);

		}
	}

	printf("Equalize done\n");
}
