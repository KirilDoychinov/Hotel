#include "ControlPanel.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include <fstream>
#include <regex>

bool validateFileExtension(const std::string&);
bool validateFileName(const std::string&);
bool validateToken(const std::string&);
Reservation* extractReservation(const std::string&);
Date* extractDate(const std::string&);
std::vector<std::string> extractTokens(const std::string&, char = ' ');
void extractContent(std::string&);

ControlPanel::ControlPanel() :hotel(nullptr), file("") {
}

ControlPanel::~ControlPanel() {
	if (hotel != nullptr)
		delete hotel;
}

void ControlPanel::start() {
	std::cout << "Open a text file (.txt) to read: (open <file>.txt)" << std::endl;
	std::string userInput;

	while (true) {
		std::getline(std::cin, userInput);
		executeCommand(userInput);
	};
}

void ControlPanel::help() const {
	std::cout << "open <file>                                  opens <file>\n"
		<< "close                                        closes currently opened file\n"
		<< "save                                         saves the currently open file\n"
		<< "saveas <file>                                saves the currently open file in <file>\n"
		<< "help                                         prints this information\n"
		<< "checkin <room> <from> <to> <note>[<guests>]  register guests\n"
		<< "availability[<date>]                         print all free rooms for <date>\n"
		<< "checkout <room>                              chechkout the room\n"
		<< "report <from> <to>                           print the rooms used for <from-to> and the number of days used\n"
		<< "find <beds> <from> <to>                      prints best room free during <from-to> with size at least <beds>\n"
		<< "unavailable <room> <from> <to> <note>        makes room unavailable during <from-to>\n"
		<< "check sports                                 print available sports\n"
		<< "subscribe <room> <sport>                     subscribe the people currently  in <room> for <sport>\n"
		<< "see <room>									 prints the sports <room> has subscribed\n"
		<< "see <sport>									 prints the rooms subscribed for <sport>\n"
		<< "exit                                         exists the program" << std::endl;

}

void ControlPanel::exit() {
	std::cout << "Programme terminated succesfully!" << std::endl;
	std::exit(0);
}

void ControlPanel::close() {
	if (hotel != nullptr) {
		delete hotel;
		hotel = nullptr;
	}

	std::cout << "Succesfully closed current file!" << std::endl;
	file = "";
}

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

void ControlPanel::save() {
	assert(!file.empty());

	std::fstream myFile(file, std::ios::out | std::ios::trunc);

	if (myFile.is_open()) {
		myFile << *hotel;
		myFile.close();
		std::cout << "Table saved successfully!" << std::endl;
	}

	else
		std::cout << "Error opening the file!" << std::endl;
}

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

void ControlPanel::saveAs(const std::string& file) {
	std::ofstream myFile(file, std::ios::out | std::ios::trunc);

	if (myFile.is_open()) {
		myFile << *hotel;
		myFile.close();
		std::cout << "Table saved successfully as " << file << "!" << std::endl;
	}

	else
		std::cout << "Error opening the file!" << std::endl;
}


void ControlPanel::readFile(const std::string& file) {
	std::ifstream myFile(file, std::ios::in);

	if (!myFile.is_open()) {
		std::cout << "Error opening the file!" << std::endl;
		return;
	}

	this->file = file;
	this->hotel = new Hotel();

	std::string line;
	while (std::getline(myFile, line)) {
		readLine(line);
	}

	if (hotel->empty()) {
		generateHotelRooms();
		std::cout << "No valid hotel data was found. Generated 11-room hotel with rooms 100-110!" << std::endl;
	}

	else
		std::cout << "Hotel data succesfully read!" << std::endl;

	myFile.close();
}


void ControlPanel::readLine(std::string& line) {
	Utils::trim(line);

	const std::regex regex("[0-9]+ [0-9]+({.*})*", std::regex_constants::ECMAScript);
	if (!std::regex_match(line, regex))
		return;

	std::vector<std::string> tokens = extractTokens(line);

	int roomNumber = std::stoi(tokens.at(0)), capacity = std::stoi(tokens.at(1));
	tokens.erase(tokens.begin(), tokens.begin() + 2);

	std::vector<Reservation*> reservations;

	for (auto token : tokens) {
		extractContent(token);
		reservations.push_back(extractReservation(token));
	}

	hotel->addRoom(new Room(roomNumber, capacity, reservations));
}

void ControlPanel::generateHotelRooms() {
	for (int roomNumber = 100; roomNumber <= 110; ++roomNumber) {
		int capacity = (roomNumber % 4 == 0) ? 4 : (roomNumber % 3 == 0) ? 3 : 2;
		hotel->addRoom(new Room(roomNumber, capacity));
	}
}














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







//void ControlPanel::executeCommand(std::string& command) {
//	Utils::trim(command);
//
//	if (command.size() < 4) {
//		std::cout << "Command too short" << std::endl;
//		return;
//	}
//
//	if (file.empty()) {
//		if (command.size() >= 10 && command.substr(0, 5) == "open ") {
//			std::string file = command.substr(5);
//			if (validateFile(file)) {
//				open(file);
//			}
//		}
//		else
//			std::cout << "Invalid command!" << std::endl;
//	}
//
//	else if (functions.find(command) != functions.end())
//		functions.at(command)();
//
//
//	else if (command.substr(0, 7) == "saveas ") {
//		std::string file = command.substr(7);
//		if (validateFile(file)) {
//			saveAs(file);
//		}
//	}
//
//	else if (command.substr(0, 5) == "edit ") {
//		std::string commandArguments = command.substr(5);
//		edit(commandArguments);
//	}
//
//	else
//		std::cout << "Invalid command! (Hint: type help to see available commands)" << std::endl;
//};

bool validateToken(const std::string& token) {
	const std::regex regex("(19|20)\d\d-(0[1-9]|1[012])-(0[1-9]|[12][0-9]|3[01]) (19|20)\d\d-(0[1-9]|1[012])-(0[1-9]|[12][0-9]|3[01]) \".*\" \d+", std::regex_constants::ECMAScript);

	return std::regex_match(token, regex);
}

std::vector<std::string> extractTokens(const std::string& line, char delimeter = ' ') {
	std::vector<std::string> tokens;

	bool quotes = false, brackets = false;
	size_t start = 0;

	for (size_t i = 0; i < line.size(); ++i) {
		char ch = line.at(i);

		if (ch == '"')
			quotes = not quotes;

		else if (ch == '{')
			brackets = true;

		else if (ch == '}')
			brackets = false;

		else if (i == line.size() - 1)
			tokens.push_back(line.substr(start, i - start + 1));

		else if (ch == delimeter && !quotes && !brackets) {
			tokens.push_back(line.substr(start, i - start));
			start = i + 1;
		}
	}

	return tokens;
}

Reservation* extractReservation(const std::string& token) {
	auto tokens = extractTokens(token);

	Date* start = extractDate(tokens.at(0));
	Date* end = extractDate(tokens.at(1));
	std::string note = tokens.at(2).substr(0, tokens.at(2).size() - 2);
	int guests = std::stoi(tokens.at(3));

	extractContent(note);
	return new Reservation(*start, *end, note, guests);
}

Date* extractDate(const std::string& token) {
	int year = std::stoi(token.substr(0, 4));
	int month = std::stoi(token.substr(5, 2));
	int day = std::stoi(token.substr(8, 2));

	return new Date(day, month, year);
}

void extractContent(std::string& str) {
	str.erase(0, 1);
	str.pop_back();
}



