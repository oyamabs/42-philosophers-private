/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/mail/freddy>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:45:13 by freddy            #+#    #+#             */
/*   Updated: 2025/02/10 15:51:28 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#define MAX_PHILOSOPHERS 1024

typedef size_t	t_timestamp;
typedef struct s_philo
{
	int	id;
	pthread_t	tid;
	int	meals_count;
	int	min_meals;
	int	philos_count;
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

t_timestamp	get_timestamp()
{
	struct timeval	tv;
	int	returned;

	returned = gettimeofday(&tv, NULL);
	if (returned < 0)
	{
		printf("gettimeofday() shat itself, sucks!\n");
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	secure_message(t_philo *philo, const char *msg)
{
	t_timestamp	time;

	pthread_mutex_lock(philo->write_check);
	time = get_timestamp() - philo->start;
	printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->write_check);
}

void	secure_sleep(t_timestamp time)
{
	t_timestamp	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < time)
		usleep(500);
}

void	armageddon(t_params *params, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < params->philos_number)
	{
		pthread_join(params->philos[i].tid, NULL);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params->death_check);
	pthread_mutex_destroy(&params->write_check);
	pthread_mutex_destroy(&params->meal_check);
}

bool	check_death(t_philo *philo)
{
	bool	death;

	death = false;
	pthread_mutex_lock(philo->death_check);
	if (*philo->is_dead)
		death = true;
	pthread_mutex_unlock(philo->death_check);
	return (death);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	secure_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	secure_message(philo, "has taken a fork");
	philo->is_eating = true;
	secure_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_check);
	philo->last_meal = get_timestamp();
	philo->meals_count++; 
	secure_sleep(philo->meal_time);
	pthread_mutex_unlock(philo->meal_check);
	philo->is_eating = false;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	secure_message(philo, "is sleeping");
	secure_sleep(philo->sleep_time);
}

void	think(t_philo *philo)
{
	secure_message(philo, "is thinking");
}

void	*philo_routine(void *philo)
{
	t_philo	*plato;

	plato = (t_philo *)philo;
	if (plato->id % 2 == 0)
		secure_sleep(1);
	while (!check_death(plato))
	{
		eat(plato);
		philo_sleep(plato);
		think(plato);
	}
	return (philo);
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
		|| ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (false);
	if (argc == 6)
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
	philo->start = get_timestamp();
	philo->last_meal = get_timestamp();
	philo->meal_time = ft_atoi(argv[3]);
	philo->sleep_time = ft_atoi(argv[4]);
	philo->death_time = ft_atoi(argv[2]);
	if (argv[5])
		philo->min_meals = ft_atoi(argv[5]);
	else
		philo->min_meals = -1;

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
		philos[i].philos_count = params->philos_number;
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

bool	check_death_solo(t_philo *philo)
{
	bool	isdead;

	pthread_mutex_lock(philo->death_check);
	pthread_mutex_lock(philo->meal_check);
	isdead = false;
	if (!philo->is_eating && get_timestamp() - philo->last_meal >= philo->death_time)
		isdead = true;
	pthread_mutex_unlock(philo->meal_check);
	pthread_mutex_unlock(philo->death_check);
	return (isdead);
}

bool	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].philos_count)
	{
		if (check_death_solo(&philo[i]))
		{
			secure_message(philo, "is dead");
			pthread_mutex_lock(philo->death_check);
			*philo->is_dead = true;
			pthread_mutex_unlock(philo->death_check);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_if_all_ate(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philo->min_meals == -1)
		return (false);
	while (i < philo->philos_count)
	{
		pthread_mutex_lock(philo->meal_check);
		if (philo[i].meals_count >= philo[i].min_meals)
			finished++;
		pthread_mutex_unlock(philo->meal_check);
		i++;
	}
	if (finished == philo->min_meals)
	{
		pthread_mutex_lock(philo->death_check);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo->death_check);
		return (true);
	}
	return (false);
}

void	*monitoring(void *philo)
{
	t_philo	*descartes;

	descartes = (t_philo *)philo;
	while (true)
	{
		if (check_if_dead(descartes) || check_if_all_ate(descartes))
			break ;
	}
	return (philo);
}

void	create_threads(t_params *params, pthread_mutex_t *forks)
{
	int	i;
	pthread_t	observer;

	if (pthread_create(&observer, NULL, &monitoring, params->philos) != 0)
		armageddon(params, forks);
	i = 0;
	while (i < params->philos_number)
	{
		if (pthread_create(&params->philos[i].tid, NULL, &philo_routine, &params->philos[i]) != 0)
			armageddon(params, forks);
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
		armageddon(params, forks);
	i = 0;
	while (i < params->philos_number)
	{
		if (pthread_join(params->philos[i].tid, NULL))
			armageddon(params, forks);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	philos[MAX_PHILOSOPHERS];
	t_params	params;
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (!check_args(argc, argv))
	{
		printf("Wrong usage: ./philo.out <philosophers> <time to die> <time to eat> <time to sleep> [min number of meals for philosphers]\n");
		return (1);
	}
	init_all(&params, forks, philos, ft_atoi(argv[1]), argv);
	create_threads(&params, forks);
	return (0);
}
