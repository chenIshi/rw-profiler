#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdlib.h> 
#include <string.h> 
//
//	test program for IO profiler
//

typedef enum _bool Bool;
enum _bool {
	true,
	false,
};

Bool reader();
Bool writer();

char buf [1024] = {};

int wc() {
	return 0;
}

int main() {
	if (reader() == true) {
		writer();
	} else {
		return 1;
	}
	return 0;
}


Bool reader() {
	int in_file = open("input.txt", O_RDONLY);
	// FILE *in_file  = open("input.txt", "r");
	if (in_file < 0) {
		fprintf(stderr, "error in reading input file\n");
		return false;
	} else {
		if (read(in_file, &buf, 1024) < 0) {
			fprintf(stderr, "error in read function call\n");
			close(in_file);
			return false;
		}
		close(in_file);
	}
	return true;
}

Bool writer() {
	int out_file  = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
	if (out_file < 0) {
		fprintf(stderr, "error in creating output file\n");
		return false;
	} else {
		if (write(out_file, &buf, 1024) < 0) {
			fprintf(stderr, "error in write function call\n");
			close(out_file);
			return false;
		}
		close(out_file);
	}
	return true;
}

/*   
    int main(int argc,char *args[]) { 
        char buff[1024]; 
        int fd1,fd2,i; 
        int baksize = sizeof(args[1])+7; 
        char bakfile[baksize]; 
    // input one file only 
        if(argc != 2){ 
            printf("Input one file a time!\n"); 
            exit(1); 
        } 
    //bakfile="XXX.backup"设置备份文件名称 
        strcpy(bakfile,args[1]); 
        strcat(bakfile,".backup"); 
    //open() 
        fd1 = open("input.txt",O_RDONLY); 
        fd2 = open("output.txt",O_RDWR|O_CREAT|O_TRUNC); 
        if(fd1 < 0){ 
            printf("Open Error-1!Check if the file is exist and you have the permission!\n"); 
            exit(1); 
        } else if (fd2 < 0) {
			printf("Open Error-2!Check if the file is exist and you have the permission!\n"); 
            exit(1); 
		}
    //read from fd1 and write buff to fd2 
        while((i = read(fd1,buff,sizeof(buff))) > 0) { 
        write(fd2,buff,i);//这里需要用读取到的字符数,否则会出错,因为buff数组有可能未被全覆盖 
        } 
        close(fd1); 
        close(fd2); 
        printf("Backup done!\n"); 
        exit(0); 
         
    } 
	*/