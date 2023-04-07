/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:47:51 by youjeon           #+#    #+#             */
/*   Updated: 2023/04/05 15:38:53 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utiles.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
# rl_on_new_line, rl_replace_line, rl_redisplay

이 메서드들은 시그널 관리에서 사용했다.몇몇 시그널들은 터미널 관련 메서드를 이용해야 하지만,단순한 시그널(`ctrl + c`)들은 이 rl~ 메서드로 처리가 가능하다.

간단하게 `ctrl + c` 에 대한 처리를 보여주면,

```
write(1, "\n", 1);
rl_on_new_line();
rl_replace_line("", 0);
rl_redisplay();
```

이와 같이 처리했다. 간단하게 설명하면,엔터 입력 후에 `rl_redisplay()`를 통해 `readline` 버퍼를 한 번더 출력해주는 형식이다.

예를들어,`read_line = readline("minishell > ");`이렇게 작성했다면,

```
minishell >
minishell >
```

이렇게 출력해주기 위해서이다.*/

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == IGN)
		signal(SIGINT, SIG_IGN);
	if (sig_int == DFL)
		signal(SIGINT, SIG_DFL);
	if (sig_int == SHE)
		signal(SIGINT, signal_handler);
	if (sig_quit == IGN)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == DFL)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == SHE)
		signal(SIGQUIT, signal_handler);
}
