/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/mail/freddy>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:45:13 by freddy            #+#    #+#             */
/*   Updated: 2025/02/05 01:12:34 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#define MAX_PHILOSOPHERS 1024

typedef size_t	t_timestamp;
typedef struct s_philo
{
	int	id;
	pthread_t	tid;
	int	meals_count;
	int	min_meals;
	bool	is_eating;
	bool	*is_dead;
	t_timestamp	sleep_time;
	t_timestamp	meal_time;
	t_timestamp	death_time;
	t_timestamp	start;
	t_timestamp	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_check;
	pthread_mutex_t	*death_check;
	pthread_mutex_t	*meal_check;
}	t_philo;

typedef struct s_params
{
	bool	dead;
	pthread_mutex_t	write_check;
	pthread_mutex_t	death_check;
	pthread_mutex_t	meal_check;
	t_philo	*philos;
	int	philos_number;
}	t_params;

int	ft_atoi(const char *s)
{
	int	isnegative;
	int	res;

	res = 0;
	isnegative = 1;
	while (*s == ' ' || *s == '\f' || *s == '\r' || *s == '\v' || *s == '\t'
		|| *s == '\n')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			isnegative = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		s++;
	}
	return (res * isnegative);
}

bool	is_arg_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	check_args(int argc, char **argv)
{
	int	current_arg;

	current_arg = 1;
	if (argc < 5 || argc > 6)
		return (false);
	while (current_arg < argc)
	{
		if (!is_arg_digit(argv[current_arg]))
			return (false);
		current_arg++;
	}
	if (ft_atoi(argv[1]) > MAX_PHILOSOPHERS || ft_atoi(argv[1]) <= 0
		|| ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) || ft_atoi(argv[4]) <= 0)
		return (false);
	if (argv[5])
		if (ft_atoi(argv[5]) < 0)
			return (false);
	return (true);
}

void	create_forks(pthread_mutex_t *forks_arr, int forks)
{
	int	i;

	i = 0;
	while (i < forks)
	{
		pthread_mutex_init(&(forks_arr[i]), NULL);
		i++;
	}
}

void	init_timestamps_params(t_philo *philo, char **argv)
{
	philo->start = 0;
	philo->last_meal = 0;
	philo->meal_time = ft_atoi(argv[2]);
	philo->sleep_time = ft_atoi(argv[3]);
	philo->death_time = ft_atoi(argv[4]);
	if (argv[5])
		philo->min_meals = ft_atoi(argv[5]);
}

void	create_philos(t_params *params, t_philo *philos, pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < params->philos_number)
	{
		philos[i].id = i + 1;
		philos[i].meals_count = 0;
		init_timestamps_params(&philos[i], argv);
		philos[i].is_eating = false;
		philos[i].write_check = &params->write_check;
		philos[i].meal_check = &params->meal_check;
		philos[i].death_check = &params->death_check;
		philos[i].is_dead = &params->dead;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[params->philos_number - 1];
		else
			philos[i].right_fork = &forks[i];
		i++;
	}
}

void	init_all(t_params *params, pthread_mutex_t *forks, t_philo *philos, int philosnum, char **argv)
{
	params->dead = false;
	params->philos = philos;
	params->philos_number = ft_atoi(argv[1]);
	pthread_mutex_init(&(params->meal_check), NULL);
	pthread_mutex_init(&(params->write_check), NULL);
	pthread_mutex_init(&(params->death_check), NULL);
	create_forks(forks, philosnum);
	create_philos(params, philos, forks, argv);
}

int	main(int argc, char **argv)
{
	t_philo	philos[MAX_PHILOSOPHERS];
	t_params	params;
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (!check_args(argc, argv))
		printf("Wrong usage: ./philo.out <philosophers> <time to die> <time to eat> <time to sleep> [min number of meals for philosphers]\n");
	init_all(&params, forks, philos, ft_atoi(argv[1]), argv);
	return (0);
}
