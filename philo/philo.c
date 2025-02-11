/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/mail/freddy>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:45:13 by freddy            #+#    #+#             */
/*   Updated: 2025/02/11 13:25:47 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		|| ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
		return (false);
	if (argc == 6)
		if (ft_atoi(argv[5]) < 0)
			return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo			philos[MAX_PHILOSOPHERS];
	t_params		params;
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (!check_args(argc, argv))
	{
		printf("Wrong usage: ./philo.out <philosophers> <time to die>"
			" <time to eat> <time to sleep> "
			"[min number of meals for philosphers]\n");
		return (1);
	}
	init_all(&params, forks, philos, argv);
	create_threads(&params, forks);
	return (0);
}
