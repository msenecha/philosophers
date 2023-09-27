/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:14:00 by msenecha          #+#    #+#             */
/*   Updated: 2023/09/27 18:05:40 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	init_args(char **argv, t_philo *philo)
{
	philo->nb_philos = ft_atoi(argv[1]);
	philo->tt_die = ft_atoi(argv[2]);
	philo->tt_eat = ft_atoi(argv[3]);
	philo->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals = ft_atoi(argv[5]);
	else
		philo->meals = -1;
}

void	init_philos(t_gen *ptr, t_philo *philo, char **argv, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while(i < ptr->nb_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].dead = ptr->dead_flag;
		philo[i].eating = 0;
		philo[i].eaten = 0;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		init_args(argv, &philo[i]);
		philo[i].display_lock = &ptr->display_lock;
		philo[i].eat_lock = &ptr->eat_lock;
		philo[i].dead_lock = &ptr->dead_lock;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[philo[i].nb_philos - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(t_gen *ptr, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while(i < ptr->nb_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init(char **argv, t_gen *ptr, t_philo *philo, pthread_mutex_t *forks)
{
	ptr->philo = philo;
	ptr->dead_flag = 0;
	ptr->nb_philosophers = ft_atoi(argv[1]);
	pthread_mutex_init(&ptr->dead_lock, NULL);
	pthread_mutex_init(&ptr->eat_lock, NULL);
	pthread_mutex_init(&ptr->display_lock, NULL);
	init_forks(ptr, forks);
	init_philos(ptr, philo, argv, forks);
}
