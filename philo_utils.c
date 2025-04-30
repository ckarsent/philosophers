/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:31:00 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/30 11:58:15 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	print_header(void)
{
	printf("+-------+-------+---------------------+-------+\n");
	printf("| Time  | Philo | Event               | Emoji |\n");
	printf("+-------+-------+---------------------+-------+\n");
}

void	print_status(t_philo *philo, char *msg)
{
	char	*emoji;

	emoji = "";
	if (!ft_strcmp(msg, "has taken a fork"))
		emoji = "🍴";
	else if (!ft_strcmp(msg, "is eating"))
		emoji = "🍝";
	else if (!ft_strcmp(msg, "is sleeping"))
		emoji = "😴";
	else if (!ft_strcmp(msg, "is thinking"))
		emoji = "💭";
	else if (!ft_strcmp(msg, "died"))
		emoji = "💀";
	pthread_mutex_lock(&philo->data->print);
	if (!is_philo_killed(philo) || !ft_strcmp(msg, "died"))
	{
		printf("| %5ld | %5d | %-20s|   %s  |\n",
			get_time() - philo->data->start_time, philo->id, msg, emoji);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	free_all(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	free(data->forks);
	free(philos);
}
