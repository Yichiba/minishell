/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:47:14 by yichiba           #+#    #+#             */
/*   Updated: 2023/07/27 23:44:21 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int variable_syntax(char *str)
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

t_env *ft_export(t_env *env,char **tab)
{
	int i = 1;
	char *var_name;
	t_env *ptr = env;
	if(!tab[1])
		while(ptr)
		{
			if(!ptr->str)
				printf("declare -x %s\n",ptr->var);
			else
				printf("declare -x %s=\"%s\"\n",ptr->var, ptr->str);
			ptr = ptr->next;
		}
	else
		while(tab[i])
		{
			var_name = set_variables_name(tab[i]);
			if( variable_syntax(var_name) == 0)
				{
					while(ptr)
					{
						if(ft_strcmp(ptr->var, var_name))
							{
								free(ptr->str);
								ptr->str = set_value(tab[i]);
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

int	ft_strcmp(char *str, char *ptr)
{
	int i = 0;
	while(str[i] && ptr[i])
	{
		if(str[i] != ptr[i])
			return(0);
		i++;
	}
	while(str[i] == 'n')
		i++;
	if(str[i] == '\0')
		return(1);
	return(0);
}

void	ft_echo(char **tab)
{
	int newline = 0;
	int i = 1;
	
	while(tab[i])
	{
		if(ft_strcmp(tab[i],"-n") == 1)
			{
				newline = 1;
				i++;
			}
		else
		while(tab[i])
		{
			printf("%s",tab[i]);
			i++;
		if(tab[i]!= NULL)
			printf(" "); 
		}
	}
	if(newline == 0 )
		printf("\n");
}


void	ft_env(t_env * env) 
{
	t_env *tmp;

	tmp = env;
	while(tmp)
	{
		if(tmp->str)
			printf("%s=%s\n",tmp->var,tmp->str);
		tmp = tmp->next;
	}
}

t_env* ft_remove_node(t_env* env, char* data) 
{
    t_env *previous = NULL;
    t_env *current = env;

    while (current) 
	{
        if (strstr(current->var, data)) 
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
		var_name = set_variables_name(tab[i]);
		if( variable_syntax(var_name) == 0)
			env = ft_remove_node(env,var_name);
		else
			printf("export: not valid in this context: %s\n",var_name);	
		i++;
	}
	return(env);
}

t_env * ft_pwd(t_env *env)
{
	printf("%s\n",getcwd(NULL,0));
	return(env);
}

t_env *    ft_builtins( t_pars *parser, t_env *env)
{
	if(!parser)
		return(env);
	
	if(ft_strcmp(parser->full_cmd[0],"export") == 1)
		env = ft_export(env, parser->full_cmd);
	else if(ft_strcmp(parser->full_cmd[0],"unset") == 1)
		env = ft_unset(env, parser->full_cmd);
	// else if(ft_strcmp(parser->full_cmd[0],"cd") == 1)
	// 	env = ft_cd(env, parser->full_cmd);
	else if(ft_strcmp(parser->full_cmd[0],"pwd") == 1)
		env = ft_pwd(env);
	else if(ft_strcmp(parser->full_cmd[0],"echo")== 1)
		ft_echo(parser->full_cmd);
	else if(ft_strcmp(parser->full_cmd[0],"env")== 1)
		ft_env(env);
	// else if(ft_strstr(parser->full_cmd[0],"exit") == 0)
	// 	env = ft_exit(env, parser->full_cmd);
	return(env);
}