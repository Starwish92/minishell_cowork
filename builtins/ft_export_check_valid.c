/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_check_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:09:28 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/17 20:10:00 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_only_digit(char *key_value, char set)
{
	while (*key_value && *key_value != set)
	{
		if (!ft_isdigit(*key_value))
			break ;
		++key_value;
	}
	if (*key_value == set)
		return (1);
	return (0);
}

int	ft_space_ch(char *key_value, char set)
{
	while (*key_value && *key_value != set)
	{
		if (ft_isspace(*key_value))
			break ;
		++key_value;
	}
	if (*key_value == set)
		return (0);
	return (1);
}

int	ft_specific_char_ch(char *key_value, char c)
{
	while (*key_value)
	{
		if (*key_value == c)
			break ;
		++key_value;
	}
	if (*key_value == '\0')
		return (0);
	return (1);
}

int	ft_is_only_key(char *argv)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
			cnt++;
		i++;
	}
	if (cnt == 0)
		return (1);
	return (0);
}

int	ft_valid_identifier_ch(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_is_only_key(argv[1]))
			return (0);
		if (!ft_specific_char_ch(argv[i], '='))
		{
			print_quote_err3("export", argv[i], "not a valid identifier1");
			return (-1);
		}
		if (ft_space_ch(argv[i], '='))
		{
			print_quote_err3("export", argv[i], "not a valid identifier2");
			return (-1);
		}
		if (ft_only_digit(argv[i], '='))
		{
			print_quote_err3("export", argv[i], "not a valid identifier3");
			return (-1);
		}
		i++;
	}
	return (0);
}
