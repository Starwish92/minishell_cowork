/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:09:13 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/18 01:22:03 by shane            ###   ########.fr       */
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

static void	ft_exit_with_two_arg(t_cmd_info *cmd)
{
	unsigned long long	check;
	int					exit_code;
	int					sign;

	sign = 1;
	check = ft_atoi_ll(cmd->cmd_and_av[1], &sign);
	exit_code = EXIT_SUCCESS;
	if (cmd->prev == NULL)
		ft_write(STDOUT_FILENO, "exit\n", 5);
	if ((check > 9223372036854775807 && sign == 1) || \
		(check - 9223372036854775807 > 1 + 1 && sign == -1))
	{
		print_err3("exit", cmd->cmd_and_av[1], "numeric argument required");
		exit_code = 255;
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
