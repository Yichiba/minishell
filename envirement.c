/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:38:13 by yichiba           #+#    #+#             */
/*   Updated: 2023/06/20 13:27:02 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *str)
{
	int i = 0;

	while(str && str[i])
		i++;
	return(i);
}
int ft_var_name(char *str)
{
	int i = 0;
	while(str[i] && str[i] != '=')
	{
		if(!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z')
			 && !(str[i] >= '0' && str[i] <= '9') && str[i] != '_')
			return(1);
		i++;	
	}
	return(0);
}

// char *set_variable_name(char *str)
// {
// 	int i = 0;
// 	while(str[i] && str[i] != '=')
	
// }

int	ft_strstr(char *str, char *ptr)
{
	int	i;
	int len_ptr;
	int len_str = ft_strlen(str);

	i = 0;
	while(ptr[i] && ptr[i]!= '=')
		i++;
	len_ptr = i;
	
	if(!str)
		return(0);
	i = 0;
	while (str[i] && ptr[i])
	{
		if(str[i] == ptr[i] && len_ptr == len_str)
			return(1);
		i++;
	}
	return (0);
}

t_env* ft_remove_node(t_env* env, char* data) 
{
    t_env *previous = NULL;
    t_env *current = env;

    while (current) 
	{
        if (strstr(current->variable, data)) 
		{
            if (previous == NULL)
			{
                env = current->next;
                free(current);
                current = env;
            }
			else 
			{
				previous->next = current->next;
                free(current);
				return(env);
            }
        } 
		else
		{
            previous = current;
            current = current->next;
		}
    }
    return env;
}

t_env *ft_unset(t_env *env,char **tab)
{
	int i = 1;
	char *var_name;
	while(tab[i])
	{
		var_name = set_variables(tab[i],0);
		if( ft_var_name(var_name) == 0)
			env = ft_remove_node(env,var_name);
		else
			printf("export: not valid in this context: %s\n",var_name);	
		i++;
	}
	return(env);
}
t_env *ft_export(t_env *env,char **tab)
{
	int i = 1;
	char *var_name;
	t_env *ptr = env;
	if(!tab[1])
		while(ptr)
		{
			if(!ptr->str)
				printf("declare -x %s\n",ptr->variable);
			else
				printf("declare -x %s=%s\n",ptr->variable, ptr->str);
			ptr = ptr->next;
		}
	else
		while(tab[i])
		{
			var_name = set_variables(tab[i],0);
			if( ft_var_name(var_name) == 0)
				{
					while(ptr)
					{
						if(ft_strstr(ptr->variable, var_name))
							{
								free(ptr->str);
								ptr->str = set_variables(tab[i],1);
								break;
							}
						if(!ptr->next)
							ptr->next = ft_add_back(tab[i]);
						ptr = ptr->next;	
					}
				}
			else
				printf("export: not valid in this context: %s\n",var_name);
			i++;
		}
	return(env);
}

t_env *ft_builtins(t_env * env, char **tab)
{
	int i = 1;
	t_env *ptr = env;

	if(ft_strstr(tab[0],"export"))
		env = ft_export(env,tab);
	else if(ft_strstr(tab[0],"env"))
		while(ptr)
		{
			if(ptr->str)
				printf("%s=%s\n",ptr->variable, ptr->str);
			ptr = ptr->next;
		}
	else if(ft_strstr(tab[0],"echo"))
		{
			while(tab[i])
			{
				printf("%s",tab[i++]);
				printf(" ");
			}
		printf("\n");
		}
	else if(ft_strstr(tab[0],"unset"))
		env = ft_unset(env,tab);
	return(env);
}
