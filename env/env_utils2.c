
#include "../minishell.h"

t_env_info	*compare_env_key(t_env_info *info_env, char *key)
{
	t_env_info	*temp;

	temp = info_env;
	while (temp->env_key != 0 && ft_strncmp(key, temp->env_key, ft_strlen(key)))
		temp = temp->next;
	return (temp);
}

char	*ft_getenv(t_env_info *info_env, char *key)
{
	t_env_info	*cur;

	cur = compare_env_key(info_env, key);
	return (cur->env_val);
}