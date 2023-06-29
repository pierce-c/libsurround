#include "libsurround.h"

int main(){
	
	char *filename="test.bmp";
	rgb_color_t red = {0, 0, 255};
	printf("red is %x\n",red);
	bmp_image_t image=create_bmp(filename,5,5,5,5);
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			set_pixel(i,j,red,image);
		}
	}


	fclose(image.fptr);
	
	
	printf("it compiled!!\n");
	
	return 0;
}
