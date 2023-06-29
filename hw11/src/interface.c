#include <stdio.h>
#include "calc.h"

void run_calculator_interface()
{
	puts("Example: 2.07+3.5");
	double num1=0.0, num2=0.0;
	char ms;
	scanf("%lf%c%lf", &num1, &ms, &num2);
	switch(ms)
	{
		case('+'):
		{
			double result=calculate_addition(num1, num2);
			printf("%lf + %lf = %lf\n", num1, num2, result);
		} break;
		case('-'):
		{
			double result=calculate_subtraction(num1, num2);
			printf("%lf - %lf = %lf\n", num1, num2, result);
		} break;
		case('*'):
		{
			double result=calculate_multiplication(num1, num2);
			printf("%lf * %lf = %lf\n", num1, num2, result);
		} break;
		case('/'):
		{
			double result=calculate_division(num1, num2);
			printf("%lf / %lf = %lf\n", num1, num2, result);
		} break;
		default:
		{
			puts("Error. Incorrect arguments. Exit.");
		} break;
	}
}