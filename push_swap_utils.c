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

int pushStack(t_stack *stack, long number)
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


int loadMap(long key, int map[MAX_INT][2])
{
	if(key < 0)
	{
		if(map[-key][1] == 1)
			return -1;
		map[-key][1] = 1;
	}
	else
	{
		if(map[key][0] == 1)
			return -1;
		map[key][0] = 1;
	}
return 0;
}
