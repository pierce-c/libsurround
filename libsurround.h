/// @file
#pragma once
#include <xcb/xcb.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
//drawing library is an interface to xcb

typedef struct{
	xcb_window_t *window;
	xcb_screen_t *screen;
	xcb_connection_t *surround_connection;
	//will add more later
}surround_window_t;

typedef struct{
	FILE* fptr;
}bmp_image_t;

typedef int sur_file_t; /// file descriptor

typedef struct rgb_color{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
}rgb_color_t;

typedef struct sur_bitmap{
	sur_file_t fd; /// file descriptor of file it is loaded from, -1 if not loaded from file
	char *pathname; /// pathname of file it is loaded from, NULL if not loaded from file
	uint32_t width; /// width of bitmap
	uint32_t height; /// height of bitmap
	uint32_t *data; /// where the bits are stored
	uint32_t data_len; /// length of data array; calculated from width and height
}sur_bitmap_t;



typedef struct sur_image{
	sur_file_t fd; /// file descriptor of file it is loaded from, -1 if not loaded from file
	char *pathname; /// pathname of file it is loaded from, NULL if not loaded from file
	uint32_t width; /// width of image
	uint32_t height; /// height of image
	// xres and yres are parameters for saving this to a file
	uint32_t **data; /// where the pixels are stored, should be indexed with data[row][column]
}sur_image_t;

int create_window(surround_window_t *win/*params*/);
int free_window(/*params*/);

int drawer_init(/*params*/);
int drawer_exit(/*params*/);

int map_window(/*params*/);
int unmap_window(/*params*/);
/**
	@brief bool enum type; defines false as 0 and true as 1
*/
typedef enum{false,true} bool;

#define curr(fd) (int)lseek(fd,0,SEEK_CUR)

/**
 * @brief prints an error message and exits with EXIT_FAILURE
 * @param format a format string to be printed(no newline required) 
 * @param ... values to be formatted into output string
 */
void err_exit(const char* format,...);


/**
 * @brief prints an error message and exits with EXIT_FAILURE without calling exit handlers
 * @param format a format string to be printed(no newline required)
 * @param ... values to be formatted into output string
 */
void err_exit_alt(const char* format,...);


/**
 * @brief prints an error message
 * @param format a format string to be printed(no newline required)
 * @param ... values to be formatted into output string
 */
void err_msg(const char* format,...);


/**
 * @brief used to inform user of error in command-line argument usage
 * @param format a format string to be printed(newline required)
 * @param ... values to be formatted into the output string
 */
void usage_err(const char* format,...);


/**
 * @brief gets a filename from a pathname
 * allocates a string containing the part of the string in pathname after all the '/' characters
 * ex: given pathname "dir1/dir2/dir3/file1" will return "file1"
 * TODO: make it work with '\'
 * @param pathname pathname to get filename from
 * @param len length of param pathname; for most use cases just set this to strlen(pathname)
 * @return a dynamically allocated string containing the filename
 */
char* filename_from_pathname(const char* pathname,int len);


/*
 * @brief initializes an instance of sur_bitmap_t
 * @param width width of bitmap
 * @param height height of bitmap
 */
sur_bitmap_t sur_bitmap_init(uint32_t width,uint32_t height);
/*
 * @brief initializes an instance of sur_bitmap_t from a file
 * @param pathname the pathname of the file to initialize sur_bitmap_t from
 */
sur_bitmap_t sur_bitmap_init_from_file(const char* pathname);
/*
 * @brief saves the information in sur_bitmap_t to a file
 * @param bitmap bitmap to get information from
 * @param xres x resolution of bitmap in file
 * @param yres y resolution of bitmap in file
 * @param compression compression algorithm to be used or none; TODO: implement this
 * @param filename name of file to store data in
 * @param filetype file format to store data in: TODO: list filetypes that work with it
 */
int sur_bitmap_save_to_file(sur_bitmap_t bitmap,uint32_t xres, uint32_t yres, int compression,
		const char* filename, const char* filetype);

/*
 * @brief free sur_image_t
 * @param image image to free
 */
