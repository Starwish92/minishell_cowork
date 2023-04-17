

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	ft_write(STDOUT_FILENO, "\n", 1);
	free(pwd);
	return (EXIT_SUCCESS);
}
