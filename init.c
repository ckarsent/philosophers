/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:13:23 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/29 12:15:15 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_meals = -1;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	data->start_time = get_time();
	data->someone_died = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
}

void	init_philo(t_philo *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		philos[i].death = &data->death;
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = get_time();
		philos[i].finished = false;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		pthread_mutex_init(&philos[i].meal_lock, NULL);
	}
}
