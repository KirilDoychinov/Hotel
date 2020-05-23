#include "ControlPanel.h"
#include "StringUtils.h"
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include <fstream>

bool validateFileExtension(const std::string&);
bool validateFileName(const std::string&);

//ControlPanel::ControlPanel() :table(nullptr), file("") {
//}
//
//ControlPanel::~ControlPanel() {
//	if (table != nullptr)
//		delete table;
//}

void ControlPanel::start() {
	std::cout << "Open a text file (.txt) to read: (open <file>.txt)" << std::endl;
	std::string userInput;

	while (true) {
		std::getline(std::cin, userInput);
		executeCommand(userInput);
	};
}

void ControlPanel::help() const {
	std::cout << "open <file>                  opens <file>\n"
		<< "close                        closes currently opened file\n"
		<< "save                         saves the currently open file\n"
		<< "saveas <file>                saves the currently open file in <file>\n"
		<< "help                         prints this information\n"
		<< "print                        print the current table\n"
		<< "edit <row> <col> <value>     print the current table\n"
		<< "exit                         exists the program" << std::endl;
}

void ControlPanel::exit() {
	std::cout << "Programme terminated succesfully!" << std::endl;
	std::exit(0);
}

//void ControlPanel::close() {
//	if (table != nullptr) {
//		delete table;
//		table = nullptr;
//	}
//
//	std::cout << "Succesfully closed current file!" << std::endl;
//	file = "";
//}

//void ControlPanel::print() const {
//	if (table != nullptr)
//		table->print();
//}

void ControlPanel::open(const std::string& file) {
	std::fstream myFile(file, std::ios::app);

	if (myFile.is_open()) {
		std::cout << "Succesfully opened file " << file << "!" << std::endl;
		myFile.close();
		readFile(file);
	}

	else
		std::cout << "Error opening the file!" << std::endl;

}



//void ControlPanel::readFile(const std::string& file) {
//	std::ifstream myFile(file, std::ios::in);
//
//	if (!myFile.is_open()) {
//		std::cout << "Error opening the file!" << std::endl;
//		return;
//	}
//
//	this->file = file;
//	char delimeter = ',';
//	int rows = 0, maxColumns = 0, countTokens = 0;
//	std::string line;
//
//	while (std::getline(myFile, line)) {
//		++rows;
//		int countTokens = std::count(line.begin(), line.end(), delimeter);
//		if (countTokens > maxColumns)
//			maxColumns = countTokens;
//	}
//
//	myFile.close();
//
//	if (rows == 0) {
//		table = new Table(10, 10);
//		std::cout << "File empty! Generated default 10x10 empty table" << std::endl;
//	}
//
//	else {
//		table = new Table(rows, maxColumns);
//		populateTable(file, delimeter);
//	}
//}




//void ControlPanel::populateTable(const std::string& file, char delim) {
//	std::ifstream myFile(file, std::ios::in);
//	std::string line;
//	int row = 0;
//	while (std::getline(myFile, line)) {
//		++row;
//
//		if (!line.empty()) {
//			int col = 0;
//			size_t pos = 0;
//			std::string token, delimeter = std::string(1, delim);
//			while ((pos = line.find(delimeter)) != std::string::npos) {
//				++col;
//				token = line.substr(0, pos);
//				if (!token.empty()) {
//					table->editCell(row, col, token);
//				}
//
//				line.erase(0, pos + delimeter.length());
//			}
//		}
//	}
//}

//void ControlPanel::save() {
//	assert(!file.empty());
//
//	std::fstream myFile(file, std::ios::out | std::ios::trunc);
//
//	if (myFile.is_open()) {
//		myFile << *table;
//		myFile.close();
//		std::cout << "Table saved successfully!" << std::endl;
//	}
//
//	else
//		std::cout << "Error opening the file!" << std::endl;
//}

//void ControlPanel::saveAs(const std::string& file) {
//	std::ofstream myFile(file, std::ios::out | std::ios::trunc);
//
//	if (myFile.is_open()) {
//		myFile << *table;
//		myFile.close();
//		std::cout << "Table saved successfully as " << file << "!" << std::endl;
//	}
//
//	else
//		std::cout << "Error opening the file!" << std::endl;
//}

bool ControlPanel::validateFile(const std::string& file) {
	if (file.size() < 5) {
		std::cout << "Filename too short! (Hint: File format should be filename.txt)" << std::endl;
		return false;
	}

	std::string name = file.substr(0, file.size() - 4);
	std::string extension = file.substr(file.size() - 4, 4);
	std::string forbiddenSymbols = "/\?%*:|\"<>.";

	return validateFileExtension(extension) && validateFileName(name);
}

bool validateFileExtension(const std::string& extension) {
	bool result = true;

	if (extension != ".txt") {
		std::cout << "Invalid file extension! (Hint: File should be .txt)" << std::endl;
		result = false;
	}

	return result;
}

bool validateFileName(const std::string& name) {
	assert(!name.empty() && "Name should not be empty string");

	bool result = true;

	std::string badChars = "/\?%*:|\"<>.";
	std::size_t badChar = name.find_first_of(badChars);

	if (badChar != std::string::npos) {
		std::cout << "Invalid file name! (Hint: Check forbidden filename characters in Windows OS)" << std::endl;
		result = false;
	}

	return result;
}

void ControlPanel::executeCommand(std::string& command) {
	StringUtils::trim(command);

	if (command.size() < 4) {
		std::cout << "Command too short" << std::endl;
		return;
	}

	if (file.empty()) {
		if (command.size() >= 10 && command.substr(0, 5) == "open ") {
			std::string file = command.substr(5);
			if (validateFile(file)) {
				open(file);
			}
		}
		else
			std::cout << "Invalid command!" << std::endl;
	}

	else if (functions.find(command) != functions.end())
		functions.at(command)();


	else if (command.substr(0, 7) == "saveas ") {
		std::string file = command.substr(7);
		if (validateFile(file)) {
			saveAs(file);
		}
	}

	else if (command.substr(0, 5) == "edit ") {
		std::string commandArguments = command.substr(5);
		edit(commandArguments);
	}

	else
		std::cout << "Invalid command! (Hint: type help to see available commands)" << std::endl;
};


