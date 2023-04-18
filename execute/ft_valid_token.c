/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:57:32 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/17 19:54:04 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_start_one_pipe(t_cmd_info *cmd)
{
	if (cmd->ft_pipe_flag && cmd->ac == 0)
	{
		print_err1("syntax error near unexpected token `|'");
		g_exit_signal_code = 258;
		return (-1);
	}
	return (0);
}

int	ft_norm(void)
{
	print_err1("syntax error near unexpected token `newline'");
	g_exit_signal_code = 258;
	return (-1);
}

static int	ft_check_redir_files(t_cmd_info *cmd, int i, int ret)
{
	const char	oc[2] = {REDIR_R, '\0'};
	const char	oa[3] = {REDIR_R, REDIR_R, '\0'};
	const char	ic[2] = {REDIR_L, '\0'};
	const char	ia[3] = {REDIR_L, REDIR_R, '\0'};

	if (cmd->ac == 0)
		return (0);
	while (i < cmd->ac)
	{
		if (!ft_strcmp(cmd->cmd_and_av[i], oc) || \
			!ft_strcmp(cmd->cmd_and_av[i], oa))
			if (cmd->cmd_and_av[i + 1] == NULL || \
				ft_strlen(cmd->cmd_and_av[i + 1]) == 0)
				ret = -1;
		if (!ft_strcmp(cmd->cmd_and_av[i], ic) || \
			!ft_strcmp(cmd->cmd_and_av[i], ia))
			if (cmd->cmd_and_av[i + 1] == NULL || \
				ft_strlen(cmd->cmd_and_av[i + 1]) == 0)
				ret = -1;
		if (ret == -1)
			return (ft_norm());
		++i;
	}
	return (0);
}

static int	ft_check_empty_token(t_cmd_info *cmd)
{
	if (cmd->ft_dollar_flag == false && cmd->ac == 1 && \
			!ft_strcmp(cmd->cmd_and_av[0], ""))
	{
		print_err2("", "command not found");
		g_exit_signal_code = 127;
		return (-1);
	}
	return (0);
}

int	check_valid_token(t_cmd_info *cmd)
{
	t_cmd_info	*cur;

	cur = cmd;
	if (ft_check_start_one_pipe(cmd) == -1)
		return (-1);
	if (cur->ac == 0)
		return (-1);
	while (cur)
	{
		if (ft_check_empty_token(cur) == -1)
			return (-1);
		else if (ft_check_redir_files(cur, 0, 0) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
