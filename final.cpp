#include <iostream>
#include "GPIO.h"
#include "AnalogIn.h"
#include <unistd.h>
#define BUTTON_GPIO "/sys/class/gpio/gpio46/"
using namespace std;
using namespace exploringBB;

void writeGPIO(string filename, string value){
	   fstream fs;
	   string path(BUTTON_GPIO);
	   fs.open((path + filename).c_str(), fstream::out);
           fs << value;
           fs.close();
}

float getResistance(int adc_value) {
	                   float cur_voltage = adc_value * (1.80f/4096.0f); // Vcc = 1.8V, 12-bit
			   float R2 = (cur_voltage * 10000)/(1.80f - cur_voltage);
			   return R2;
}

float getTemperature(int adc_value) {     // from the TMP36 datasheet
	           float cur_voltage = adc_value * (1.80f/4096.0f); // Vcc = 1.8V, 12-bit
		   float diff_degreesC = (cur_voltage-0.75f)/0.01f;
	           return (25.0f + diff_degreesC);
}

int main(){

           GPIO button(46); 
	   GPIO led(60);
	   button.setDirection(INPUT);
	   led.setDirection(OUTPUT);
	   writeGPIO("mode", "gpio_pu"); // Function does not work on mode. Need to configure pin.
	   if (button.getValue() == HIGH){
		   AnalogIn Temp(2); // USES AIN2 P9_37 
		   Temp.getNumber();
	           Temp.setNumber(2);
		   cout << "Button Not Pressed" << endl;
		   Temp.readADCsample();
		   std::cout << "The ADC value input is: " << Temp.readADCsample() << endl;
	           float temp = getTemperature(Temp.readADCsample());
		   float fahr = 32 + ((temp * 9)/5);    // convert deg. C to deg. F
	           cout << "Temperature is " << temp << "°C (" << fahr << "°F)" << endl;
     		   led.setValue(HIGH);
                   sleep(1);
                   led.setValue(LOW);		 
	   }	   
	   else if (button.getValue() == LOW){ 
		      cout << "Button Pressed" << endl;     
	   	      cout << "Using AIN6 to read analog value." << endl;
	   	      AnalogIn AIN(6); // USES P9_35 AIN6
           	      AIN.getNumber();
	              AIN.setNumber(6);
                      AIN.readADCsample();
	              cout << "Measuring resistance ..." << endl;
	              cout << "ADC value is: " << AIN.readADCsample() << endl;
	   	      float Resistance  = getResistance(AIN.readADCsample());
                      cout << "Resistance: " << Resistance << " Ohms " <<  endl;
	              led.setValue(HIGH);
		      sleep(1);
		      led.setValue(LOW);
		      sleep(1);
	              led.setValue(HIGH);
		      sleep(1);
	              led.setValue(LOW);	      

	     }
	   else cout << "<div> Invalid command! </div>";
}
