/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:44:06 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 15:50:42 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*parse_in_pipe(char *str, int *pipe, t_cmd_info **cmd, t_cmd_info *next) //str == echo 42
{
	if (*pipe == 1) //파이프 중복 검사
		exit_with_err("argv error", "||", 1);
	(*cmd)->ft_pipe_flag = true;
	//str = echo 42
	(*cmd)->cmd_and_av = ft_split_argc(str, ' ', &((*cmd)->ac));
	//cmd->argv == echo,  
	//cmd->argv == 42,
	next = ft_list_init(); //노드 잇기
	(*cmd)->next = next;
	next->prev = (*cmd);
	(*cmd) = next;
	str = ft_frees(str);
	*pipe = 1;
	return (str);
}

static char	*add_redirect_space(char *str, char *line, char c)
{
	if (c == '>')
	{
		line--;
		if (!(*line == '>' || *line == ' ')) // >> 처리
		{
			str = ft_strjoin_char(str, ' ');
		}
		line++;
		str = ft_strjoin_char(str, -76); // ">" >랑 구분짓기 위해, 실행부에서 따로 처리 필요하다.
		line++;
		if (!(*line == '>' || *line == ' '))
			str = ft_strjoin_char(str, ' ');
	}
	else if (c == '<')
	{
		line--;
		if (!(*line == '<' || *line == ' '))
			str = ft_strjoin_char(str, ' ');
		line++;
		str = ft_strjoin_char(str, -74); // 위와 동일
		line++;
		if (!(*line == '<' || *line == ' '))
			str = ft_strjoin_char(str, ' ');
	}
	return (str);
}

/*
 "<" 와 < 는 실제 동작이 다른데, 이걸 실행부에 넘겨줄 때는 둘 다 < 로 넘어가게 되어있었다.
  이 구조에서는 해결할 방법을 찾지 못해서 파싱 할 때 해당 부분을 음수로 바꿔서 넘기고
	그걸 실행부에서 다시 해석하는 식으로 동작하게 만들었다.
*/

static char	*parse_out_pipe(char *str, char *line, int quotes, int *pipe)
{
	if ((*line == ';' || *line == '\\') && quotes == 0)
		exit_with_err("symbol error", line, 1);
	else if (quotes != 0 && *line == ' ')
		str = ft_strjoin_char(str, -32); //공백처리할때 공백이 스플릿으로 나뉘지지 않게 하는 부분
	else if (quotes == 0 && ft_isspace(*line))
		str = ft_strjoin_char(str, ' ');
	else if ((*line == '>' || *line == '<') && quotes == 0)
		str = add_redirect_space(str, line, *line);
	else
	{
		str = ft_strjoin_char(str, line[0]); //캐릭터 하나씩.
		*pipe = 0; //파이프 다시 사용 가능하게 초기화
	}
	return (str);
}

void	parse(char *line, t_cmd_info *cmd)
{
	t_cmd_info	*next;
	char	*str;
	int		quotes;
	int		pipe;

	str = NULL;
	next = NULL;
	quotes = 0;
	pipe = 0;
	while (*line) //캐릭터 하나씩 검사
	{
		quotes = parse_set_quotes(*line, quotes, cmd); // ', "처리. 짝이 맞는지 돌면서 확인
		if (*line == '|' && quotes == 0) //', "가 짝이 맞거나 없거나
			str = parse_in_pipe(str, &pipe, &cmd, next);
		else
			str = parse_out_pipe(str, line, quotes, &pipe);
		line++;
	}
	if (quotes != 0) //', "짝이 맞지 않는다
		exit_with_err("quotes error", NULL, 1);
	if (str != NULL)
	{
		cmd->cmd_and_av = ft_split_argc(str, ' ', &(cmd->ac));
		str = ft_frees(str);
	}
}
