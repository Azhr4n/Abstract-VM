/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 18:29:02 by pivanovi          #+#    #+#             */
/*   Updated: 2015/01/26 18:29:03 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TOperand.hpp"
#include "Factory.hpp"

#include <cstdio>

typedef const IOperand *(Factory::*IOptr)(const std::string&);

Factory::Factory(void)
{
	_tab[0] = &Factory::createInt8;
	_tab[1] = &Factory::createInt16;
	_tab[2] = &Factory::createInt32;
	_tab[3] = &Factory::createFloat;
	_tab[4] = &Factory::createDouble;
}

Factory::Factory(const Factory &src)
{
	*this = src;
}

Factory::~Factory(void)
{

}

const IOperand	*Factory::createInt8(const std::string &value) const
{
	std::istringstream		stream(value);
	int						val;

	stream >> val;
	if (val > VALUE_MAX_INT8)
	{
		val = val % (-VALUE_MAX_INT8) - 1;
		val = VALUE_MIN_INT8 + val;
	}
	else if (val < VALUE_MIN_INT8)
	{
		val = val % (-VALUE_MIN_INT8) + 1;
		val = VALUE_MAX_INT8 + val;
	}
	TOperand<int> *ret = new TOperand<int>(val, Int8);
	return (ret);
}

const IOperand	*Factory::createInt16(const std::string &value) const
{
	std::istringstream		stream(value);
	int						val;

	stream >> val;
	if (val > VALUE_MAX_INT16)
	{
		val = val % VALUE_MAX_INT16 - 1;
		val = VALUE_MIN_INT16 + val;
	}
	else if (val < VALUE_MIN_INT16)
	{
		val = val % (-VALUE_MIN_INT16) + 1;
		val = VALUE_MAX_INT16 + val;
	}
	TOperand<int> *ret = new TOperand<int>(val, Int16);
	return (ret);
}

const IOperand	*Factory::createInt32(const std::string &value) const
{
	std::istringstream		stream(value);
	int						val;

	stream >> val;
	TOperand<int> *ret = new TOperand<int>(val, Int32);
	return (ret);
}

const IOperand	*Factory::createFloat(const std::string &value) const
{
	std::istringstream		stream(value);
	float					val;

	stream >> val;
	TOperand<float> *ret = new TOperand<float>(val, Float);
	return (ret);
}

const IOperand	*Factory::createDouble(const std::string &value) const
{
	std::istringstream		stream(value);
	double					val;

	stream >> val;
	TOperand<double> *ret = new TOperand<double>(val, Double);
	return (ret);
}

const IOperand	*Factory::createOperand(eOperandType type, const std::string &value) const
{
	if (type == Int8)
		return (createInt8(value));
	else if (type == Int16)
		return (createInt16(value));
	else if (type == Int32)
		return (createInt32(value));
	else if (type == Float)
		return (createFloat(value));
	else
		return (createDouble(value));
}

Factory			&Factory::operator=(const Factory &rhs)
{
	(void)rhs;
	return (*this);
}

