/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:46:29 by mher              #+#    #+#             */
/*   Updated: 2023/04/07 14:31:20 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	**get_envp(t_info_env *head)
{
	int		i;
	int		size;
	char	*key;
	t_info_env	*tmp;
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
		key = ft_strjoin(tmp->key, "=");
		result[i] = ft_strjoin(key, tmp->value);
		i++;
		tmp = tmp->next;
		free(key);
	}
	result[i] = NULL;
	return (result);
}

static int	os_builtins(t_cmd_info *cmd, t_info_env *env_head)
{
	char	*env_path;
	char	**now_env;

	env_path = ft_getenv(env_head, "PATH");
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
	now_env = get_envp(env_head);
	ft_execve(cmd->ft_command_path, cmd->cmd_and_av, now_env);
	return (EXIT_FAILURE);
}

static int	execute_cmd(t_cmd_info *cmd, t_info_env *env_head)
{
	restore_redirection_char(cmd);
	if (!ft_strcmp(cmd->cmd_and_av[0], "echo"))
		return (ft_echo(cmd->ac, cmd->cmd_and_av));
	if (!ft_strcmp(cmd->cmd_and_av[0], "cd"))
		return (ft_cd(cmd->cmd_and_av[1], env_head));
	if (!ft_strcmp(cmd->cmd_and_av[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->cmd_and_av[0], "export"))
		return (ft_export(cmd->ac, cmd->cmd_and_av, env_head));
	if (!ft_strcmp(cmd->cmd_and_av[0], "unset"))
		return (ft_unset(cmd->ac, cmd->cmd_and_av, env_head));
	if (!ft_strcmp(cmd->cmd_and_av[0], "env"))
		return (ft_env(env_head));
	if (!ft_strcmp(cmd->cmd_and_av[0], "exit"))
		return (ft_exit(cmd));
	return (os_builtins(cmd, env_head));
}

static void	do_fork_cmd(t_cmd_info *cmd, t_info_env *env_head)
{
	pid_t	pid;
	int		exit_code;

	set_signal(DFL, DFL);
	pid = ft_fork();
	if (pid == 0)
	{
		redirect(cmd);
		close_unused_fd(cmd, pid);
		exit_code = execute_cmd(cmd, env_head);
		exit (exit_code);
	}
	else
	{
		close_unused_fd(cmd, pid);
		set_signal(IGN, IGN);
	}
	return ;
}

static void	do_cmd(t_cmd_info *cmd, t_info_env *env_head)
{
	g_exit_signal_code = execute_cmd(cmd, env_head);
	close_unused_fd(cmd, 1);
}

void	executor(t_cmd_info *cmd_head, t_info_env *env_head)
{
	t_cmd_info	*cmd_cur;

	cmd_cur = cmd_head;
	if (check_valid_syntax(cmd_head) == -1)
		return (clear_cmd(cmd_head));
	if (init_heredoc(cmd_cur) == -1)
		return (clear_cmd(cmd_head));
	while (cmd_cur)
	{
		if (io_file_open(cmd_cur, env_head) == -1)
		{
			cmd_cur = cmd_cur->next;
			continue ;
		}
		if (is_need_fork(cmd_cur) == true)
			do_fork_cmd(cmd_cur, env_head);
		else
			do_cmd(cmd_cur, env_head);
		cmd_cur = cmd_cur->next;
	}
	wait_child();
	set_signal(SHE, SHE);
	return (clear_cmd(cmd_head));
}
