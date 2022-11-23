/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_all.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 15:34:52 by jbax          #+#    #+#                 */
/*   Updated: 2022/11/23 15:15:59 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ALL_H
# define PHILO_ALL_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo_time
{
	int	n_philo;
	int	t_death;
	int	t_eat;
	int	t_sleep;
	int	x_eat;
}				t_philo_time;

typedef struct s_philo_list
{
	t_philo_time		*time;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	struct s_philo_list	*next;
	struct s_philo_list	*back;
	int					philo_id;
	int					*sync;
	pthread_mutex_t		*death;
	int					last_meal;
	pthread_t			thread_id;
}				t_philo_list;

int				time_new(int argc, char **argv, t_philo_time *ph);
int				ft_atoi(const char *str);
void			put_s(char *str);
int				error_table(int error);
t_philo_list	*philo_new(t_philo_time *time, int id, int *synk);
void			philo_addback(t_philo_list **plist, t_philo_list *new);
int				check_args(int argc);

#endif