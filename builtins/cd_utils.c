

#include "../minishell.h"

char	*ft_getcwd(char *buf, size_t size)
{
	char	*pwd;

	pwd = getcwd(buf, size);
	if (pwd == NULL)
		exit_errno("getcwd()", strerror(errno), EXIT_FAILURE);
	return (pwd);
}

char	*get_pwd_key_value(const char *key)
{
	char	*tmp;
	char	*pwd_key_value;

	tmp = ft_getcwd(NULL, 0);
	pwd_key_value = ft_strjoin(key, tmp);
	free(tmp);
	return (pwd_key_value);
}

void	export_pwd(const char *pwd, t_env_info *env_head)
{
	char	*tmp_pwd;

	tmp_pwd = get_pwd_key_value(pwd);
	export_key_value(env_head, tmp_pwd);
	free(tmp_pwd);
}