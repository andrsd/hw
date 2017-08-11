#ifndef LEXER_H
#define LEXER_H

#include <queue>
#include <string>
#include <iostream>
#include <cstdlib>

class Lexer
{
public:
	/// Lexical unit
	struct LexUnit {
		enum Type {
			NUMBER,
			OPERATOR,
		};

		enum Operator {
			ADD,
			SUB,
			MUL,
			DIV
		};

		Type _type;
		union {
			Operator _oper;
			double _number;
		};

		LexUnit(Operator oper) { _type = OPERATOR; _oper = oper; }
		LexUnit(double d) { _type = NUMBER; _number = d; }
	};

public:
	/// build the stack with lexical units from `expr`
	Lexer(const std::string & expr) {
		parse(expr);
	}

	/// look at the lexical unit to be processed, keep it on the stack
	LexUnit peek() { return _stack.front(); }

	/// remove the lexical unit to be processed and retrieve it
	LexUnit pop() {
		LexUnit r = peek();
		_stack.pop_front();
		return r;
	}

	/// return true if there is no lexical unit left to process
	bool empty() { return _stack.size() == 0; }

protected:
	/// parse the `expr` and put all lexical unit on stack
	void parse(const std::string & expr) {
		unsigned int pos = 0;
		while (pos < expr.length()) {
			// skip white spaces
			while ((expr[pos] == ' ' || expr[pos] == '\t' || expr[pos] == '\n') && (pos < expr.length()))
				pos++;

			if (pos == expr.length())
				break;
			else if (expr[pos] == '+') {
				_stack.push_back(LexUnit(LexUnit::ADD));
				pos++;
			}
			else if (expr[pos] == '-') {
				_stack.push_back(LexUnit(LexUnit::SUB));
				pos++;
			}
			else if (expr[pos] == '*') {
				_stack.push_back(LexUnit(LexUnit::MUL));
				pos++;
			}
			else if (expr[pos] == '/') {
				_stack.push_back(LexUnit(LexUnit::DIV));
				pos++;
			}
			else {
				// parse a number
				std::string num;
				while (((expr[pos] >= '0' && expr[pos] <= '9') || (expr[pos] == '.')) && (pos < expr.length())) {
					num += expr[pos];
					pos++;
				}
				if (num.length() > 0) {
					double d = std::stod(num);
					_stack.push_back(LexUnit(d));
				}
				else {
					std::cerr << "Invalid character '" << expr[pos] << "' at position " << pos << std::endl;
					exit(-2);
				}
			}
		}
	}

	// print the stack for self-check
	void print() {
		for (auto && k : _stack) {
			if (k._type == LexUnit::OPERATOR) {
				std::cout << "Operator ";
				switch (k._oper) {
					case LexUnit::ADD: std::cout << "+"; break;
					case LexUnit::SUB: std::cout << "-"; break;
					case LexUnit::MUL: std::cout << "*"; break;
					case LexUnit::DIV: std::cout << "/"; break;
				}
				std::cout << std::endl;
			}
			else if (k._type == LexUnit::NUMBER) {
				std::cout << "Number " << k._number << std::endl;
			}
			else {
				std::cerr << "WTF?" << std::endl;
				exit(-1);
			}
		}
	}

protected:
	// stack with lexical units
	std::deque<LexUnit> _stack;
};

#endif
