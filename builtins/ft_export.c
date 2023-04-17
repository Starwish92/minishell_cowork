
#include "../minishell.h"

static void	ft_add_env(t_env_info *env, char *key, char *value)
{
	t_env_info	*new_env_lst;

	new_env_lst = new_env(NULL);
	new_env_lst->prev = env;
	env->next = new_env_lst;
	env->env_key = key;
	env->env_val = value;
	return ;
}

static void	ft_change_env(t_env_info *env, char *key, char *value)
{
	free(env->env_val);
	free(key);
	env->env_val = value;
	return ;
}

static int	ft_export_with_no_arg(t_env_info *info_env)
{
	t_env_info	*tmp;
	t_env_info	*sorted_env;
	t_env_info	*cur;

	tmp = ft_dup_env_list(info_env);
	sorted_env = ft_sort_env_list(tmp);
	cur = sorted_env;
	while (cur->env_key)
	{
		ft_write(STDOUT_FILENO, "declare -x ", 11);
		ft_write(STDOUT_FILENO, cur->env_key, ft_strlen(cur->env_key));
		ft_write(STDOUT_FILENO, "=\"", 2);
		ft_write(STDOUT_FILENO, cur->env_val, ft_strlen(cur->env_val));
		ft_write(STDOUT_FILENO, "\"\n", 2);
		cur = cur->next;
	}
	ft_free_env_list(sorted_env);
	return (EXIT_SUCCESS);
}

void	ft_export_val(t_env_info *info_env, char *key_value)
{
	t_env_info	*env;
	char	*key;
	char	*value;

	printf("%s\n", key_value);
	key = get_env_key(key_value);
	value = get_env_value(key_value);
	env = compare_env_key(info_env, key);
	if (env->env_key != NULL)
		ft_change_env(env, key, value);
	else
		ft_add_env(env, key, value);
	return ;
}

int	ft_export(int argc, char **argv, t_env_info *info_env)
{
	int	i;
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	// printf("%d\n", argc);
	if (ft_valid_identifier_ch(argc, argv) == -1)
		exit_code = EXIT_FAILURE;
	else if (argc == 1)
		exit_code = ft_export_with_no_arg(info_env);
	else
	{
		i = 1;
		while (i < argc)
		{
			ft_export_val(info_env, argv[i]);
			++i;
		}
	}
	return (exit_code);
}
