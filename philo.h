/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:06:48 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/30 12:31:38 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	bool			finished;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*death;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				someone_died;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}					t_data;

/* init.c */
int		init_data(t_data *data, int argc, char **argv);
void	init_philo(t_philo *philos, t_data *data);

/* main.c */
int		setup(int argc, char **argv, t_data *data, t_philo **philos);
int		launch_threads(t_philo *philos, t_data *data);
void	join_threads(t_philo *philos, t_data *data, pthread_t monitor);
int		main(int argc, char **argv);

/* monitor.c */
int		is_all_finished(t_philo *philo);
int		is_finished(t_philo *philo);
int		has_someone_died(t_data *data);
int		check_philo_death(t_philo *philo);
void	*monitor_routine(void *arg);

/* monitor2.c */
int		is_philo_killed(t_philo *philo);
void	declare_death(t_philo *philo);
int		all_philos_ate_enough(t_philo *philos, t_data *data);

/* parsing.c */
int		ft_atoi(char *s);
int		is_valid(int argc, char **argv);

/* philo_utils.c */
int		ft_strcmp(char *s1, char *s2);
void	print_header(void);
void	print_status(t_philo *p, char *msg);
void	free_all(t_data *data, t_philo *philos);

/* routine.c */
void	sleep_and_think(t_philo *philo);
void	set_to_finished(t_philo *philo);
void	handle_one_philo(t_philo *philo);
void	*routine(void *arg);

/* routine2.c */
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	eat(t_philo *philo);

/* time.c */
long	get_time(void);
void	ft_usleep(long time);

#endif
