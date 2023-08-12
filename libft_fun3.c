/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fun3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:30:59 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/12 11:17:08 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_alpha(char str)
{
	if (str >= 'a' && str <= 'z')
		return (1);
	else if (str >= 'A' && str <= 'Z')
		return (1);
	else
		return (0);
}

int	ft_num(char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	else
		return (0);
}

char	*set_var(char *input, int *i)
{
	int		j;
	char	*var;

	j = 0;
	while (ft_alpha(input[*i + j]) || ft_num(input[*i + j])
		|| input[*i + j] == '_')
		j++;
	var = ft_calloc(j + 2, sizeof(char));
	j = 0;
	var[j++] = '$';
	while (ft_alpha(input[*i]) || ft_num(input[*i]) || input[*i] == '_')
		var[j++] = input[(*i)++];
	var[j] = '\0';
	(*i)--;
	return (var);
}

char	*ft_dollar(char *input, int *i)
{
	char	var[10];

	while (input[*i])
	{
		(*i)++;
		if (input[*i] == '$')
			return (ft_strdup("$$"));
		else if (input[*i] == '@')
			return (ft_strdup(""));
		else if (input[*i] == '?')
			return (ft_strdup("$?"));
		else if (ft_num(input[*i]))
		{
			var[0] = '$';
			var[1] = input[*i];
			var[2] = '\0';
			return (ft_strdup(var));
		}
		else if (ft_alpha(input[*i]) || input[*i] == '_')
			return (set_var(input, i));
		else
			return ((*i)--, ft_strdup("$"));
	}
	return (ft_strdup("$"));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
