#include<stdio.h>
#include<float.h>
#include<math.h> 

int main (void)
{ 
	char s;	
	printf("Enter phone number: ");
	
	while((s=getchar()) != '\n')    //!!
	{
		switch(s)
		{
			case 'A':case 'B':case 'C':
				printf("2");
				break;
			case 'D':case 'E':case 'F':
				printf("3");
				break;
			case 'G':case 'H':case 'I':
				printf("4");
				break;
			case 'J':case 'K':case 'L':
				printf("5");
				break;
			case 'M':case 'N':case 'O':
				printf("6");
				break;
			case 'P':case 'Q':case 'R':case 'S':
				printf("7");
				break;
			case 'T':case 'U':case 'V':
				printf("8");
				break;
			case 'W':case 'X':case 'Y':case 'Z':
				printf("9");
				break;	 
			case '-':
				printf("-");
				break;	
			case '+':
				printf("+");
				break;	
		}
		if(s>='0' && s <='9')
			printf("%d", s-'0');
	}
	
	return 0;
}
