# Operatng-systems-
Csc 360

--------- Overview -----------


I did not implement the sub-directories

Makefile only has Diskinfo, Disklist and Diskget



Diskinfo:

This is fully implemented, the program opens the test.img file, and calls on several functions which access the superblock and read its information using the byte information provided. Next I access the FAT by using the information I obtained from the superblock and using that information I count how many free, reserved and allocated Fat blocks there are.

Disklist:

Using the information I got from the superblock to find out where my root directory started, I skipped over to that area of memeory and used the structures to store the data about that file. I looped through it 8 times because there were 8 root directory blocks but only output the information for files which exited. 

Diskget:

This is not fully implemented. My program can open a file in the current Linux directory named foo.txt, and it can tell if a file does not exist, but my foo.txt output is incorrent in the file. I used the same type of structure as i did in the Disklist to find the file, but could not get the memory to copy into it properly. It displays the letters but they are surrounded by other data.
