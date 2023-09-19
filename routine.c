/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:15:12 by msenecha          #+#    #+#             */
/*   Updated: 2023/09/19 16:08:08 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	ft_sleep(t_philo *philo)
{
	print_actions("is sleeping", philo->id, philo);
	ft_usleep(philo->tt_sleep);
}

void	ft_think(t_philo *philo)
{
	print_actions("is thinking", philo->id, philo);
}

void	ft_eat(t_philo *philo)
{
	philo->start_time = get_current_time();
	pthread_mutex_lock(philo->r_fork);
	print_actions("has taken a fork", philo->id, philo);
	pthread_mutex_lock(philo->l_fork);
	print_actions("has taken a fork", philo->id, philo);
	pthread_mutex_lock(philo->eat_lock);
	philo->eating = 1;
	print_actions("is eating", philo->id, philo);
	ft_usleep(philo->tt_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->eat_lock);
	philo->last_meal = get_current_time();
	philo->eaten += 1;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	dead_loop(t_philo *ptr)
{
	pthread_mutex_lock(ptr->dead_lock);
	if (ptr->dead == 1)
	{
		pthread_mutex_unlock(ptr->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(ptr->dead_lock);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (ptr);
}
