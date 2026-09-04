#include "push_swap.h"


int maxIndex(t_stack *stack)
{
	t_node *node;
	int max;

	node = stack->head;
	max = stack->head->index;
	while(node->next)
	{
		node = node->next;
		if(node->index > max)
			max = node->index;
	}
return max;
}


void DEBUG_printStack(t_stack *stack,char x)
{
	t_node *tmp;
	if(stack->head)
	tmp = stack->head;
	else
		{
			printf("empty\n");
			return;
		}
	printf("#####DEBUG %c#####\n",x);
	while(tmp->next)
	{
		printf("I:%d, D:%ld\n",tmp->index,tmp->data);
		tmp = tmp->next;
	}
		printf("I:%d, D:%ld\n",tmp->index,tmp->data);

	printf("#####DEBUG %c#####\n",x);

}
