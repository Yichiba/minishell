/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:20:08 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/04 11:51:42 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main()
{
    int fd[2];
    int id;
    int out;
    int in;
    int i = 0;
    
        out = dup(1);
        in = dup(0);
     
        pipe(fd);
        id  = fork();
        if (id == 0)
        {

            // close(fd[0]);
            dup2(fd[1],1);
            printf("%d\n",115);

            close(fd[1]);
        }
        else
        {
            dup2(1,out);
            close(fd[1]);
            dup2(fd[0],0);
            scanf("%d",&id);
            dup2(0,in);
            printf("%d\n",id);
            close(fd[0]);
        }
}