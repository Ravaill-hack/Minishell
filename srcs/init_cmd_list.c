/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 11:22:39 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
t_type_fd	ft_find_fd_type(t_token_list *node)
{
	if (node->type == S_LESS || node->type == S_GREAT)
		return (SIMPLE);
	else
		return (DOUBLE);
}

int	ft_choose_fd_in(t_token_list *node, t_type_fd type, t_var *var, t_cmd *cmd)
{
	if (type == SIMPLE)
		return (ft_special_open(node, var));
	else if (type == DOUBLE)
	{
		cmd->heredoc = ft_strdup(str);
		return (0);
	}
}

t_fd	*ft_fd_list_new_node(t_token_list *node, t_var *var)
{
	t_fd	*new;

	new = (t_fd *)malloc(sizeof(t_fd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->type = ft_find_fd_type(node);
	new->fd = ft_choose_fd(node, new->type, var);
	return (new);
}

t_fd	*ft_fd_list_last(t_fd *list)
{
	while (list)
		list = list->next;
	return (list);
}

void	ft_fd_add_back(t_fd *new_fd, t_fd **fd_list)
{
	t_fd	*last;

	last = ft_fd_list_last(*fd_list);
	if (*fd_list == NULL)
		*fd_list = new_fd;
	else
		last->next = new_fd;
}

t_token_list *ft_go_to_next_chevron(t_token_list *node)
{
	node = node->next;
	while (node && node->type != PIPE)
	{
		node = node->next;
		if (node->type == 0 || node->type == 1
		|| node->type == 2 || node->type == 3)
			return (node);
	}
	return (NULL);
}

t_fd	**ft_build_fd(t_token_list	*node, t_var *var)
{
	t_fd	**fd_list;

	fd_list = (t_fd **)malloc(sizeof(t_fd *));
	if (!fd_list)
		return (NULL);
	*fd_list = NULL;
	while (node)
	{
		node = ft_go_to_next_chevron(node); // en realite il faut aller jusqu'a la prochaine valeur et pas le prochain chevron
		if (!node)
			break;
		ft_fd_add_back(ft_fd_new(node, var), fd_list);
	}
	return (fd_list);
}
*/

int	ft_len_new_array(char **old)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (old[i])
	{
		len ++;
		if (old[i][0] == '<' || old[i][0] == '>')
		{
			len --;
			i ++;
		}
		i++;
	}
	return (len);
}

char	**ft_epure_args_array(char **old)
{
	int		len;
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	
	len = ft_len_new_array(old);
	ft_putstr_fd("new nb_lines : ", 1);
	ft_putnbr_fd(len, 1);
	ft_putchar_fd('\n', 1);
	new_array = (char **)malloc((len + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	while (old[i])
	{
		if (old[i][0] != '<' && old[i][0] != '>')
		{
			new_array[j] = ft_strdup(old[i]);
			if (!new_array[j])
				return (ft_free_char_array(new_array, j), NULL);
			j++;
		}
		i++;
	}
	new_array[j] = NULL;
	return (new_array);
}

int		ft_is_path(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

int	ft_nb_opt(char **str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i][0] == '-')
			res++;
		i++;
	}
	return (res);
}

char	**ft_extract_opt_from_array(char **str)
{
	char	**opt_tab;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_nb_opt(str);
	opt_tab = (char **)malloc((len + 1) * sizeof(char *));
	if (!opt_tab)
		return (NULL);
	while (j < len)
	{
		if (str[i][0] == '-')
		{
			opt_tab[j] = ft_strdup(str[i]);
			if (!opt_tab[j])
				return (ft_free_char_array(opt_tab, j), NULL);
			j++;
		}
		i++;
	}
	opt_tab[j] = NULL;
	return (opt_tab);
}

char	*ft_extract_cmd_from_array(t_cmd *node)
{
	int		i;

	i = 0;
	if (!ft_is_path(node->raw[0]))
		return (ft_strdup(node->raw[0]));
	while (node->raw[0][i] != '/')
		i++;
	i++;
	return (ft_strdup(&(node->raw[0][i])));
}

int	ft_check_for_in_redir(t_token_list *node)
{
	while (node && node->type != PIPE)
	{
		if (node->type == S_LESS)
			return (1);
		if (node->type == D_LESS)
			return (2);
	}
	return (0);
}

int	ft_check_for_out_redir(t_token_list *node)
{
	while (node && node->type != PIPE)
	{
		if (node->type == S_GREAT)
			return (1);
		if (node->type == D_GREAT)
			return (2);
	}
	return (0);
}

size_t	ft_strlen_nb(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_is_nb_exit(char *str)
{
	if (str[0] == '?')
		return (1);
	return (0);
}

t_token_list	*ft_go_to_next_node(t_token_list *node)
{
	node = node->next;
	while (node)
	{
		if (node->prev && node->prev->print_space_after == 1 
			&& (node->type != PIPE))
			break;
		node = node->next;
	}
	return (node);
}



char	*ft_dolljoin(char *str, char *doll, char **env)
{
	size_t	src_len;
	size_t	size;
	char	*val_doll;
	char	*joined_str;

	src_len = ft_strlen(str);
	size = ft_strlen(str) + (size_t)ft_doll_val_len(doll, env);
	if (size == 0)
		return (NULL);
	joined_str = (char *)ft_calloc((size + 1), sizeof(char));
	if (!joined_str)
		return (NULL);
	val_doll = ft_extract_env_value_from_key(env, &(doll[1]));
	if (str)
		ft_strlcpy(joined_str, str, src_len + 1);
	if (val_doll)
		ft_strlcat(joined_str, val_doll, size + 1);
	if (!str && !val_doll)
		return (NULL);
	return (joined_str);
}

char	*ft_nb_ex_join(char *str, char *doll, int nb_ex)
{
	size_t	size_tot;
	char	*val_doll;
	char	*joined_str;

	size_tot = ft_strlen(str) + ft_strlen_nb(nb_ex);
	if (doll[2] != '\0')
		size_tot += ft_strlen(&doll[2]);
	joined_str = (char *)ft_calloc((size_tot + 1), sizeof(char));
	if (!joined_str)
		return (NULL);
	val_doll = ft_itoa(nb_ex);
	ft_strlcpy(joined_str, str, ft_strlen(str) + 1);
	ft_strlcat(joined_str, val_doll, ft_strlen(str) + ft_strlen_nb(nb_ex) + 1);
	if (doll[2] != '\0')
		ft_strlcat(joined_str, &(doll[2]), size_tot + 1);
	return (joined_str);
}

char	*ft_dup_operand(t_line_token type)
{
	if (type == S_LESS)
		return (ft_strdup ("<"));
	else if (type == D_LESS)
		return (ft_strdup ("<<"));
	else if (type == S_GREAT)
		return (ft_strdup (">"));
	else if (type == D_GREAT)
		return (ft_strdup (">>"));
	return (NULL);
}

int	ft_find_special_len(t_token_list *node, char **env)
{
	int	len;
	int	len_doll;

	len = 0;
	len_doll = 0;
	while (node && (node->print_space_after == 0 || (node->type != CONTENT
		|| node->type != DOLL)))
	{
		if (node->type == DOLL)
		{
			len_doll = ft_doll_val_len(node->val, env);
			if (len_doll == 0)
				node = node->next;
			else
				len += len_doll;
		}
		else if (node->type == CONTENT)
			len += ft_strlen((const char *)node->val);
		node = node->next;
	}
	return (len);
}

t_token_list	*ft_go_to_cmd_node(t_token_list	*list, int i)
{
	int	ind;

	ind = 0;
	while (list && ind < i)
	{
		if (list->type == PIPE)
			ind++;
		list = list->next;
	}
	return (list);
}

char	*ft_fill_arg(t_token_list *node)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	while (node && (node->type != PIPE))
	{
		tmp = str;	
		if (node->type == CONTENT || node->type == DOLL)
		{
			if (node->type == DOLL && node->val[0] == '\0')
				return (NULL);
			str = ft_strjoin(str, node->val);
		}
		else if (node->type == 0 || node->type == 1 || node->type == 2 || node->type == 3)
			str = ft_dup_operand(node->type);
		if (tmp != str)
			free (tmp);
		if (!str)
			return (NULL);
		if (node->print_space_after != 0)
			break;
		node = node->next;
	}
	return (str);
}

char	**ft_token_list_to_char_array(t_token_list *node)
{
	char	**array;
	int		len;
	int		j;

	len = ft_nb_str(node);
	ft_putnbr_fd(len, 1);
	ft_putchar_fd('\n', 1);
	j = 0;
	array = (char **)malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (j < len)
	{
		array[j] = ft_fill_arg(node);
		//if (!array[j])
		//	return (ft_free_char_array(array, j), NULL);
		node = ft_go_to_next_node(node);
		if (array[j])
			j++;
	}
	array[j] = NULL;
	return (array);
}

t_cmd	*ft_create_cmd_node(t_var *var, int i)
{
	t_token_list	*token_node;
	t_cmd			*cmd_node;

	(void) var;
	cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_node)
		return (NULL);
	token_node = ft_go_to_cmd_node(*(var->token_list), i);
	cmd_node->raw = ft_token_list_to_char_array(token_node);
	if (!cmd_node->raw)
		return (NULL);
	//cmd_node->chev = ft_extract_chev_from_array(cmd_node->raw);
	cmd_node->arg = ft_epure_args_array(cmd_node->raw);
	//cmd_node->cmd = ft_strdup((cmd_node->raw)[0]);
	//cmd_node->fd = ft_build_fd(token_node, var); // A REFAIRE
	//ft_free_char_array(cmd_node->raw, -1);
	return (cmd_node);
}

t_cmd	**ft_build_cmd_list(t_var *var)
{
	t_cmd	**cmd_list;
	int		i;

	i = 0;
	var->nb_cmd = ft_nb_pipes(*(var->token_list)) + 1;
	cmd_list = (t_cmd **)malloc((var->nb_cmd + 1) * sizeof(t_cmd *));
	if(!cmd_list)
		return (NULL);
	while (i < var->nb_cmd)
	{
		cmd_list[i] = ft_create_cmd_node(var, i);
		if (!cmd_list[i])
			return (ft_free_cmd_list(var, cmd_list, i), NULL);
		i++;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}
