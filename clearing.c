/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:19:35 by msenecha          #+#    #+#             */
/*   Updated: 2023/09/28 09:39:43 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	destroy_everything(t_gen *ptr, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&ptr->display_lock);
	pthread_mutex_destroy(&ptr->eat_lock);
	pthread_mutex_destroy(&ptr->dead_lock);
	while (i < ptr->philo[0].nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

/*
void	clear_threads(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = ptr->philo;
	i = 0;
	while(i < philo[0].nb_philos)
	{
		if (philo[i].dead == 1)
			destroy_everything(philo);
		i++;
	}
}
*/
