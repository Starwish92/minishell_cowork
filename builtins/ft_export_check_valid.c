
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

int	ft_valid_identifier_ch(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_specific_char_ch(argv[i], '='))
		{
			print_quote_err3("export", argv[i], "not a valid identifier");
			return (-1);
		}
		if (ft_space_ch(argv[i], '='))
		{
			print_quote_err3("export", argv[i], "not a valid identifier");
			return (-1);
		}
		if (ft_only_digit(argv[i], '='))
		{
			print_quote_err3("export", argv[i], "not a valid identifier");
			return (-1);
		}
		i++;
	}
	return (0);
}
