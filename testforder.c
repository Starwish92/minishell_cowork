#include "minishell.h"

void print_checker(t_cmd_info *cmd, t_env_info *env)
{
	t_cmd_info	*cur;
	t_env_info 	*env_cur;
	int			i;
	
	cur = cmd;
	int k = 1;
	// while (cur)
	// {
	// 	printf("--------- how many whiles == %d ---------\n", k++);
	// 	i = 0;
	// 	if (cur->ac == 0 && cur->ft_pipe_flag == 1)
	// 		printf("error pipe\n");
	// 	else if (cur->cmd_and_av[i] && cur->ac != 0)
	// 	{
	// 		while (cur->cmd_and_av[i])
	// 		{
	// 			printf("i == %d, value == %s\n", i, cur->cmd_and_av[i]);
	// 			i++;
	// 		}
	// 	}
	// 	cur = cur->next;
	// }
	//-------------------------------------환경변수 찍어보기
	env_cur = env;
	printf("---------환경변수 출력-----------\n");
	while (env_cur)
	{
		if (env_cur->env_key)
			printf("env_key = %s, env_value = %s\n", env_cur->env_key, env_cur->env_val);
		env_cur = env_cur->next;
	}
}
