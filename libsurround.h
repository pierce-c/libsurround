#pragma once
#include <xcb/xcb.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

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
typedef struct sur_file{
	int fd;
	off_t offset;
}sur_file_t;

int create_window(surround_window_t *win/*params*/);
int free_window(/*params*/);

int drawer_init(/*params*/);
int drawer_exit(/*params*/);

int map_window(/*params*/);
int unmap_window(/*params*/);
/*
	@brief bool enum type; defines false as 0 and true as 1
*/
typedef enum{false,true} bool;

#define curr(fd) lseek(fd,0,SEEK_CUR);

/*
 * @brief prints an error message and exits with EXIT_FAILURE
 * @param format a format string to be printed(no newline required) 
 * @param ... values to be formatted into output string
 */
 
void err_exit(const char* format,...);



void err_exit_alt(const char* format,...);



void err_msg(const char* format,...);



void usage_err(const char* format,...);



char* filename_from_pathname(const char* pathname,int len);


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
#define tell(fd) lseek(fd,0,SEEK_CUR);


typedef struct{
	FILE* fptr;
}bmp_image_t;


unsigned int bmp_image_get_width(bmp_image_t image);
unsigned int bmp_image_get_height(bmp_image_t image);
unsigned int get_pixel(unsigned int x, unsigned int y,bmp_image_t image);
void set_pixel(unsigned int x, unsigned int y,unsigned int color, bmp_image_t image);
bmp_image_t create_bmp(unsigned int width, unsigned int height,unsigned int xres, unsigned int yres);
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
