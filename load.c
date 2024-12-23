//Neacsa Leonard 315CA
#include <stdio.h>
#include <string.h>
#include "alloc_free.h"
#include "function.h"
#include "image.h"

//Read a image that is type P3
void read_image_rgb_text(image_rgb *pic, char *name_file)
{
	FILE *in = fopen(name_file, "rt");
	fscanf(in, "%s%d%d%d", pic->name, &pic->m, &pic->n, &pic->max_value);
	for (int i = 0; i < pic->n; i++) {
		for (int j = 0; j < pic->m; j++) {
			fscanf(in, "%d%d%d", &pic->pixel[i][j].R,
				   &pic->pixel[i][j].G, &pic->pixel[i][j].B);
		}
	}
	fclose(in);
}

//Read a image that is type P6
void read_image_rgb_bin(image_rgb *pic, char *name_file)
{
	FILE *in = fopen(name_file, "rb");
	unsigned char value;

	fscanf(in, "%s%d%d%d", pic->name, &pic->m, &pic->n, &pic->max_value);
	fseek(in, SEEK_CUR, 1);
	for (int i = 0; i < pic->n; i++) {
		for (int j = 0; j < pic->m; j++) {
			fread(&value, sizeof(unsigned char), 1, in);
			pic->pixel[i][j].R = value;
			fread(&value, sizeof(unsigned char), 1, in);
			pic->pixel[i][j].G = value;
			fread(&value, sizeof(unsigned char), 1, in);
			pic->pixel[i][j].B = value;
		}
	}
	fclose(in);
}

//Read a image that is type P2
void read_image_gray_text(image_gray *pic, char *name_file)
{
	FILE *in = fopen(name_file, "rt");
	fscanf(in, "%s%d%d%d", pic->name, &pic->m, &pic->n, &pic->max_value);

	for (int i = 0; i < pic->n; i++) {
		for (int j = 0; j < pic->m; j++) {
			fscanf(in, "%d", &pic->pixel[i][j]);
		}
	}
	fclose(in);
}

//Read a image that is type P5
void read_image_gray_bin(image_gray *pic, char *name_file)
{
	FILE *in = fopen(name_file, "rb");
	unsigned char value;
	fscanf(in, "%s%d%d%d", pic->name, &pic->m, &pic->n, &pic->max_value);
	fseek(in, SEEK_CUR, 1);
	for (int i = 0; i < pic->n; i++)
		for (int j = 0; j < pic->m; j++) {
			fread(&value, sizeof(unsigned char), 1, in);
			pic->pixel[i][j] = value;
		}
	fclose(in);
}

//Function that loads a image into memory
void load(image_rgb **rgb, image_gray **gray,
		  int *x1, int *y1, int *x2, int *y2, char *command)
{
	// static int first = 0;
	image_rgb *pic_rgb = *rgb;
	image_gray *pic_g = *gray;
	char name_file[100], name[100];

	strcpy(name_file, command + 5);

	FILE *in = fopen(name_file, "rt");
	int n, m;

	//Verifies that the file exists
	if (!in) {
		printf("Failed to load %s\n", name_file);
		if (pic_rgb)
			free_image_rgb(&pic_rgb);
		if (pic_g)
			free_image_gray(&pic_g);
		*rgb = NULL;
		*gray = NULL;
		return;
	}

	if (pic_rgb)
		free_image_rgb(&pic_rgb);
	if (pic_g)
		free_image_gray(&pic_g);

	fscanf(in, "%s%d%d", name, &m, &n);
	fclose(in);

	//initiate the values for the selection
	*x1 = 0;
	*y1 = 0;
	*x2 = n;
	*y2 = m;

	//Allocs memory for the type needed
	if (name[1] == '3' || name[1] == '6') {
		pic_rgb = alloc_image_rgb(n, m);
		pic_g = NULL;
	} else {
		pic_g = alloc_image_gray(n, m);
		pic_rgb = NULL;
	}

	//Sees what type of file need to be read
	if (name[1] == '3')
		read_image_rgb_text(pic_rgb, name_file);
	else if (name[1] == '6')
		read_image_rgb_bin(pic_rgb, name_file);
	else if (name[1] == '2')
		read_image_gray_text(pic_g, name_file);
	else if (name[1] == '5')
		read_image_gray_bin(pic_g, name_file);

	//Passes the pointers to the main function
	*rgb = pic_rgb;
	*gray = pic_g;

	printf("Loaded %s\n", name_file);
}
