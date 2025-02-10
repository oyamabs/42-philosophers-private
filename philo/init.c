/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/spool/mail/freddy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:47:42 by freddy            #+#    #+#             */
/*   Updated: 2025/02/10 16:59:40 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	create_philos(t_params *params, t_philo *philos,
			pthread_mutex_t *forks, char **argv)
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
