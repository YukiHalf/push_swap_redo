#include "push_swap.h"

int allocate_stacks(t_stack *stack_a,t_stack *stack_b)
{
	stack_a = malloc(sizeof(t_stack));
	if(!stack_a)
		return -1;
	stack_b = malloc(sizeof(t_stack));
	if(!stack_b)
	{
		free(stack_a);
		return -1;
	}
	return 0;
}

void parse_args(t_stack *stack_a,int count,char **numbers)
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
			push_stack(stack_a, tmp_nb);
			j++;
		}
		free(tmp);
		i++;
	}
}


int check_args(int count, char **numbers)
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
			if((tmp_nb > MAX_INT || tmp_nb < MIN_INT) || has_alpha(tmp[j]) == 1)
			{
					free(tmp);
					return 1;
			}
			j++;
		}
		free(tmp);
		i++;
	}
	return 0;
}


int main(int argc,char **argv)
{
	if(argc == 1)
		return 0;

	t_stack *stack_a;
	t_stack *stack_b;

	if(check_args(argc,argv) == 1)
		display_error("Error\n",true);
	if(!(allocate_stacks(&stack_a,&stack_b)))
		display_error("Malloc failed\n",true);
	parse_args(stack_a,argc,argv);

}
