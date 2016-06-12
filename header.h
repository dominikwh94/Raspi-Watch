/**
 * HEADER-FILE FOR test.cpp
 * WRITTEN BY DOMINIK HALLEY, 2016
 */

#include <iostream>
#include <ostream>
#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <cctype>
#include <vector>

#define LCDOFS(x)(lcdofs + x)

const int lcdofs = 0x64;
using namespace std;

int fd;
string temp;
string temperature;

const char* ch_temp;

// function to retrieve the current temperature, give the value descriped in test.cpp
string getTemperature(char const* path) {
	ifstream inf(path);
	string c;
	string file_contents;

	while(getline(inf, c)) {
		file_contents += c;
		file_contents.push_back('\n');
	}
	file_contents.erase(0, 69);
	file_contents.erase(3, 2);
	file_contents.insert(2, ".");

	// output temperature also on shell
	cout << "Current Temperature: " << file_contents;

	return file_contents;
}

// function to display usage help
static void show_usage(string name, string argument) {
	cerr << "Usage: " << argument << endl
		 << "-datetime" << " = displays the current date and time" << endl
		 << "-timetemp" << " = displays the current time and temperature" << endl
		 << "-datetemp" << " = displays the current date and temperature" << endl;
}

void display(string line1, string line2) {
	// get current temperature, replace 28-0415932c86ff with your id
	temp = getTemperature("/sys/bus/w1/devices/28-0415932c86ff/w1_slave");
	// build temperature string
	temperature="Temp: ";
	temperature.append(temp);
	temperature.append(" Deg");
	// convert string to char
	ch_temp = temperature.c_str();
	time_t timer;
	char buffer_date[26];
	char buffer_time[26];
	struct tm* tm_info;

	time(&timer);
	tm_info=localtime(&timer);
	// build string for time and date
	strftime(buffer_date, 26, "Date: %d.%m.%Y", tm_info);
	strftime(buffer_time, 26, "Time: %H:%M:%S", tm_info);
	// output the information
	if ((line1 == "date")&&(line2 == "time")) {
		lcdPosition(fd, 0,0);
		lcdPrintf(fd, buffer_date);
		lcdPosition(fd, 0,1);
		lcdPuts(fd, buffer_time);
	} else if ((line1 == "time")&&(line2 == "temp")) {
		lcdPosition(fd, 0,0);
		lcdPrintf(fd, buffer_time);
		lcdPosition(fd, 0,1);
		lcdPuts(fd, ch_temp);
	} else if ((line1 == "date")&&(line2 == "temp")) {
		lcdPosition(fd, 0,0);
		lcdPrintf(fd, buffer_date);
		lcdPosition(fd, 0,1);
		lcdPuts(fd, ch_temp);
	}
}
