#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
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
	HEREDOC,
	ERROR
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	int				quote;
	struct s_token	*next;
}	t_token;

// struct

typedef struct s_data
{
	char	**arg;
	char	**my_env;
}	t_data;

// fonction principal


// fonction utilitaires


// lexer
bool	is_space(char c);
bool	is_operator(char c);
bool	is_word(char c);
bool	is_redir_out(char c);
bool	is_redir_in(char c);
bool	is_append(char c, char d);
bool	is_heredoc(char c, char d);
bool	is_pipe(char c);
bool	is_error_syntax(char c, char d);
char	*get_operator(char *line, int *i);
char	*get_word(char *line, int *i);
void	ft_tokadd_back(t_token **lst, t_token *new);
t_type	what_type(char c, char d);
t_token	*ft_toknew(char *content, t_type token_type);
t_token	*ft_toklast(t_token *lst);
t_token	*lexer(char *line);

// Parsing


// commande a executer built in(cd, env, pwd..ect)


// debugg
void	print_tokens(t_token *tokens);

#endif