int sur_bitmap_free(sur_bitmap_t bitmap);




/*
 * @brief initializes an instance of sur_image_t
 * @param width width of image
 * @param height height of image
 */
sur_image_t sur_image_init(uint32_t width,uint32_t height);
/*
 * @brief initializes an instance of sur_image_t from a file
 * @param pathname the pathname of the file to initialize sur_image_t from
 */
sur_image_t sur_image_init_from_file(const char* pathname);
/*
 * @brief saves the information in sur_image_t to a file
 * @param image image to get information from
 * @param xres x resolution of image in file
 * @param yres y resolution of image in file
 * @param compression compression algorithm to be used or none; TODO: implement this
 * @param filename name of file to store data in
 * @param filetype file format to store data in: TODO: list filetypes that work with it
 */
int sur_image_save_to_file(sur_image_t image,uint32_t xres, uint32_t yres, int compression,
		const char* filename, const char* filetype);

/*
 * @brief free sur_image_t
 * @param image image to free
 */
int sur_image_free(sur_image_t image);






/**
 * @brief get width of image
 * @param image image to get width of
 * @return width on success, -1 on failure with errno set accordingly
 */
int bmp_image_get_width(bmp_image_t image);



/**
 * @brief get height of image
 * @param image image to get height of
 * @return height on success, -1 on failure with errno set accordingly
 */
int bmp_image_get_height(bmp_image_t image);


/**
 * @brief get color in rgb of given pixel of given image
 * @param x x-coordinate of pixel
 * @param y y-coordinate of pixel
 * @param image image to get pixel from
 * @return rgb_color_t with first byte as red value, second as green, third as blue, -1 on failure with errno set accordingly
 */
rgb_color_t bmp_image_get_pixel(uint32_t x, uint32_t y, bmp_image_t image);


/**
 * @brief set a pixel to a given color in a given image
 * @param x x-coordinate of pixel
 * @param y y-coordinate of pixel
 * @param color color to set pixel to
 * @param image image to set pixel of
 * @return -1 on failure with errno set accordingly
 */
int set_pixel(uint32_t x, uint32_t y, rgb_color_t color, bmp_image_t image);


/**
 * @brief create and return a bmp file
 * @param filename filename of bmp file to be created
 * @param width width of image to be stored in bmp
 * @param height height of image to be stored in bmp
 * @param xres x resolution of image to be stored in bmp
 * @param yres y resolution of image to be stored in bmp
 * @return file descriptor of image file or -1 on failure with errno set accordingly
 */
bmp_image_t create_bmp(const char* filename, uint32_t width, uint32_t height, uint32_t xres, uint32_t yres);


static int sur_image_init_bmp_from_file(sur_image_t* image);
	//nested function in sur_image_init_from_file




