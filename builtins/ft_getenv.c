
#include "../minishell.h"

char	*ft_getenv(t_env_info *info_env, char *key)
{
	t_env_info	*cur;

	cur = compare_env_key(info_env, key);
	return (cur->env_val);
}
