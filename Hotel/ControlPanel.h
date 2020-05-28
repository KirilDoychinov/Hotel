#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include "Hotel.h"
#include "Activity.h"
#include <iostream>
#include <string>
#include <functional>
#include <map>

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
		{ "availability", std::bind(&ControlPanel::exit, this)},
		{ "sport", std::bind(&ControlPanel::printSports, this)}
	};

	const std::map<std::string, std::function<void(const std::string&)>>  advancedCommands = {
		{ "saveas", std::bind(&ControlPanel::saveAs, this)},
		{ "checkin", std::bind(&ControlPanel::checkin, this)},
		{ "availability", std::bind(&ControlPanel::availability, this)},
		{ "checkout", std::bind(&ControlPanel::checkout, this)},
		{ "report", std::bind(&ControlPanel::report, this)},
		{ "find", std::bind(&ControlPanel::find, this)},
		{ "unavailable", std::bind(&ControlPanel::unavailable, this)},	
		{ "sub", std::bind(&ControlPanel::subscribe, this)},
		{ "activities", std::bind(&ControlPanel::printRoomSport, this)},
		{ "subs", std::bind(&ControlPanel::printSubs, this)},
	};

	void help() const;
	void exit();
	void close();
	void open(const std::string& file);
	void readFile(const std::string& file);
	void save();
	void saveAs(const std::string& args);
	void checkin(const std::string& args);
	void checkout(const std::string& args);
	void report(const std::string& args) const;
	void find(const std::string& args) const;
	void availability(const std::string& args = "") const;
	void unavailable(const std::string& args);
	void printSports() const;
	void subscribe(const std::string& args);
	void printRoomSport(const std::string& args) const;
	void printSubs(const std::string& args) const;

	void executeCommand(std::string& command);
	void readLine(std::string& line);
	void generateHotelRooms();
	//bool validateRoom(int) const;
	void writeRecord(int room, const std::string& record);

};


#endif
