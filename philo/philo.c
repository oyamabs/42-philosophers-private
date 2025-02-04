/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/mail/freddy>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:45:13 by freddy            #+#    #+#             */
/*   Updated: 2025/02/05 00:20:28 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_PHILOSOPHERS 1024

typedef size_t	t_timestamp;
typedef struct s_philo
{
	int	id;
	pthread_t	tid;
	int	meals_count;
	int	min_meals;
	bool	is_eating;
	t_timestamp	sleep_time;
	t_timestamp	meal_time;
	t_timestamp	thinking_time;
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

int	main(int argc, char **argv)
{
	t_philo	philos[MAX_PHILOSOPHERS];
	t_params	params;
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (!check_args(argc, argv))
		printf("Wrong usage: ./philo.out <philosophers> <time to die> <time to eat> <time to sleep> [min number of meals for philosphers]\n");
	return (0);
}
