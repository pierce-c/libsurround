#include <stdio.h>
#include <unistd.h>

unsigned int bmp_image_get_width(bmp_image_t image){
	fseek(image.fptr,0x12,SEEK_SET);
	unsigned int var;
	fread(&var,4,1,image.fptr);
	return var;
}

unsigned int bmp_image_get_height(bmp_image_t image){
	fseek(image.fptr,0x16,SEEK_SET);
	unsigned int var;
	fread(&var,3,1,image.fptr);
	return var;
}
unsigned int get_pixel(unsigned int x, unsigned int y,bmp_image_t image){
	unsigned int res;
	fseek(image.fptr,0x36+(3*(x+(bmp_image_get_width(image)*y))),SEEK_SET);
	fread(&res,3,1,image.fptr);
	return res;
}
void set_pixel(unsigned int x, unsigned int y,unsigned int color, bmp_image_t image){
	fseek(image.fptr,0x36+(3*(x+(bmp_image_get_width(image)*y))),SEEK_SET);
	fwrite(&color,3,1,image.fptr);
}
bmp_image_t create_bmp(unsigned int width, unsigned int height,unsigned int xres, unsigned int yres){
	FILE* fp=fopen("image.bmp","w+");
	fpos_t fpos;
	unsigned int image_size=width*height*4;
	unsigned int var=0x36+image_size;
	fputc('B',fp);
	fputc('M',fp);
	fwrite(&var, 4,1,fp);
	var=0;
	fwrite(&var,4,1,fp);
	var=0x36;
	fwrite(&var,4,1,fp);
	var=40;
	fwrite(&var,4,1,fp);
	fwrite(&width,4,1,fp);
	fwrite(&height,4,1,fp);
	var=1;
	fwrite(&var,2,1,fp);
	var=24;
	fwrite(&var,2,1,fp);
	var=0;
	fwrite(&var,4,1,fp);
	fwrite(&image_size,4,1,fp);
	fwrite(&xres,4,1,fp);
	fwrite(&yres,4,1,fp);
	var=1;
	fwrite(&var,4,1,fp);
	var=0;
	fwrite(&var,4,1,fp);
	bmp_image_t bmp_image;
	bmp_image.fptr=fp;
	return bmp_image;
}
/*int main(){
	bmp_image_t test_image = create_bmp(8,8,1890,1890);
	unsigned int width = bmp_image_get_width(test_image);
	unsigned int height = bmp_image_get_height(test_image);
	for(unsigned int i=0;i<8;i++){
		for(unsigned int j=0;j<8;j++){
			set_pixel(i,j,0xffffff,test_image);
		}
	}
	set_pixel(0,0,0x0,test_image);
	set_pixel(1,1,0xff,test_image);
	set_pixel(2,2,0xffff,test_image);
	fclose(test_image.fptr);
	return 0;
}
	
*/
