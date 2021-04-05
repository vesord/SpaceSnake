#include "bmp.h"
#include "stdlib.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void fixImage(unsigned char * image, int width, int height, int channels) {
	int size = width * height * channels;
	char tmp;
	for (int i = 0; i < size; i += channels) {
		tmp = image[i];
		image[i] = image[i + 2];
		image[i + 2] = tmp;
	}
}

int		create_bmp_img_write(t_bmp_file_header *bfh, t_bmp_info *bmi,
								char *data)
{
	int		fd;

	fd = open("cub.bmp", O_RDWR | O_CREAT, 0755);
	if (fd < 0)
		return (0);
	write(fd, &(bfh->type_1), 1);
	write(fd, &(bfh->type_2), 1);
	write(fd, &(bfh->size), 4);
	write(fd, &(bfh->reserved), 4);
	write(fd, &(bfh->offset_to_color_bits), 4);
	write(fd, &(bmi->size), 4);
	write(fd, &(bmi->width), 4);
	write(fd, &(bmi->height), 4);
	write(fd, &(bmi->planes), 2);
	write(fd, &(bmi->btp), 2);
	write(fd, &(bmi->compression), 4);
	write(fd, &(bmi->img_size), 4);
	write(fd, &(bmi->ppm_x), 4);
	write(fd, &(bmi->ppm_y), 4);
	write(fd, &(bmi->color_table), 4);
	write(fd, &(bmi->color_table_size), 4);
	char *dummy = calloc(1, bmi->size - 40);
	write(fd, dummy, bmi->size - 40);
	free(dummy);
	write(fd, data, bmi->img_size);
	close(fd);
	return (1);
}

unsigned char *myBMPLoader(const char *filename, int *width, int *height, int *channels) {
	int fd;
	t_bmp_file_header	bfh;
	t_bmp_info			bmi;
	unsigned char *		data = NULL;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		printf("can't open file %s\n", filename);
		exit(1);
	}

	read(fd, &(bfh.type_1), 1);
	read(fd, &(bfh.type_2), 1);
	read(fd, &(bfh.size), 4);
	read(fd, &(bfh.reserved), 4);
	read(fd, &(bfh.offset_to_color_bits), 4);
	read(fd, &(bmi.size), 4);
	read(fd, &(bmi.width), 4);
	read(fd, &(bmi.height), 4);
	read(fd, &(bmi.planes), 2);
	read(fd, &(bmi.btp), 2);
	read(fd, &(bmi.compression), 4);
	read(fd, &(bmi.img_size), 4);
	read(fd, &(bmi.ppm_x), 4);
	read(fd, &(bmi.ppm_y), 4);
	read(fd, &(bmi.color_table), 4);
	read(fd, &(bmi.color_table_size), 4);

	data = malloc(bmi.img_size);
	if (!data)
		exit(1);

	lseek(fd, bmi.size - 40, SEEK_CUR);
	read(fd, data, bmi.img_size);

	close(fd);
	*width = bmi.width;
	*height = bmi.height;
	*channels = bmi.btp >> 3;

	return data;
}
