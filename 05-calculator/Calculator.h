#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "Lexer.h"

class Calculator
{
public:
	Calculator(const std::string & expr) : _l(expr) {}

	/// Evaluate the expression
	double eval() {
		if (_l.empty()) {
			std::cerr << "Expected a mathematical expression" << std::endl;
			exit(-4);
		}
		double r = as();
		return r;
	}

protected:
	/// process addition and subtraction
	double as() {
		double a = md();
		do {
			if (_l.empty())
				break;

			Lexer::LexUnit op = _l.peek();
			if (op._type != Lexer::LexUnit::OPERATOR) {
				std::cerr << "Expected an operator" << std::endl;
				exit(-4);
			}
			else {
				if (op._oper == Lexer::LexUnit::ADD) {
					op = _l.pop();
					double b = md();
					a = a + b;
				}
				else if (op._oper == Lexer::LexUnit::SUB) {
					op = _l.pop();
					double b = md();
					a = a - b;
				}
				else
					break;
			}
		} while (true);

		return a;
	}

	/// process multiplication and division
	double md() {
		double a = t();
		do {
			if (_l.empty())
				break;

			Lexer::LexUnit op = _l.peek();
			if (op._type != Lexer::LexUnit::OPERATOR) {
				std::cerr << "Expected an operator" << std::endl;
				exit(-4);
			}
			else {
				if (op._oper == Lexer::LexUnit::MUL) {
					op = _l.pop();
					double b = t();
					a = a * b;
				}
				else if (op._oper == Lexer::LexUnit::DIV) {
					op = _l.pop();
					double b = t();
					a = a / b;
				}
				else
					break;
			}
		} while (true);

		return a;
	}

	/// process a number
	double t() {
		if (_l.empty()) {
			std::cerr << "Expected a number" << std::endl;
			exit(-3);
		}

		Lexer::LexUnit n = _l.peek();
		if (n._type != Lexer::LexUnit::NUMBER) {
			std::cerr << "Expected a number" << std::endl;
			exit(-3);
		}
		// eat the number
		n = _l.pop();

		return n._number;
	}

	Lexer _l;
};

#endif
