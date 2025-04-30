/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:19:53 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/30 12:28:15 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, "is thinking");
}

void	set_to_finished(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	philo->finished = true;
	pthread_mutex_unlock(philo->death);
}

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	print_status(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->data->death);
	philo->data->someone_died = 1;
	pthread_mutex_unlock(&philo->data->death);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->data->nb_philos == 1)
		return (handle_one_philo(p), NULL);
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (is_philo_killed(p))
			break ;
		take_forks(p);
		if (is_philo_killed(p))
			return (release_forks(p), NULL);
		eat(p);
		if (is_philo_killed(p))
			return (release_forks(p), NULL);
		release_forks(p);
		if (p->data->nb_meals != -1 && p->meals_eaten >= p->data->nb_meals)
			return (set_to_finished(p), NULL);
		if (is_philo_killed(p))
			break ;
		sleep_and_think(p);
	}
	return (NULL);
}
