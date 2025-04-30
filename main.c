/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:06:38 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/30 12:06:21 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup(int argc, char **argv, t_data *data, t_philo **philos)
{
	if (is_valid(argc, argv))
		return (1);
	print_header();
	init_data(data, argc, argv);
	*philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!*philos)
		return (1);
	init_philo(*philos, data);
	return (0);
}

int	launch_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			data->someone_died = 1;
			return (1);
		}
	}
	return (0);
}

void	join_threads(t_philo *philos, t_data *data, pthread_t monitor)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philos[i].thread, NULL);
	if (data->nb_philos > 1)
		pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor;

	monitor = 0;
	if (setup(argc, argv, &data, &philos))
		return (1);
	if (launch_threads(philos, &data))
		return (free_all(&data, philos), 1);
	if (data.nb_philos > 1)
	{
		if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
			return (free_all(&data, philos), 1);
	}
	join_threads(philos, &data, monitor);
	free_all(&data, philos);
	return (0);
}

//int	main(int argc, char **argv)
//{
//	t_data		data;
//	t_philo		*philos;
//	pthread_t	monitor;
//	int			i;

//	if (is_valid(argc, argv))
//		return (1);
//	print_header();
//	init_data(&data, argc, argv);
//	philos = malloc(sizeof(t_philo) * data.nb_philos);
//	if (!philos)
//		return (1);
//	init_philo(philos, &data);
//	i = -1;
//	while (++i < data.nb_philos)
//	{
//		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
//		{
//			data.someone_died = 1;
//			break ;
//		}
//	}
//	if (data.nb_philos > 1)
//	{
//		if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
//			return (free_all(&data, philos), 1);
//	}
//	i = -1;
//	while (++i < data.nb_philos)
//		pthread_join(philos[i].thread, NULL);
//	if (data.nb_philos > 1)
//		pthread_join(monitor, NULL);
//	free_all(&data, philos);
//	return (0);
//}
