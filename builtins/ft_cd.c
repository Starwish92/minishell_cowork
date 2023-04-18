/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:28:25 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/18 19:34:33 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_home_directory(char *path, t_env_info *info_env)
{
	int		exit_code;
	char	*home;
	char	*tmp_workgin_dir;

	exit_code = EXIT_FAILURE;
	home = ft_getenv(info_env, "HOME");
	if (home == NULL)
		print_err2("cd", "home not set");
	else
	{
		tmp_workgin_dir = get_env_pwd("OLDPWD=");
		exit_code = chdir(home);
		if (exit_code == -1)
			print_err3("cd", path, strerror(errno));
		else
			ft_export_val(info_env, tmp_workgin_dir);
		free(tmp_workgin_dir);
	}
	if (exit_code != -1)
		get_pwd("PWD=", info_env);
	return (exit_code);
}

static int	ft_tilde_dir(t_env_info *info_env)
{
	int		exit_code;
	char	*home;
	char	*tmp_pwd;

	exit_code = EXIT_FAILURE;
	home = getenv("HOME");
	if (home == NULL)
		print_err2("cd", "home not set");
	else
	{
		tmp_pwd = get_env_pwd("OLDPWD=");
		exit_code = chdir(home);
		if (exit_code == -1)
			print_err3("cd", home, strerror(errno));
		else
			ft_export_val(info_env, tmp_pwd);
		free(tmp_pwd);
	}
	if (exit_code != -1)
		get_pwd("PWD=", info_env);
	return (exit_code);
}

static int	ft_tilde_path(char *path, t_env_info *info_env)
{
	int		exit_code;
	char	*home;
	char	*tmp_pwd;
	char	*home_path;

	exit_code = EXIT_FAILURE;
	home = getenv("HOME");
	if (home == NULL)
		print_err2("cd", "home not set");
	else
	{
		tmp_pwd = get_env_pwd("OLDPWD=");
		home_path = ft_strjoin(home, path + 1);
		exit_code = chdir(home_path);
		if (exit_code == -1)
			print_err3("cd", home_path, strerror(errno));
		else
			ft_export_val(info_env, tmp_pwd);
		free(home_path);
		free(tmp_pwd);
	}
	if (exit_code != -1)
		get_pwd("PWD=", info_env);
	return (exit_code);
}

static int	ft_dir_path(char *path, t_env_info *info_env, t_cmd_info *cmd)
{
	int		exit_code;
	char	*tmp_pwd;

	exit_code = EXIT_FAILURE;
	tmp_pwd = get_env_pwd("OLDPWD=");
	exit_code = chdir(path);
	if (exit_code == -1)
	{
		if (ft_strcmp(cmd->cmd_and_av[1], "netexist"))
			exit_code = 1;
		print_err3("cd", path, strerror(errno));
	}
	else
	{
		ft_export_val(info_env, tmp_pwd);
	}
	free(tmp_pwd);
	if (exit_code != -1)
		get_pwd("PWD=", info_env);
	return (exit_code);
}

int	ft_cd(char *path, t_env_info *info_env, t_cmd_info *cmd)
{
	if (path == NULL)
		return (ft_home_directory(path, info_env));
	else if (!ft_strcmp("~", path))
		return (ft_tilde_dir(info_env));
	else if (!ft_strncmp("~/", path, 2))
		return (ft_tilde_path(path, info_env));
	else
		return (ft_dir_path(path, info_env, cmd));
}