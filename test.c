#include "libsurround.h"

rgb_color_t red = {0, 0, 255};
rgb_color_t blue = {255, 0, 0};

void make_image(){//makes a 5x5 image with old api; all red image
	char *filename="test.bmp";
//	printf("red is %x\n",red);
	bmp_image_t image=create_bmp(filename,5,5,5,5);
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			set_pixel(i,j,red,image);
		}
	}
	set_pixel(1,1,blue,image);
	fclose(image.fptr);//upside down, will make pixel blue at (3,1)
}

int main(){
	make_image();
	sur_image_t image = sur_image_init_from_file("test.bmp");
	for(int i=0;i<image.height;i++){
		for(int j=0;j<image.width;j++){
			printf("image pixel (%d,%d) is 0x%06x\n",i,j,image.data[i][j]);
		}
	}
	printf("it compiled!!\n");
	
	return 0;
}
