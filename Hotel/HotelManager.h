#ifndef HOTEL_MANAGER_H
#define HOTEL_MANAGER_H

#include "Hotel.h"
#include <string>
#include <utility>
#include <functional>
#include <map>

using namespace std::placeholders;

/**
 * Some regular expressions constants used for validating the programme input
 */
const std::string DATE = "(19|20)[0-9][0-9]-(0[1-9]|1[012])-(0[1-9]|[12][0-9]|3[01])";
const std::string NUM = "[0-9]+";
const std::string OPT_NUM = "( [0-9]*)?";
const std::string OPT_DATE = "((19|20)[0-9][0-9]-(0[1-9]|1[012])-(0[1-9]|[12][0-9]|3[01]))?";
const std::string QUOTED_TEXT = "\\\".*\\\"";
const std::string WORD = "[a-zA-Z]+";
const std::string TXTFILE = "[^ <>:\"/|\\\\?*.]+\\.txt";

/**
 * @class	HotelManager
 *
 * @brief	Class responsible for running and managing the hotel system,
 * 			handling user commands and data files
 *
 */

class HotelManager
{
public:
	HotelManager();
	~HotelManager();

	void startConsole();

private:
	/**
	 * Hotel being currently operated
	 */
	Hotel* hotel;

	/**
	 * The file the system is currently working with, if present
	 */
	std::string file;

	/**
	 * Map of user-available plain commands (with no arguments) and their string representation
	 */
	const std::map<std::string, std::function<void(void)>>  commandsNoArgs = {
		{ "save", std::bind(&HotelManager::save, this)},
		{ "help", std::bind(&HotelManager::help, this)},
		{ "close", std::bind(&HotelManager::close, this)},
		{ "exit", std::bind(&HotelManager::exit, this)},
		{ "all_activities", std::bind(&HotelManager::printAvailableActivities, this)}
	};

	/**
	 * Map of user-available commands with arguments along with their string representation and arguments pattern
	 */
	const std::map < std::string, std::pair<std::string, std::function<void(const std::string&)>>> commandsWithArguments = {
		{ "saveas", std::pair(TXTFILE,std::bind(&HotelManager::saveAs, this,_1))},
		{ "checkin", std::pair(NUM + " " + DATE + " " + DATE + " " + QUOTED_TEXT + OPT_NUM,std::bind(&HotelManager::checkin, this,_1))},
		{ "availability", std::pair(OPT_DATE,std::bind(&HotelManager::availability, this, _1))},
		{ "checkout", std::pair(NUM,std::bind(&HotelManager::checkout, this, _1))},
		{ "report", std::pair(DATE + " " + DATE,std::bind(&HotelManager::report, this, _1))},
		{ "find", std::pair(NUM + " " + DATE + " " + DATE,std::bind(&HotelManager::find, this, _1))},
		{ "unavailable", std::pair(NUM + " " + DATE + " " + DATE + " " + QUOTED_TEXT,std::bind(&HotelManager::unavailable, this, _1))},
		{ "subscribe", std::pair(NUM + " " + WORD,std::bind(&HotelManager::subscribe, this,_1))},
		{ "activities", std::pair(NUM,std::bind(&HotelManager::printRoomActivities, this, _1))},
		{ "subs", std::pair(WORD,std::bind(&HotelManager::printActivitySubscribers, this, _1))}
	};

	void open(const std::string& file);
	void close();
	void save();
	void saveAs(const std::string& args);
	void help() const;
	void exit();

	void checkin(const std::string& args);
	void checkout(const std::string& args);
	void report(const std::string& args) const;
	void find(const std::string& args) const;
	void availability(const std::string& args = "") const;
	void unavailable(const std::string& args);
	void printAvailableActivities() const;
	void subscribe(const std::string& args);
	void printRoomActivities(const std::string& args) const;
	void printActivitySubscribers(const std::string& args) const;

	void executeCommand(std::string& command);
	void readFile(const std::string& file);
	void readLine(std::string& line);
	void readRecord(int room, const std::string& record);

	void generateHotelRooms();
};


#endif
