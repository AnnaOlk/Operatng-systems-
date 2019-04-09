# Operatng-systems-
Csc 360

3 Requirements
17 3.1 Part I (3 points)
18 In part I, you will write a program that displays information about the file system. In order to complete part I, you
19 will need to read the file system super block and use the information in the super block to read the FAT.
20 Your program for part I will be invoked as follows (output value just for illustration purposes):
./diskinfo test.img
21 Sample output:
Super block information:
Block size: 512
Block count: 5120
FAT starts: 1
1
FAT blocks: 40
Root directory start: 41
Root directory blocks: 8
FAT information:
Free Blocks: 5071
Reserved Blocks: 41
Allocated Blocks: 8
22 Please be sure to use the exact same output format as shown above.
23 3.2 Part II (4 points)
24 In part II, you will write a program, with the routines already implemented for part I, that displays the contents of
25 the root directory or a given sub-directory in the file system.
26 Your program for part II will be invoked as follows:
./disklist test.img /sub_dir
27 The directory listing should be formatted as follows:
28 1. The first column will contain:
29 (a) F for regular files, or
30 (b) D for directories;
31 followed by a single space
32 2. then 10 characters to show the file size, followed by a single space
33 3. then 30 characters for the file name, followed by a single space
34 4. then the file modification date (we will not display the file creation date).
For example:
F 2560 foo.txt 2005/11/15 12:00:00
F 5120 foo2.txt 2005/11/15 12:00:00
F 48127 makefs 2005/11/15 12:00:00
F 8 foo3.txt 2005/11/15 12:00:00
35 3.3 Part III (4 points)
36 In part III, you will write a program that copies a file from the file system to the current directory in Linux. If the
37 specified file is not found in the root directory or a given sub-directory of the file system, you should output the
38 message File not found. and exit.
39 Your program for part III will be invoked as follows:
./diskget test.img /sub_dir/foo2.txt foo.txt
