#include "checker.h"


int complexMove(char *move,t_stack *stack_a,t_stack *stack_b)
{
	if(ft_strcmp(move,"ss\n") == 0)
	{
		swapStack(stack_a,'a',true);
		swapStack(stack_b,'b',true);
	}
	else if(ft_strcmp(move,"rr\n") == 0)
		rotateBothStacks(stack_a,stack_b,false,true);
	else if(ft_strcmp(move,"rrr\n") == 0)
		rotateBothStacks(stack_a,stack_b,true,true);
	else
		return -1;
	return 0;
}

void simpleMove(char move,char dir,t_stack *stack_a,t_stack *stack_b)
{
	if(dir == 'a')
	{
		if(move == 's')
			swapStack(stack_a,dir,true);
		else if(move == 'p')
			pushStack(stack_a,stack_b,dir,true);
		else if(move == 'r')
			rotateStack(stack_a,dir,true);
		else
			rRotateStack(stack_a,dir,true);
	}else
	{
		if(move == 's')
			swapStack(stack_b,dir,true);
		else if(move == 'p')
			pushStack(stack_b,stack_a,dir,true);
		else if(move == 'r')
			rotateStack(stack_b,dir,true);
		else
			rRotateStack(stack_b,dir,true);
	}
}

int doMove(char *move,t_stack *stack_a,t_stack *stack_b)
{
	if(move[0] && (move[0] == 's' || move[0] == 'p' || move[0] == 'r'))
	{
		if(move[1] && (move[1] == 'a' || move[1] == 'b'))
			simpleMove(move[0],move[1],stack_a,stack_b);
		if(move[1] && move[1] == 'r')
		{
			if(move[2] && (move[2] == 'a' || move[2] == 'b'))
				simpleMove('1',move[2],stack_a,stack_b);
		}
	}else
		if(complexMove(move,stack_a,stack_b) == -1)
			return -1;
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


void initStacks(t_stack *stack_a,t_stack *stack_b)
{
	stack_a->head = NULL;
	stack_b->head = NULL;
	stack_a->size = 0;
	stack_b->size = 0;
}



void DEBUG_printStack(t_stack *stack,char x)
{
	t_node *tmp;
	if(stack->head)
		tmp= stack->head;
	else
		return;
	printf("#####DEBUG %c#####\n",x);
	while(tmp->next)
	{
		printf("I:%d, D:%ld\n",tmp->index,tmp->data);
		tmp = tmp->next;
	}
		printf("I:%d, D:%ld\n",tmp->index,tmp->data);

	printf("#####DEBUG %c#####\n",x);
}


int main(int argc,char **argv)
{
	char *line;
	t_stack stack_a;
	t_stack stack_b;

	if(argc == 1)
		return 0;
	initStacks(&stack_a,&stack_b);
	parseArgs(&stack_a,argc,argv);
	line = get_next_line(0);
	while(line)
	{
		if(doMove(line,&stack_a,&stack_b) == -1)
		{printf("move not good :%d",line);	break;}
		free(line);
		line = get_next_line(0);
	}
	if(line)
		free(line);
	DEBUG_printStack(&stack_a,'a');
	DEBUG_printStack(&stack_b,'b');
	if(isSorted(&stack_a) == 0 && stack_b.head == NULL && stack_b.size == 0)
	{
		ft_putendl_fd("OK",1);
		return 0;
	}
	ft_putendl_fd("KO",1);
	return 1;
}
