#include "stdio.h"
#include "stdlib.h"
#include "Sound.h"

int main(){
	Sound * I = new Sound(1,44000,2);
	
	
	if(I->read("words/I.wav")) {
		printf("open.wav");
	}
	Sound * make = new Sound(1,44000,2);
	make->read("words/make.wav");
	I->append(make);
	I->write("imake.wav");

}
