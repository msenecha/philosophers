/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:58:30 by msenecha          #+#    #+#             */
/*   Updated: 2023/09/16 18:11:50 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	init_philos(t_gen *ptr, t_philo *philo, char **argv)
{
	philo->tt_die = ft_atoi(argv[2]);
	philo->tt_eat = ft_atoi(argv[3]);
	philo->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals = ft_atoi(argv[5]);
	else
		philo->meals = -1;
}

void	init_forks(t_gen *ptr, t_philo *forks)
{
	int	i;

	i = 0;
	while(i < ptr->nb_philos)
	{
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
}

void	init(int argc, char **argv, t_gen *ptr, t_philo *philo, t_philo *forks)
{
	ptr->philos = philo;
	ptr->dead_flag = 0;
	ptr->nb_philos = ft_atoi(argv[1]);
	pthread_mutex_init(ptr->dead_lock, NULL);
	pthread_mutex_init(ptr->eat_lock, NULL);
	pthread_mutex_init(ptr->display_lock, NULL);
	init_forks(ptr, forks);
	init_philos(ptr, philo, argv);
}

int	check_param(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (write(1, "Error : Wrong number of arguments\n", 35), 1);
	if (ft_atoi(argv[i]) > 200)
		return(write(1, "Error : Number of philosophers should not be more than 200.\n", 61), 1);
	while (i < (argc - 1))
	{
		if (check_nb(argv[i]) == 1)
			return(write(1, "Error : Arguments are not numerical values\n", 44), 1);
		if (ft_atoi(argv[i]) <= 0)
			return(write(1, "Error : Arguments should be positive values only\n", 50), 1);
		i++;
	}
	if (ft_atoi(argv[i]) < 0 || check_nb(argv[i]) == 1)
		return (write(1, "Error : Number of meals is invalid\n", 36), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_gen	*ptr;
	t_philo	philo[ft_atoi(argv[1])];
	t_philo	forks[ft_atoi(argv[1])];

	if (check_param(argc, argv) == 1)
		return (1);
	ptr = malloc(sizeof(t_gen));
	init(argc, argv, ptr, philo, forks);
	return (0);
}
