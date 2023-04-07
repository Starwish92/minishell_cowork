#include "minishell.h"



void print_checker(t_cmd_info *cmd)
{
	t_cmd_info	*cur;
	int			i;

	cur = cmd;
	while (cur)
	{
		i = 0;
		if (cur->cmd_and_av[i])
		{
			while (cur->cmd_and_av[i])
			{
				printf("i == %d, value == %s\n", i, cur->cmd_and_av[i]);
				i++;
			}
		}
		cur = cur->next;
	}
}