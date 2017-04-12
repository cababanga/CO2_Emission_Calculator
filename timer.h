//timer

class timer {

public:
timer();
void           start();
void           stop();
void           reset();
bool           isRunning();
double	       getTime();
bool           isOver(unsigned long seconds);

private:
bool           resetted;
bool           running;
time_t  beg;
time_t  end;
};

double emission(timer timer, double gco2) {
double time = timer.getTime();
double CO2emission;
CO2emission = time * gco2;
return CO2emission;
}