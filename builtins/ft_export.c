
#include "../minishell.h"

static void	append_env(t_env_info *env, char *key, char *value)
{
	t_env_info	*new;

	new = new_env(NULL);
	new->prev = env;
	env->next = new;
	env->env_key = key;
	env->env_val = value;
	return ;
}

static void	change_env(t_env_info *env, char *key, char *value)
{
	free(env->env_val);
	free(key);
	env->env_val = value;
	return ;
}

static int	export_no_arg(t_env_info *env_head)
{
	t_env_info	*tmp;
	t_env_info	*sorted_env;
	t_env_info	*cur;

	tmp = dup_env_list(env_head);
	sorted_env = sort_env_list(tmp);
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
	free_env_list(sorted_env);
	return (EXIT_SUCCESS);
}

void	export_key_value(t_env_info *env_head, char *key_value)
{
	t_env_info	*env;
	char	*key;
	char	*value;

	key = get_env_key(key_value);
	value = get_env_value(key_value);
	env = compare_env_key(env_head, key);
	if (env->env_key != NULL)
		change_env(env, key, value);
	else
		append_env(env, key, value);
	return ;
}

int	ft_export(int argc, char *argv[], t_env_info *env_head)
{
	int	i;
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (check_valid_identifier(argc, argv) == -1)
		exit_code = EXIT_FAILURE;
	else if (argc == 1)
		exit_code = export_no_arg(env_head);
	else
	{
		i = 1;
		while (i < argc)
		{
			export_key_value(env_head, argv[i]);
			++i;
		}
	}
	return (exit_code);
}
