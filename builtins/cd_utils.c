

#include "../minishell.h"

char	*ft_get_cwd(char *buf, size_t size)
{
	char	*current_path;

	current_path = getcwd(buf, size);
	if (current_path == NULL)
		exit_errno("getcwd()", strerror(errno), EXIT_FAILURE);
	return (current_path);
}

char	*get_env_pwd(const char *pwd_val)
{
	char	*tmp_path;
	char	*pwd_key_value;

	tmp_path = ft_get_cwd(NULL, 0);
	pwd_key_value = ft_strjoin(pwd_val, tmp_path);
	free(tmp_path);
	return (pwd_key_value);
}

void	get_pwd(const char *pwd, t_env_info *info_env)
{
	char	*tmp_working_dir;

	tmp_working_dir = get_env_pwd(pwd);
	ft_export_val(info_env, tmp_working_dir);
	free(tmp_working_dir);
}
