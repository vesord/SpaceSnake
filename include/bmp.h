#ifndef SPACESNAKE_BMP_H
#define SPACESNAKE_BMP_H

typedef struct	s_bmp_file_header
{
	char	type_1;
	char	type_2;
	int		size;
	int		reserved;
	int		offset_to_color_bits;
}				t_bmp_file_header;

typedef struct	s_bmp_info
{
	int		size;
	int		width;
	int		height;
	short	planes;
	short	btp;
	int		compression;
	int		img_size;
	int		ppm_x;
	int		ppm_y;
	int		color_table;
	int		color_table_size;
}				t_bmp_info;

unsigned char *myBMPLoader(const char *filename, int *width, int *height, int *channels);
void fixImage(unsigned char * image, int width, int height, int channels);

#endif //SPACESNAKE_BMP_H
