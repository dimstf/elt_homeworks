#if !defined phbook_h
#define phbook_h
struct phonebook
{
	char name[20];
	char surname[20];
	char phone[20];
};
int is_empty(struct phonebook *checked);
struct phonebook find_contact(struct phonebook *pb, char * name, char * surname, int n);
void add_contact(char * name, char * surname, char * phone, int n, struct phonebook *pb);
void delete_contact(struct phonebook *contact);
void print_all(struct phonebook *pb, int n);
void exit_program(struct phonebook *pb);
void init_phonebook(struct phonebook *pb, int n);
#endif
