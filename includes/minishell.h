/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:47:54 by epfennig          #+#    #+#             */
/*   Updated: 2021/08/09 11:36:23 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <termcap.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BLUE		"\x1b[34m"
# define GREEN		"\e[1;32m"
# define RESET		"\x1b[0m"

typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char			*content;
}	t_lexer;

typedef struct s_token
{
	enum
	{
		TK_ID,
		TK_EQUALS,
		TK_STRING,
		TK_LPAREN,
		TK_RPAREN,
		TK_PIPE,
		TK_DOLAR,
		TK_ARR_L,
		TK_ARR_R,
		TK_D_ARR_R,
		TK_D_ARR_L,
		TK_SIMPLQ
	} e_type;
	char	*value;
}	t_token;

typedef struct s_env
{
	struct s_env	*previous;
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char		*av;
	int			type;
}	t_cmd;

typedef struct s_data
{
	char				*cmd;

	char				**exec_tab;
	int					nbtabexec;

	t_cmd				**tkcmd;
	t_env				*env;

	char				**tabenv;

	char				*var;
	char				*temp;
	char				**env2;

	int					fd[2];
	int					fd1;
	int					fd2;
	char				**tabdchevr;

	t_env				*new;
	int					i;
	int					j;
	char				*name;
	char				*content;

	char				*buff;
	char				**path;
	int					is_env;
	int					is_fork;
	int					exec;
	int					quoterror;
	int					dotoken;
	int					ac;
	int					is_redir;
	int					is_pipe;
	int					is_dlredir;
	int					arrstart;
	int					on;
	int					ctrlc;
	int					success;

	t_lexer				*lexer;
	t_token				*token;
}	t_data;

/*
** ===================GLOBAL STRUCT==================
** To handle signal and have less args in prototypes
*/
t_data		g_data;
/*
** ==================================================
*/
void		minishell(void);
void		non_builtin_exec(char **cmd, char *path, char **env);
void		free_all(void);
/*
** ====================TOKENIZER=====================
*/
t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token);
t_token		*init_token(int type, char *value);
t_lexer		*init_lexer(char *content);
t_token		*lexer_get_next_token(t_lexer *lexer);
t_token		*lexer_collect_string(t_lexer *lexer);
t_token		*lexer_string_simpleq(t_lexer *lexer, t_token *string);
t_token		*lexer_string(t_lexer *lexer, t_token *string);
t_token		*lexer_collect_id(t_lexer *lexer);
char		*lexer_dollar_id(t_lexer *lexer, char *values, char *s);
char		*lexer_get_current_char_as_string(t_lexer *lexer, int arr);
char		*get_alpha_string(t_lexer *lexer);
void		lexer_back(t_lexer *lexer);
void		lexer_advance(t_lexer *lexer);
void		lexer_isspace_skip(t_lexer *lexer);
int			ft_isprint_token(int c);
/*
** ================FUNCTIONS BUILTINS================
*/
void		ft_exit(char *str);
void		exit_handle(void);
void		changedircd(char *str);
void		echo_handle(int j);
void		affiche_echo(int j, int i);
void		pwd_print(void);
void		boucle_executable(char *cmd, char **env, int j);
void		export_handle(t_data *data);
void		replace_content_env(char *name, char *content);
void		norminette_friendly(t_env *new);
void		env_print(t_data *data);
void		unset_handle(void);
/*
** ===================== SIGNAL =====================
*/
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		echo_control_seq(int c);
/*
** =====================LIST ENV=====================
*/
int			ft_getname(char *var);
char		*ft_getenv(char *var);
void		stock_env(char **ev);
char		**listenv_to_tabstr(int i);
int			get_env_size(void);
t_env		*ft_lstnew(char *name, char *content);
void		ft_lstadd_front(t_env **alst, t_env *new);
void		rl_replace_line(const char *text, int clear_undo);
/*
** =================TOKEN TO PARSING=================
*/
void		choose_cmd(char **env, int j);
void		pre_parser_test(void);
void		tokeniser_loop(void);
char		*ft_realloc(char *src, int size);
/*
** ==================RANDOM UTILS====================
*/
int			get_next_line(int fd, char **line);
void		ascii_minishell(void);
void		free_tab(char **tabfree);
void		ft_error(char *s1, char *s2, char *s3);
int			check_arg(int i, int j, int flag);
void		norme_friendly2(void);
void		init_ij(void);
/*
** ==================REDIRECTION=====================
*/
int			is_pipe(void);
int			is_redirect(void);
int			is_dredirleft(void);
void		ft_pipe(char **env);
void		double_arrow_left(char **tabenv);
void		ft_redirection(char **env, int j);
void		ft_exectab(char **env);
void		double_redir_left(int j, char *line, char **env);
/*
* ====================TABCMD=========================
*/
void		init_exectab(void);
/*
** =================STRUCT_INIT======================
*/
int			init_data(void);

#endif
