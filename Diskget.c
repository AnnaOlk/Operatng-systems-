#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 
#include <limits.h> 
#include <assert.h> 
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

struct __attribute__((__packed__)) dir_entry_timedate_t {
  uint16_t year;
  uint8_t  month;
  uint8_t  day;
  uint8_t  hour;
  uint8_t  minute;
  uint8_t  second;
};

struct __attribute__((__packed__)) dir_entry_t {
  uint8_t                       status;
  uint32_t                      starting_block;
  uint32_t                      block_count;
  uint32_t                      size;
  struct   dir_entry_timedate_t modify_time;
  struct   dir_entry_timedate_t create_time;
  uint8_t                       filename[31];
  uint8_t                       unused[6];
};

int cpy(char* image, char* name){
	int filesize1;
	char* filename1;
	int filesize2;
	char* filename2;
	int temp = 0;
	int found = 0;
	int count = 0;
	int i;
	int starting_block;
	char* orig_image;
	int hold;


	struct dir_entry_t* t;
	
	orig_image = image;

	while(temp < 8) {
		t = (struct dir_entry_t*)image;

		if(filesize1 = ntohl(t->size) != 0) {
			
			filesize1 = ntohl(t->size);
			filename1 = t->filename;	
			
			if(strcmp(filename1, name) == 0){
//----------------------------------------------------------------------------
				FILE *fd1;
				fd1 = fopen(name, "w");
				image = orig_image + ntohl(t->starting_block);
				fwrite(image, 4, filesize1, fd1);
				
//------------------------------------------------------------------
				found = 1;
				break;
			}
		
		}

		image+= 64;
		temp++;
	}

	if(found == 0){
		return 1;	
	} else {
		return 0;
	}



}

// ------------------------ main ----------------------------
int main(int argc, char* argv[]) {
	int returned;

	if( argc < 3) {
		printf("Error: include test.img and 2 other input files\n");
		exit(1);
	}

	// open disk image 1
	
	int fd = open(argv[1], O_RDWR);
	
	struct stat buffer;
	int status = fstat(fd, &buffer);

	char* image = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	returned = cpy(image+512*53, argv[2]);

	if(returned == 1) {
		printf("File Not Found\n");
		exit(1);
	}

	munmap(image,buffer.st_size);
	close(fd);
}
