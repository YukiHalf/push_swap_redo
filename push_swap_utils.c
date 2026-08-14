#include "push_swap.h"

int hasAlpha(char *s)
{
	int i;
	bool reachedDigit;

	reachedDigit = false;
	i = 0;
	while (s[i] && *s)
	{
		if(reachedDigit == true && ft_isdigit((int)s[i]) == 0)
			return 1;
		if(ft_isdigit((int)s[i]) == 0 && s[i] != '-' && s[i] != '+')
			return 1;
		if((s[i] == '-' || s[i] == '+') && (s[i + 1] && ft_isdigit((int)s[i + 1])) == 0)
			return 1;
		if(ft_isdigit((int)s[i]) == 1)
			reachedDigit = true;
		i++;
	}
return 0;
}

int addNodeStack(t_stack *stack, long number)
{
	t_node *newNode;
	t_node *tmp;

	newNode = malloc(sizeof(t_node));
	if(!newNode)
		return -1;
	if(stack->head == NULL)
		stack->head = newNode;
	else
	{
		tmp = stack->head;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = newNode;
	}
	newNode->data = number;
	stack->size++;
	return 0;
}

int checkDupes(t_node *node)
{
	t_node *tmp;

	while(node)
	{
		if(node->next)
			tmp = node->next;
		else
			tmp = NULL;
		while(tmp)
		{
			if(tmp->data == node->data)
				return -1;
			tmp = tmp->next;
		}
		node = node->next;
	}
	return 0;
}


void rankStack(t_stack *stack)
{
	t_node *tmp;
	t_node *node;
	int index;

	node = stack->head;
	while(node)
	{
		index = 0;
		tmp = stack->head;
		while(tmp)
		{
			if(node->data > tmp->data)
				index++;
			tmp = tmp->next;
		}
	node->index = index;
	node = node->next;
	}
}


void sortStacks(t_stack *stack_a,t_stack *stack_b)
{
	rankStack(stack_a);
	if(isSorted(stack_a) == 0)
			return;
	else if(stack_a->size == 2)
		swapStack(stack_a,'a');
	else if (stack_a->size == 3)
		simpleSort(stack_a);
	else if(stack_a->size > 3 && stack_a->size <= 7)
		quickSort(stack_a,stack_b);
	else if(stack_a->size > 7)
		turkSort(stack_a,stack_b);
	else
		return;



}
