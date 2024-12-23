//Neacsa Leonard 315CA
#include <stdio.h>
#include <string.h>
#include "image.h"
#include "error_utils.h"
#include "function.h"
#define MAX 100

//Function that prints a colored image to a file in ascii
void print_image_rbg_text(image_rgb *pic, FILE *out)
{
	fprintf(out, "%s\n%d %d\n%d\n", "P3", pic->m, pic->n, pic->max_value);

	for (int i = 0; i < pic->n; i++) {
		for (int j = 0; j < pic->m; j++)
			fprintf(out, "%d %d %d ", pic->pixel[i][j].R,
					pic->pixel[i][j].G, pic->pixel[i][j].B);
		fprintf(out, "\n");
	}
	fclose(out);
}

//Function that prints a gray image to a file in ascii
void print_image_gray_text(image_gray *pic, FILE *out)
{
	fprintf(out, "%s\n%d %d\n%d\n", "P2", pic->m, pic->n, pic->max_value);
	// printf("%d, %d\n", pic->n, pic->m);

	for (int i = 0; i < pic->n; i++) {
		for (int j = 0; j < pic->m; j++)
			fprintf(out, "%d ", pic->pixel[i][j]);
		fprintf(out, "\n");
	}
	fclose(out);
}

//Function that prints a colored image to a file in binary
void print_image_rbg_bin(image_rgb *pic, FILE *out)
{
	fprintf(out, "%s\n%d %d\n%d\n", "P6", pic->m, pic->n, pic->max_value);

	for (int i = 0; i < pic->n; i++) {
		for (int j = 0; j < pic->m; j++) {
			fwrite(&pic->pixel[i][j].R, sizeof(unsigned char), 1, out);
			fwrite(&pic->pixel[i][j].G, sizeof(unsigned char), 1, out);
			fwrite(&pic->pixel[i][j].B, sizeof(unsigned char), 1, out);
		}
	}
	fclose(out);
}

//Function that prints a colored image to a file in binary
void print_image_gray_bin(image_gray *pic, FILE *out)
{
	fprintf(out, "%s\n%d %d\n%d\n", "P5", pic->m, pic->n, pic->max_value);

	for (int i = 0; i < pic->n; i++) {
		for (int j = 0; j < pic->m; j++)
			fwrite(&pic->pixel[i][j], sizeof(unsigned char), 1, out);
	}
	fclose(out);
}

//Function that saves the image to a specific file in
//binary or ascii
void save(image_rgb *pic_rgb, image_gray *pic_g, char *command)
{
	char name_file[MAX];
	strcpy(name_file, command + 5);

	//Determit if a image is loaded into the program
	if (!test_memory(pic_rgb, pic_g))
		return;

	//Determits if the image needs to be saved in binary or ascii
	if (strstr(name_file, "ascii")) {
		char *p = strtok(name_file, " ");
		FILE *out = fopen(p, "wt");
		if (pic_g)
			print_image_gray_text(pic_g, out);
		if (pic_rgb)
			print_image_rbg_text(pic_rgb, out);
		printf("Saved %s\n", p);
		return;
	}

	char *p = strtok(name_file, " ");

	FILE *out = fopen(p, "wb");
	if (pic_g)
		print_image_gray_bin(pic_g, out);
	if (pic_rgb)
		print_image_rbg_bin(pic_rgb, out);

	printf("Saved %s\n", p);
}
