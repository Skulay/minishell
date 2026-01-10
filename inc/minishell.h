#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define PROMPT "minishell> "

// struct

typedef struct s_data
{
	char	**path;
}	t_data;

// fonction principal


// fonction utilitaires


// Parsing


// commande a executer (cd, env, pwd..ect)


#endif
