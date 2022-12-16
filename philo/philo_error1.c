/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_error1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 13:02:06 by jbax          #+#    #+#                 */
/*   Updated: 2022/12/16 20:12:00 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// 1	EPERM	Operation not permitted
// 11	EAGAIN	Try again
// 12	ENOMEM	Out of memory
// 22	EINVAL	Invalid argument
// 35	EDEADLK	Resource deadlock would occur
#include <unistd.h>
#include "philo_all.h"

int	time_new(int argc, char **argv, t_philo_time *ph)
{
	int	error;

	error = 0;
	ph->n_philo = ft_atoi(argv[1]);
	ph->t_death = ft_atoi(argv[2]);
	ph->t_eat = ft_atoi(argv[3]);
	ph->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ph->x_eat = ft_atoi(argv[5]);
	else
		ph->x_eat = -3;
	what_error(ph, &error, argc);
	if (error == 1)
		return (1);
	if (ph->n_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ph->t_death * 1000);
		printf("%i 1 died\n", ph->t_death);
		return (1);
	}
	return (0);
}

void	put_s(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i = write(1, str, i);
	if (i < 1)
		write(2, "error can't be writen", 21);
}

int	check_args(int argc)
{
	if (argc < 5)
	{
		put_s("not enouf arg's\n");
		return (1);
	}
	if (argc > 6)
	{
		put_s("to many arg's\n");
		return (1);
	}
	return (0);
}

int	write_error(char *message, int error)
{
	put_s(message);
	return (error);
}

void	what_error(t_philo_time *ph, int *error, int argc)
{
	if ((ph->n_philo) <= 0)
		*error = write_error("number philo's smaller than one\n", 1);
	if ((ph->t_death) <= 0)
		*error = write_error("time to die is smaller than one\n", 1);
	if ((ph->t_eat) <= 0)
		*error = write_error("time to eat is smaller than one\n", 1);
	if ((ph->t_sleep) <= 0)
		*error = write_error("time to sleep is smaller than one\n", 1);
	if (argc == 6 && (ph->x_eat) <= 0)
		*error = write_error("times to eat is smaller than one\n", 1);
}
