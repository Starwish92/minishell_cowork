/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:55:17 by mher              #+#    #+#             */
/*   Updated: 2023/04/07 14:30:33 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_path(char **path)
{
	size_t	i;

	i = 0;
	while (path[i])
		free (path[i++]);
	free (path);
}

static char	*get_absolute_path(t_cmd_info *cmd, char *env_path)
{
	char	*ret;
	char	*slash;
	char	**path;
	int		i;

	i = 0;
	path = ft_split(env_path, ':');
	slash = ft_strjoin("/", cmd->cmd_and_av[0]);
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

static int	check_relative(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (!ft_isalnum(str[i]))
	{
		if (str[i] == '.' || str[i] == '/')
		{
			ret = 1;
		}
		i++;
	}
	return (ret);
}

char	*get_cmd_path(t_cmd_info *cmd, t_info_env *env_head)
{
	char	*ret;
	char	*env_path;

	ret = NULL;
	env_path = ft_getenv(env_head, "PATH");
	if (check_relative(cmd->cmd_and_av[0]) && is_exist_file(cmd->cmd_and_av[0]))
		return (ft_strdup(cmd->cmd_and_av[0]));
	else if (env_path != NULL)
		ret = get_absolute_path(cmd, env_path);
	if (ret == NULL && is_exist_file(cmd->cmd_and_av[0]))
		return (ft_strdup(cmd->cmd_and_av[0]));
	return (ret);
}
