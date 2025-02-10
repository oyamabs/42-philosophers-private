/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/spool/mail/freddy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:46:16 by freddy            #+#    #+#             */
/*   Updated: 2025/02/10 17:10:14 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		secure_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		secure_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		secure_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		secure_message(philo, "has taken a fork");
	}
	pthread_mutex_lock(philo->meal_check);
	philo->is_eating = true;
	secure_message(philo, "is eating");
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
