
#include "../minishell.h"

int	ft_env(t_env_info *cur)
{
	while (cur->env_key != 0)
	{
		ft_write(STDOUT_FILENO, cur->env_key, ft_strlen(cur->env_key));
		ft_write(STDOUT_FILENO, "=", 1);
		ft_write(STDOUT_FILENO, cur->env_val, ft_strlen(cur->env_val));
		ft_write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}
