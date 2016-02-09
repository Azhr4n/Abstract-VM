/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 18:14:29 by pivanovi          #+#    #+#             */
/*   Updated: 2015/01/23 18:14:29 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Exceptions.hpp"
#include "Factory.hpp"
#include "Parser.hpp"

int			main(int ac, char **av)
{
	if (ac < 2)
	{
		Parser	parser;

		try {
			parser.readFromStdin();
		}
		catch (NoExitCommand &e) {
			std::cout << e.what();
		}
	}
	else if (ac == 2)
	{
		Parser	parser(av[1]);

		try {
			parser.readFromFile();
		}
		catch (NoExitCommand &e) {
			std::cout << e.what();
		}
	}
	else
		std::cout << "Too much args for avm" << std::endl;

	return (0);
}
