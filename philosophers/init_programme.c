/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_programme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:52:03 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/06 19:21:17 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void convert_input (char **argv, t_philo *philo)
{
    if (!philo)
        return ;
    philo->philo_count = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        philo->num_times_to_eat = ft_atoi(argv[5]);
    else
        philo->num_times_to_eat = -1;
}

void initialise_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv)
{
    int i;;
    i = 0;
    while (i < ft_atoi(argv[1]))
    {
        philos[i].id = i + 1;
        philos[i].is_eating = false;
        philos[i].dead_flag = &program->dead_flag;
        convert_input(argv, &philos[i]);
        philos[i].start_time = get_time();
        philos[i].last_meal = philos[i].start_time;
        philos[i].output_mutex = &program->output_lock;
        philos[i].eating_mutex = &program->eating_lock;
        philos[i].dead_mutex = &program->dead_lock;
        philos[i].left_fork = &forks[i];
        if (i == 0)
            philos[i].right_fork = &forks[philos[i].philo_count - 1];
        else
            philos[i].right_fork = &forks[i - 1];
        i++;
    }
}

void create_forks(pthread_mutex_t *forks, int philo_count)
{
    int i;
    i = 0;
    while (i < philo_count)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void init_program_struct(t_program *program, t_philo *philos)
{
    program->philos = philos;
    program->dead_flag = 0;
    program->philo_count = philos[0].philo_count;
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->eating_lock, NULL);
    pthread_mutex_init(&program->output_lock, NULL);
}
   
     