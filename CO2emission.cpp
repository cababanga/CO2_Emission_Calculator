#include <iostream>
#include <ncurses.h>
#include "timer.h"
#include <vector>
#include <numeric>
#include <cmath> 
#include <limits>
#include "co2.h"
#include <algorithm> 
#include <iomanip>
#include "avspeed.h"

timer::timer() {
    resetted = true;
    running = false;
    beg = time(NULL);
    end = time(NULL);
}

void timer::start() {
    if (!running) {
        if (resetted)
            beg = time(NULL);
        else
            beg -= end - time(NULL);
        running = true;
        resetted = false;
    }
}

void timer::stop() {
    if (running) {
        end = time(NULL);
        running = false;
    }
}

void timer::reset() {
    bool wereRunning = running;
    if (wereRunning)
        stop();
    resetted = true;
    beg = time(NULL);
    end = time(NULL);
    if (wereRunning)
        start();
}

bool timer::isRunning() {
    return running;
}

double  timer::getTime() {
    if (running)
        return (time(NULL) - beg); // CLOCKS_PER_SEC;
    else
        return (end - beg); // CLOCKS_PER_SEC;
}

bool timer::isOver(unsigned long seconds) {
    return seconds >= getTime();
}

double findDistance(double distance);

int main() {

char reply;
std::cout << "Do you want to track your CO2 emission or get a recommendation for the most efficient type of transporation for your journey? " << std::endl;
std::cout << "For tracking type: T" << std::endl;
std::cout << "For recommendation type: R" << std::endl;
std::cin >> reply;

if (reply == 'T'){

    std::vector<double> dailyemission;
    bool quit = false;
    char choice;
    timer t;
	std::cout << " Please choose one of the following options: " << std::endl;
        std::cout << " s   start/stop " << std::endl;
        std::cout << " r   reset " << std::endl;
        std::cout << " v   view time " << std::endl;
        std::cout << " q   quit " << std::endl;
        std::cout << std::endl;
    while (!quit) {
	std::cin >> choice;
	//while (getchar() != '\n');
	if (! (choice == 's' || choice == 'r' || choice == 'v' || choice == 'q')) {    	
	std::cout << "Please only choose one of the possible options: s,r,v or q. " << std::endl;
	}
	else {
        switch (choice) {
            case 's':
                if (t.isRunning()) {
                    t.stop();
			std::cout << "stopped" << std::endl;
			std::cout << " Please choose one of the following options: " << std::endl;
			std::cout << " s   start/stop " << std::endl;
			std::cout << " r   reset " << std::endl;
			std::cout << " v   view time " << std::endl;
			std::cout << " q   quit " << std::endl;
			std::cout << std::endl;
                }
                else {
                    t.start();
                    std::cout << "started" << std::endl;
       			std::cout << "Please choose your transportation type from the following menu" << std::endl;
       			std::cout << "::Menu::" << std::endl;
       			std::cout << "1. Bicycle/Walk" << std::endl;
       			std::cout << "2. Bus" << std::endl;
        		std::cout << "3. Car" << std::endl;
        		std::cout << "4. Metro" << std::endl;
        		std::cout << "5. Motorbike" << std::endl;
        		std::cout << "6. RER" << std::endl;
        		std::cout << "7. Train" << std::endl;
        		std::cout << "8. Tram" << std::endl << std::endl;
			std::cout << "---- Please stop the timer by pressing s when you finish your journey and when you leave the transportation vehicle ---- " << 	                      std::endl;
        		std::cout << "Choice: ";
        		std::cin >> choice;
        		std::cin.ignore(1, ',');

        switch (choice) {
            case '1':
                double cobike;
                cobike = emission(t, 0.000);
                std::cout << "Environment Friendly! " << cobike << " gCO2 emission" << std::endl;

		dailyemission.push_back (cobike);
                break;

            case '2':
                double cobus;
                cobus = emission(t, 0.248);
                std::cout << "Your journey by bus generated " << cobus << " gCO2 emission" << std::endl;
		dailyemission.push_back (cobus);
                break;

            case '3':
                double cocar;
                cocar = emission(t, 0.661);
                std::cout << "Your journey by car generated " << cocar << " gCO2 emission" << std::endl;
		dailyemission.push_back (cocar);
                break;

            case '4':
                double cometro;
                cometro = emission(t, 0.022);
                std::cout << "Your journey by metro generated " << cometro << " gCO2 emission" << std::endl;
		dailyemission.push_back (cometro);
                break;

            case '5':
                double comotorbike;
                comotorbike = emission(t, 1.129);
                std::cout << "Your journey by motorbike generated " << comotorbike << " gCO2 emission" << std::endl;
		dailyemission.push_back (comotorbike);
                break;

            case '6':
                double coRER;
                coRER = emission(t, 0.044);
                std::cout << "Your journey by RER generated " << coRER << " gCO2 emission" << std::endl;
		dailyemission.push_back (coRER);
                break;

            case '7':
                double cotrain;
                cotrain = emission(t, 0.180);
                std::cout << "Your journey by train generated " << cotrain << " gCO2 emission" << std::endl;
		dailyemission.push_back (cotrain);
                break;

            case '8':
                double cotram;
                cotram = emission(t, 0.016);
                std::cout << "Your journey by tram generated " << cotram << " gCO2 emission" << std::endl;
		dailyemission.push_back (cotram);
                break;
		
		default:
                std::cout << "Invalid Selection. Please try Again." << std::endl;
        	}
                }
                break;

            case 'r':
                t.reset();
                std::cout << "resetted" << std::endl;
		std::cout << " Please choose one of the following options: " << std::endl;
        	std::cout << " s   start/stop " << std::endl;
        	std::cout << " r   reset " << std::endl;
        	std::cout << " v   view time " << std::endl;
        	std::cout << " q   quit " << std::endl;
        	std::cout << std::endl;
                break;

            case 'v':
                std::cout << "time = " << t.getTime() << " sec" << std::endl;
		std::cout << " Please choose one of the following options: " << std::endl;
        	std::cout << " s   start/stop " << std::endl;
        	std::cout << " r   reset " << std::endl;
        	std::cout << " v   view time " << std::endl;
        	std::cout << " q   quit " << std::endl;
        	std::cout << std::endl;
                break;

            case 'q':
                quit = true;
		double totaldailyemission;
		totaldailyemission = std::accumulate(dailyemission.begin(), dailyemission.end(), 0);
		std::cout << "Your total CO2 emission for today was: " << totaldailyemission << " gCO2 " << std::endl;
		return 0;
   
        }

        std::cout << "------------------------------------------------------" << std::endl;
}
}
        std::cout << std::endl << std::endl;
}
else if (reply == 'R'){
int x1, x2, y1, y2;
  
std::cout << "The point coordinates of your current location (i.e x,y): ";
std::cin >> x1; std::cout << ","; std::cin >> y1;
  
std::cout << "The point coordinates of the place you want to go (i.e x,y): ";
std::cin >> x2; std::cout << ","; std::cin >> y2;

if(!std::cin){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 
std::cout << "Invalid Selection. Please try Again.\n" << std::endl;
return 0;
}
double x = pow((x2-x1),2);
  double y = pow((y2-y1),2);

  double distance = sqrt(x+y); 

  
findDistance(distance);
std::cin.get(); 
}
}

