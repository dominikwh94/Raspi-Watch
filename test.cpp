/**
 * MAIN-FILE FOR RASPI-WATCH
 * WRITTEN BY DOMINIK HALLEY, 2016
 */

#include "header.h"

void firstSetup() {
	pcf8574Setup(lcdofs, 0x3f);
	wiringPiSetup();
}

int main(int argc, char** argv) {
	cout << "Raspi-Test" << endl;

	firstSetup();

	// LCD-AREA START
    pinMode(LCDOFS(1), OUTPUT);
    pinMode(LCDOFS(3), OUTPUT);
    digitalWrite(LCDOFS(1), 0);
    digitalWrite(LCDOFS(3), 1);

    fd = lcdInit(2, 16, 4, LCDOFS(0), LCDOFS(2), LCDOFS(4), LCDOFS(5), LCDOFS(6), LCDOFS(7), 0, 0, 0, 0);
    lcdHome(fd);
    lcdClear(fd);
    // LCD-AREA END

    // Print started
    lcdPrintf(fd, "   Raspi-Watch      started!    ");
    cout << "Raspi-Watch Started!" << endl;

    lcdClear(fd);


    while(1) {
    	temp = getTemperature("/sys/bus/w1/devices/28-0415932c86ff/w1_slave");

		temperature="Temp: ";
		temperature.append(temp);
		temperature.append(" Deg");
		ch_temp = temperature.c_str();
    	time_t timer;
    	char buffer_date[26];
    	char buffer_time[26];
    	struct tm* tm_info;

    	time(&timer);
    	tm_info=localtime(&timer);
    	strftime(buffer_date, 26, "Date: %d.%m.%Y", tm_info);
    	strftime(buffer_time, 26, "Time: %H:%M:%S", tm_info);
    	lcdPosition(fd, 0,0);
    	lcdPrintf(fd, ch_temp);
    	lcdPosition(fd, 0,1);
    	lcdPuts(fd, buffer_time);

    }
	}
