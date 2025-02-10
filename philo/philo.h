/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/spool/mail/freddy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:41:27 by freddy            #+#    #+#             */
/*   Updated: 2025/02/10 17:04:12 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# define MAX_PHILOSOPHERS 1024

typedef size_t	t_timestamp;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	int				meals_count;
	int				min_meals;
	int				philos_count;
	bool			is_eating;
	bool			*is_dead;
	t_timestamp		sleep_time;
	t_timestamp		meal_time;
	t_timestamp		death_time;
	t_timestamp		start;
	t_timestamp		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_check;
	pthread_mutex_t	*death_check;
	pthread_mutex_t	*meal_check;
}	t_philo;

typedef struct s_params
{
	bool			dead;
	pthread_mutex_t	write_check;
	pthread_mutex_t	death_check;
	pthread_mutex_t	meal_check;
	t_philo			*philos;
	int				philos_number;
}	t_params;

int			ft_atoi(const char *s);
bool		is_arg_digit(char *arg);
t_timestamp	get_timestamp(void);
void		secure_message(t_philo *philo, const char *msg);
void		secure_sleep(t_timestamp time);
void		armageddon(t_params *params, pthread_mutex_t *forks);
bool		check_death(t_philo *philo);
void		eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		think(t_philo *philo);
void		*philo_routine(void *philo);
bool		check_args(int argc, char **argv);
void		create_forks(pthread_mutex_t *forks_arr, int forks);
void		init_timestamps_params(t_philo *philo, char **argv);
void		create_philos(t_params *params, t_philo *philos,
				pthread_mutex_t *forks, char **argv);
void		init_all(t_params *params, pthread_mutex_t *forks,
				t_philo *philos, int philosnum, char **argv);
bool		check_death_solo(t_philo *philo);
bool		check_if_dead(t_philo *philo);
bool		check_if_all_ate(t_philo *philo);
void		*monitoring(void *philo);
void		create_threads(t_params *params, pthread_mutex_t *forks);

#endif
