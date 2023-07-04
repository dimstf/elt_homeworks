#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
	char input_str[13]="Hello, world!";
	
	int fd=open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if(fd<0) 
	{ 
		perror("Cannot open file (write)."); 
		exit(1); 
	} 
	
	if(write(fd,input_str,13)!=13)
		perror("Write Error");
	close(fd);
	
	char output_str[13]="";
		
	if ((fd=open("test.txt", O_RDONLY, S_IRWXO))==-1) 
	{
		perror("Cannot open file (read).");
		exit(1);
	}
	
	if(read(fd,output_str,13)!=13)
		perror("Read Error");
	puts(output_str);
	
	return 0;
}