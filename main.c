//Neacsa Leonard 315CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"
#include "image.h"
#include "alloc_free.h"
#include "error_utils.h"

int main(void)
{
	char command[100];
	image_gray *pic_g = NULL;
	image_rgb *pic_rgb = NULL;
	int ok = 1, x1, x2, y1, y2;

	while (ok) {
		fgets(command, 100, stdin);
		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = 0;
		if (strstr(command, "LOAD"))
			load(&pic_rgb, &pic_g, &x1, &y1, &x2, &y2, command);
		else if (strstr(command, "SELECT")) {
			select(pic_rgb, pic_g, &x1, &y1, &x2, &y2, command);
		} else if (strstr(command, "SAVE")) {
			save(pic_rgb, pic_g, command);
		} else if (strstr(command, "APPLY")) {
			apply(&pic_rgb, &pic_g, &x1, &y1, &x2, &y2, command);
		} else if (strstr(command, "EQUALIZE")) {
			equalize(&pic_rgb, &pic_g);
		} else if (strstr(command, "HISTOGRAM")) {
			histogram(&pic_rgb, &pic_g, command);
		}  else if (strstr(command, "CROP")) {
			crop(&pic_rgb, &pic_g, &x1, &y1, &x2, &y2);
		} else if (strstr(command, "EXIT")) {
			test_memory(pic_rgb, pic_g);
			ok = 0;
		} else if (strstr(command, "ROTATE")) {
			rotate(&pic_rgb, &pic_g, &x1, &y1, &x2, &y2, command);
		} else
			invalid_command();
	}
	if (pic_g)
		free_image_gray(&pic_g);
	else if (pic_rgb)
		free_image_rgb(&pic_rgb);
	return 0;
}
