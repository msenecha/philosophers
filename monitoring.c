/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:04:17 by msenecha          #+#    #+#             */
/*   Updated: 2023/10/26 16:31:32 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

int	check_if_dead(t_philo *philo, size_t tt_die)
{
	pthread_mutex_lock(philo->eat_lock);
	if ((get_current_time() - philo->last_meal) >= tt_die && philo->eating == 0)
	{
		pthread_mutex_unlock(philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

int	check_death(t_philo *philo)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < philo[0].nb_philos)
	{
		if (check_if_dead(&philo[i], philo[i].tt_die) == 1)
		{
			pthread_mutex_lock(philo[i].dead_lock);
			philo[i].flag->dead_flag = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			time = get_current_time() - philo[i].start_time;
			pthread_mutex_lock(philo[i].display_lock);
			printf("%04zu : Philo %d died\n", time, philo[i].id);
			pthread_mutex_unlock(philo[i].display_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_meals_eaten(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philo[0].meals == -1)
		return (0);
	while (i < philo[0].nb_philos)
	{
		pthread_mutex_lock(philo[i].eat_lock);
		if (philo[i].eaten >= philo[i].meals)
			finished++;
		pthread_mutex_unlock(philo[i].eat_lock);
		i++;
	}
	if (finished == philo[0].nb_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		philo[0].flag->dead_flag = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (1)
	{
		if ((check_death(philo) == 1) || (check_meals_eaten(philo) == 1))
			break ;
	}
	return (NULL);
}
