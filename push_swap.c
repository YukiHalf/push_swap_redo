#include "push_swap.h"

void parse_args(node_t stack_a,node_t stack_b,int count,char **numbers)
{

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

	node_t stack_a;
	node_t stack_b;

	if(check_args(argc,argv) == 1)
		display_error("Error\n",true);
	//parse_args(&stack_a,&stack_b,argc,argv);

}
