#include <stdio.h>
#include <string.h>

// the four arithmetic operations
// one of these functions is selected at runtime with a swicth or a function pointer


typedef struct {
	char  *function_name;
	float (*pt2Func)(float, float);
} conv_t;

conv_t convertion_array[] = {
"Plus", Plus,
"Minus", Minus,
"Multiply", Multiply,
"Divide", Divide,
	0, 0
};


// execute example code
void main()
{
	char   minus_str[] = "Divide";
	conv_t *tmp;
	float  param1 = 5, param2 = 3, result;

	for (tmp = convertion_array; tmp->function_name && strcmp(minus_str, tmp->function_name); tmp++);
		if (tmp->function_name) {
			result = tmp->pt2Func(param1, param2);
			printf("Result = %f\n", result);
		}
		else
			printf("Wrong function name\n", result);
}

float Plus     (float a, float b) { return a+b; }
float Minus    (float a, float b) { return a-b; }
float Multiply (float a, float b) { return a*b; }
float Divide   (float a, float b) { return a/b; }

