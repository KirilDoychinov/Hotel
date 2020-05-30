#include "HotelManager.h"
#include "TextUtilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std::regex_constants;

bool validateRecord(const std::string&);
bool validateLine(const std::string& line);

 /**
  * @brief	Default constructor creating with no hotel
  * 		present and empty data file
  *
  */

HotelManager::HotelManager() :hotel(nullptr), file("") {
}

/**
 * @brief	Destructor destroying the object and taking care
 * 			of allocated dynamic memory
 *
 */

HotelManager::~HotelManager() {
	if (hotel != nullptr)
		delete hotel;
}

/**
 * @brief	Starts the command console to read user commands
 *
 */

void HotelManager::startConsole() {
	std::cout << "Open a text file (.txt) to read: (open <file>.txt)" << std::endl;
	std::string userInput;

	while (true) {
		std::getline(std::cin, userInput);
		executeCommand(userInput);
	};
}

/**
 * @brief	             Executes a console-typed user command. If the given input
 * 						 does not match any command, proper error message is printed
 *
 * @param [in]  input	 User console input
 *
 */

void HotelManager::executeCommand(std::string& input) {
	TextUtilities::trim(input);

	size_t space = input.find_first_of(" ");
	std::string command = (space == std::string::npos) ? input : input.substr(0, space);
	std::string args = (space == std::string::npos) ? "" : input.substr(space + 1);

	if (file.empty()) {
		if (command == "open" && std::regex_match(args, std::regex(TXTFILE, ECMAScript)))
			open(args);
		else
			std::cout << "Invalid command! Use 'open <filename>.txt' to open or create file in current dir!" << std::endl;
	}

	else if (commandsNoArgs.find(command) != commandsNoArgs.end())
		commandsNoArgs.at(command)();

	else if (commandsWithArguments.find(command) != commandsWithArguments.end()) {
		auto match = commandsWithArguments.at(command);
		if (std::regex_match(args, std::regex(match.first, ECMAScript))) {
			match.second(args);
		}
		else
			std::cout << "Invalid arguments! Type 'help' to see the required arguments!" << std::endl;
	}

	else
		std::cout << "Invalid command! Type 'help' to see available commands!" << std::endl;
};

/**
 * @brief	           Opens a file to read from
 *
 * @param [in]  file   File to read
 *
 */

void HotelManager::open(const std::string& file) {
	std::fstream myFile(file, std::ios::app);

	if (myFile.is_open()) {
		std::cout << "Succesfully opened file " << file << "!" << std::endl;
		myFile.close();
		readFile(file);
	}

	else
		std::cout << "Error opening the file!" << std::endl;
}

/**
 * @brief    Prints available user commands
 *
 */

