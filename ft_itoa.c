/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:06:33 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/10 12:06:18 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	nchar(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		sl;
	char	*str;

	sl = nchar(n);
	if (n == (-2147483648))
		return (ft_strdup("-2147483648"));
	str = (char *)ft_calloc(sl + 1, sizeof(char));
	if (!str)
		return (0);
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	sl--;
	while (n >= 10)
	{
		str[sl] = (n % 10) + '0';
		n = n / 10;
		sl--;
	}
	if (n < 10)
		str[sl] = n + '0';
	return (str);
}
char	*ft_strchr(const char *s, int c)
{
	int i;
	
	i = 0;
	while(s[i])
	{
		if(s[i] == c)
			return((char *)&s[i]);
		i++;
	}
	if(s[i] == c)
		return((char *)&s[i]);
	return(NULL);
}

char *ft_trim(char *str, char sep)
{
	int i = 0;
	int j = 0;
	int start;
	char *new;
	while(str[i] == sep)
		i++;
	start = i;
	while(str[i])
		{
			if((str[i] == sep && str[i+1] == sep) || (str[i] == sep && str[i+1] == '\0'))
				i++;
			else
			{
				j++;
				i++;
			}
		}
	new = (char *)malloc(j + 1);
	i = start;
	j = 0;
	while(str[i])
	{
		if((str[i] == sep && str[i+1] == sep) || (str[i] == sep && str[i+1] == '\0'))
			i++;
		else
				new[j++] = str[i++];	
	}
	new[j] = '\0';
	if(str)
	{
		free(str);
		str =NULL;
	}
	return(new);
}
