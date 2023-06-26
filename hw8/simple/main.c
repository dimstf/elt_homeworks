#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int n=16;

struct phonebook
{
	char name[20];
	char surname[20];
	char phone[20];
};

struct phonebook add_contact(char * name, char * surname, char * phone)
{
	struct phonebook contact;
	strncpy(contact.name,name,20);
	strncpy(contact.surname,surname,20);
	strncpy(contact.phone,phone,20);
	
	return contact;
}

void delete_contact(struct phonebook *contact)
{
	memset(contact->name, 0, 20);
	memset(contact->surname, 0, 20);
	memset(contact->phone, 0, 20);
}

struct phonebook find_contact(struct phonebook *pb, char * name, char * surname)
{
	struct phonebook founded;
	for(int i=0;i<n;i++)
	{
		if((strcmp(pb[i].name,name)==0)&&(strcmp(pb[i].surname,surname)==0))
		{
			founded=pb[i];
			break;
		}
	}
	
	return founded;
}

void print_all(struct phonebook *pb)
{
	for(int i=0;i<n;i++)
	{
		if((strlen(pb[i].name)!=0)&&(strlen(pb[i].surname)!=0)&&(strlen(pb[i].phone)!=0))
		{
			printf("Name: %s\n",pb[i].name);
			printf("Surname: %s\n",pb[i].surname);
			printf("Phone: %s\n\n",pb[i].phone);
		}
	}
}

void exit_program(struct phonebook *pb)
{
	free(pb);
	printf("Exit.\n");
	exit(0);
}

void init_phonebook(struct phonebook *pb)
{
	for(int i=0;i<n;i++)
	{
		memset(pb[i].name, 0, 20);
		memset(pb[i].surname, 0, 20);
		memset(pb[i].phone, 0, 20);
	}
}

int main()
{
	struct phonebook * pb=calloc(n,sizeof(struct phonebook));
	init_phonebook(pb);
	pb[0]=add_contact("Alexey","Ivanov","89137775566");
	pb[1]=add_contact("Vasiliy","Sokolov","89247774466");
	pb[2]=add_contact("Dmitryy","Petrov","89237773366");
	pb[5]=add_contact("Ivan","Kuznetsov","89637775522");
	pb[9]=add_contact("Alexey","Berezin","89437775555");
	
	printf("Before deleting 1 contact:\n");
	print_all(pb);
	
	printf("Search contact Vasiliy Sokolov:\n");
	struct phonebook res=find_contact(pb,"Vasiliy","Sokolov");
	printf("Name: %s\n",res.name);
	printf("Surname: %s\n",res.surname);
	printf("Phone: %s\n\n",res.phone);
	
	printf("After deleting Vasiliy Sokolov:\n");
	delete_contact(&(pb[1]));
	print_all(pb);
	
	exit_program(pb);
	return 0;
}
