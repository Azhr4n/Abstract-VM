/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:34:54 by pivanovi          #+#    #+#             */
/*   Updated: 2015/01/23 15:34:54 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPERAND_HPP
# define TOPERAND_HPP

# include <iostream>
# include <iomanip>
# include <sstream>

# include "Exceptions.hpp"
# include "IOperand.hpp"
# include "Factory.hpp"

template<typename T>
class TOperand : virtual public IOperand
{
	public:
		TOperand(T value, eOperandType type)
		{
			_string = new std::string;
			_val = value;
			_type = type;
		}

		TOperand(const TOperand &src)
		{
			*this = src;
		}

		virtual ~TOperand(void)
		{
			delete _string;
		}

		virtual int					getPrecision(void) const {return (_type);}
		virtual eOperandType		getType(void) const {return (_type);}
		virtual T					getValue(void) const {return (_val);}

		virtual void				setValue(T value) {_val = value;}

		virtual const IOperand		*operator+(const IOperand &rhs) const
		{
			std::istringstream	is(rhs.toString());
			std::ostringstream	os;
			eOperandType		type;
			double				val;
			double				tmp;

			if (getPrecision() > rhs.getPrecision())
				type = eOperandType(getPrecision());
			else
				type = eOperandType(rhs.getPrecision());
			val = static_cast<double>(getValue());
			is >> tmp;
			try {
				ValueFlow::additionFlow(type, val, tmp);
			}
			catch (ValueOverflow &e) {
				throw ValueOverflow();
			}
			catch (ValueUnderflow &e) {
				throw ValueUnderflow();
			}
			val += tmp;
			os << std::fixed << std::fixed << val;
			return (_factory.createOperand(type, os.str()));
		}

		virtual const IOperand		*operator-(const IOperand &rhs) const
		{
			std::istringstream	is(rhs.toString());
			std::ostringstream	os;
			eOperandType		type;
			double				val;
			double				tmp;

			if (getPrecision() > rhs.getPrecision())
				type = eOperandType(getPrecision());
			else
				type = eOperandType(rhs.getPrecision());
			val = static_cast<double>(getValue());
			is >> tmp;
			try {
				ValueFlow::additionFlow(type, val, -tmp);
			}
			catch (ValueOverflow &e) {
				throw ValueOverflow();
			}
			catch (ValueUnderflow &e) {
				throw ValueUnderflow();
			}
			val -= tmp;
			os << std::fixed << val;
			if (getPrecision() > rhs.getPrecision())
				return (_factory.createOperand(eOperandType(getPrecision()), os.str()));
			return (_factory.createOperand(eOperandType(rhs.getPrecision()), os.str()));
		}

		virtual const IOperand		*operator*(const IOperand &rhs) const
		{
			std::istringstream	is(rhs.toString());
			std::ostringstream	os;
			eOperandType		type;
			double				val;
			double				tmp;

			if (getPrecision() > rhs.getPrecision())
				type = eOperandType(getPrecision());
			else
				type = eOperandType(rhs.getPrecision());
			val = static_cast<double>(getValue());
			is >> tmp;
			try {
				ValueFlow::multiplicationFlow(type, val, tmp);
			}
			catch (ValueOverflow &e) {
				throw ValueOverflow();
			}
			catch (ValueUnderflow &e) {
				throw ValueUnderflow();
			}
			val *= tmp;
			os << std::fixed << val;
			if (getPrecision() > rhs.getPrecision())
				return (_factory.createOperand(eOperandType(getPrecision()), os.str()));
			return (_factory.createOperand(eOperandType(rhs.getPrecision()), os.str()));
		}

		virtual const IOperand		*operator/(const IOperand &rhs) const
		{
			std::istringstream	is(rhs.toString());
			std::ostringstream	os;
			double				val;
			double				tmp;

			val = static_cast<double>(getValue());
			is >> tmp;
			val = val / tmp;
			os << std::fixed << val;
			if (getPrecision() > rhs.getPrecision())
				return (_factory.createOperand(eOperandType(getPrecision()), os.str()));
			return (_factory.createOperand(eOperandType(rhs.getPrecision()), os.str()));
		}

		virtual const IOperand		*operator%(const IOperand &rhs) const
		{
			std::istringstream	is(rhs.toString());
			std::ostringstream	os;
			int					val;
			int					tmp;

			val = static_cast<int>(getValue());
			is >> tmp;
			val = val % tmp;
			os << std::fixed << val;
			if (getPrecision() > rhs.getPrecision())
				return (_factory.createOperand(eOperandType(getPrecision()), os.str()));
			return (_factory.createOperand(eOperandType(rhs.getPrecision()), os.str()));
		}

		TOperand					&operator=(const TOperand &rhs)
		{
			_val = rhs.getValue();
			_type = rhs.getType();
			*_string = rhs.toString();
			return (*this);
		}

		virtual const std::string	&toString(void) const
		{
			std::ostringstream		oss;

			oss << std::fixed << std::setprecision(2) << _val;
			*_string = oss.str();
			return (*_string);
		}

	private:
		TOperand(void);
		T							_val;
		eOperandType				_type;
		std::string					*_string;
		Factory						_factory;

};

#endif
