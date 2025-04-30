/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:06:41 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/28 18:48:51 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	long	res;
	int		i;

	if (s[0] == '-')
		return (write(2, "need a postive value\n", 21), -1);
	i = 0;
	if (s[0] == '+')
		i++;
	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if (res > INT_MAX)
			return (write(2, "arg overflow\n", 13), -1);
		i++;
	}
	if (s[i] != '\0')
		return (write(2, "non digit char\n", 15), -1);
	return (res);
}

int	is_valid(int argc, char **argv)
{
	int	i;
	int	res;

	if (argc != 5 && argc != 6)
		return (write(2, "wrong number of args\n", 21), 1);
	i = 1;
	while (i < argc)
	{
		res = ft_atoi(argv[i]);
		if (res < 0)
			return (1);
		if (i == 1 && res == 0)
			return (write(2, "need at least 1 philosopher\n", 28), 1);
		i++;
	}
	return (0);
}