double findDistance(double distance){
if (distance < 5) {
std::cout << "The distance is: " << distance << "km" << std::endl;

	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Transportation" << std::setw(1) << "|" << std::setw(17) << std::left << "CO2 Emission (g)" << std::setw(1) << "|"  << std::setw(25) << std::left << "Duration of Journey (min)" << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Bicycle" << std::setw(1) << "|" << std::setw(17) << std::left << distance*bicycle << std::setw(1) << "|"  << std::setw(25) << std::left << distance/bicycleh*60 << std::setw(1) << "|" << std::endl;
        std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Bus" << std::setw(1) << "|" << std::setw(17) << std::left << distance*bus << std::setw(1) << "|"  << std::setw(25) << std::left << distance/bush*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Car" << std::setw(1) << "|" << std::setw(17) << std::left << distance*car << std::setw(1) << "|"  << std::setw(25) << std::left << distance/carh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Metro" << std::setw(1) << "|" << std::setw(17) << std::left << distance*metro << std::setw(1) << "|"  << std::setw(25) << std::left << distance/metroh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Motorbike" << std::setw(1) << "|" << std::setw(17) << std::left << distance*motorbike << std::setw(1) << "|"  << std::setw(25) << std::left << distance/motorbikeh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "RER" << std::setw(1) << "|" << std::setw(17) << std::left << distance*RER << std::setw(1) << "|"  << std::setw(25) << std::left << distance/RERh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Tramway" << std::setw(1) << "|" << std::setw(17) << std::left << distance*tramway << std::setw(1) << "|"  << std::setw(25) << std::left << distance/tramwayh*60 << std::setw(1) << "|" << std::endl;
        std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Walk" << std::setw(1) << "|" << std::setw(17) << std::left << distance*walk << std::setw(1) << "|"  << std::setw(25) << std::left << distance/walkh*60 << std::setw(1) << "|" << std::endl;
        std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;

std::cout << "The most environment friendly way is either walking or riding a bicycle which will cause 0 g of CO2 emission." << std::endl; 

}

else if (distance >= 5 && distance < 12) {
std::cout << "The distance is: " << distance << "km" << std::endl;

	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Transportation" << std::setw(1) << "|" << std::setw(17) << std::left << "CO2 Emission (g)" << std::setw(1) << "|"  << std::setw(25) << std::left << "Duration of Journey (min)" << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Bicycle" << std::setw(1) << "|" << std::setw(17) << std::left << distance*bicycle << std::setw(1) << "|"  << std::setw(25) << std::left << distance/bicycleh*60 << std::setw(1) << "|" << std::endl;
        std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Bus" << std::setw(1) << "|" << std::setw(17) << std::left << distance*bus << std::setw(1) << "|"  << std::setw(25) << std::left << distance/bush*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Car" << std::setw(1) << "|" << std::setw(17) << std::left << distance*car << std::setw(1) << "|"  << std::setw(25) << std::left << distance/carh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Metro" << std::setw(1) << "|" << std::setw(17) << std::left << distance*metro << std::setw(1) << "|"  << std::setw(25) << std::left << distance/metroh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Motorbike" << std::setw(1) << "|" << std::setw(17) << std::left << distance*motorbike << std::setw(1) << "|"  << std::setw(25) << std::left << distance/motorbikeh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "RER" << std::setw(1) << "|" << std::setw(17) << std::left << distance*RER << std::setw(1) << "|"  << std::setw(25) << std::left << distance/RERh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Tramway" << std::setw(1) << "|" << std::setw(17) << std::left << distance*tramway << std::setw(1) << "|"  << std::setw(25) << std::left << distance/tramwayh*60 << std::setw(1) << "|" << std::endl;
        std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;

std::cout << "The most environment friendly way is riding a bicycle which will cause " << std::min(std::min(std::min(distance*bus,distance*car),std::min(distance*metro,distance*motorbike)),std::min(std::min(distance*RER,distance*tramway),distance*bicycle)) << " g of CO2 emission." << std::endl; 

}


else if (distance >= 12 && distance < 30) {
std::cout << "The distance is: " << distance << "km" << std::endl;

	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Transportation" << std::setw(1) << "|" << std::setw(17) << std::left << "CO2 Emission (g)" << std::setw(1) << "|"  << std::setw(25) << std::left << "Duration of Journey (min)" << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Bus" << std::setw(1) << "|" << std::setw(17) << std::left << distance*bus << std::setw(1) << "|"  << std::setw(25) << std::left << distance/bush*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Car" << std::setw(1) << "|" << std::setw(17) << std::left << distance*car << std::setw(1) << "|"  << std::setw(25) << std::left << distance/carh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Metro" << std::setw(1) << "|" << std::setw(17) << std::left << distance*metro << std::setw(1) << "|"  << std::setw(25) << std::left << distance/metroh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Motorbike" << std::setw(1) << "|" << std::setw(17) << std::left << distance*motorbike << std::setw(1) << "|"  << std::setw(25) << std::left << distance/motorbikeh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "RER" << std::setw(1) << "|" << std::setw(17) << std::left << distance*RER << std::setw(1) << "|"  << std::setw(25) << std::left << distance/RERh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
        std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Tramway" << std::setw(1) << "|" << std::setw(17) << std::left << distance*tramway << std::setw(1) << "|"  << std::setw(25) << std::left << distance/tramwayh*60 << std::setw(1) << "|" << std::endl;
        std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;

std::cout << "The most environment friendly way is using tramway which will cause " << std::min(std::min(std::min(distance*bus,distance*car),std::min(distance*metro,distance*motorbike)),std::min(distance*RER,distance*tramway)) << " g of CO2 emission." << std::endl; 

}

else if (distance >= 30) {
std::cout << "The distance is: " << distance << "km" << std::endl;

	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Transportation" << std::setw(1) << "|" << std::setw(17) << std::left << "CO2 Emission (g)" << std::setw(1) << "|"  << std::setw(25) << std::left << "Duration of Journey (min)" << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Bus" << std::setw(1) << "|" << std::setw(17) << std::left << distance*bus << std::setw(1) << "|"  << std::setw(25) << std::left << distance/busfasth*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Car" << std::setw(1) << "|" << std::setw(17) << std::left << distance*car << std::setw(1) << "|"  << std::setw(25) << std::left << distance/carfasth*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Train" << std::setw(1) << "|" << std::setw(17) << std::left << distance*train << std::setw(1) << "|"  << std::setw(25) << std::left << distance/trainh*60 << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" << std::setw(1) << "+" << std::setw(17) << "-" << std::setw(1) << "+" << std::setw(25) << "-" << std::setw(1) << "+" << std::endl;


std::cout << "The most environment friendly way is using a train which will cause " << std::min(std::min(distance*bus,distance*car),distance*train) << " g of CO2 emission." << std::endl; 

}
}
