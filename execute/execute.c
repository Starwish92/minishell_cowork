/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:57:50 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/14 20:54:14 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_envp(t_env_info *head)
{
	int		i;
	int		size;
	char	*env_key;
	t_env_info	*tmp;
	char	**result;

	i = 0;
	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	result = malloc(sizeof(char *) * size);
	tmp = head;
	while (i < size - 1)
	{
		env_key = ft_strjoin(tmp->env_key, "=");
		result[i] = ft_strjoin(env_key, tmp->env_val);
		i++;
		tmp = tmp->next;
		free(env_key);
	}
	result[i] = NULL;
	return (result);
}

void	ft_execve(const char *file, char *const *argv, char *const *envp)
{
	if (execve(file, argv, envp) == -1)
		exit_errno("execve()", strerror(errno), 126);
	return ;
}

static int	os_builtins(t_cmd_info *cmd, t_env_info *info_env)
{
	char	*env_path;
	char	**now_env;

	env_path = ft_getenv(info_env, "PATH");
	if (env_path == NULL && cmd->ft_command_path == NULL)
	{
		print_err3(cmd->cmd_and_av[0], NULL, "No such file or directory");
		return (127);
	}
	if (env_path != NULL && ft_strlen(env_path) == 0 && cmd->ft_command_path == NULL)
	{
		print_err3(cmd->cmd_and_av[0], NULL, "No such file or directory");
		return (127);
	}
	if (cmd->ft_command_path == NULL)
	{
		print_err3(cmd->cmd_and_av[0], NULL, "command not found");
		return (127);
	}
	now_env = get_envp(info_env);
	ft_execve(cmd->ft_command_path, cmd->cmd_and_av, now_env);
	return (EXIT_FAILURE);
}

static int	execute_cmd(t_cmd_info *cmd, t_env_info *info_env)
{
	restore_redirection_char(cmd);
	if (!ft_strcmp(cmd->cmd_and_av[0], "echo"))
		return (ft_echo(cmd->ac, cmd->cmd_and_av));
	if (!ft_strcmp(cmd->cmd_and_av[0], "cd"))
		return (ft_cd(cmd->cmd_and_av[1], info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->cmd_and_av[0], "export"))
		return (ft_export(cmd->ac, cmd->cmd_and_av, info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "unset"))
		return (ft_unset(cmd->ac, cmd->cmd_and_av, info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "env"))
		return (ft_env(info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "exit"))
		return (ft_exit(cmd));
	return (os_builtins(cmd, info_env));
}

static void	do_fork_cmd(t_cmd_info *cmd, t_env_info *info_env)
{
	pid_t	pid;
	int		exit_code;

	set_signal(DFL, DFL);
	pid = ft_fork();
	if (pid == 0)
	{
		ft_redirect(cmd);
		ft_close_not_use_fd(cmd, pid);
		exit_code = execute_cmd(cmd, info_env);
		exit (exit_code);
	}
	else
	{
		ft_close_not_use_fd(cmd, pid);
		set_signal(IGN, IGN);
	}
	return ;
}

static void	do_cmd(t_cmd_info *cmd, t_env_info *info_env)
{
	g_exit_signal_code = execute_cmd(cmd, info_env);
	ft_close_not_use_fd(cmd, 1);
}

void	execute(t_cmd_info *cmd_head, t_env_info *info_env)
{
	t_cmd_info	*cmd_cur;

	cmd_cur = cmd_head;
	if (check_valid_token(cmd_head) == -1)
		return (ft_clear_command(cmd_head));
	if (ft_here_init(cmd_cur) == -1)
		return (ft_clear_command(cmd_head));
	while (cmd_cur)
	{
		if (io_file_open(cmd_cur, info_env) == -1)
		{
			cmd_cur = cmd_cur->next;
			continue ;
		}
		if (ft_is_need_fork_cmd(cmd_cur) == true)
			do_fork_cmd(cmd_cur, info_env);
		else
			do_cmd(cmd_cur, info_env);
		cmd_cur = cmd_cur->next;
	}
	wait_child();
	set_signal(SHE, SHE);
	return (ft_clear_command(cmd_head));
}
