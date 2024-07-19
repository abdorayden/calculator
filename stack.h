#ifndef STACK_H_
#define STACK_H_

typedef struct stack{
	int value;
	struct stack* next;
}Stack;

void Stack_Init(Stack**);
int Stack_Is_Empty(Stack*);
int Stack_Get_Last_In_Val(Stack*);
void Stack_Push(Stack**,int);
void Stack_Pop(Stack**,int*);
void Stack_Print(Stack*);

#endif //STACK_H_

#ifdef STACK_C_

void Stack_Init(Stack** stack){
	*stack = NULL;
}

int Stack_Is_Empty(Stack* stack){
	return (stack == NULL);
}

int Stack_Get_Last_In_Val(Stack* stack){
	//if(!Stack_Is_Empty(stack))	return stack->value;
	if((stack) != NULL)	return stack->value;
}

//void Stack_Push(Stack** stack , int value){
void Stack_Push(Stack** stack , int value){
	Stack* temp = malloc(sizeof(Stack));
	temp->value = value;
	temp->next = *stack;
	*stack = temp;
}
//void Stack_Pop(Stack** stack , int* value){
void Stack_Pop(Stack** stack , int* value){
	if(!Stack_Is_Empty(*stack)){
		if(value != NULL)
			*value = (*stack)->value;
		Stack* temp = *stack;
		(*stack) = (*stack)->next;
		free(temp);
	}
}
void Stack_Print(Stack* stack){
	int val;
	Stack* temp;
	Stack_Init(&temp);
	while(!Stack_Is_Empty(stack)){
		Stack_Pop(&stack , &val);
		printf("%d\n" , val);
		Stack_Push(&temp , val);
	}
	while(!Stack_Is_Empty(temp)){
		Stack_Pop(&temp , &val);
		Stack_Push(&stack , val);
	}

}
#endif  //STACK_C_
