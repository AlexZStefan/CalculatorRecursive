#include "Calculator.h"
#include <sstream>
/*
	Developer: Alex Zarnescu

	Recursive calculator. Supports decimals and negative numbers.

	The program works by reading user input and parsing it according to operator precedence rules:
		- Parentheses
		- Multiplication and division
		- Addition and subtraction

	The parser is implemented with recursion, relying on the call stack to manage nested expressions.
	Each parsing function checks for symbols or numbers, evaluates them, and combines results
	depending on the operator encountered.
*/

int main() {
	std::cout << "--- C++ Calculator ---\n";
	std::cout << "--- Tests ---\n\n";

	/*std::string asd = "123 + 2 + 3 + 4 + 5";
	std::stringstream ss(asd);

	char c;
	while (ss >> c) {

		if (std::isdigit(ss.peek()))
		{
			std::string s = "";
			s[0] = '1';
			double val; 
			ss >> val;

			std::string news = std::to_string(val); 
			
			std::string third = s + news;

			int d = std::stod(third);

			std::cerr << d << '\n';
		}
		else if (std::ispunct(c)) {
			std::cerr << c << '\n';
		}
		else 
			std::cerr << c << '\n';
	}*/

	Calculator calculator = Calculator();
	cerr << (5 / 2) << endl;
	//calculator.evaluate("1 + 3 + 2");
	calculator.evaluate("2 ^ -2");
	/*calculator.evaluate("(1 + 3) * 2");
	calculator.evaluate("(1 + -3) * 2");
	calculator.evaluate("(4 / 2) + 6");
	calculator.evaluate("4+ (12 / (1*2))");
	calculator.evaluate("(1 + (12 * 2)");

	calculator.evaluate("2 ^ 2 ^ 2 ^ 2");*/

	std::cout << "Supports +, -, *, /, (), decimals, and negative numbers\n\n";
	std::cout << "Type expression ";
	while (true) {
		std::string line;
		if (!std::getline(std::cin, line) || line.empty()) {
			return 0;
		}

		std::stringstream inputStream(line);
		auto result = calculator.parse_expression(inputStream);

		inputStream >> std::ws;
		if (!result || inputStream.peek() != EOF) {
			std::cerr << "Error: invalid expression\n\n";
		}
		else {
			std::cout << "Result: " << *result << "\n\n";
		}
	}
}
