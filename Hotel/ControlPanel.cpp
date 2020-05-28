#include "ControlPanel.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include <fstream>
#include <regex>

const std::string DATE = "(19|20)\d\d-(0[1-9]|1[012])-(0[1-9]|[12][0-9]|3[01])";
const std::string NUM = "[0-9]+";
const std::string OPT_NUM = "( [0-9]*)?";
const std::string TEXT = "\".*\"";
const std::string OPT_TEXT = "( \".*\")?";
const std::string FILE = "[^ <>:\"/|\\?*.]+\.txt";

bool validateFileExtension(const std::string&);
bool validateFileName(const std::string&);
bool validateRecord(const std::string&);
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

void ControlPanel::executeCommand(std::string& line) {
	Utils::trim(line);

	size_t space = line.find_first_of(" ");
	std::string command = (space == std::string::npos) ? line : line.substr(0, space);
	std::string args = (space == std::string::npos) ? "" : line.substr(space + 1);

	if (file.empty()) {
		if (command == "open")
			open(args);
		else
			std::cout << "Invalid command! Use 'open <filename>.txt' to open or create file in current dir!" << std::endl;
	}

	else if (simpleCommands.find(command) != simpleCommands.end())
		simpleCommands.at(command)();

	else if (advancedCommands.find(command) != advancedCommands.end())
		advancedCommands.at(command)(args);

	else
		std::cout << "Invalid command! Type 'help' to see available commands!" << std::endl;
};

void ControlPanel::open(const std::string& file) {
	if (!std::regex_match(file, std::regex(FILE, std::regex_constants::ECMAScript))) {
		std::cout << "Invalid file name! File should be .txt with standart Windows character restriction!" << std::endl;
		return;
	}

	std::fstream myFile(file, std::ios::app);

	if (myFile.is_open()) {
		std::cout << "Succesfully opened file " << file << "!" << std::endl;
		myFile.close();
		readFile(file);
	}

	else
		std::cout << "Error opening the file!" << std::endl;
}

void ControlPanel::help() const {
	std::cout << "open <file>                                     opens <file>\n"<< "close                                           closes currently opened file\n"
		<< "save                                            saves the currently open file\n"
		<< "saveas <file>                                   saves the currently open file in <file>\n"
		<< "help                                            prints this information\n"
		<< "checkin <room> <from> <to> \"<note>\" [<guests>]  register guests\n"
		<< "availability[<date>]                            print all free rooms for <date>\n"
		<< "checkout <room>                                 chechkout the room\n"
		<< "report <from> <to>                              print the rooms used for <from-to> and the number of days used\n"
		<< "find <beds> <from> <to>                         prints best room free during <from-to> with size at least <beds>\n"
		<< "unavailable <room> <from> <to> \"<note>\"             makes room unavailable during <from-to>\n"
		<< "sport                                    print available sports\n"
		<< "sub <room> <sport>                              subscribe the people currently  in <room> for <sport>\n"
		<< "activities <room>						        prints the sports <room> has subscribed\n"
		<< "subs <sport>							    prints the rooms subscribed for <sport>\n"
		<< "exit                                            exists the program" << std::endl;

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


void ControlPanel::save() {
	std::fstream myFile(file, std::ios::out | std::ios::trunc);

	if (myFile.is_open()) {
		myFile << *hotel;
		myFile.close();
		std::cout << "Data saved successfully!" << std::endl;
	}

	else
		std::cout << "Error opening the file!" << std::endl;
}

void ControlPanel::saveAs(const std::string& file) {
	if (!std::regex_match(file, std::regex(FILE, std::regex_constants::ECMAScript))) {
		std::cout << "Invalid file name! File should be .txt with standart Windows character restriction!" << std::endl;
		return;
	}

	std::ofstream myFile(file, std::ios::out | std::ios::trunc);

	if (myFile.is_open()) {
		myFile << *hotel;
		myFile.close();
		std::cout << "Data saved successfully as " << file << "!" << std::endl;
	}

	else
		std::cout << "Error opening the file!" << std::endl;
}

void ControlPanel::checkin(const std::string& args) {
	if (!std::regex_match(args, std::regex((NUM + " " + DATE + " " + DATE + " " + TEXT + OPT_NUM), std::regex_constants::ECMAScript))) {
		std::cout << "Invalid arguments!" << std::endl;
		return;
	}

	auto tokens = extractTokens(args);
	int room = std::stoi(tokens.at(0));
	Date* start = extractDate(tokens.at(1));
	Date* end = extractDate(tokens.at(2));
	std::string note = tokens.at(3);

	if (!hotel->hasRoom(room))
		std::cout << "Error! Invalid room!" << std::endl;

	else if (*start >= *end)
		std::cout << "Error! Invalid dates!" << std::endl;

	else {
		if (tokens.size() == 4)
			hotel->makeReservation(room, start, end, note);
		else
			hotel->makeReservation(room, start, end, note, std::stoi(tokens.at(4)));
	}
}

void ControlPanel::availability(const std::string& args = "") const {

	if (!args.empty() && !std::regex_match(args, std::regex(DATE, std::regex_constants::ECMAScript))) {
		std::cout << "Invalid arguments!" << std::endl;
		return;
	}

	Date* date = args.empty() ? Date::today() : extractDate(args);
	hotel->availability(date);
}

void ControlPanel::checkout(const std::string& args) {
	if (!std::regex_match(args, std::regex(NUM, std::regex_constants::ECMAScript))) {
		std::cout << "Error! Invalid argument!" << std::endl;
		return;
	}

	int room = std::stoi(args);

	if (!hotel->hasRoom(room))
		std::cout << "Error! Invalid room!" << std::endl;
	else
		hotel->emptyRoom(room);
}

void ControlPanel::report(const std::string& args) const {
	if (!std::regex_match(args, std::regex((DATE + " " + DATE), std::regex_constants::ECMAScript))) {
		std::cout << "Error! Invalid arguments!" << std::endl;
		return;
	}

	auto dates = extractTokens(args);
	Date* start = extractDate(dates.at(0));
	Date* end = extractDate(dates.at(1));

	hotel->report(start, end);
}

void ControlPanel::find(const std::string& args)const {
	if (!std::regex_match(args, std::regex((NUM + " " + DATE + " " + DATE), std::regex_constants::ECMAScript))) {
		std::cout << "Error! Invalid arguments!" << std::endl;
		return;
	}

	auto tokens = extractTokens(args);

	int beds = std::stoi(tokens.at(0));
	Date* start = extractDate(tokens.at(1));
	Date* end = extractDate(tokens.at(2));

	int room = hotel->findRoom(beds, start, end);
	room == -1 ? std::cout << "No room found!" << std::endl : std::cout << room << std::endl;
}

void  ControlPanel::unavailable(const std::string& args) {
	if (!std::regex_match(args, std::regex((NUM + " " + DATE + " " + DATE + " " + TEXT), std::regex_constants::ECMAScript))) {
		std::cout << "Error! Invalid arguments!" << std::endl;
		return;
	}

	auto tokens = extractTokens(args);

	int room = std::stoi(tokens.at(0));
	Date* start = extractDate(tokens.at(1));
	Date* end = extractDate(tokens.at(2));
	std::string note = tokens.at(3);
	extractContent(note);

	hotel->makeReservation(room, start, end, note, 0);
}

void  ControlPanel::printSports() const {
	Activity::printAllActivities();
}

void  ControlPanel::subscribe(const std::string& args) {
	auto tokens = extractTokens(args);

	int room = std::stoi(tokens.at(0));
	std::string activity = tokens.at(1);
	hotel->findRoom(room)->getCurrentReservation()->addActivity;
}

void  ControlPanel::printRoomSport(const std::string& args) const {

}

void  ControlPanel::printSubs(const std::string& args) const {

}













////////////////////////



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

	if (!validateLine(line))
		return;

	std::vector<std::string> tokens = extractTokens(line);

	int room = std::stoi(tokens.at(0)), capacity = std::stoi(tokens.at(1));
	hotel->addRoom(room, capacity);

	for (size_t i = 2; i < tokens.size(); ++i) {
		auto record = tokens.at(i);
		extractContent(record);

		if (validateRecord(record))
			writeRecord(room, record);
	}
}


