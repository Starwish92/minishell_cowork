

#include "../minishell.h"

static void	ft_remove_env(t_env_info *env)
{
	t_env_info	*next;
	t_env_info	*prev;

	next = env->next;
	prev = env->prev;
	prev->next = env->next;
	next->prev = env->prev;
	free(env->env_key);
	free(env->env_val);
	free(env);
}

static int	ft_valid_key_identifier_ch(int argc, char **argv)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (++i < argc)
	{
		if (argv[i] == NULL)
		{
			print_quote_err3("unset", "", "not a valid identifier");
			return (-1);
		}
		if (ft_specific_char_ch(argv[i], '='))
			ret = -1;
		else if (ft_space_ch(argv[i], '\0'))
			ret = -1;
		else if (ft_only_digit(argv[i], '\0'))
			ret = -1;
		if (ret == -1)
		{
			print_quote_err3("unset", argv[i], "not a valid identifier");
			return (ret);
		}
	}
	return (0);
}

static void	unset(t_env_info *info_env, char *key)
{
	t_env_info	*env;

	env = compare_env_key(info_env, key);
	if (env->env_key == NULL)
		return ;
	else
		ft_remove_env(env);
}

int	ft_unset(int argc, char **argv, t_env_info *info_env)
{
	int	i;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if (ft_valid_key_identifier_ch(argc, argv) == -1)
		return (EXIT_FAILURE);
	i = 1;
	while (i < argc)
	{
		unset(info_env, argv[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}
