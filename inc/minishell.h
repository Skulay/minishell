/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 04:17:16 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/22 03:26:40 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell> "

// enum
typedef enum e_expand
{
	NORMAL,
	SOLO_QUOTE,
	DUAL_QUOTE
}					t_expand;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ERROR
}					t_type;

// liste chainer lexer

typedef struct s_token
{
	char			*value;
	t_type			type;
	int				quote;
	struct s_token	*next;
}					t_token;

// struct env

typedef struct s_data
{
	char			**my_env;
	int				last_exit_code;
}					t_data;

// struct pour l'expand

typedef struct s_exstruct
{
	int				i;
	t_expand		state;
	int				make_split;
	char			*result;
	t_data			*env;
}					t_exstruct;

// struct redirection & cmd

typedef struct s_redir
{
	int				type;
	char			*file;
	int				quote;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**arg_cmd;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

// fonction principal

// fonction utilitaires

// lexer
bool				is_space(char c);
bool				is_operator(char c);
bool				is_word(char c);
bool				is_redir_out(char c);
bool				is_redir_in(char c);
bool				is_append(char c, char d);
bool				is_heredoc(char c, char d);
bool				is_pipe(char c);
bool				is_error_syntax(char c, char d);
char				*get_operator(char *line, int *i);
char				*get_word(char *line, int *i);
void				ft_tokadd_back(t_token **lst, t_token *new);
t_type				what_type(char c, char d);
t_token				*ft_toknew(char *content, t_type token_type);
t_token				*ft_toklast(t_token *lst);
t_token				*lexer(char *line);

// Parsing
t_cmd				*parsing(t_token *token, t_data *data);
t_cmd				*parse_cmd(t_token *token);
bool				check_tok(t_token *token);
bool				check_error(t_token *token);
bool				is_redir(int type);
void				add_redir(t_cmd *cmd, t_token *token);
void				add_arg(t_cmd *cmd, char *arg);

// EXPAND
void				expand_redirs(t_cmd *cmd, t_data *data);
void				expand_args(t_cmd *cmd, t_data *data);
void				ft_expand(t_cmd *cmd, t_data *data);
void				ft_dollar(t_exstruct *ex, char *str, t_data *data);
char				*expand_flag(char *str, t_data *data, int *make_split);
char				**expand_split(char *str, t_data *data);
char				**append_all(char **dest, char **src);
int					heredoc_not_quoted(t_redir *redir);
char				*add_var(char *res, char *str, int *i, t_data *env);
char				*add_char(char *str, char c);
char				*add_str(char *res, char *add);
char				*expand_var_quote(char *str, t_data *env);
char				*rm_quotes(char *str);
char				*my_get_env(t_data *data, char *var);
char				*extract_var(char *str, int *i, t_data *data);
int					tab_len(char **tab);
char				**single_to_tab(char *str);

// env
t_data				*make_my_env(char **env);
t_data				*craft_my_env(void);
t_data				*copy_my_env(char **env);
int					maj_shlvl(char **env);

// execution

int					exec_cmd(t_cmd *command, t_data *data);
char				*findvalidpath(char **env, char *binary);
char				*testpath(char **paths, char *binary);
char				*getpath(char **env);
void				execute_pipeline(t_cmd *cmd, t_data *data);
int					is_builtin(char *str);
int					exec_builtin(t_cmd *cmd, t_data *data);

// redirection
int					redirection_manager(t_redir *redir);
// clean up
void				free_tok(t_token *token);
void				free_cmd(t_cmd *cmd);
void				free_tab(char **tab);

// init
t_cmd				*init_cmd(void);

// commande a executer built in(cd, env, pwd..ect)
char				**ft_unset(t_data *data, char *unset);
void				ft_cd(t_data *data, char *str);
int					ft_echo(t_cmd *cmd);
void				ft_env(t_data *data);
void				ft_export(t_data *data);
void				ft_pwd(t_data *data);
int					ft_exit(t_cmd *cmd, t_data *data);

// debugg
void				print_tokens(t_token *tokens);
void				print_cmd(t_cmd *cmd);
void				print_env(t_data *data);

#endif
