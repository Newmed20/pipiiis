/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:47:07 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/06 00:08:30 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include "libft/libft.h"

# define PROMPT "\033[1;31m$ \033[0m"
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

extern int		exit_status;

typedef struct	s_redir t_redir;

enum e_state
{
	IN_SQUOTE,
	IN_DQUOTE,
	GENERAL
};

enum e_type
{
	WORD,
	WHITE_SPACE,
	S_QUOTE,
	D_QUOTE,
	PIPE_LINE,
	ENV,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC
};

typedef struct s_token
{
	char			*content;
	int				len;
	enum e_type		type;
	enum e_state	state;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tkn_lst
{
	t_token	*tokens;
}	t_tkn_lst;

typedef struct	s_env
{
	char			*key;
	char			*value;
	int 			is_valid;
	struct s_env	*next;
}	t_env;

typedef struct s_fds
{
	int					pfd[2];
	int					prev_pfd;
}						t_fds;


typedef struct s_pfds
{
	int					prev_pfd[2];
	int					pfd[2];
}						t_pfds;

typedef struct	s_command
{
	char				*command; // The command name (e.g., "echo", "ls")
	char				*full_path; // The full path to the command (e.g., "/bin/echo", "/bin
	char				**args; // Array of arguments including the command
	int					arg_count; // Number of arguments
	t_redir				*input_files; // For input redirection (<)
	t_redir				*oa_files; // For output redirection (>)
	t_redir				*heredoc_delimiters; // For heredoc (<<)
	t_redir				*heredoc_content; // Content of heredoc
	bool				cmd_found; // if found a command
	int					pipe_out; // 1 if this c , 0 otherwise
	int					pid; // Process ID
	struct s_command	*next; // Pointer to next command in pipeline
}	t_command;


typedef struct s_pipeline
{
	t_pfds				*pfds;
	int					*pids;
	t_command			*current;
	int					i;
	int					original_stdin;
}				t_pipeline;


struct s_redir
{
	void			*content;
	int				type;
	int				state; // 1 for valid expand in herdoc , 0 for invalid expand in herdoc
	struct s_redir	*next;
};

typedef struct	s_data
{
	char		*prompt;
	t_command	*cmd;
	t_env		*env_copy;
	t_tkn_lst	*lexer;
}	t_data;

/* ------------------- errors ------------------- */

int	syntax_error(t_tkn_lst	*lst);
int	print_error(int errror);

/* ------------------- lexer ------------------- */

t_tkn_lst	*lexer(char *line);
void		free_tkn_lst(t_tkn_lst **lst);
void		free_tkn(t_token **tkn);
t_token		*skip_spaces(t_token *el, int flg);

/* ------------------- utils ------------------- */

char	**ft_strdup_2d(char **_2d);
void	free_2d(char **str, int n);
void	free_split(char **arr);
bool	ft_isspace(char c);
char	*ft_strndup(const char *s1, int n);
void	free_env(t_env **env);
void	get_string(t_token **token, t_data *data, char **redir, char **file);
void	free_str(char **str);
int		is_special(char *s);
int		check_empty(t_data *data);

/* ------------------- expander ------------------- */

t_data	*get_env_cpy(t_data *data, char **env);
char	*ft_expand(t_data *data, t_token *token);
char	*get_var_value(t_env *env, char *key);

/* ------------------- parser ------------------- */

void		ft_parser(t_data *data);
int			ft_is_command(t_data *data, t_command *command, char *cmd);
t_redir		*init_list(void);
void		append_to_list(t_redir **lst, t_redir *new);
void		free_command(t_command **cmd);
void		handle_redirections_heredoc(t_token **token, t_command *cmd, t_data *data);
t_redir		*create_redir(t_token **token, t_data *data);
int			is_redir(t_token *token);
void		handle_heredoc(t_token **token, t_command *cmd, t_data *data);
void		lst_add_back(t_command **cmds, t_command *cmd);
t_command	*init_command(void);
t_command	*create_command(t_data *data, t_command *cmd, t_token **token);
void		_first_arg(t_command *cmd, char ***args);
void		tokens_loop(t_data *data, t_token **tmp, t_command **cmd);
void		fill_args(t_token **token, t_command *cmd, t_data *data);

/* ------------------- execution ------------------- */

int     ft_execute(t_data *data);
char 	**ft_transform_env(t_env *env);
void	ft_redirection(t_command *cmd);
void	ft_heredoc(t_command *cmd, t_env *env, int flag);// here-doc
void    execute_multiple(t_data *data, char **env);//pipe
// void     execute_multiple(t_command *cmd, char **envp, t_env **env);
int		ft_isbuitin(char *cmd); //buitins
void	execute_builtins(t_data *data);
int		ft_cd(t_data *data, t_command *command);
int		ft_echo(t_command *s_command);
int		ft_pwd(void);
int     ft_env(t_data *data);
int		ft_exit(t_data *data);
int		ft_export(t_data *data);
int		ft_unset(t_data *data);
void	ft_clear_command(t_command **cmd); // clear
void	free_array(char **array);
void	ft_lstclear_list(t_redir **head);





#endif