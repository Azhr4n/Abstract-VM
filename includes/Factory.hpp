/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 18:22:13 by pivanovi          #+#    #+#             */
/*   Updated: 2015/01/26 18:22:14 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

# include <vector>
# include <string>

# include "IOperand.hpp"

class Factory
{
	public:
		Factory(void);
		Factory(const Factory &src);
		virtual ~Factory(void);

		const IOperand	*createInt8(const std::string &value) const;
		const IOperand	*createInt16(const std::string &value) const;
		const IOperand	*createInt32(const std::string &value) const;
		const IOperand	*createFloat(const std::string &value) const;
		const IOperand	*createDouble(const std::string &value) const;

		const IOperand	*createOperand(eOperandType type, const std::string &value) const;

		Factory			&operator=(const Factory &rhs);

	private:
		const IOperand *(Factory::*_tab[5])(const std::string&) const;

};

#endif
