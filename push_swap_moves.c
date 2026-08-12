#include "push_swap.h"

void pushStack(t_stack *toStack,t_stack *fromStack,char x)
{
	t_node *tmp;
	if(!fromStack->head)
		return;
	tmp = fromStack->head;
	fromStack->head = fromStack->head->next;
	tmp->next = toStack->head;
	toStack->head = tmp;
	fromStack->size--;
	toStack->size++;
	write(1,"p",2);
	write(1,&x,1);
	write(1,"\n",1);
}


void rotateStack(t_stack *stack,char x)
{

	t_node *tmp;

	tmp = stack->head;
	while(tmp->next)
			tmp = tmp->next;
	tmp->next = stack->head;
	tmp = stack->head;
	stack->head = stack->head->next;
	tmp->next = NULL;
	write(1,"r",2);
	write(1,&x,1);
	write(1,"\n",1);
}

void rRotateStack(t_stack *stack,char x)
{
	t_node *tmp;

	tmp = stack->head;
	while(tmp->next->next)
		tmp = tmp->next;
	tmp->next->next = stack->head;
	stack->head = tmp->next;
	tmp->next = NULL;
	write(1,"rr",2);
	write(1,&x,1);
	write(1,"\n",1);
}


void swapStack(t_stack *stack,char x)
{
	t_node *tmp;

	if(stack->size == 1)
		return;
	tmp = stack->head->next;
	stack->head->next = tmp->next;
	tmp->next = stack->head;
	stack->head = tmp;
	write(1,"s",1);
	write(1,&x,1);
	write(1,"\n",1);
}
