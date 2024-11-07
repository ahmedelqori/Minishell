/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 06:35:54 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/01 12:27:07 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLDBLACK "\033[1m\033[30m"
# define BOLDRED "\033[1m\033[31m"
# define BOLDGREEN "\033[1m\033[32m"
# define BOLDYELLOW "\033[1m\033[33m"
# define BOLDBLUE "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN "\033[1m\033[36m"
# define BOLDWHITE "\033[1m\033[37m"

# define TMP_FILE "/tmp/"
# define HERE_DOC "HereDoc $> "
# define COMMAND_NOT_FOUND ": command not found\n"
# define MAX_HERE_DOC " maximum here-document count exceeded\n"
# define FAIL -1
# define SUCCESS 0

typedef struct s_hold
{
	char				*key;
	char				*value;
	struct s_hold		*next;
}						t_hold;

typedef struct s_redirect
{
	char				*str;
	int					flag;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_option
{
	char				*str;
	struct s_option		*next;
}						t_option;

typedef struct s_command
{
	t_redirect			*redirection;
	t_option			*node_options;
	char				**options;
	char				syntax;
	struct s_command	*next;
}						t_command;

typedef struct s_node
{
	int					exit_nb;
	pid_t				last;
	t_command			*command;
}						t_node;

// G    L   O   B   A   L       U    T   I   L   S

char					*ft_strdup(char *s);
void					*ft_memcpy(void *dest, const void *src, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strjoin(char *s1, char *s2);
void					ft_bzero(char *str, int size);
int						ft_strcmp(char *s1, char *s2);
void					print_env(t_hold *current);
void					change_pwd(t_hold **env);
int						is_num(char c);
int						is_alpha(char c);
char					*ft_itoa(int nb);
long					ft_atoi_long(char *str);
void					*ft_global_syntax_check(void);
char					*ft_calloc(int size);
void					copy_content(t_node *content, t_option *list);
void					helper(char **s, char **buffer, t_hold *env,
							t_node *content);
char					*copy_str(char *s);
int						ismatch(char *s, char *p, char *ss, char *pp);
void					copy_quote(char **s, char **buffer, t_hold *env,
							t_node *content);
t_option				*matching_list(char *str, char *ss, char *pp,
							char *buffer);
t_option				*helper2(char *str);
int						has_quote(char *str);
void					add_default(char *str, t_hold **env);
void					set_default(t_hold **lst);
char					*last_argument(char **str);
void					change_variable(t_hold **env, t_command *command);

//  P   A   R   S   I   N   G

void					parsing(t_node *content, char *str, t_hold *env);
void					split_parsing(t_node *content, char *s);
void					parsing_quote(char **temp, char **str);
int						handle_variable(char **temp, char *s2, t_hold *env,
							int i);
int						check_var(char *str, t_hold *env, char *s2, int i);
int						split_command(char *s);
int						copy_nb(t_node *content, char *buffer, int k);
char					*expand_command(t_node *content, char *str,
							t_hold *env);
char					*expand_redirection(t_node *content, char *str,
							int flag, t_hold *env);
int						escape_quote(char **s1, char **p1);
void					del_env(char *str, t_hold **env);
char					*modify_pwd(t_hold **env, char *s1, char *s2,
							char *new);
void					copy(char *s1, char *s2);
char					*expand_buffer(char *str, t_hold *env, t_node *content);
void					update_syntax_status(char x);
void					print_error(t_node *node);
int						check_export(char *str, int *k);
void					print_export_error(char *str);
void					print_cd_error(t_command *content, t_node *node);
unsigned char			unsigned_char_atoi(char *str);
void					redirect_error(t_node *content);
void					escape_space(char **s1, char **s2);
void					copy_list(t_option *list1, t_option **list2);

//  R   E   D   I   R   E   C   T       U   T   I   L   S

t_redirect				*ft_new_redirect(char *buffer, int k);
void					ft_add_redirect(t_redirect **lst, t_redirect *new);
void					free_redirect(t_redirect **lst);

//  O   P   T   I   O   N       U   T   I   L   S

void					ft_add_option(t_option **lst, t_option *new);
t_option				*ft_new_option(char *buffer);
void					free_option(t_option **lst);
void					ft_del_option(t_option **lst);
int						ft_listsize(t_option *node);

//  N   O   D   E       U   T   I   L   S

void					ft_new_node(t_node *new);

//  E   N   V       U   T   I   L   S

t_hold					*ft_new_env(char *buffer_1, char *buffer_2);
void					ft_add_env(t_hold **lst, t_hold *new);
void					free_env(t_hold **lst);
void					initialize_env(t_hold **lst, char **env);
char					*find_value(char *str, char *buffer);
char					*find_key(char *str, char *buffer);

//  C   O   M   M   A   N   D       U   T   I   L   S

void					ft_add_command(t_command **lst, t_command *new);
t_command				*ft_new_command(void);
void					free_command(t_command **lst);
void					ft_del_command(t_command **lst);
int						ft_lstsize(t_command *command);
t_command				*ft_last_command(t_command *node);

//  S   I   G   N   A   L   S

void					ft_signals(void);
void					copy_redirection(char **s1, char **s2);
void					copy_rest(char **temp, char **tmp, t_hold *env,
							t_node *content);
// BUILTIN
void					handle_echo(t_command *content, t_hold **env,
							t_node *node);
void					handle_export(t_command *content, t_hold **env,
							t_node *node);
void					handle_env(t_command *content, t_hold **env,
							t_node *node);
void					handle_unset(t_command *content, t_hold **env,
							t_node *node);
void					handle_pwd(t_command *content, t_hold **env,
							t_node *node);
void					handle_exit(t_command *content, t_hold **env,
							t_node *node);
void					handle_cd(t_command *content, t_hold **env,
							t_node *node);

// execution
void					ft_start_execution(t_node *list, int *fd, t_hold **env);
void					ft_execution(t_node *list, t_hold **env, char c);
void					ft_handle_child(t_node *list, int *files, int *fd,
							t_hold **env);
int						ft_initialize_files(int *files);
void					ft_close_all_files(int *fd, int *files);
void					ft_handle_builtin(t_hold **env, t_node *node,
							t_command *command, int *fd);
int						is_built_in(char *s);
void					ft_handle_builtin_2(t_hold **env, t_node *node,
							t_command *command);
int						ft_strcmp_2(char *s1, char *s2);
char					**ft_creat_env_arr(t_hold *env);
char					*ft_get_right_path(t_hold *env, char *command);
char					*ft_strjoin_1(char const *s1, char const *s2);
int						ft_strcmp_1(char *s1, char *s2);
char					*ft_get_unique_file(void);
void					ft_delete_all_here_doc(t_command *list);
int						ft_handle_heredoc(t_node *list, t_hold *env);
int						ft_open_files(t_node *list, int *files_2, int *files_3);
char					**ft_split(char const *s, char c);
void					*ft_global_exit_status(void);
char					*expand_line(char *str, t_hold *env, t_node *content);
void					ft_wait_all_child_process(t_node *list);
int						ft_help_here_doc(t_node *list, t_hold *env,
							t_redirect *input);
int						ft_len_env(t_hold *env);
int						ft_is_any_file(t_redirect *redirection, int n);
int						ft_open_input_files(t_node *list, int *files_2,
							t_redirect *redirection);
int						ft_open_output_files(t_node *list, int *files_3,
							t_redirect *redirection);
int						ft_open_append_files(t_node *list, int *files_3,
							t_redirect *redirection);
void					ft_dup_close_wait(int org_stdin, int org_stdout,
							t_node *list, t_command *tmp);
void					ft_handle_start_execution(t_node **list, int *fd,
							t_hold **env);
void					ft_handle_erros(char *command, char **args, char **arr,
							t_hold *env);
int						ft_strchr(char *str, char c);
void					ft_handle_sigint(int sig);
void					ft_start(t_node *cur, int *fd, t_hold **env, char c);
void					ft_dup_and_close(int org_stdin, int org_stdout);
void					ft_open_random_file(int *id);
char					*ft_get_unique_file(void);
void					ft_free_array_1(char **arr);
char					*ft_free_and_return(char **arr, char *s);
int						ft_search_env(t_hold *tmp);
void					ft_handle_signal_child_2(int sig);
void					ft_print_error_and_exit(char *command, int nb);
void					ft_putstr_error(char *str);
void					ft_put_env_arr_2(t_hold *t);
#endif
