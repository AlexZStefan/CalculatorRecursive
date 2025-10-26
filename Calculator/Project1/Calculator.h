#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include <cctype>
#include <math.h>

class Calculator {
public:

	std::optional<double> parse_factor(std::istream& in) {
		in >> std::ws;
		bool negate = false;

		if (in.peek() == '-' || in.peek() == '+') {
			char sign = in.get();
			in >> std::ws;
			if (sign == '-') {
				negate = true;
			}
		}

		// Parenthesized sub-expression
		if (in.peek() == '(') {
			in.get(); // consume '('
			in >> std::ws;
			auto result = parse_expression(in);
			if (!result) return std::nullopt;

			if (in.peek() == ')') {
				in.get();
			}

			if (negate) {
				*result *= -1.0;
			}
			return result;
		}

		if (std::isdigit(in.peek()) || in.peek() == '.' || in.peek() == '-' || in.peek() == '+') {
			double value;
			in >> value;
			if (in.fail()) {
				return std::nullopt;
			}

			if (negate) {
				value *= -1;
			}
			return value;
		}

		return std::nullopt;
	}

	void evaluate(std::string const& expresion)
	{
		std::stringstream inputStream(expresion);
		auto result = parse_expression(inputStream);

		if (!result) {
			std::cerr << expresion + " = Error: invalid expression\n\n";
			return;
		}
		std::cerr << expresion + " = " << *result << "\n\n";
	}

	std::optional<double> parse_exp(std::istream& in) {
		auto result = parse_factor(in);

		if (!result) return std::nullopt;

		in >> std::ws;

		if (in.peek() == '^') {
			char op = in.get();
			auto rhs = parse_exp(in);
			if (!rhs) return std::nullopt;
			return pow(*result, *rhs);
		}
		return result;
	}

	std::optional<double> parse_term(std::istream& in) {
		auto result = parse_exp(in);
		if (!result) return std::nullopt;

		in >> std::ws;
		while (in.peek() == '*' || in.peek() == '/') {
			char op = in.get();
			auto rhs = parse_factor(in);
			if (!rhs) return std::nullopt;

			if (op == '*') {
				*result *= *rhs;
			}
			else {
				if (*rhs == 0) {
					return std::nullopt;
				}
				*result /= *rhs;
			}
			in >> std::ws;
		}
		return result;
	}

	std::optional<double> parse_expression(std::istream& in) {
		auto result = parse_term(in);
		if (!result) return std::nullopt;

		in >> std::ws;
		while (in.peek() == '+' || in.peek() == '-') {
			char op = in.get();
			auto rhs = parse_term(in);
			if (!rhs) return std::nullopt;

			if (op == '+') {
				*result += *rhs;
			}
			else {
				*result -= *rhs;
			}
			in >> std::ws;
		}
		return result;
	}
};