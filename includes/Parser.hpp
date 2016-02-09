/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:06:39 by pivanovi          #+#    #+#             */
/*   Updated: 2015/03/02 13:06:40 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <fstream>
# include <list>

# include "Factory.hpp"
# include "IOperand.hpp"

class Parser
{
	public:
		Parser(void);
		Parser(const char *path);
		Parser(const Parser &src);
		virtual ~Parser(void);

		void						readFromStdin(void);
		void						readFromFile(void);
		void						execCommand(std::string &buf);

		Parser						&operator=(const Parser &rhs);

	private:
		bool						isPushCommand(std::string &buf, int &current_pos);
		void						pushCommand(std::string &buf, int &current_pos);
		bool						valueIsValid(std::string &buf, int &current_pos);
		std::string					getPushedValue(std::string &buf, int &current_pos);
		bool						isPopCommand(int &current_pos);
		void						popCommand(void);
		void						dumpCommand(void);
		bool						isAssertCommand(std::string &buf, int &current_pos);
		void						assertCommand(std::string &buf, int &current_pos);
		bool						isAddCommand(int &current_pos);
		void						addCommand(void);
		bool						isSubCommand(int &current_pos);
		void						subCommand(void);
		bool						isMulCommand(int &current_pos);
		void						mulCommand(void);
		bool						isDivCommand(int &current_pos);
		void						divCommand(void);
		bool						isModCommand(int &current_pos);
		void						modCommand(void);
		bool						isPrintCommand(int &current_pos);
		void						printCommand(void);
		void						debugCommand(std::string &buf, int &current_pos);

		const char					*_path;
		Factory						_factory;
		std::list<const IOperand *>	_stack;
		bool						_stdin;
		std::ifstream				_ifs;
		bool						_exit;

};

#endif
