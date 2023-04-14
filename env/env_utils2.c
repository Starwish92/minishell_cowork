
#include "../minishell.h"

t_env_info	*compare_env_key(t_env_info *env_head, char *key)
{
	t_env_info	*temp;

	temp = env_head;
	// while (cur->key != 0 && ft_strncmp(key, cur->key, ft_strlen(cur->key)))
	while (temp->env_key != 0 && ft_strncmp(key, temp->env_key, ft_strlen(key)))
		temp = temp->next;
	return (temp);
}

char	*ft_getenv(t_env_info *env_head, char *key)
{
	t_env_info	*cur;

	cur = compare_env_key(env_head, key);
	return (cur->env_val);
}