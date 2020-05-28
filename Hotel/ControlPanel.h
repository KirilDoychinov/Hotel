#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include "Hotel.h"
#include "Activity.h"
#include <string>
#include <utility>
#include <functional>
#include <map>

using namespace std::placeholders;

const std::string DATE = "(19|20)[0-9][0-9]-(0[1-9]|1[012])-(0[1-9]|[12][0-9]|3[01])";
const std::string NUM = "[0-9]+";
const std::string OPT_NUM = "( [0-9]*)?";
const std::string OPT_DATE = "( (19|20)[0-9][0-9]-(0[1-9]|1[012])-(0[1-9]|[12][0-9]|3[01]))?";
const std::string QUOTED_TEXT = "\".*\"";
const std::string WORD = "[a-zA-Z]+";
const std::string TXTFILE = "[^ <>:\"/|\\\\?*.]+\\.txt";

class ControlPanel
{
public:
	ControlPanel();
	~ControlPanel();

	void start();

private:
	Hotel* hotel;
	std::string file;

	const std::map<std::string, std::function<void(void)>>  simpleCommands = {
		{ "save", std::bind(&ControlPanel::save, this)},
		{ "help", std::bind(&ControlPanel::help, this)},
		{ "close", std::bind(&ControlPanel::close, this)},
		{ "exit", std::bind(&ControlPanel::exit, this)},
		{ "all_activities", std::bind(&ControlPanel::printAvailableActivities, this)}
	};

	const std::map < std::string, std::pair<std::string, std::function<void(const std::string&)>>> advancedCommands = {
		{ "saveas", std::pair(TXTFILE,std::bind(&ControlPanel::saveAs, this,_1))},
		{ "checkin", std::pair(NUM + " " + DATE + " " + DATE + " " + QUOTED_TEXT + OPT_NUM,std::bind(&ControlPanel::checkin, this,_1))},
		{ "availability", std::pair(OPT_DATE,std::bind(&ControlPanel::availability, this, _1))},
		{ "checkout", std::pair(NUM,std::bind(&ControlPanel::checkout, this, _1))},
		{ "report", std::pair(DATE + " " + DATE,std::bind(&ControlPanel::report, this, _1))},
		{ "find", std::pair(NUM + " " + DATE + " " + DATE,std::bind(&ControlPanel::find, this, _1))},
		{ "unavailable", std::pair(NUM + " " + DATE + " " + DATE + " " + QUOTED_TEXT,std::bind(&ControlPanel::unavailable, this, _1))},
		{ "subscribe", std::pair(NUM + " " + WORD,std::bind(&ControlPanel::subscribe, this,_1))},
		{ "activities", std::pair(NUM,std::bind(&ControlPanel::printRoomActivities, this, _1))},
		{ "subs", std::pair(WORD,std::bind(&ControlPanel::printActivitySubscribers, this, _1))}
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
