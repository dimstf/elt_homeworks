#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct phonebook
{
	char name[20];
	char surname[20];
	char phone[20];
};

int is_empty(struct phonebook *checked)
{
	if((strlen(checked->name)==0)&&(strlen(checked->surname)==0)&&(strlen(checked->phone)==0))
	{
		return 1;
	}
	return 0;
}

struct phonebook find_contact(struct phonebook *pb, char * name, char * surname, int n)
{
	struct phonebook founded;
	memset(founded.name, 0, 20);
	memset(founded.surname, 0, 20);
	memset(founded.phone, 0, 20);

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

void add_contact(char * name, char * surname, char * phone, int n, struct phonebook *pb)
{
	int i=0;
	
	int status=0;
	for(int i=0;i<n;i++)
	{
		if((strcmp(pb[i].name,name)==0)&&(strcmp(pb[i].surname,surname)==0))
		{
			status=1;
			break;
		}
	}
	if(status)
	{
		printf("Cannot add contact. Contact with this name and surname already exists.\n");
		return;
	}

	for(i=0;i<n;i++)
	{
		if(is_empty(&pb[i]))
			break;
	}
	if((is_empty(&pb[i]))&&(i<n))
	{
		strncpy(pb[i].name,name,20);
		strncpy(pb[i].surname,surname,20);
		strncpy(pb[i].phone,phone,20);
		printf("The contact was succesfully created.\n");		
	} else {
		printf("Cannot add contact. Not enought space.\n");
	}
}

void delete_contact(struct phonebook *contact)
{
	if(!is_empty(contact))
	{
		memset(contact->name, 0, 20);
		memset(contact->surname, 0, 20);
		memset(contact->phone, 0, 20);
		printf("The contact was succesfully deleted.\n");
	} else {
		printf("Cannot find this contact. Nothing has been deleted.\n");
	}
}

void print_all(struct phonebook *pb, int n)
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

void init_phonebook(struct phonebook *pb, int n)
{
	for(int i=0;i<n;i++)
	{
		memset(pb[i].name, 0, 20);
		memset(pb[i].surname, 0, 20);
		memset(pb[i].phone, 0, 20);
	}
}
