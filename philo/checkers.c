/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/spool/mail/freddy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:48:53 by freddy            #+#    #+#             */
/*   Updated: 2025/02/10 16:49:35 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	check_death_solo(t_philo *philo)
{
	bool	isdead;

	pthread_mutex_lock(philo->death_check);
	pthread_mutex_lock(philo->meal_check);
	isdead = false;
	if (get_timestamp() - philo->last_meal >= philo->death_time && !philo->is_eating)
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
			secure_message(philo, "died");
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
