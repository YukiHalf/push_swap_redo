#include "push_swap.h"

int has_alpha(char *s)
{
	int i;

	i = 0;
	while (s[i] && *s)
	{
		if(ft_isdigit((int)s[i]) == 0 && s[i] != '-' && s[i] != '+')
			return 1;
		if( (s[i] == '-' || s[i] == '+') && (s[i + 1] && ft_isdigit(s[i + 1])) == 0)
			return 1;
		i++;
	}
return 0;
}
