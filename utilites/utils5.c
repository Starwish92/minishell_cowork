/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:27:56 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/07 15:28:13 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utiles.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while (n-- > 0)
	{
		if (*t1 != *t2 || !*t1 || !*t2)
			return (*t1 - *t2);
		++t1;
		++t2;
	}
	return (0);
}
