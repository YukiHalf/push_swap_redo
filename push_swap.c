#include "push_swap.h"

void initStacks(t_stack *stack_a,t_stack *stack_b)
{
	stack_a->head = NULL;
	stack_b->head = NULL;
	stack_a->size = 0;
	stack_b->size = 0;
}

void parseArgs(t_stack *stack_a,int count,char **numbers)
{
	int i;
	int j;
	char **tmp;
	long tmp_nb;

	i = 1;
	while(i < count)
	{
		tmp = ft_split(numbers[i],' ');
		j = 0;
		while(tmp[j] && *tmp)
		{
			tmp_nb = ft_atol(tmp[j]);
			addNodeStack(stack_a, tmp_nb);
			j++;
		}
		free(tmp);
		i++;
	}
}


int checkArgs(int count, char **numbers)
{
	int i;
	int j;
	char **tmp;
	long tmp_nb;

	i = 0;
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


int main(int argc,char **argv)
{
	if(argc == 1)
		return 0;

	t_stack stack_a;
	t_stack stack_b;

	if(checkArgs(argc,argv) == 1)
		display_error("Error\n",true);
	initStacks(&stack_a,&stack_b);
	parseArgs(&stack_a,argc,argv);
	if(checkDupes(stack_a.head) == -1)
		display_error("Error\n",true);
	sortStacks(&stack_a,&stack_b);

	t_node *tmp= stack_a.head;

	while(tmp->next)
	{
		printf("%d %ld\n",tmp->index,tmp->data);
		tmp = tmp->next;
	}
		printf("%d %ld\n",tmp->index,tmp->data);

}
