#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>  //Для getwd
#include <limits.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <curses.h>
#include <sys/stat.h>

void sig_winch(int signo)
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}

void run_interface()
{
	DIR *dir[2];
    struct dirent *entry[2];
	char curr_dir[2][PATH_MAX];
	getcwd(curr_dir[0], PATH_MAX);
	getcwd(curr_dir[1], PATH_MAX);
	//strcat(curr_dir,"/123");
	//printf("Current directory: %s\n", curr_dir);
    dir[0] = opendir(curr_dir[0]);
	if(!dir[0]) 
        exit(1);
	dir[1] = opendir(curr_dir[1]);
	if(!dir[1]) 
        exit(1);
	
	WINDOW * wnd[2];
	initscr();
	curs_set(FALSE);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	wnd[0] = newwin(40, 60, 1, 1);
	wnd[1] = newwin(40, 60, 1, 62);
	wbkgd(wnd[0], COLOR_PAIR(1));
	wbkgd(wnd[1], COLOR_PAIR(1));
	wattron(wnd[0], A_BOLD);
	wattron(wnd[1], A_BOLD);
	signal(SIGWINCH, sig_winch);
	int list_end[2]={0,0};
	char list_files[2][128][PATH_MAX];
	int i=0;
	while((entry[0] = readdir(dir[0]))!= NULL)
	{
		strcpy(list_files[0][i],entry[0]->d_name);
		wprintw(wnd[0], "  %s\n", entry[0]->d_name);
		list_end[0]++;
		i++;
	}
	i=0;
	while((entry[1] = readdir(dir[1]))!= NULL)
	{
		strcpy(list_files[1][i],entry[1]->d_name);
		wprintw(wnd[1], "  %s\n", entry[1]->d_name);
		list_end[1]++;
		i++;
	}
	wrefresh(wnd[0]);
	wrefresh(wnd[1]);

	keypad(stdscr, TRUE);
	int pres_key=0;
	int curr_panel=0;	// press tab for change
	int sel_pos[2]={0,0};
	int x_w=0;
	mvwaddch(wnd[0], sel_pos[0], x_w, '*');
	//mvwaddch(wnd[1], sel_pos, x_w, '*');	// cursor on second panel
	wrefresh(wnd[0]);
	wrefresh(wnd[1]);
	while(1)
	{
		pres_key=getch();
		
		switch(pres_key)
		{
			case KEY_F(10):
			{
				delwin(wnd[0]);
				delwin(wnd[1]);
				refresh();
				curs_set(TRUE);
				endwin();
				closedir(dir[0]);
				closedir(dir[1]);
				exit(0);
			} break;
			case KEY_UP:
			{
				if(sel_pos[curr_panel]>0)
				{
					mvwaddch(wnd[curr_panel], sel_pos[curr_panel], x_w, ' ');
					sel_pos[curr_panel]-=1;
				}
				mvwaddch(wnd[curr_panel], sel_pos[curr_panel], x_w, '*');
				wrefresh(wnd[curr_panel]);
			} break;
			case KEY_DOWN:
			{		
				if(sel_pos[curr_panel]<list_end[curr_panel]-1)
				{
					mvwaddch(wnd[curr_panel], sel_pos[curr_panel], x_w, ' ');
					sel_pos[curr_panel]+=1;
				}
				mvwaddch(wnd[curr_panel], sel_pos[curr_panel], x_w, '*');
				wrefresh(wnd[curr_panel]);
			} break;
			case '\n':
			{
				struct stat st;
				if(stat(list_files[curr_panel][sel_pos[curr_panel]],&st)==0)
				{
					if((st.st_mode & S_IFDIR))
					{
						strcat(curr_dir[curr_panel],"/");
						strcat(curr_dir[curr_panel],list_files[curr_panel][sel_pos[curr_panel]]);
						wclear(wnd[curr_panel]);
						dir[curr_panel] = opendir(curr_dir[curr_panel]);
						if(!dir[curr_panel])
						{
							delwin(wnd[0]);
							delwin(wnd[1]);
							refresh();
							curs_set(TRUE);
							endwin();
							closedir(dir[0]);
							closedir(dir[1]);
							exit(1);
						}		
						sel_pos[curr_panel]=0;
						// "folders" /. OR /..
						char *p=strstr(curr_dir[curr_panel],"/..");
						if(p!=NULL)
						{
							int k=strlen(curr_dir[curr_panel])-1;
							int bck=2;
							while(bck>0)
							{
								curr_dir[curr_panel][k]='\0';
								k--;
								if(k==0)
									break;
								if(curr_dir[curr_panel][k]=='/')
									bck--;
							}
							if(k!=0)
								curr_dir[curr_panel][k]='\0';
						}
						char *t=strstr(curr_dir[curr_panel],"/.");
						if(t!=NULL)
						{
							int l=strlen(curr_dir[curr_panel])-1;
							while(curr_dir[curr_panel][l]!='/')
							{
								curr_dir[curr_panel][l]='\0';
								l--;
								if(l==0)
									break;
							}
							if(l!=0)
								curr_dir[curr_panel][l]='\0';
							continue;
						}
						list_end[curr_panel]=0;
						while((entry[curr_panel] = readdir(dir[curr_panel]))!= NULL)
						{
							wprintw(wnd[curr_panel], "  %s\n", entry[curr_panel]->d_name);
							list_end[curr_panel]++;
						}
						wrefresh(wnd[curr_panel]);
						mvwaddch(wnd[curr_panel], sel_pos[curr_panel], x_w, '*');
					}
				} else {
					//wclear(wnd[curr_panel]);
					//wprintw(wnd[curr_panel], "Cannot open directory");
					wrefresh(wnd[curr_panel]);
				}
			} break;
			case '\t':
			{
				if(sel_pos[curr_panel]>=0)
					mvwaddch(wnd[curr_panel], sel_pos[curr_panel], x_w, ' ');
				sel_pos[curr_panel]=0;
				if(curr_panel==0)
					curr_panel=1;
				else
					curr_panel=0;
				mvwaddch(wnd[curr_panel], sel_pos[curr_panel], x_w, '*');
				wrefresh(wnd[0]);
				wrefresh(wnd[1]);
			} break;
			
			default:
			{} break;
		}
	}
}