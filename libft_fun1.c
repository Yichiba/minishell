/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fun1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:09:35 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/11 13:37:37 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoiin(char *str, char *tab, int flag)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(str) + ft_strlen(tab) + 2, sizeof(char));
	while (str && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	if (flag == 1)
		tmp[i++] = '=';
	else if (flag == 0)
		tmp[i++] = '/';
	while (tab && tab[j])
	{
		tmp[i] = tab[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_count(char *str, char sep)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str && str[i])
	{
		if (str[i] == sep)
			counter++;
		i++;
	}
	return (counter + 1);
}

char	*ft_substr(char *str, int start, int end)
{
	char	*tab;
	int		i;

	i = start;
	tab = ft_calloc(end - start + 1, sizeof(char));
	i = 0;
	while (str[start] && start < end)
	{
		tab[i] = str[start];
		start++;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char *str, char sep)
{
	char	**tab;
	int		start;
	int		i;
	int		counter;

	start = 0;
	i = 0;
	counter = 0;
	tab = ft_calloc(sizeof(char *), ft_count(str, ':') + 1);
	while (str && str[i])
	{
		if (str[i] == sep)
		{
			tab[counter++] = ft_substr(str, start, i);
			start = i + 1;
		}
		if (str[i + 1] == '\0')
			tab[counter++] = ft_substr(str, start, i + 1);
		i++;
	}
	tab[counter] = NULL;
	return (tab);
}
