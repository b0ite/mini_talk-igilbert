/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:18:10 by igilbert          #+#    #+#             */
/*   Updated: 2025/01/16 00:31:21 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_charjoin(char *str, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str)
	{
		tmp = malloc(ft_strlen(str) + 5);
		while (str[i])
		{
			tmp[i] = str[i];
			i++;
		}
	}
	else
		tmp = malloc(5);
	tmp[i] = c;
	tmp[i + 1] = '\0';
	if (str)
		free(str);
	return (tmp);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

void	handler(int sig)
{
	static char	c = 0;
	static int	i = 0;
	static char	*str = NULL;

	if (sig == SIGUSR1)
		c = c | (0 << i);
	else if (sig == SIGUSR2)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		str = ft_charjoin(str, c);
		if (c == 0)
		{
			str = ft_charjoin(str, '\n');
			write(1, str, ft_strlen(str));
			free(str);
			str = NULL;
		}
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
    {
    	write(1, "Error setting up signal handlers\n", 33);
        return (1);
    }
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
