/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:13:54 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/09 20:43:53 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


#define PHILOSOPHERS_MAX 200

typedef struct s_philo
{
    int id;
    int philo_count;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    int num_times_to_eat;
    int meals_eaten;
    size_t last_meal;
    size_t start_time;
    int is_eating;
    int *dead_flag;  
    pthread_t  thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *eating_mutex;
    pthread_mutex_t *output_mutex;
    pthread_mutex_t *dead_mutex;
} t_philo;

typedef struct s_program
{
    t_philo *philos;
    int dead_flag;
    int philo_count;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	output_lock;
}   t_program;


int ft_atoi(const char *str); 
int ft_isdigit(char *str);
//int check_input(int argc, char **argv);
//void convert_input (char **argv, t_philo *philo);
int	check_valid_args(char **argv);
int	check_arg_content(char *arg);
void create_forks(pthread_mutex_t *forks, int philo_count);
void init_program_struct(t_program *program, t_philo *philos);
void initialise_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv);
int create_threads(t_program *program, pthread_mutex_t *forks);
void clean_up(char *str, t_program *program, pthread_mutex_t *forks);
void *routine(void *arg);
void print_timestamp(t_philo *philo, char *action);
int this_philo_dead(t_philo *philo, size_t time_to_die);
int check_if_any_died(t_philo *philos);
int check_all_ate(t_philo *philos);
void *monitor(void *arg);
void philo_think(t_philo *philo);
void philo_sleep(t_philo *philo);
void philo_eat(t_philo *philo);
size_t get_time(void);
int dead_checker(t_philo *philo);
int ft_strlen(const char *str);
void	*one_philo_routine(t_philo *philo);
int	ft_usleep(size_t milliseconds);


