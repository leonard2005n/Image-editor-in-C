#Neacsa Leonard 315CA
# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g
TARGETS=main.c error_utils.c load.c alloc_free.c save.c select.c crop.c rotate.c apply.c equalize.c histogram.c
NAME = image_editor

build: $(TARGETS)
	$(CC) $(CFLAGS) $(TARGETS) -o $(NAME) -lm
pack:
	zip -FSr 315CA_NeacsaLeonard_Tema3.zip README Makefile *.c *.h
clean:
	rm -f $(NAME)
.PHONY: pack clean
