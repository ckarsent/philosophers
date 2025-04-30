/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:26:02 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/30 12:27:03 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_killed(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->someone_died)
		return (pthread_mutex_unlock(&philo->data->death), 1);
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

void	declare_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (!philo->data->someone_died)
	{
		philo->data->someone_died = 1;
		print_status(philo, "died");
	}
	pthread_mutex_unlock(&philo->data->death);
}

int	all_philos_ate_enough(t_philo *philos, t_data *data)
{
	int	i;
	int	done;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		done = philos[i].meals_eaten >= data->nb_meals;
		pthread_mutex_unlock(&philos[i].meal_lock);
		if (!done)
			return (0);
		i++;
	}
	return (1);
}
