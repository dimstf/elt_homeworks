#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phbook.h"

void print_help()
{
	printf("Phone book v1.0\n\n");
	printf("Commands list:\n\n");
	printf("h OR i - help\n");
	printf("e OR q - exit\n");
	printf("p OR l - print all contacts\n");
	printf("f OR s - search contact\n");
	printf("a OR n - add new contact\n");
	printf("d OR r - delete contact\n");
	printf("\n");
}

int prog_comm(char c)
{
	int res=1;
	if((c=='\n')||(c==' '))
		res=0;
	if((c=='e')||(c=='q'))
		res=2;
	if((c=='i')||(c=='h'))
		res=3;
	if((c=='p')||(c=='l'))
		res=4;
	if((c=='a')||(c=='n'))
		res=5;
	if((c=='f')||(c=='s'))
		res=6;
	if((c=='r')||(c=='d'))
		res=7;
	
	return res;
}

void run_prog(int n)
{
	if(n<0)
	{
		printf("Size cannot be less 0. Exit.\n");
		exit(0);
	}
	if(n==0)
	{	// Test mode
		n=16;
		struct phonebook * pb=calloc(n,sizeof(struct phonebook));
		init_phonebook(pb,n);
		add_contact("Alexey","Ivanov","89137775566",n,pb);
		add_contact("Vasiliy","Sokolov","89247774466",n,pb);
		add_contact("Dmitryy","Petrov","89237773366",n,pb);
		add_contact("Ivan","Kuznetsov","89637775522",n,pb);
		add_contact("Alexey","Berezin","89437775555",n,pb);
	
		printf("Before deleting 1 contact:\n");
		print_all(pb,n);
	
		printf("Search contact Vasiliy Sokolov:\n");
		struct phonebook res=find_contact(pb,"Vasiliy","Sokolov",n);
		printf("Name: %s\n",res.name);
		printf("Surname: %s\n",res.surname);
		printf("Phone: %s\n\n",res.phone);
	
		printf("After deleting Vasiliy Sokolov:\n");
		delete_contact(&(pb[1]));
		print_all(pb,n);
	
		exit_program(pb);
	} else {
		struct phonebook * pb=calloc(n,sizeof(struct phonebook));
		init_phonebook(pb,n);
		printf("Ready\n");
		while(1)
		{
			char c;
			scanf("%c",&c);
			int sw=prog_comm(c);
			switch(sw)
			{
				// Empty input
				case(0):
				{}
				break;
				
				// Another input
				case(1):
				{
					printf("Unknows command. Input h OR i for command list.\n");
				}
				break;
				
				// Exit
				case(2):
				{
					exit_program(pb);
				}
				break;
				
				// Help
				case(3):
				{
					print_help();
				}
				break;				
				
				// Print all
				case(4):
				{
					print_all(pb,n);
				}
				break;
				
				// Add new contact
				case(5):
				{
					printf("Input name, surname and phone:\n");
					char name[20];
					char surname[20];
					char phone[20];
					scanf("%s%s%s", name, surname, phone);
					add_contact(name,surname,phone,n,pb);
				}
				break;
				
				// Search contact
				case(6):
				{
					printf("Input name and surname:\n");
					char name[20];
					char surname[20];
					scanf("%s%s", name, surname);
					struct phonebook res=find_contact(pb,name,surname,n);
					printf("Name: %s\n",res.name);
					printf("Surname: %s\n",res.surname);
					printf("Phone: %s\n\n",res.phone);
				}
				break;
				
				// Delete contact
				case(7):
				{
					printf("Input name and surname:\n");
					char name[20];
					char surname[20];
					scanf("%s%s", name, surname);
					int status=1;
					for(int i=0;i<n;i++)
					{
						if((strcmp(pb[i].name,name)==0)&&(strcmp(pb[i].surname,surname)==0))
						{
							delete_contact(&(pb[i]));
							status=0;
							break;
						}
					}
					if(status)
						printf("Cannot find this contact. Nothing has been deleted.\n");
					
				}
				break;
				
				// Another input
				default:
				{
					printf("Unknows command. Input h OR i for command list.\n");
				}
				break;
			}
		}
	}
}
