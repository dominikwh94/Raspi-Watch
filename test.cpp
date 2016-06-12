/**
 * MAIN-FILE FOR RASPI-WATCH
 * WRITTEN BY DOMINIK HALLEY, 2016
 */

#include "header.h"

void firstSetup() {
	// Initialize the PCF8574 Port Expander
	pcf8574Setup(lcdofs, 0x3f);
	// Initialize wiringPi
	wiringPiSetup();
}

int main(int argc, char* argv[]) {

	if (argc < 2 ) {
		show_usage("test", argv[0]);
	} else {
		cout << "Raspi-Test" << endl;
		// Run initialization void
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

		// Output the text on LCD and debug message on shell
		lcdPrintf(fd, "   Raspi-Watch      started!    ");
		cout << "Raspi-Watch Started!" << endl;

		lcdClear(fd);
	}

    vector<string> args(argv, argv+argc);
    for (size_t i=1; i< args.size(); ++i) {
    	if (args[i] == "-datetime"){
    		while(1) {
				display("date", "time");
			}
    	} else if (args[i] == "-timetemp") {
    		while(1) {
    			display("time", "temp");
    		}
    	} else if (args[i] == "-datetemp") {
    		while(1) {
    			display("date", "temp");
    		}
    	}
    }
}
