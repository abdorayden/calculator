#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_C_
#include "./stack.h"

typedef enum{
	false = 0,
	true = !false
}bool;


// EXAMPLE :
		// 4*(3+1*6)+3*2
		// ^
		// fmt : 4 , stack :
	// result: 4
		// 4*(3+1*6)+3*2
		//  ^
		// fmt : 4 , stack : *
	// result: 4
		// 4*(3+1*6)+3*2
		//   ^
		// fmt : 4 , stack : *(
	// result: 4
		// 4*(3+1*6)+3*2
		//    ^
		// fmt : 43 , stack : *(
	// result: 43
		// 4*(3+1*6)+3*2
		//     ^
		// fmt : 43 , stack : *(+
	// result: 43
		// 4*(3+1*6)+3*2
		//      ^
		// fmt : 431 , stack : *(+
	// result: 431
		// 4*(3+1*6)+3*2
		//       ^
		// fmt : 431 , stack : *(+*
	// result: 431
		// 4*(3+1*6)+3*2
		//        ^
		// fmt : 4316 , stack : *(+*
	// result: 4316
		// 4*(3+1*6)+3*2
		//         ^
		// fmt : 4316 , stack : 
	// result: 4316*+*
		// 4*(3+1*6)+3*2
		//          ^
		// fmt : 4316 , stack : +
	// result: 4316*+*
		// 4*(3+1*6)+3*2
		//           ^
		// fmt : 43163 , stack : +
	// result: 4316*+*3
		// 4*(3+1*6)+3*2
		//            ^
		// fmt : 43163 , stack : +*
	// result: 4316*+*3
		// 4*(3+1*6)+3*2
		//             ^
		// fmt : 431632 , stack : 
	// result: 4 3 1 6 * + * 3 2 * +
	// 	   4 3 6 + * 3 2 * +
	// 	   4 9 * 3 2 * +
	// 	   36 3 2 * +
	// 	   36 6 +
	// 	   42
bool is_integer(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    } else {
        return false;
    }
}
int pre(char ch){
	if(ch == '(')	return 0;
	else if(ch == '+' || ch == '-')	return 1;
	else if(ch == '*' || ch == '/')	return 2;
	else return -1;
}
int cal(int num1 , int num2 , char op){
	switch(op){
		case '*':
			return num1*num2;
		case '+':
			return num1+num2;
		case '-':
			return num1-num2;
		case '/':
			return num1/num2;
		default :
			return -1;
	}
}
int isOP(char ch){
	return (ch == '+' || ch == '-' || ch == '/' || ch == '*');
}
double _pow(double val , long of_what){
	if(of_what == 0)	return 1;
	else if(of_what > 0){
		return val * _pow(val , of_what - 1);
	}else{
		double res = 1;
		while(of_what-- > 0){
			res *= val;
		}
		return 1/(res);
	}
}
int to_i(char* num){
	if(strlen(num) < 1)	return -1;
	int outnum[strlen(num)];
	for(size_t i = 0 ; i < strlen(num) ; i++){
		if(((int)num[i] > 57) && ((int)num[i] < 48))
			return -1;
		outnum[i] = num[i] - 48;
	}
	int res = 0;
	for(int j = 1 ; j <= (strlen(num) - 1) ; j++){
		res += *(outnum + (j - 1)) * _pow(10, (strlen(num) - j));
	}
	res += outnum[strlen(num) - 1];
	return res;
}

char fmt[128];
// postfix
void create_stack_format(const char* format){
	Stack* stack;
	int index = 0;
	int i = 0;
	int j = 0;
	Stack_Init(&stack);
	char c;
	// format : 24+26 
	//
	// stack : | | | | | |
	// fmt : 
	for(;format[i] != '\0';i++){
		c = format[i];
		if(c == '('){
			Stack_Push(&stack , '(');
		}else if(isOP(c)){
			fmt[index++] = ')';
			while(!Stack_Is_Empty(stack) && pre(Stack_Get_Last_In_Val(stack)) >= pre(c)){
				Stack_Pop(&stack,(int*)&fmt[index++]);
			}
			Stack_Push(&stack , c);
			j = 0;
		}else if(c == ')'){
			while(!Stack_Is_Empty(stack) && Stack_Get_Last_In_Val(stack) != '('){
				Stack_Pop(&stack,(int*)&fmt[index++]);
			}
			Stack_Pop(&stack,NULL);
		}else{
			if(j == 0)	fmt[index++] = '(';
			fmt[index++] = c;
			j++;

		}
	}
	while(!Stack_Is_Empty(stack)){
		Stack_Pop(&stack , (int*)&fmt[index++]);
	}
	fmt[index++] = ')';
	fmt[index] = '\0';
}
int stack_ele(Stack* s){
	int res = 0;
	while(s != NULL){
		res++;
		s = s->next;
	}
	return res;
}
#define calll(c)					\
	int n;						\
	int m;						\
	if(stack_ele(stack) > 1){			\
		Stack_Pop(&stack , &n);			\
		Stack_Pop(&stack , &m);			\
		Stack_Push(&stack , cal(m,n,(c)));	\
	}						\

// infix
int calc(char* fmtop){
	Stack* stack;
	int i = 0;
	char c;
	Stack_Init(&stack);
	char tmp[20];
       	memset(tmp,0, 20);
	int t = 0;
	// (23)(2*)
	for(;*fmtop != '\0';fmtop++){
		while(*fmtop != ')'){
			if(isOP(*fmtop)){
				if(strlen(tmp) > 0){
					Stack_Push(&stack , to_i(tmp));
       					memset(tmp,0, 20);
					i = 0;
				}
				calll(*fmtop);
			}
			else if(is_integer(*fmtop)){
				tmp[i++] = *fmtop;
			}
			fmtop++;
		}
		if(strlen(tmp) > 0){
			Stack_Push(&stack , to_i(tmp));
       			memset(tmp,0, 20);
			i = 0;
		}
	}
	return Stack_Get_Last_In_Val(stack);
}

int main(int argc , char** argv){
	printf("\033[2J");
	printf("\033[0;0H");
	printf("\n");
	printf("\n\t\t╔═╗╔═╗╦  ╔═╗╦ ╦╦  ╔═╗╔╦╗╔═╗╦═╗\n");
	printf("\t\t║  ╠═╣║  ║  ║ ║║  ╠═╣ ║ ║ ║╠╦╝\n");
	printf("\t\t╚═╝╩ ╩╩═╝╚═╝╚═╝╩═╝╩ ╩ ╩ ╚═╝╩╚═\n");

	char calcfmt[128]; 
	calcfmt[strlen(calcfmt) - 1] = '\0';
	printf("[+] Calculator \n");
	printf("[+] Put Your Operation : ");
	fgets(calcfmt , 128 , stdin);
	create_stack_format(calcfmt);
	if(argc > 1){
		if(strcmp(argv[1] , "-v") == 0){
			printf("[+] Your Operation : %s",calcfmt);
			printf("[+] Your Operation format : ");
			puts(fmt);
		}
	}
	printf("[+] The result is %d\n" , calc(fmt));
	return 0;
}