void ControlPanel::generateHotelRooms() {
	for (int roomNumber = 100; roomNumber <= 110; ++roomNumber) {
		int capacity = (roomNumber % 4 == 0) ? 4 : (roomNumber % 3 == 0) ? 3 : 2;
		hotel->addRoom(roomNumber, capacity);
	}
}

bool validateLine(const std::string& line) {
	const std::regex regex("[0-9]+ [0-9]+( {.*})*", std::regex_constants::ECMAScript);

	return std::regex_match(line, regex);
}

bool validateRecord(const std::string& record) {
	const std::regex regex(DATE + " " + DATE + " " + TEXT + " " + NUM, std::regex_constants::ECMAScript);

	return std::regex_match(record, regex);
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

void extractContent(std::string& str) {
	str.erase(0, 1);
	str.pop_back();
}

void ControlPanel::writeRecord(int room, const std::string& record) {
	auto data = extractTokens(record);
	Date* start = extractDate(data.at(0));
	Date* end = extractDate(data.at(1));
	std::string note = data.at(2);
	int guests = std::stoi(data.at(3));

	extractContent(note);
	hotel->makeReservation(room, start, end, note, guests);
}

Date* extractDate(const std::string& token) {
	int year = std::stoi(token.substr(0, 4));
	int month = std::stoi(token.substr(5, 2));
	int day = std::stoi(token.substr(8, 2));

	return new Date(day, month, year);
}

//bool ControlPanel::validateRoom(int roomNumber) {
//	if (hotel->findRoom(roomNumber) == nullptr) {
//		std::cout << "Room with this number does NOT exists!" << std::endl;
//		return false;
//	}
//
//	return true;
//}

bool validateArguments(const std::string& command, const std::string& args) {
	const std::map<std::string, std::string>  functionSignatures = {
		{ "saveas", FILE},
		{ "checkin", NUM + " " + DATE + " " + DATE + " " + TEXT + OPT_NUM},
		{ "availability", "(" + DATE + ")?"},
		{ "checkout", NUM},
		{ "report", DATE + " " + DATE},
		{ "find", NUM + " " + DATE + " " + DATE},
		{ "unavailable",NUM + " " + DATE + " " + DATE + " " + TEXT }
		//{ "sub", std::bind(&ControlPanel::sub, this)},
		//{ "activities", std::bind(&ControlPanel::activities, this)},
		//{ "list", std::bind(&ControlPanel::list, this)},
	};

	if (functionSignatures.find(command) != functionSignatures.end()) {
		if (std::regex_match(args, std::regex(functionSignatures.at(command), std::regex_constants::ECMAScript)))
			return true;	
	}

	return false;
}




