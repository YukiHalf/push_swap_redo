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