void HotelManager::help() const {
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

/**
 * @brief    Exits the programme
 *
 */

void HotelManager::exit() {
	std::cout << "Programme has been terminated succesfully!" << std::endl;
	std::exit(0);
}

/**
 * @brief    Closes the current open file and clears any data read
 *
 */

void HotelManager::close() {
	if (hotel != nullptr) {
		delete hotel;
		hotel = nullptr;
	}

	std::cout << "Succesfully closed current file!" << std::endl;
	file = "";
}

/**
 * @brief    Saves the current data in the current file
 *
 */

void HotelManager::save() {
	std::fstream myFile(file, std::ios::out | std::ios::trunc);

	if (myFile.is_open()) {
		myFile << *hotel;
		myFile.close();
		std::cout << "Data saved successfully!" << std::endl;
	}

	else
		std::cout << "Error opening the file!" << std::endl;
}

/**
 * @brief			   Writes current data to the file specified
 *
 * @param [in]  file   File to write data to
 *
 */

void HotelManager::saveAs(const std::string& file) {
	std::ofstream myFile(file, std::ios::out | std::ios::trunc);

	if (myFile.is_open()) {
		myFile << *hotel;
		myFile.close();
		std::cout << "Data saved successfully as " << file << "!" << std::endl;
	}

	else
		std::cout << "Error opening the file!" << std::endl;
}

/**
 * @brief			   Makes new hotel reservation
 *
 * @param [in]  str    String to be read from
 *
 */

void HotelManager::checkin(const std::string& str) {
	auto tokens = TextUtilities::extractTokens(str);

	int roomNumber = std::stoi(tokens.at(0));
	Date* start = TextUtilities::extractDate(tokens.at(1));
	Date* end = TextUtilities::extractDate(tokens.at(2));
	std::string note = tokens.at(3);
	TextUtilities::removeFirstAndLastElement(note);

	if (validate(*start, *end))
		if (tokens.size() == 4)
			hotel->makeReservation(roomNumber, start, end, note);
		else
			hotel->makeReservation(roomNumber, start, end, note, std::stoi(tokens.at(4)));
}

/**
 * @brief			   Prints available rooms at given date
 *
 * @param [in]  str    String to be read from
 *
 */

void HotelManager::printAvailableRooms(const std::string& str) const {
	Date* date = str.empty() ? Date::today() : TextUtilities::extractDate(str);
	hotel->printAvailableRooms(date);
}

/**
 * @brief			   Checkout given room
 *
 * @param [in]  str    String to be read from
 *
 */

void HotelManager::checkout(const std::string& str) {
	int roomNumber = std::stoi(str);
	hotel->emptyRoom(roomNumber);
}

/**
 * @brief			   Prints room usage in given period
 *
 * @param [in]  str    String to be read from
 *
 */

void HotelManager::reportRoomUsage(const std::string& str) const {
	auto dates = TextUtilities::extractTokens(str);
	Date* start = TextUtilities::extractDate(dates.at(0));
	Date* end = TextUtilities::extractDate(dates.at(1));

	if (validate(*start, *end))
		hotel->printRoomsUsage(start, end);
}

/**
 * @brief			   Find suitabe free room for given period and number of guests
 *
 * @param [in]  str    String to be read from
 *
 */

void HotelManager::findSuitableRoom(const std::string& str) const {
	auto tokens = TextUtilities::extractTokens(str);

	int bedsNeeded = std::stoi(tokens.at(0));
	Date* start = TextUtilities::extractDate(tokens.at(1));
	Date* end = TextUtilities::extractDate(tokens.at(2));

	auto room = hotel->findAvailabeRoom(bedsNeeded, start, end);
	if (room.has_value())
		std::cout << room.value() << std::endl;
	else
		std::cout << "No suitable room found!" << std::endl;
}

/**
 * @brief			   Makes room unavailable for guests during given period
 *
 * @param [in]  str    String to be read from
 *
 */

void  HotelManager::closeRoomTemporarily(const std::string& str) {
	auto tokens = TextUtilities::extractTokens(str);

	int room = std::stoi(tokens.at(0));
	Date* start = TextUtilities::extractDate(tokens.at(1));
	Date* end = TextUtilities::extractDate(tokens.at(2));

	if (validate(*start, *end)) {
		std::string note = tokens.at(3);
		TextUtilities::removeFirstAndLastElement(note);
		hotel->makeReservation(room, start, end, note, 0);
	}
}

/**
 * @brief	 Prints available hotel activities
 *
 */

void  HotelManager::printAvailableActivities() const {
	for (const auto& activity : hotel->getAllActivities())
		std::cout << activity << std::endl;
}

/**
 * @brief			 Subscribe given room for given sport activity
 *
 * @param [in]  str  String to be read from
 *
 */

void  HotelManager::subscribeForSport(const std::string& str) {
	auto tokens = TextUtilities::extractTokens(str);

	int room = std::stoi(tokens.at(0));
	std::string activity = tokens.at(1);
	hotel->subscribeRoom(room, activity);
}

/**
 * @brief			 Prints all activites room currently has subscribed for
 *
 * @param [in]  str  String to be read from
 *
 */

void  HotelManager::printRoomActivities(const std::string& str) const {
	int room = std::stoi(str);
	hotel->printRoomActivities(room);
}

/**
 * @brief			 Prints all rooms currently has subscribed for given acitivity. 
 *
 * @param [in]  str  String to be read from
 *
 */

void  HotelManager::printActivitySubscribers(const std::string& str) const {
	std::string activity = str;
	hotel->printSubscribedRooms(activity);
}

/**
 * @brief			  Reads data from specified file 
 *
 * @param [in]  file  Text file to read from
 *
 */

void HotelManager::readFile(const std::string& file) {
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

	if (!hotel->hasRooms()) {
		std::cout << "No valid hotel data was found. Generated 11-room hotel with rooms 100-110!" << std::endl;
		generateHotelRooms();
		
	}
	else
		std::cout << "Hotel data succesfully read!" << std::endl;

	myFile.close();
}

/**
 * @brief			  Read hotel data from given text file line. If any invalid data token is met
 * 					  the function skips it and continues with the next one
 *
 * @param [in]  line  Line of text to be read from
 *
 * @throws			  std::out_of_range exception if line is not in expected format
 */

void HotelManager::readLine(std::string& line) {
	TextUtilities::trim(line);

	if (!validateLine(line))
		return;

	std::vector<std::string> tokens = TextUtilities::extractTokens(line);
	int room = std::stoi(tokens.at(0)), capacity = std::stoi(tokens.at(1));
	hotel->addRoom(room, capacity);

	for (size_t i = 2; i < tokens.size(); ++i) {
		auto record = tokens.at(i);
		TextUtilities::removeFirstAndLastElement(record);
		if (validateRecord(record)) {
			readRecord(room, record);
		}
	}
}

/**
 * @brief	Generating hotel with 2-,3- and 4-sized rooms with numbers
 * 			from 100 to 110, incuding.
 *
 */

void HotelManager::generateHotelRooms() {
	for (int roomNumber = 100; roomNumber <= 110; ++roomNumber) {
		int capacity = (roomNumber % 4 == 0) ? 4 : (roomNumber % 3 == 0) ? 3 : 2;
		hotel->addRoom(roomNumber, capacity);
	}
}

/**
 * @brief				      Read reservation data from given text. Text format should be specified exactly
 * 							  as in help menu list and the corresponding regex map
 *
 * @param [in]  roomNumber    Number of room corresponding to the given reservation
 *
 *  @param [in]  record       Text record to be read from
 *
 *  @throws					  std::out_of_range exception if line is not in expected format
 *  											
 */

void HotelManager::readRecord(int roomNumber, const std::string& record) {
	auto data = TextUtilities::extractTokens(record);
	Date* start = TextUtilities::extractDate(data.at(0));
	Date* end = TextUtilities::extractDate(data.at(1));
	std::string note = data.at(2);
	int guests = std::stoi(data.at(3));
	TextUtilities::removeFirstAndLastElement(note);
	hotel->makeReservation(roomNumber, start, end, note, guests);
}

/**
 * @brief			Checks if given text line matches the regular expression pattern 
 * 					for text file hotel record as specified in the documentation
 *
 * @param 	line	Text line to be checked
 *
 * @returns			True if the line matches the regular expression, false if otherwise
 * 					
 */

bool validateLine(const std::string& line) {
	const std::regex regex("[0-9]+ [0-9]+( \\{.*\\})*", ECMAScript);
	return std::regex_match(line, regex);
}

/**
 * @brief			 Checks if given text  matches the regular expression pattern
 * 					 for reservation record as specified in the documentation
 *
 * @param 	record	 Text record to be checked
 *
 * @returns			 True if the record matches the regular expression, false if otherwise
 *
 */

bool validateRecord(const std::string& record) {
	const std::regex regex(DATE + " " + DATE + " " + QUOTED_TEXT + " " + NUM, ECMAScript);
	return std::regex_match(record, regex);
}






