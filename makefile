LIBS=-lwiringPi -lwiringPiDev

test: 
	g++ test.cpp -o test $(LIBS)
	
trigger:
	g++ trigger.cpp -o trigger $(LIBS)