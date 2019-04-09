#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 

int getBlocksize(char *image) {
	int blocksize = 0;
	memcpy(&blocksize, image+8, 2);
	blocksize = htons(blocksize);
	return blocksize;
}

int getBlockcount(char *image) {
	int blockcount = 0;
	memcpy(&blockcount, image+10, 4);
	blockcount = ntohl(blockcount);
	return blockcount;
}

int getFatstart(char *image) {
	int fatstart = 0;
	memcpy(&fatstart, image+14, 4);
	fatstart = ntohl(fatstart);
	return fatstart;
}

int getFatblocks(char *image) {
	int fatblocks = 0;
	memcpy(&fatblocks, image+18, 4);
	fatblocks = ntohl(fatblocks);
	return fatblocks;
}

int getRdirstart(char *image) {
	int rdirstart = 0;
	memcpy(&rdirstart, image+22, 4);
	rdirstart = ntohl(rdirstart);
	return rdirstart;
}

int getRdirblocks(char *image) {
	int rdirblocks = 0;
	memcpy(&rdirblocks, image+26, 4);
	rdirblocks = ntohl(rdirblocks);
	return rdirblocks;
}

void getFreeblocks(char *image) {
	int freeblocks = 0;
	int reserved = 0;
	int allocated = 0;
	int i;
	int temp = 0;

	memcpy(&i, image, 4);
	i = htonl(i);
	image += 4;

	while(temp < 6400) {
		if(i == 0) {
	 		freeblocks++;
		} else if( i == 1) {
			reserved++;
		} else {
			allocated++;
		}
		
		memcpy(&i, image, 4);
		i = htonl(i);
		image +=4;
		temp++;
	}

	printf("Free Blocks: %d\n", freeblocks);
	printf("Reserved Blocks %d\n", reserved);
	printf("Allocated Blocks %d\n", allocated);
	
}

void printResult(int blocksize, int blockcount, int fatstart, int fatblocks, int rdirstart, int rdirblocks) {
	printf("Super block information:\n");
	printf("Block size: %d\n", blocksize);
	printf("Block count: %d\n", blockcount);
	printf("Fat starts: %d\n", fatstart);
	printf("FAT blocks: %d\n", fatblocks);
	printf("Root directory start: %d\n", rdirstart);
	printf("Root directory blocks: %d\n\n", rdirblocks);
	printf("FAT information: \n");
	//printf("free blocks: %d\n", freeblocks);
}

//---------------main--------------------------

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

	// getting info

	int blocksize = getBlocksize(image);
	int blockcount = getBlockcount(image);
	int fatstart = getFatstart(image);
	int fatblocks = getFatblocks(image);
	int rdirstart = getRdirstart(image);
	int rdirblocks = getRdirblocks(image);

	// call to print	
	printResult(blocksize, blockcount, fatstart, fatblocks, rdirstart, rdirblocks);
	getFreeblocks(image + 512*2);

	munmap(image,buffer.st_size);
	close(fd);
}
