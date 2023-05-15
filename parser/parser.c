/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:14:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/13 13:22:09 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

/*t_simple_cmd	parse_simple_command()
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = malloc(sizeof(t_simple_cmd));
	return (simple_cmd);
}

t_command	*parse_command()
{
	t_commmand	*command;

	command = malloc(sizeof(t_command));
	command->cmd = parse_simple_command();
	return (command);
}

t_pipe	*parse_pipe()
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->left_child = parse_command();
	pipe->right_child = parse();

	return (pipe);
}

t_ast	*parse(void)
{
	t_ast	*tree;
	t_token	*token;
	
	tree = NULL;
	token = get_token(T_GET);
	if (token->type == T_PIPE)
		printf("syntax error\n");
	parse_command();
	token = get_token(t_GET);
	tree = malloc(sizeof(t_ast));
	tree->type = AST_PIPE;
	tree->data = pipe;
	parse_pipe();
	return (tree);
}*/
