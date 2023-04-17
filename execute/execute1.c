#include "../minishell.h"

static char	**get_envp(t_env_info *head)
{
	int		i;
	int		size;
	char	*env_key;
	t_env_info	*tmp;
	char	**result;

	i = 0;
	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	result = malloc(sizeof(char *) * size);
	tmp = head;
	while (i < size - 1)
	{
		env_key = ft_strjoin(tmp->env_key, "=");
		result[i] = ft_strjoin(env_key, tmp->env_val);
		i++;
		tmp = tmp->next;
		free(env_key);
	}
	result[i] = NULL;
	return (result);
}

void	ft_execve(const char *file, char *const *argv, char *const *envp)
{
	if (execve(file, argv, envp) == -1)
		exit_errno("execve()", strerror(errno), 126);
	return ;
}
