#include "ControlPanel.h"
#include "TextUtilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std::regex_constants;

bool validateRecord(const std::string&);
bool validateLine(const std::string& line);

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
	TextUtilities::trim(line);

	size_t space = line.find_first_of(" ");
	std::string command = (space == std::string::npos) ? line : line.substr(0, space);
	std::string args = (space == std::string::npos) ? "" : line.substr(space + 1);

	if (file.empty()) {
		if (command == "open" && std::regex_match(args, std::regex(TXTFILE, ECMAScript)))
			open(args);
		else
			std::cout << "Invalid command! Use 'open <filename>.txt' to open or create file in current dir!" << std::endl;
	}

	else if (simpleCommands.find(command) != simpleCommands.end())
		simpleCommands.at(command)();

	else if (advancedCommands.find(command) != advancedCommands.end()) {
		auto match = advancedCommands.at(command);
		if (std::regex_match(args, std::regex(match.first, ECMAScript))) {
			match.second(args);
		}
		else
			std::cout << "Invalid arguments! Type 'help' to see the required arguments!" << std::endl;
	}

	else
		std::cout << "Invalid command! Type 'help' to see available commands!" << std::endl;
};

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

void ControlPanel::help() const {
	std::cout << "open <file>                                     opens <file>\n"
		<< "close                                           closes currently opened file\n"
		<< "save                                            saves the currently open file\n"
		<< "saveas <file>                                   saves the currently open file in <file>\n"
		<< "help                                            prints this information\n"
		<< "checkin <room> <from> <to> \"<note>\" [<guests>]  register guests\n"
		<< "availability [<date>]                           print all free rooms for <date>\n"
		<< "checkout <room>                                 chechkout the room\n"
		<< "report <from> <to>                              print the rooms used for <from-to> and the number of days used\n"
		<< "find <beds> <from> <to>                         prints best room free during <from-to> with size at least <beds>\n"
		<< "unavailable <room> <from> <to> \"<note>\"         makes room unavailable during <from-to>\n"
		<< "sport                                           print available sports\n"
		<< "subscribe <room> <sport>                        subscribe the people currently  in <room> for <sport>\n"
		<< "activities <room>                               prints the sports <room> has subscribed\n"
		<< "subs <sport>                                    prints the rooms subscribed for <sport>\n"
		<< "exit                                            exists the program" << std::endl;
}

void ControlPanel::exit() {
	std::cout << "Programme has been terminated succesfully!" << std::endl;
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
	auto tokens = TextUtilities::extractTokens(args);

	int roomNumber = std::stoi(tokens.at(0));
	Date* start = TextUtilities::extractDate(tokens.at(1));
	Date* end = TextUtilities::extractDate(tokens.at(2));
	std::string note = tokens.at(3);
	TextUtilities::extractContent(note);

	if (validate(*start, *end))
		if (tokens.size() == 4)
			hotel->makeReservation(roomNumber, start, end, note);
		else
			hotel->makeReservation(roomNumber, start, end, note, std::stoi(tokens.at(4)));
}

void ControlPanel::availability(const std::string& args) const {
	Date* date = args.empty() ? Date::today() : TextUtilities::extractDate(args);
	hotel->printAvailableRooms(date);
}

void ControlPanel::checkout(const std::string& args) {
	int roomNumber = std::stoi(args);
	hotel->emptyRoom(roomNumber);
}

void ControlPanel::report(const std::string& args) const {
	auto dates = TextUtilities::extractTokens(args);
	Date* start = TextUtilities::extractDate(dates.at(0));
	Date* end = TextUtilities::extractDate(dates.at(1));

	if (validate(*start, *end))
		hotel->report(start, end);
}

void ControlPanel::find(const std::string& args) const {
	auto tokens = TextUtilities::extractTokens(args);

	int bedsNeeded = std::stoi(tokens.at(0));
	Date* start = TextUtilities::extractDate(tokens.at(1));
	Date* end = TextUtilities::extractDate(tokens.at(2));

	auto room = hotel->findAvailabeRoom(bedsNeeded, start, end);
	if (room.has_value())
		std::cout << room.value() << std::endl;
	else
		std::cout << "No suitable room found!" << std::endl;
}

void  ControlPanel::unavailable(const std::string& args) {
	auto tokens = TextUtilities::extractTokens(args);

	int room = std::stoi(tokens.at(0));
	Date* start = TextUtilities::extractDate(tokens.at(1));
	Date* end = TextUtilities::extractDate(tokens.at(2));

	if (validate(*start, *end)) {
		std::string note = tokens.at(3);
		TextUtilities::extractContent(note);
		hotel->makeReservation(room, start, end, note, 0);
	}
}

void  ControlPanel::printAvailableActivities() const {
	for (const auto& activity : hotel->getAllActivities())
		std::cout << activity << std::endl;
}

void  ControlPanel::subscribe(const std::string& args) {
	auto tokens = TextUtilities::extractTokens(args);

	int room = std::stoi(tokens.at(0));
	std::string activity = tokens.at(1);
	hotel->subscribeRoom(room, activity);
}

void  ControlPanel::printRoomActivities(const std::string& args) const {
	int room = std::stoi(args);
	hotel->printRoomActivities(room);
}

void  ControlPanel::printActivitySubscribers(const std::string& args) const {
	std::string activity = args;
	hotel->printSubscribedRooms(activity);
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

	if (hotel->isEmpty()) {
		generateHotelRooms();
		std::cout << "No valid hotel data was found. Generated 11-room hotel with rooms 100-110!" << std::endl;
	}
	else
		std::cout << "Hotel data succesfully read!" << std::endl;

	myFile.close();
}

void ControlPanel::readLine(std::string& line) {
	TextUtilities::trim(line);

	if (!validateLine(line))
		return;

	std::vector<std::string> tokens = TextUtilities::extractTokens(line);
	int room = std::stoi(tokens.at(0)), capacity = std::stoi(tokens.at(1));
	hotel->addRoom(room, capacity);

	for (size_t i = 2; i < tokens.size(); ++i) {
		auto record = tokens.at(i);
		TextUtilities::extractContent(record);
		if (validateRecord(record)) {
			readRecord(room, record);
		}
	}
}

void ControlPanel::generateHotelRooms() {
	for (int roomNumber = 100; roomNumber <= 110; ++roomNumber) {
		int capacity = (roomNumber % 4 == 0) ? 4 : (roomNumber % 3 == 0) ? 3 : 2;
		hotel->addRoom(roomNumber, capacity);
	}
}

void ControlPanel::readRecord(int room, const std::string& record) {
	auto data = TextUtilities::extractTokens(record);
	Date* start = TextUtilities::extractDate(data.at(0));
	Date* end = TextUtilities::extractDate(data.at(1));
	std::string note = data.at(2);
	int guests = std::stoi(data.at(3));
	TextUtilities::extractContent(note);
	hotel->makeReservation(room, start, end, note, guests);
}

bool validateLine(const std::string& line) {
	const std::regex regex("[0-9]+ [0-9]+( \\{.*\\})*", ECMAScript);
	return std::regex_match(line, regex);
}

bool validateRecord(const std::string& record) {
	const std::regex regex(DATE + " " + DATE + " " + QUOTED_TEXT + " " + NUM, ECMAScript);
	return std::regex_match(record, regex);
}






