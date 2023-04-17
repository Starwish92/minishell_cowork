/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:08:58 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/17 20:09:57 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_option_ch(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strncmp(str, "-n", 2))
		return (0);
	++str;
	while (*str == 'n')
		str++;
	if (*str != 0)
		return (0);
	return (1);
}

static int	ft_option_ch_n(int argc, char **argv, int *index)
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	if (argc == 1)
		return (0);
	option_n = ft_option_ch(argv[i]);
	while (i < argc && ft_option_ch(argv[i]))
		++i;
	*index = i;
	return (option_n);
}

int	ft_echo(int argc, char **argv)
{
	int	index;
	int	option_n;

	index = 1;
	option_n = ft_option_ch_n(argc, argv, &index);
	while (index < argc && argv[index])
	{
		ft_write(STDOUT_FILENO, argv[index], ft_strlen(argv[index]));
		if (index + 1 != argc)
			ft_write(STDOUT_FILENO, " ", 1);
		++index;
	}
	if (option_n == 0)
		ft_write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