#include "ename.c.inc"
void err_exit(const char* format,...){
	va_list args;
	int bufsize=500;
	char usermsg[bufsize];
	va_start(args,format);
	vsnprintf(usermsg,bufsize,format,args);
	va_end(args);
	fprintf(stderr,"ERROR: %s: %s (%s)\n",usermsg,strerror(errno),(errno>0&&errno<=MAX_ENAME)?ename[errno]:"UNKNOWN");
	fflush(stderr);
	char* s=getenv("EF_DUMPCORE");
	if(s!=NULL&&*s!=(char)0)abort();
	exit(EXIT_FAILURE);
}
void err_exit_alt(const char* format,...){
	va_list args;
	int bufsize=500;
	char usermsg[bufsize];
	va_start(args,format);
	vsnprintf(usermsg,bufsize,format,args);
	va_end(args);
	fflush(stdout);
	fprintf(stderr,"ERROR: %s: %s (%s)\n",usermsg,strerror(errno),(errno>0&&errno<=MAX_ENAME)?ename[errno]:"UNKNOWN");
	fflush(stderr);
	char* s=getenv("EF_DUMPCORE");
	if(s!=NULL&&*s!=(char)0)abort();
	_exit(EXIT_FAILURE);
}
void err_msg(const char* format,...){
	va_list args;
	int bufsize=500;
	char usermsg[bufsize];
	int saved=errno;
	va_start(args,format);
	vsnprintf(usermsg,bufsize,format,args);
	va_end(args);
	fprintf(stderr,"ERROR: %s: %s (%s)\n",usermsg,strerror(errno),(errno>0&&errno<=MAX_ENAME)?ename[errno]:"UNKNOWN");
	fflush(stderr);
	errno=saved;
}
void usage_err(const char* format,...){
	va_list args;
	fflush(stdout);
	fprintf(stderr,"usage: ");
	va_start(args,format);
	vfprintf(stderr,format,args);
	va_end(args);
	fflush(stderr);
	exit(EXIT_FAILURE);
}
char* filename_from_pathname(const char* pathname,int len){
	char* filename;
	int index=0;
	for(int i=0;i<len;i++)
		if(pathname[i]=='/')
			index=i;
	filename=malloc((len-index)*sizeof(char));
	if(!filename)err_exit("malloc");
	if(index==0 && *pathname!='/')index=-1;
	for(int i=0;i<len;i++) filename[i]=pathname[index+i+1];
	return filename;
}
int bmp_image_get_width(bmp_image_t image){
	fseek(image.fptr,0x12,SEEK_SET);
	unsigned int var;
	fread(&var,4,1,image.fptr);
	return var;
}

