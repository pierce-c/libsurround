#include "libsurround.h"
#include <math.h>

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

void swap(int* x,int* y){
	int temp = *x;
	*x = *y;
	*y = temp;
}
int abs(x){
	if(x<0)
		return ~x + 1;
	return x;
}
void draw_line(int x0, int y0, int x1, int y1, sur_image_t image, uint32_t color){
	bool steep = false;
	if(abs(y1-y0)>abs(x1-x0)){
		swap(&x0,&y0);
		swap(&x1,&y1);
		steep = true;
	}
	if(x0>x1){
		swap(&x0,&x1);
		swap(&y0,&y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;
	if(dy < 0){
		yi = -1;
		dy = -dy;
	}
	int D = (dy<<1) - dx;
	int y = y0;
	for(int x=x0; x<x1;x++){
		if(steep)
			image.data[x][y] = color;
		else
			image.data[y][x] = color;
		if(D>0){
			y += yi;
			D += (dy - dx)<<1;
		}
		else
			D += dy;
	}
}


int main(){
//	make_image();
	sur_image_t image = sur_image_init(100,100);
	for(int i=0;i<image.height;i++){
		for(int j=0;j<image.width;j++){
			image.data[i][j] = 0x00ff00;
			//image.data[i][j] = 0x1dcf52;
			//if(i == j || i+j==9)
			//	image.data[i][j] = 0xe82372;
		}
	}
//	image.data[0][1] = 0xff00;
	draw_line(10,10,50,50,image,0xff0000);
	sur_image_save_to_file(image, 10000, 10000,"test.bmp");
	
	printf("it compiled!!\n");
	
	return 0;
}
