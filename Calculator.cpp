#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

bool EndTask(char input[]) {
	if (!(input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't')) {
		return false;
	}
	else {
		return true;
	}
}

bool IsInputValid(char* input) {
	if (input[0] < '0' || input[0] > '9') {
		return false;
	}

	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
			if (input[i - 1] != ' ' || input[i + 1] != ' ') {
				return false;
			}
		}
		else if (input[i] == '!') {
			if (input[i - 1] < '0' || input[i - 1] > '9') {
				return false;
			}
		}
		else if ((input[i] >= '0' && input[i] <= '9') && input[i - 1] == '!' && i != 0) {
			return false;
		}
		else if ((i == strlen(input) - 1) && !((input[i] >= '0' && input[i] <= '9') || input[i] == '!')) {
			return false;
		}
		else if (input[i] == ' ') {
			if (!(input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/') && !(input[i + 1] == '+' ||
				input[i + 1] == '-' || input[i + 1] == '*' || input[i + 1] == '/')) {
				return false;
			}
		}
		else if (!((input[i] >= '0' && input[i] <= '9') || input[i] == '+' || input[i] == '-' || input[i] == '*' || 
			input[i] == '/' || input[i] == '!' || input[i] == ' ')) {
			return false;
		}
	}
	return true;
}

int ConvertStringToInt(char* str) {
	return atoi(str);
}

int factorial(int num) {
	if (num > 1) {
		return num * factorial(num - 1);
	}
	else {
		return 1;
	}
}

void SplitStringToNumbers(char* str, const char* delimiter, int* container, int& numCount) {
	char* remainingWords = nullptr;
	char* currentWord = strtok_s(str, delimiter, &remainingWords);
	int currentWordSize = 0;
	int numIndex = 0;

	while (currentWord != nullptr) {
		currentWordSize = strlen(currentWord);

		if (currentWord[currentWordSize - 1] == '!') {
			container[numIndex] = factorial(ConvertStringToInt(currentWord));
		}
		else {
			container[numIndex] = ConvertStringToInt(currentWord);
		}
		numCount++;
		numIndex++;
		currentWord = strtok_s(nullptr, delimiter, &remainingWords);
	}
}

void CopyOperators(char* input, char* copiedOper) {
	int operatorIndex = 0;

	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
			copiedOper[operatorIndex] = input[i];
			operatorIndex++;
		}
	}
}

void CalculateResult(int* numbers, char* operators, int numCount) {
	int result = 0;

	if (numCount == 1) {
		result = numbers[0];
	}
	for (int i = 0; i < numCount - 1; i++) {
		if (operators[i] == '+') {
			if (i == 0) {
				result = numbers[i] + numbers[i + 1];
			}
			else {
				result = result + numbers[i + 1];
			}
		}
		else if (operators[i] == '-') {
			if (i == 0) {
				result = numbers[i] - numbers[i + 1];
			}
			else {
				result = result - numbers[i + 1];
			}
		}
		else if (operators[i] == '*') {
			if (i == 0) {
				result = numbers[i] * numbers[i + 1];
			}
			else {
				result = result * numbers[i + 1];
			}
		}
		else if (operators[i] == '/') {
			if (i == 0) {
				result = numbers[i] / numbers[i + 1];
			}
			else {
				result = result / numbers[i + 1];
			}
		}
	}
	cout << "The result is: " << result << endl;
}

int main() {
	char expression[100]{ 0 };
	int numbers[100];
	char operators[100]{ 0 };
	char copiedOperators[100]{ 0 };
	int copiedNumbers[100];
	int numberOfTypedNums = 0;

	while (1) {
		numberOfTypedNums = 0;

		do {
			cout << "Input an expression to calculate: " << endl;
			cin.getline(expression, 100);
			if (EndTask(expression) == true) {
				return 0;
			}
			if (IsInputValid(expression) == false) {
				cout << "Invalid expression! Try again!" << endl;
			}
		} while (IsInputValid(expression) == false);

		CopyOperators(expression, operators);
		SplitStringToNumbers(expression, " +-/*", numbers, numberOfTypedNums);

		CalculateResult(numbers, operators, numberOfTypedNums);
	}
}
