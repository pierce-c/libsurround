
typedef struct{
	FILE* fptr;
}bmp_image_t;


unsigned int bmp_image_get_width(bmp_image_t image);
unsigned int bmp_image_get_height(bmp_image_t image);
unsigned int get_pixel(unsigned int x, unsigned int y,bmp_image_t image);
void set_pixel(unsigned int x, unsigned int y,unsigned int color, bmp_image_t image);
bmp_image_t create_bmp(unsigned int width, unsigned int height,unsigned int xres, unsigned int yres);
