/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:28:10 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/18 18:36:47 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_all_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && !ft_isspace(*str) && *str != '-')
			return (0);
		str++;
	}
	return (1);
}

static void	ft_exit_with_no_arg(t_cmd_info *cmd)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->prev == NULL)
		ft_write(STDOUT_FILENO, "exit\n", 5);
	exit(exit_code);
}

static void	ft_exit_with_two_arg2(t_cmd_info *cmd)
{
	int			exit_code;

	exit_code = EXIT_SUCCESS;
	if ((ft_all_number(cmd->cmd_and_av[1]) && \
		ft_strlen(cmd->cmd_and_av[1]) == 2) || \
		(ft_all_number(cmd->cmd_and_av[1]) && \
		ft_strlen(cmd->cmd_and_av[1]) == 1) || \
		(!ft_strcmp(cmd->cmd_and_av[1], "-9223372036854775808")) || \
		(!ft_strcmp(cmd->cmd_and_av[1], "9223372036854775807")))
	{
		if (cmd->prev == NULL)
			ft_write(STDOUT_FILENO, "exit\n", 5);
		exit_code = ft_atoi(cmd->cmd_and_av[1]) % 256;
		exit(exit_code);
	}
}

static void	ft_exit_with_two_arg(t_cmd_info *cmd)
{
	int			exit_code;
	long long	check;

	ft_exit_with_two_arg2(cmd);
	check = ft_atoi(cmd->cmd_and_av[1]);
	exit_code = EXIT_SUCCESS;
	if (cmd->prev == NULL)
		ft_write(STDOUT_FILENO, "exit\n", 5);
	if (check == 0 || check == -1)
	{
		print_err3("exit", cmd->cmd_and_av[1], "numeric argument required");
		exit_code = 255;
		exit(exit_code);
	}
	else if (!ft_all_number(cmd->cmd_and_av[1]))
	{
		print_err3("exit", cmd->cmd_and_av[1], "numeric argument required");
		exit_code = 255;
	}
	else
		exit_code = ft_atoi(cmd->cmd_and_av[1]) % 256;
	exit(exit_code);
}

int	ft_exit(t_cmd_info *cmd)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->ac == 1)
		ft_exit_with_no_arg(cmd);
	else if (cmd->ac == 2)
		ft_exit_with_two_arg(cmd);
	else if (cmd->ac > 2)
	{
		if (!ft_all_number(cmd->cmd_and_av[1]))
			exit_code = 255;
		if (cmd->prev == NULL && exit_code == 255)
		{
			ft_write(STDOUT_FILENO, "exit\n", 5);
			print_err3("exit", cmd->cmd_and_av[1], "numeric argument required");
			exit(exit_code);
		}
	}
	ft_write(STDOUT_FILENO, "exit\n", 5);
	print_err3("exit", NULL, "too many arguments");
	return (0);
}
