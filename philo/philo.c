/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/mail/freddy>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:45:13 by freddy            #+#    #+#             */
/*   Updated: 2025/02/03 15:44:26 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/pthreadtypes.h>
typedef struct s_philo
{
	int	id;
	pthread_t	tid;
	int	left_fork_id;
	int	right_fork_id;
}	t_philo;

int	main(int argc, char **argv)
{
	return (0);
}
