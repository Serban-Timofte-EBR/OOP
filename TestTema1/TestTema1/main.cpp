#include<iostream>
using namespace std;

char* removeSpaces(const char* text)
{
	int index = 0;
	int n = strlen(text);

	if (n == 0) {
		return nullptr;
	}

	char* modifyString = new char[n + 1];

	for (int i = 0; i < n; i++) {
		if (text[i] != ' ') {
			modifyString[index] = text[i];
			index += 1;
		}
	}

	modifyString[index] = '\0';

	return modifyString;
}

int main() {
	const char* inputText = "    hello. this is a test   ";
	char* resultText = removeSpaces(inputText);

		std::cout << "Input Text: " << inputText << std::endl;
		std::cout << "Text without spaces: " << resultText << std::endl;

		delete[] resultText; // Deallocate the dynamically allocated memory

	return 0;
}