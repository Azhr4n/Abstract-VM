/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:23:13 by pivanovi          #+#    #+#             */
/*   Updated: 2015/01/23 15:23:13 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# define VALUE_MIN_INT8 -128
# define VALUE_MAX_INT8 127
# define VALUE_MIN_INT16 -32768
# define VALUE_MAX_INT16 32767

# include <string>

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand
{
	public:
		virtual ~IOperand(void) {}

		virtual int					getPrecision(void) const = 0;
		virtual eOperandType		getType(void) const = 0;

		virtual const IOperand		*operator+(const IOperand &rhs) const = 0;
		virtual const IOperand		*operator-(const IOperand &rhs) const = 0;
		virtual const IOperand		*operator*(const IOperand &rhs) const = 0;
		virtual const IOperand		*operator/(const IOperand &rhs) const = 0;
		virtual const IOperand		*operator%(const IOperand &rhs) const = 0;

		virtual const std::string	&toString(void) const = 0;

	protected:

	private:

};

#endif
