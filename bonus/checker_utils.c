#include "checker.h"

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

int checkArgs(int count, char **numbers)
{
	int i;
	int j;
	char **tmp;
	long tmp_nb;

	i = 0;
	if(numbers[1] && numbers[1][0] == '\0')
		return 1;
	while(++i < count)
	{
		tmp = ft_split(numbers[i],' ');
		j = -1;
		while(tmp[++j] && *tmp)
		{
			tmp_nb = ft_atol(tmp[j]);
			if((tmp_nb > MAX_INT || tmp_nb < MIN_INT) || hasAlpha(tmp[j]) == 1)
			{
					free(tmp);
					return 1;
			}
		}
		free(tmp);
	}
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
