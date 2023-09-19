/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:58:30 by msenecha          #+#    #+#             */
/*   Updated: 2023/09/19 17:10:57 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	create_threads(t_gen *ptr)
{
	int	i;
	pthread_t	monitor;

	i = 0;
	pthread_create(&monitor, NULL, monitoring, ptr->philo);
	while(i < ptr->philo[i].nb_philos)
	{
		pthread_create(&ptr->philo[i].thread, NULL, routine, &ptr->philo[i]);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < ptr->philo[i].nb_philos)
	{
		pthread_join(ptr->philo[i].thread, NULL);
		i++;
	}
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
	t_gen			*ptr;
	t_philo			philo[ft_atoi(argv[1])];
	pthread_mutex_t	forks[ft_atoi(argv[1])];

	if (check_param(argc, argv) == 1)
		return (1);
	ptr = malloc(sizeof(*ptr));
	init(argv, ptr, philo, forks);
	create_threads(ptr);
	return (0);
}
