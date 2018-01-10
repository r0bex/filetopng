/* r0bex - 2018
 * This program uses the std_image_write library, found at
 * https://github.com/nothings/stb by Sean T. Barrett et al */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct file_size {
	int size;
	char *data;
};

struct file_size file_to_bytes(char *filename)
{
	FILE             *f;
	struct file_size fdata;
	int              fsize;

	// check if the file is valid
	if ((f = fopen(filename, "r")) == NULL) {
		printf("error opening the file, aborting...\n");
		exit(0);
	}
	
	// get size of file beforehand to allocate mem
	fseek(f, 0L, SEEK_END);
	fsize = ftell(f);
	rewind(f);

	fdata.data = malloc(fsize * sizeof(char));
	fdata.size = fread(fdata.data, 1, fsize, f);
	if (fdata.size == 0) {
		printf("error reading the file, aborting...");
		exit(0);
	}
	fclose(f);
	return fdata;
}

int main(int argc, char *argv[])
{
	int              imside;
	struct file_size f;

	if (argc == 1) {
		printf("usage: ./filetopng [filename]\n");
		return 0;
	}

	f = file_to_bytes(argv[1]);

	//calculate the length of the side for a square
	imside = ceil(sqrt(f.size));

	stbi_write_png("out.png", imside, imside, 1, f.data, imside);
	free(f.data);
}
