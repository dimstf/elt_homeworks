#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

int get_name_of_operation(char * fp)
{
	if(strstr(fp,"libadd.so")!=NULL)
		return 0;
	if(strstr(fp,"libsub.so")!=NULL)
		return 1;
	if(strstr(fp,"libmul.so")!=NULL)
		return 2;
	if(strstr(fp,"libdiv.so")!=NULL)
		return 3;
	
	return -1;
}

void print_supported_operations(int st_add, int st_sub, int st_mul, int st_div)
{
	if(st_add==1)
		puts("Add +");
	if(st_sub==1)
		puts("Sub -");
	if(st_mul==1)
		puts("Mul *");
	if(st_div==1)
		puts("Div /");
}

void run_calculator_interface()
{
	puts("Example: 2.07+3.5");
	double num1=0.0, num2=0.0;
	char ms;
	puts("Input count of modules:");
	int n=0,i=0;
	scanf("%d",&n);
	if(n<1)
	{
		puts("No modules. Exit");
		exit(0);
	}
	char file_paths[80];
	char path_add[80];
	char path_sub[80];
	char path_mul[80];
	char path_div[80];
	int status_add=0, status_sub=0;
	int status_mul=0, status_div=0;
	for(i=0;i<n;i++)
	{
		puts("Input module file path:");
		scanf("%s",file_paths);
		if(access(file_paths,0))
		{
			puts("File not Found");
			i--;
			continue;
		}
		int st=get_name_of_operation(file_paths);
		switch(st)
		{
			case -1:
			{
				puts("Not a calculator module.");
				i--;
			} break;
			case 0:
			{
				if(status_add!=0)
				{
					puts("Lib libadd.so is already been added.");
					memset(file_paths,0,80);
					i--;
				} else {
					status_add=1;
					strncpy(path_add,file_paths,80);
				}
			} break;
			
			case 1:
			{
				if(status_sub!=0)
				{
					puts("Lib libsub.so is already been added.");
					memset(file_paths,0,80);
					i--;
				} else {
					status_sub=1;
					strncpy(path_sub,file_paths,80);
				}
			} break;
			
			case 2:
			{
				if(status_mul!=0)
				{
					puts("Lib libmul.so is already been added.");
					memset(file_paths,0,80);
					i--;
				} else {
					status_mul=1;
					strncpy(path_mul,file_paths,80);
				}
			} break;
			
			case 3:
			{
				if(status_div!=0)
				{
					puts("Lib libdiv.so is already been added.");
					memset(file_paths,0,80);
					i--;
				} else {
					status_div=1;
					strncpy(path_div,file_paths,80);
				}
			} break;
			default:
			{
				puts("Error.");
			} break;
		}
	}
	print_supported_operations(status_add, status_sub, status_mul, status_div);
	puts("Input expression:");
	scanf("%lf%c%lf", &num1, &ms, &num2);
	void *handle;
	char *error;
	
	switch(ms)
	{
		case('+'):
		{
			if(status_add!=1)
			{
				puts("Error. The module is not connected. Exit.");
				exit(0);
			}
			handle = dlopen(path_add, RTLD_LAZY);
			if (!handle) 
			{
				fprintf(stderr, "%s\n", dlerror());
				exit(1);
			}
			dlerror();
			double (*calculate_result)(double, double)=dlsym(handle, "calculate_addition");;
			double result=calculate_result(num1, num2);
			printf("%lf + %lf = %lf\n", num1, num2, result);
			dlclose(handle);
		} break;
		case('-'):
		{
			if(status_sub!=1)
			{
				puts("Error. The module is not connected. Exit.");
				exit(0);
			}
			handle = dlopen(path_sub, RTLD_LAZY);
			if (!handle) 
			{
				fprintf(stderr, "%s\n", dlerror());
				exit(1);
			}
			dlerror();
			double (*calculate_result)(double, double)=dlsym(handle, "calculate_subtraction");
			double result=calculate_result(num1, num2);
			printf("%lf - %lf = %lf\n", num1, num2, result);
			dlclose(handle);
		} break;
		case('*'):
		{
			if(status_mul!=1)
			{
				puts("Error. The module is not connected. Exit.");
				exit(0);
			}
			handle = dlopen(path_mul, RTLD_LAZY);
			if (!handle) 
			{
				fprintf(stderr, "%s\n", dlerror());
				exit(1);
			}
			dlerror();
			double (*calculate_result)(double, double)=dlsym(handle, "calculate_multiplication");
			double result=calculate_result(num1, num2);
			printf("%lf * %lf = %lf\n", num1, num2, result);
			dlclose(handle);
		} break;
		case('/'):
		{
			if(status_div!=1)
			{
				puts("Error. The module is not connected. Exit.");
				exit(0);
			}
			handle = dlopen(path_div, RTLD_LAZY);
			if (!handle) 
			{
				fprintf(stderr, "%s\n", dlerror());
				exit(1);
			}
			dlerror();
			double (*calculate_result)(double, double)=dlsym(handle, "calculate_division");
			double result=calculate_result(num1, num2);
			printf("%lf / %lf = %lf\n", num1, num2, result);
			dlclose(handle);
		} break;
		default:
		{
			puts("Error. Incorrect arguments. Exit.");
		} break;
	}
}