int bmp_image_get_height(bmp_image_t image){
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
int set_pixel(uint32_t x, uint32_t y, rgb_color_t color, bmp_image_t image){
//int set_pixel(unsigned int x, unsigned int y,unsigned int color, bmp_image_t image){
	int width=bmp_image_get_width(image);
	fseek(image.fptr,0x36+(3*x + y * (3 * width + (4 - (3*width)%4))),SEEK_SET);
	fwrite(&color,3,1,image.fptr);
}

bmp_image_t create_bmp(const char* filename,unsigned int width, unsigned int height,unsigned int xres, unsigned int yres){
	FILE* fp=fopen(filename,"w+");
	fpos_t fpos;
	unsigned int image_size = height*(width*3 + 4 - (3 * width) % 4);
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







sur_image_t sur_image_init(uint32_t width,uint32_t height){
	sur_image_t image;
	image.fd = -1;
	image.width = width;
	image.height = height;
	image.pathname=NULL; // no file name, is not loaded from file
	
	image.data = malloc(height * sizeof(uint32_t*));
	if(image.data == NULL)
		err_exit("malloc");

	for(int i=0;i<height;i++){
		image.data[i] = malloc(width * sizeof(uint32_t));
		if(image.data == NULL)
			err_exit("malloc");
	}

	return image;
}

sur_image_t sur_image_init_from_file(const char* pathname){
	sur_image_t image;
	int fd = open(pathname,O_RDONLY);// open file for read only
	if(fd == -1)
		err_exit("open");
	image.pathname = malloc(strlen(pathname)*sizeof(char));
	// TODO: in the free function make sure to free this as well

	if(!image.pathname)
		err_exit("malloc");

	image.fd = (sur_file_t)fd;
	strcpy(image.pathname,pathname);



	// typically the first two bytes of the file are used to specify file format
	char buffer[3];
	if(read(fd,buffer,2) == -1)
		err_exit("read");
	buffer[2]='\0';
	if(!strcmp(buffer,"BM")){// is a .bmp file
		printf("sur_image_init_from_file: %s is a .bmp file\n", pathname);
		sur_image_init_bmp_from_file(&image);//TODO: add a return checker
	}
	// TODO: implement handlers for more file formats
	else{
		printf("sur_image_init_from_file: unrecognized file format\n");
		exit(EXIT_FAILURE);
	}
	return image;
}


static int sur_image_init_bmp_from_file(sur_image_t* image){
	int fd = (int)image->fd;
	int data_offset;
	int image_size;
	int filesize;
	int calc_size;
	int offset;
	uint32_t temp;
/*	uint32_t temp7;
	uint32_t temp8;
	uint32_t temp9;
	*/
					   // TODO: implement this
					   // TODO: test this works
		
		if(read(fd,&filesize,4) == -1)// getting filesize
			err_exit("read");
		if(lseek(fd,4,SEEK_CUR) == -1)// unused area
			err_exit("lseek");
		if(read(fd,&data_offset,4) == -1)// offset of pixel data
			err_exit("read");
		if(read(fd,&temp,4) == -1)//size of infoheader, should be 40, throw error if not 40
			err_exit("read");
		if(temp != 40){
			printf("error reading file on line %d\n",__LINE__);
			exit(EXIT_FAILURE);
		}
		if(read(fd,&(image->width),4) == -1)// read width into image.width
			err_exit("read");

//		printf("width of image is %d pixels\n",image->width);

		if(read(fd,&(image->height),4) == -1)// read height into image.height
			err_exit("read");

//		printf("height of image is %d pixels\n",image->height);

		if(read(fd,&temp,2) == -1)//number of planes, should be 1, throw error if not 1
			err_exit("read");
		if(temp != 1){
			printf("error reading file on line %d\n",__LINE__);
			exit(EXIT_FAILURE);
		}
		if(read(fd,&temp,2) == -1)//bits per pixel, should be 24, throw error if not 24
								  //TODO: add compatibility with other values {1, 4, 8, 16, 24}
			err_exit("read");

		//here temp is the bits per pixel

		if(read(fd,&temp,4) == -1)
			err_exit("read");
			// compression algorithm, see bmp file format website for specifics
			// currently unused, TODO: implement compression and decompression algorithms

		//here temp corresponds to a compression algorithm
		
		if(read(fd,&image_size,4) == -1)// image size in bytes of the data part of the file
			err_exit("read");
		calc_size = image->height * (image->width*3 + 4 - (image->width * 3) % 4);
		if(!(image_size == calc_size)){//error with image
			printf("error reading file on line %d\n",__LINE__);
			exit(EXIT_FAILURE);
		}

		if(lseek(fd,8,SEEK_CUR) == -1)
			//skipping over the horizontal and vertical resolution (not needed here)
			err_exit("lseek");




		if(read(fd,&temp,4) == -1)//number of colors in image, important for color table
								  //TODO: currently not implementation for this
			err_exit("read");

		//here temp is the number of colors in the image
		
		if(lseek(fd,4,SEEK_CUR) == -1)//unimportant
			err_exit("lseek");

		//here there should be a colortable for certain values of 'bpp' 
		// ( important for something yet to implement )
		
		//printf("data offset is %d\n",data_offset);
		if(lseek(fd,data_offset,SEEK_SET) == -1)
			err_exit("lseek");
		
		image->data = malloc(image->height * sizeof(uint32_t*));
		if(image->data == NULL)
			err_exit("malloc");
		for(int i = 0;i < image->height;i++){
			image->data[i] = malloc(image->width * sizeof(uint32_t));
			if(image->data[i] == NULL)
				err_exit("malloc");
			for(int j = 0; j<image->width;j++){
				offset = data_offset + 3*j + (image->height - i-1) * (3 * image->width + (4 - 3*image->width%4));
				//offset of pixel neccessary
				if(lseek(fd,offset,SEEK_SET) == -1)
					err_exit("lseek");
				if(read(fd,&image->data[i][j],3) == -1)
					err_exit("lseek");
				/*
				temp7 = image->data[i][j] & 0xff;
				temp8 = image->data[i][j] & 0xff00;
				temp9 = image->data[i][j] & 0xff0000;
				
				image->data[i][j] = (temp7 << 16) | (temp8) | (temp9 >> 16);
				*/
			}

		}



	return 0;
}
int sur_image_save_to_file(sur_image_t image,uint32_t xres, uint32_t yres, int compression,
		const char* filename, const char* filetype){
	int fd = open(image.pathname, O_RDWR);
	if(fd == -1)
		err_exit("open");
	// TODO: actually make this function do its intended purpose
	if(close(fd))
		err_exit("close");
	return 0;
}
