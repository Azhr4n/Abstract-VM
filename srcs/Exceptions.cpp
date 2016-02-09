/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 14:22:14 by pivanovi          #+#    #+#             */
/*   Updated: 2015/03/03 14:22:14 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <limits>
#include <iostream>

#include "Exceptions.hpp"

const char	*MissingArgument::what() const throw()
{
	return "Argument is missing.\n";
}

const char	*UnknownInstruction::what() const throw()
{
	return "Unknown instruction.\n";
}

const char	*InvalidValue::what() const throw()
{
	return "Value incorrect.\n";
}

const char	*PopOnEmptyStack::what() const throw()
{
	return "Pop on empty stack.\n";
}

const char	*AssertInstructionNotTrue::what() const throw()
{
	return "Assert instruction is not true.\n";
}

const char	*NotEnoughValueOnStack::what() const throw()
{
	return "Not enough value on the stack.\n";
}

const char	*NoExitCommand::what() const throw()
{
	return "No exit at the end of the file.\n";
}

const char	*DivByZero::what() const throw()
{
	return "Div by 0.\n";
}

void		ValueFlow::additionFlow(eOperandType type, double val1, double val2)
{
	double	under_limit;
	double	over_limit;
	double	dif;

	if (type == Int8)
	{
		under_limit = VALUE_MIN_INT8;
		over_limit = VALUE_MAX_INT8;
	}
	else if (type == Int16)
	{
		under_limit = VALUE_MIN_INT16;
		over_limit = VALUE_MAX_INT16;
	}
	else if (type == Int32)
	{
		under_limit = std::numeric_limits<int>::min();
		over_limit = std::numeric_limits<int>::max();
	}
	else if (type == Float)
	{
		under_limit = std::numeric_limits<float>::lowest();
		over_limit = std::numeric_limits<float>::max();
	}
	else if (type == Double)
	{
		under_limit = std::numeric_limits<double>::lowest();
		over_limit = std::numeric_limits<double>::max();
	}
	dif = over_limit - val1;
	if (val2 > dif)
		throw ValueOverflow();
	dif = under_limit - val1;
	if (val2 < dif)
		throw ValueUnderflow();
}

void		ValueFlow::multiplicationFlow(eOperandType type, double val1, double val2)
{
	double	under_limit;
	double	over_limit;
	double	dif;

	if (type == Int8)
	{
		under_limit = VALUE_MIN_INT8;
		over_limit = VALUE_MAX_INT8;
	}
	else if (type == Int16)
	{
		under_limit = VALUE_MIN_INT16;
		over_limit = VALUE_MAX_INT16;
	}
	else if (type == Int32)
	{
		under_limit = std::numeric_limits<int>::min();
		over_limit = std::numeric_limits<int>::max();
	}
	else if (type == Float)
	{
		under_limit = std::numeric_limits<float>::lowest();
		over_limit = std::numeric_limits<float>::max();
	}
	else if (type == Double)
	{
		under_limit = std::numeric_limits<double>::lowest();
		over_limit = std::numeric_limits<double>::max();
	}
	dif = fabs(over_limit / val2);
	if (abs(val1) > dif)
		throw ValueOverflow();
	dif = fabs(under_limit / val2);
	if (abs(val1) > dif)
		throw ValueUnderflow();
}

const char	*ValueOverflow::what() const throw()
{
	return "Value overflow.\n";
}

const char	*ValueUnderflow::what() const throw()
{
	return "Value underflow.\n";
}
