/**
 * HEADER-FILE FOR test.cpp
 * WRITTEN BY DOMINIK HALLEY, 2016
 */

#include <iostream>
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

#define LCDOFS(x)(lcdofs + x)

const int lcdofs = 0x64;
using namespace std;

int fd;
string temp;
string temperature;

const char* ch_temp;

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

	cout << "Current Temperature: " << file_contents;

	return file_contents;
}
