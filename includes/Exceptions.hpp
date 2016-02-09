/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 17:53:33 by pivanovi          #+#    #+#             */
/*   Updated: 2015/02/27 17:53:33 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>

#include "IOperand.hpp"

class MissingArgument : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class UnknownInstruction : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class InvalidValue : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class PopOnEmptyStack : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class AssertInstructionNotTrue : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class NotEnoughValueOnStack : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class NoExitCommand : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class DivByZero : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class ValueFlow : public std::exception
{
	public:
		static void			additionFlow(eOperandType type, double val1, double val2);
		static void			multiplicationFlow(eOperandType type, double val1, double val2);
};

class ValueOverflow : public std::exception
{
	public:
		virtual const char	*what() const throw();
};

class ValueUnderflow : public std::exception
{
	public:
		virtual const char	*what() const throw();
};
