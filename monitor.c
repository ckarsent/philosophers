/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:39:10 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/30 12:27:17 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_all_finished(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->death);
		if (!philo[i].finished)
			return (pthread_mutex_unlock(&philo->data->death), false);
		pthread_mutex_unlock(&philo->data->death);
		i++;
	}
	return (true);
}

int	is_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->finished)
		return (pthread_mutex_unlock(&philo->data->death), true);
	return (pthread_mutex_unlock(&philo->data->death), false);
}

int	has_someone_died(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->death);
	res = data->someone_died;
	pthread_mutex_unlock(&data->death);
	return (res);
}

int	check_philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time() - philo->last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death);
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->death);
		print_status(philo, "died");
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		i;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		if (has_someone_died(data))
			break ;
		if (is_all_finished(philos))
			break ;
		i = -1;
		while (++i < data->nb_philos)
		{
			if (is_finished(&philos[i]))
				continue ;
			if (check_philo_death(&philos[i]))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

//void	*monitor_routine(void *arg)
//{
//	t_philo	*philos;
//	t_data	*data;
//	int		i;

//	philos = (t_philo *)arg;
//	data = philos[0].data;
//	while (1)
//	{
//		pthread_mutex_lock(&data->death);
//		if (data->someone_died)
//		{
//			pthread_mutex_unlock(&data->death);
//			break ;
//		}
//		pthread_mutex_unlock(&data->death);
//		if (is_all_finished(philos))
//			break ;
//		i = -1;
//		while (++i < data->nb_philos)
//		{
//			if (is_finished(&philos[i]))
//				continue ;
//			pthread_mutex_lock(&philos[i].meal_lock);
//			if (get_time() - philos[i].last_meal_time > data->time_to_die)
//			{
//				pthread_mutex_lock(&data->death);
//				data->someone_died = 1;
//				pthread_mutex_unlock(&data->death);
//				print_status(&philos[i], "died");
//				pthread_mutex_unlock(&philos[i].meal_lock);
//				return (NULL);
//			}
//			pthread_mutex_unlock(&philos[i].meal_lock);
//		}
//		usleep(1000);
//	}
//	return (NULL);
//}
