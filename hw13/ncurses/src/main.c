#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_TEXT_LEN 256
void sig_winch(int signo)
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
} 

int main(int argc, char ** argv)
{
	char file_path[128];
	puts("Input file path:");
	scanf("%s",file_path);
	int input_st=-1;
	if(access(file_path,0))
	{
		puts("File not found."); 
		char usr_var[4];
		do
		{
			puts("Do you want create new file? (yes or no)");
			scanf("%s",usr_var);
			if(strcmp(usr_var, "yes")==0)
			{
				input_st=1;
				break;
			}
			if(strcmp(usr_var, "no")==0)
			{
				input_st=0;
				break;
			}
		} while(1);
		
		if(input_st==0)
		{
			puts("Exit.");
			exit(0);
		}
	}
	int fd=open(file_path, O_RDWR | O_CREAT, 0644);
	if(fd<0)
	{
		perror("Cannot open file.");
		exit(1);
	}
	
	WINDOW * wnd;
	char text[MAX_TEXT_LEN];
	initscr();
	signal(SIGWINCH, sig_winch);
	curs_set(TRUE);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	wnd = newwin(100, 200, 0, 0);
	wbkgd(wnd, COLOR_PAIR(1));
	wattron(wnd, A_BOLD);
	if(input_st==-1)
	{
		char output_str[MAX_TEXT_LEN];
		read(fd,output_str,MAX_TEXT_LEN);
		wprintw(wnd,output_str,MAX_TEXT_LEN);
		lseek(fd, 0, SEEK_SET);
		for(int i=0;i<strlen(output_str);i++)
			write(fd,"",1);
		lseek(fd, 0, SEEK_SET);
		char nstr[2]="\n";
		wprintw(wnd,nstr,2);
	}
	wprintw(wnd, "Enter new text:\n");
	wgetnstr(wnd, text, MAX_TEXT_LEN);
	write(fd,text,strlen(text));
	delwin(wnd);
	curs_set(FALSE);
	move(20, 5);
	printw("Press any key to continue...");
	refresh();
	getch();
	endwin();
	close(fd);
	
	exit(EXIT_SUCCESS);
}