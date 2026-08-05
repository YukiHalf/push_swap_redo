#include "push_swap.h"

int isSorted(t_stack *stack)
{
	t_node *tmp;

	tmp = stack->head;
	while(tmp)
	{
		if(tmp->next && tmp->data > tmp->next->data)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}
