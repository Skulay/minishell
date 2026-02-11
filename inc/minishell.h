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
# include <stdbool.h>
# include "../libft/libft.h"

# define PROMPT "minishell> "

// enum pour le lexer avec ca liste chainer

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

// struct

typedef struct s_data
{
	char	**path;
}	t_data;

// fonction principal


// fonction utilitaires


// lexer
t_type	what_type(char *str, char c, char d);
bool	is_word(char *str);
bool	is_redir_out(char c);
bool	is_redir_in(char c);
bool	is_append(char c, char d);
bool	is_heredoc(char c, char d);
bool	is_pipe(char c);


// Parsing


// commande a executer (cd, env, pwd..ect)


#endif
