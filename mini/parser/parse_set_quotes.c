/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_set_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:46:53 by youjeon           #+#    #+#             */
/*   Updated: 2023/04/07 14:30:03 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_set_quotes(char line, int quotes, t_cmd_info *cmd) //리턴값 quote, 0으로 초기화된 상태
{
	int	result;

	result = quotes;
	if (line == '$')
		cmd->ft_dollar_flag = true;
	if (line == '\'') // ' 처리
	{
		if (quotes == 1) //2. '가 닫혔다면 다시 result = 0
			result = 0;
		else if (quotes == 2) //닫을게 있을때까지 돔.
			result = 2;
		else //1. '로 들어오면 result = 1
			result = 1;
	}
	else if (line == '\"') // " 처리
	{
		if (quotes == 2) //2. "가 닫혔다면 다시 result를 0으로
			result = 0;
		else if (quotes == 1) //닫을게 있을때까지 돔.
			result = 1;
		else //1. "가 있고 quote가 0이라면 result == 2
			result = 2;
	}
	return (result);
}
