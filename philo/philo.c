/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/mail/freddy>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:45:13 by freddy            #+#    #+#             */
/*   Updated: 2025/02/03 17:12:35 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int	main(int argc, char **argv)
{
	return (0);
}
