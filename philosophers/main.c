/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:07:17 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/06 19:23:53 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_philo philos[PHILOSOPHERS_MAX]; //array of structs
    pthread_mutex_t forks[PHILOSOPHERS_MAX]; //array of mutexes
   t_program program;
    
    if (argc < 5 || argc > 6)
        return (write(2, "Invalid number of arguments\n", 29), 1);
    if (check_valid_args(argv) == 1)
        return (1);
    init_program_struct(&program, philos);
    create_forks(forks, ft_atoi(argv[1]));
    initialise_philos(philos, &program, forks, argv);
    create_threads(&program, forks);
    clean_up(NULL, &program, forks);
    return (0);
}

