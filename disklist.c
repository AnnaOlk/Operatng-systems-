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

void directorylist(char *image) {
	char filetype;
	int status;
	int filesize;
	char* filename;
	int temp = 0;
//time
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	struct dir_entry_timedate_t* time;		
	struct dir_entry_t* t;

	//t = (struct dir_entry_t*)image;
	while(temp < 8) {
		t = (struct dir_entry_t*)image;

		if(filesize = ntohl(t->size) != 0) {
			if((image[11] & 16) == 16) {
				filetype = 'D';
			} else {
				filetype = 'F';
			}
			
			filesize = ntohl(t->size);
			filename = t->filename;

			//-------time ----------

			year = ntohs(t->create_time.year);
			month = t->create_time.month;
			day = t->create_time.day;
			hour = t->create_time.hour;
			minute = t->create_time.minute;
			second = t->create_time.second;
			//--------------------
			printf("%c %10d %20s %04d/%02d/%02d %02d:%02d:%02d\n", filetype, filesize, filename, year, month, day, hour, minute, 					second);
		
		}
		image+= 64;
		temp++;
	}
}

// -----------------------main---------------------------------------

int main(int argc, char* argv[]) {

	if( argc < 2) {
		printf("Error: test.img not found\n");
		exit(1);
	}

	// open disk image
	
	int fd = open(argv[1], O_RDWR);
	
	struct stat buffer;
	int status = fstat(fd, &buffer);

	char* image = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, 			MAP_SHARED, fd, 0);

	directorylist(image+512*53);

	munmap(image,buffer.st_size);
	close(fd);
}
