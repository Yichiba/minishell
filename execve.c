/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:03:46 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/05 19:06:49 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoiin(char *str, char *tab,int flag)
{
	int i = 0;
	int j = 0;
	char *tmp;
	tmp = ft_calloc(ft_strlen(str) + ft_strlen(tab) + 2, sizeof(char));
	while(str && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
    if(flag == 1)
        tmp[i++] = '=';
    else if(flag == 0)
        tmp[i++] = '/';
	while(tab && tab[j])
	{
		tmp[i] = tab[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return(tmp);
}

char    **ft_env_to_tab(t_env *env)
{
    char **tab;
    t_env *tmp;
    int i = 0;
    
    tmp = env;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    tab = ft_calloc((i + 1) , sizeof(char *));
    tmp = env;
    i = 0;
    while(tmp)
    {
        tab[i] = ft_strjoiin(tmp->var,tmp->str,1);
        i++;
        tmp = tmp->next;
    }
    tab[i] = NULL;
    return(tab);
}

int ft_count(char *str,char sep)
{
    int i = 0;
    int counter = 0;
    while(str && str[i])
    {
        if(str[i] == sep)
            counter++;
        i++;
    }
    return(counter + 1);
}

char *ft_substr(char *str,int start, int end)
{
    char *tab;
    int i  = start;
   
    tab = ft_calloc(end - start +1, sizeof(char));
    i = 0;
    while(str[start] && start < end)
       {
            tab[i] = str[start];
            start++;
            i++;
       }
    tab[i] = '\0';
     return(tab);
}

char **ft_split(char *str, char sep)
{
    char **tab;
    int start = 0;
    int i ;
    i = 0;
    
    int counter = 0;
    tab = ft_calloc(sizeof(char *),ft_count(str,':')+1);
    while(str && str[i])
    {
        if(str[i] == sep)
        {
            tab[counter++] = ft_substr(str,start,i);
            start = i+1;
        }
        if(str[i+1] == '\0')
            tab[counter++] = ft_substr(str,start,i+1);
        i++;
    }
    tab[counter] = NULL;
    return(tab);
}


char *ft_access(char ** tab,char *cmd)
{
    char *path =NULL;
    int i = 0;
    if(access(cmd,F_OK) == 0)
            return(cmd);
    while(tab[i])
    {
        path = ft_strjoiin(tab[i],cmd,0);
        if(access(path,F_OK) == 0)
                return(path);
        free(path);
        i++;
    }
    printf(" Minishell: %s : command not found.\n", cmd);
    return(NULL);
}


void    ft_excute_cmd(char *path,char **cmd,char **env)
{
    pid_t   pid ;
    int     status;
    pid = fork();
    if(pid == 0)
    {
        execve(path,cmd,env);
    }
    else
    {
        waitpid(pid,&status,0);
    }
}

t_env   *find_commands(t_env *env,t_pars *parser)
{
    char **env_tab=NULL;
    (void)parser;
    char *path = NULL;
    t_env *tmp = NULL;
    char **path_tab;
    tmp = env;
    while(tmp)
    {
        if(tmp->var && ft_strcmp(tmp->var,"PATH"))
        {
            path = tmp->str;
            break;
        }
        tmp = tmp->next;
    }
    env_tab = ft_env_to_tab(env);
    path_tab = ft_split(path,':');
    path = ft_access(path_tab,parser->full_cmd[0]); 
    if(path)
        execve(path,parser->full_cmd,env_tab);
    // ft_excute_cmd(path,parser->full_cmd,env_tab);
    // free(path);
    // for(int i = 0;path_tab[i];i++)
    //     free(path_tab[i]);
    // free(path_tab);
    // for(int i = 0;env_tab[i];i++)
    //     free(env_tab[i]);
    // free(env_tab);
    return(env);
}
