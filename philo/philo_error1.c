/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_error1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 13:02:06 by jbax          #+#    #+#                 */
/*   Updated: 2022/11/29 18:30:43 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// 1	EPERM	Operation not permitted
// 11	EAGAIN	Try again
// 12	ENOMEM	Out of memory
// 22	EINVAL	Invalid argument
// 35	EDEADLK	Resource deadlock would occur
#include <unistd.h>

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

int	error_table(int error)
{
	if (error == 1)
		put_s("error code 1\n");
	else if (error == 11)
		put_s("error code 11\n");
	else if (error == 12)
		put_s("error code 12\n");
	else if (error == 22)
		put_s("error code 22\n");
	else if (error == 35)
		put_s("error code 35\n");
	else if (error)
		put_s("error code ?\n");
	else
		return (0);
	return (1);
}
