/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:12:36 by pivanovi          #+#    #+#             */
/*   Updated: 2015/03/02 13:12:37 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <stdlib.h>
#include <sstream>

#include "Parser.hpp"
#include "Exceptions.hpp"

Parser::Parser(void) : _exit(false)
{
	_stdin = false;
}

Parser::Parser(const char *path) : _path(path)
{
	_stdin = true;
	_ifs.open(path);
}

Parser::Parser(const Parser &src)
{
	*this = src;
}

Parser::~Parser(void)
{
	const IOperand	*tmp;

	if (_stdin)
		_ifs.close();
	while (!_stack.empty())
	{
		tmp = _stack.front();
		_stack.pop_front();
		delete tmp;
	}
}

void		Parser::readFromStdin(void)
{
	std::list<std::string>				list;
	std::list<std::string>::iterator	it;
	bool								stop = false;
	std::string							buf;

	if (!_stdin)
	{
		while (!stop)
		{
			getline(std::cin, buf);
			list.push_back(buf);
			if (!std::strncmp(list.back().c_str(), ";;", 2))
				stop = true;
		}
		buf.clear();
		it = list.begin();
		while (it != list.end())
		{
			buf += *it;
			if (*it == "exit")
				_exit = true;
			buf += '\n';
			it++;
		}
	}
	if (!_exit)
		throw NoExitCommand();
	try {
		execCommand(buf);
	}
	catch (UnknownInstruction &e) {
		std::cout << e.what();
	}
}

void		Parser::readFromFile(void)
{
	std::string		buf;
	char			buffer[1024];

	if (_ifs.is_open())
	{
		while (_ifs.getline(buffer, 1024))
		{
			buf += buffer;
			buf += '\n';
			if (!std::strncmp("exit", buffer, 4))
				_exit = true;
		}
		if (!_exit)
			throw NoExitCommand();
		try {
			execCommand(buf);
		}
		catch (UnknownInstruction &e) {
			std::cout << e.what();
		}
	}
}

void		Parser::execCommand(std::string &buf)
{
	int			current_pos = 0;
	bool		stop = false;

	while (buf[current_pos] && !stop)
	{
		if (buf[current_pos] == ' ' || buf[current_pos] == '\t' || buf[current_pos] == '\n')
			current_pos++;
		else if (buf[current_pos] == ';' && buf[current_pos + 1] != ';')
		{
			while (buf[current_pos] != '\n')
				current_pos++;
			current_pos++;
		}
		else if (!std::strncmp(&buf[current_pos], "push", 4))
			stop = isPushCommand(buf, current_pos);
		else if (!std::strncmp(&buf[current_pos], "pop", 3))
			stop = isPopCommand(current_pos);
		else if (!std::strncmp(&buf[current_pos], "dump", 4))
		{
			current_pos += 4;
			dumpCommand();
		}
		else if (!std::strncmp(&buf[current_pos], "assert", 6))
			stop = isAssertCommand(buf, current_pos);
		else if (!std::strncmp(&buf[current_pos], "add", 3))
			stop = isAddCommand(current_pos);
		else if (!std::strncmp(&buf[current_pos], "sub", 3))
			stop = isSubCommand(current_pos);
		else if (!std::strncmp(&buf[current_pos], "mul", 3))
			stop = isMulCommand(current_pos);
		else if (!std::strncmp(&buf[current_pos], "div", 3))
			stop = isDivCommand(current_pos);
		else if (!std::strncmp(&buf[current_pos], "mod", 3))
			stop = isModCommand(current_pos);
		else if (!std::strncmp(&buf[current_pos], "print", 5))
			stop = isPrintCommand(current_pos);
		else if (!std::strncmp(&buf[current_pos], "debug", 5))
			debugCommand(buf, current_pos);
		else if (!std::strncmp(&buf[current_pos], "exit", 4))
		{
			current_pos += 4;
			_exit = true;
		}
		else if (!std::strncmp(&buf[current_pos], ";;", 2))
			stop = true;
		else
		{
			throw UnknownInstruction();
			stop = true;
		}
	}
}

bool		Parser::isPushCommand(std::string &buf, int &current_pos)
{
	current_pos += 4;
	try {
		pushCommand(buf, current_pos);
	}
	catch (MissingArgument &e) {
		std::cout << e.what();
		return true;
	}
	catch (InvalidValue &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::pushCommand(std::string &buf, int &current_pos)
{
	std::string		value;

	while ((buf[current_pos] == ' ' || buf[current_pos] == '\t') && buf[current_pos])
		current_pos++;
	if (!std::strncmp(&buf[current_pos], "int8", 4))
	{
		current_pos += 4;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			_stack.push_front(_factory.createInt8(value));
		}
	}
	else if (!std::strncmp(&buf[current_pos], "int16", 5))
	{
		current_pos += 5;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			_stack.push_front(_factory.createInt16(value));
		}
	}
	else if (!std::strncmp(&buf[current_pos], "int32", 5))
	{
		current_pos += 5;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			_stack.push_front(_factory.createInt32(value));
		}
	}
	else if (!std::strncmp(&buf[current_pos], "float", 5))
	{
		current_pos += 5;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			_stack.push_front(_factory.createFloat(value));
		}
	}
	else if (!std::strncmp(&buf[current_pos], "double", 6))
	{
		current_pos += 6;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			_stack.push_front(_factory.createDouble(value));
		}
	}
	else
		throw MissingArgument();
}

std::string	Parser::getPushedValue(std::string &buf, int &current_pos)
{
	std::ostringstream	os;
	double				value;

	current_pos++;
	value = atof(&buf[current_pos]);
	if (!valueIsValid(buf, current_pos))
		return "";
	os << std::fixed << value;
	current_pos++;
	return os.str();
}

bool		Parser::valueIsValid(std::string &buf, int &current_pos)
{
	int		point = 0;

	if (buf[current_pos] == '-')
		current_pos++;
	while ((buf[current_pos] <= '9' && buf[current_pos] >= '0') || buf[current_pos] == '.')
	{
		if (buf[current_pos] == '.')
		{
			if (point)
				return false;
			else
				point = 1;
		}
		current_pos++;
	}
	if (buf[current_pos] == ')')
		return true;
	return false;
}

bool		Parser::isPopCommand(int &current_pos)
{
	current_pos += 3;
	try {
		popCommand();
	}
	catch (PopOnEmptyStack &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::popCommand(void)
{
	if (_stack.empty())
		throw PopOnEmptyStack();
	_stack.pop_front();
}

void		Parser::dumpCommand(void)
{
	std::list<const IOperand *>::iterator	it;

	for (it = _stack.begin(); it != _stack.end(); it++)
		std::cout << std::fixed << (*it)->toString() << std::endl;
}

bool		Parser::isAssertCommand(std::string &buf, int &current_pos)
{
	current_pos += 6;
	try {
		assertCommand(buf, current_pos);
	}
	catch (AssertInstructionNotTrue &e) {
		std::cout << e.what();
		return true;
	}
	catch (NotEnoughValueOnStack &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::assertCommand(std::string &buf, int &current_pos)
{
	std::string		value;
	const IOperand	*val;

	if (_stack.empty())
		throw NotEnoughValueOnStack();
	while ((buf[current_pos] == ' ' || buf[current_pos] == '\t') && buf[current_pos])
		current_pos++;
	if (!std::strncmp(&buf[current_pos], "int8", 4))
	{
		current_pos += 4;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			val = _factory.createInt8(value);
		}
	}
	else if (!std::strncmp(&buf[current_pos], "int16", 5))
	{
		current_pos += 5;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			val = _factory.createInt16(value);
		}
	}
	else if (!std::strncmp(&buf[current_pos], "int32", 5))
	{
		current_pos += 5;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			val = _factory.createInt32(value);
		}
	}
	else if (!std::strncmp(&buf[current_pos], "float", 5))
	{
		current_pos += 5;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			val = _factory.createFloat(value);
		}
	}
	else if (!std::strncmp(&buf[current_pos], "double", 6))
	{
		current_pos += 6;
		if (buf[current_pos] == '(')
		{
			value = getPushedValue(buf, current_pos);
			if (value.empty())
				throw InvalidValue();
			val = _factory.createDouble(value);
		}
	}
	else
		throw MissingArgument();
	if (val->toString() != _stack.front()->toString() || val->getType() != _stack.front()->getType())
	{
		delete val;
		throw AssertInstructionNotTrue();
	}
}

bool		Parser::isAddCommand(int &current_pos)
{
	current_pos += 3;
	try {
		addCommand();
	}
	catch (NotEnoughValueOnStack &e) {
		std::cout << e.what();
		return true;
	}
	catch (ValueUnderflow &e) {
		std::cout << e.what();
		return true;
	}
	catch (ValueOverflow &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::addCommand(void)
{
	const IOperand	*val1;
	const IOperand	*val2;
	const IOperand	*result;

	if (_stack.size() < 2)
		throw NotEnoughValueOnStack();
	val1 = _stack.front();
	popCommand();
	val2 = _stack.front();
	popCommand();
	try {
		result = *val2 + *val1;
	}
	catch (ValueUnderflow &e) {
		throw ValueUnderflow();
	}
	catch (ValueOverflow &e) {
		throw ValueOverflow();
	}
	_stack.push_front(result);
	delete val1;
	delete val2;
}

bool		Parser::isSubCommand(int &current_pos)
{
	current_pos += 3;
	try {
		subCommand();
	}
	catch (NotEnoughValueOnStack &e) {
		std::cout << e.what();
		return true;
	}
	catch (ValueUnderflow &e) {
		std::cout << e.what();
		return true;
	}
	catch (ValueOverflow &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::subCommand(void)
{
	const IOperand	*val1;
	const IOperand	*val2;
	const IOperand	*result;

	if (_stack.size() < 2)
		throw NotEnoughValueOnStack();
	val1 = _stack.front();
	popCommand();
	val2 = _stack.front();
	popCommand();
	try {
		result = *val2 - *val1;
	}
	catch (ValueUnderflow &e) {
		throw ValueUnderflow();
	}
	catch (ValueOverflow &e) {
		throw ValueOverflow();
	}
	_stack.push_front(result);
	delete val1;
	delete val2;
}

bool		Parser::isMulCommand(int &current_pos)
{
	current_pos += 3;
	try {
		mulCommand();
	}
	catch (NotEnoughValueOnStack &e) {
		std::cout << e.what();
		return true;
	}
	catch (ValueUnderflow &e) {
		std::cout << e.what();
		return true;
	}
	catch (ValueOverflow &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::mulCommand(void)
{
	const IOperand	*val1;
	const IOperand	*val2;
	const IOperand	*result;

	if (_stack.size() < 2)
		throw NotEnoughValueOnStack();
	val1 = _stack.front();
	popCommand();
	val2 = _stack.front();
	popCommand();
	try {
		result = *val2 * *val1;
	}
	catch (ValueUnderflow &e) {
		throw ValueUnderflow();
	}
	catch (ValueOverflow &e) {
		throw ValueOverflow();
	}
	_stack.push_front(result);
	delete val1;
	delete val2;
}

bool		Parser::isDivCommand(int &current_pos)
{
	current_pos += 3;
	try {
		divCommand();
	}
	catch (NotEnoughValueOnStack &e) {
		std::cout << e.what();
		return true;
	}
	catch (DivByZero &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::divCommand(void)
{
	const IOperand	*val1;
	const IOperand	*val2;
	const IOperand	*result;

	if (_stack.size() < 2)
		throw NotEnoughValueOnStack();
	if (_stack.front()->toString() == "0")
		throw DivByZero();
	val1 = _stack.front();
	popCommand();
	val2 = _stack.front();
	popCommand();
	result = *val2 / *val1;
	_stack.push_front(result);
	delete val1;
	delete val2;
}

bool		Parser::isModCommand(int &current_pos)
{
	current_pos += 3;
	try {
		modCommand();
	}
	catch (NotEnoughValueOnStack &e) {
		std::cout << e.what();
		return true;
	}
	catch (DivByZero &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::modCommand(void)
{
	const IOperand	*val1;
	const IOperand	*val2;
	const IOperand	*result;

	if (_stack.size() < 2)
		throw NotEnoughValueOnStack();
	if (_stack.front()->toString() == "0")
		throw DivByZero();
	val1 = _stack.front();
	popCommand();
	val2 = _stack.front();
	popCommand();
	result = *val2 % *val1;
	_stack.push_front(result);
	delete val1;
	delete val2;
}

bool		Parser::isPrintCommand(int &current_pos)
{
	current_pos += 5;
	try {
		printCommand();
	}
	catch (AssertInstructionNotTrue &e) {
		std::cout << e.what();
		return true;
	}
	catch (NotEnoughValueOnStack &e) {
		std::cout << e.what();
		return true;
	}
	return false;
}

void		Parser::printCommand(void)
{
	if (!_stack.empty())
	{
		if (_stack.front()->getPrecision() != eOperandType(Int8))
			throw AssertInstructionNotTrue();
		else
		{
			char					a = 0;
			int						tmp;
			std::istringstream		stream(_stack.front()->toString());

			stream >> tmp;
			if (tmp >= 0)
				a = tmp;
			std::cout << a << std::endl;
		}
	}
	else
		throw NotEnoughValueOnStack();
}

void		Parser::debugCommand(std::string &buf, int &current_pos)
{
	int	next_pos;

	current_pos += buf.substr(current_pos).find('\"') + 1;
	next_pos = current_pos + buf.substr(current_pos).find('\"');
	if (next_pos != -1)
	{
		while (current_pos != next_pos)
		{
			std::cout << buf[current_pos];
			current_pos++;
		}
		current_pos++;
		std::cout << std::endl;
	}
}

Parser		&Parser::operator=(const Parser &rhs)
{
	(void)rhs;
	return (*this);
}
