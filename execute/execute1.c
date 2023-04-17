#include "../minishell.h"

void	ft_execve(const char *file, char *const *argv, char *const *envp)
{
	if (execve(file, argv, envp) == -1)
		exit_errno("execve()", strerror(errno), 126);
	return ;
}
