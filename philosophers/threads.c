/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:27 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/08 19:23:07 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	dead_checker(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->dead_flag == 1) //maybe need *
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	pthread_mutex_unlock(philo->dead_mutex);
	return (0);
}


int create_threads(t_program *program, pthread_mutex_t *forks)
{
  pthread_t monitor_thread;
    int i;
    i = 0;
    if (pthread_create(&monitor_thread, NULL, &monitor, program->philos) != 0)
    {
        clean_up("Thread creation failed", program, forks);
    }
    i = 0;
    while (i < program->philos[0].philo_count)
    {
        if (pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]) != 0)
        {
            clean_up("Thread creation failed", program, forks);
        }
        i++;
    }
    i = 0;
    if (pthread_join(monitor_thread, NULL) != 0)
	    clean_up("Thread join error", program, forks);
    while (i < program->philos[0].philo_count)
    {
        if (pthread_join(program->philos[i].thread, NULL) != 0)
        {
            clean_up("Thread join failed", program, forks);
        }
        i++;
    }
        return(0);
}


void clean_up(char *str, t_program *program, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    if (str)
    {
        write(2, str, ft_strlen(str));
		write(2, "\n", 1);
    }
    pthread_mutex_destroy(&program->output_lock);
    pthread_mutex_destroy(&program->eating_lock);
    pthread_mutex_destroy(&program->dead_lock);
    while (i < program->philos[0].philo_count)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
}



