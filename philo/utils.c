/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/spool/mail/freddy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:45:07 by freddy            #+#    #+#             */
/*   Updated: 2025/02/10 16:45:47 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	time = get_timestamp(); // - philo->start;
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
