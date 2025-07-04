#include <stdio.h>
#include <ctype.h>

#define ARR_SIZE 20
#define TRUE 1
#define FALSE 0

double atof(char str[], int arr_size);
int getline(char str[], int arr_size);

int main() {

	char str[ARR_SIZE];

#if 0
	char str[ARR_SIZE] = "-1234.5e2";
#endif

#if 1
	printf("enter value >");
	getline(str, ARR_SIZE);
	printf("\n");
#endif

	for (int i = 0; str[i] != EOF; i++)
		printf("i = %c\n", str[i]);

	printf("double = %.15f\n", atof(str, ARR_SIZE));
	
	return 0; 
}

double atof(char str[], int arr_size) {
	
	double val, power;
	int i, sign, exp_val, exp_sign=0;
	int exp_state = FALSE;
	
	for (i = 0; isspace(str[i]); i++) // bypassing the starting space charracters if present
		;
	sign = (str[i] == '-') ? -1 : 1; // checking for the sign of the value
	
		
	if ((str[i] == '-') || (str[i] == '+'))  // move to the next character after '-' or '+'
		i++;

	for (val = 0.0; isdigit(str[i]); i++) {  // processing integer part of a number
		val = 10.0 * val + (str[i] - '0');
	}

	if (str[i] == '.')
		i++;
	for (power = 1.0; isdigit(str[i]); i++) { // processing fractional part of a number
		val = 10.0 * val + (str[i] - '0');
		power /= 10; 
		printf("power = %.15f\n", power);
	}

	if (str[i] == 'e' || str[i] == 'E') {  // enabling processing the exponential part of a number
		exp_state = TRUE;
		i++; 
	} 
		
	(exp_state == TRUE) ? printf("exp_state set -> true\n") : printf("exp_state set -> false\n"); // debug line

	if (str[i] == '-' && exp_state == TRUE) {   // saving the sign of the exponential part
		exp_sign = -1;
		i++;
	}		
	else if(isdigit(str[i])) {
		exp_sign = 1;		
	}
	
	printf("exp_sign = %d\n", exp_sign); // debug line

	for (exp_val = 0; isdigit(str[i]); i++) {	// processing the exponential part of a number
		printf("exp = %c\n", str[i]);  // debug line
		exp_val = exp_val * 10 + (str[i] - '0');
	}

	printf("exp_val = %d\n", exp_val * exp_sign);	// debug line

	if (exp_state == TRUE) {

		for (int j = 1; j <= exp_val; j++) {
			if (exp_sign == 1) {
				power *= 10;
				printf("power = %.15f\n", power);	// debug line
			}
			else if (exp_sign == -1) {
				power /= 10;
				printf("power = %.15f\n", power);	// debug line
			}
		}
	}

	return sign * val * power;
	
}

int getline(char str[], int arr_size) {
	
	char c;
	int i=0;

	while ((c = getchar()) != '\n' && i < arr_size) {
		str[i++] = c;
	}
	str[i] = EOF;
}