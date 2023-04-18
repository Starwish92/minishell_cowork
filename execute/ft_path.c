/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:01:41 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/18 22:01:58 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_path(char **path)
{
	size_t	i;

	i = 0;
	while (path[i])
		free (path[i++]);
	free (path);
}

static char	*ft_get_abs_path(t_cmd_info *cmd, char *path_env)
{
	char	*ret;
	char	*slash;
	char	**path;
	int		i;

	i = 0;
	path = ft_split(path_env, ':');
	slash = ft_strjoin("/", cmd->cmd_av[0]);
	while (path[i])
	{
		ret = ft_strjoin(path[i], slash);
		if (is_exist_file(ret))
			break ;
		free(ret);
		++i;
	}
	free(slash);
	if (path[i] == NULL)
		ret = NULL;
	free_path(path);
	return (ret);
}

static int	ft_chk_relative(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (!ft_isalnum(str[i]))
	{
		if (str[i] == '.' || str[i] == '/')
			ret = 1;
		else
			return (0);
		i++;
	}
	return (ret);
}

char	*ft_get_cmd_path(t_cmd_info *cmd, t_env_info *info_env)
{
	char	*ret;
	char	*path_env;

	ret = NULL;
	path_env = ft_getenv(info_env, "PATH");
	if (ft_chk_relative(cmd->cmd_av[0]) && \
		is_exist_file(cmd->cmd_av[0]))
		return (ft_strdup(cmd->cmd_av[0]));
	else if (path_env != NULL)
		ret = ft_get_abs_path(cmd, path_env);
	if (ret == NULL && is_exist_file(cmd->cmd_av[0]))
		return (ft_strdup(cmd->cmd_av[0]));
	return (ret);
}
