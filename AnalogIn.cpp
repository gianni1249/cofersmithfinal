#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "AnalogIn.h"
#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"
#define ADC 0

using std::stringstream;
using std::fstream; 

AnalogIn::AnalogIn(){}

AnalogIn::AnalogIn(unsigned int n){
	

}

void AnalogIn::setNumber(unsigned int n){
	
	number = n;
}

int AnalogIn::readADCsample(){
	
	   stringstream ss;
	   ss << ADC_PATH << number << "_raw";
	   fstream fs;
           fs.open(ss.str().c_str(), fstream::in);
           fs >> number;
           fs.close();
	   return number;

}


AnalogIn::~AnalogIn(){}


