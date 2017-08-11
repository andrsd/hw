#include "Calculator.h"

int main() {
	Calculator c("1 + 123.1 * 2");
	double result = c.eval();
	std::cerr << "Result = " << result << std::endl;
	return 0;
}
