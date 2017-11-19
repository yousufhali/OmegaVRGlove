#ifndef RCTiming
#define RCTiming

#include <ugpio/ugpio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

/*----------------------------------- INPUT = 0 -------------------------------- OUTPUT = 1 -----------------------------------*/

struct HAND{
    int hand;
    FINGER *finger;
};

struct FINGER {
    int GPIOPIN;
    int IO;
    int VALUE;
};

class RCTIMING {

    public:
        static long readvalue(FINGER& finger);
        void exitprotocol(&HAND hand);
    private:
        bool errorcheck(FINGER& finger);
        int setpin(FINGER& finger, int direction);
        int writepin(FINGER& finger, int direction);
        int readpin(FINGER& finger);
        
};

// RCTIMING::readvalue(hand.finger[0])

void exitprotocol(&HAND hand){
    for(int i = 0; i < 5; i++){
        gpio_free(hand.finger[i].GPIOPIN);
    }
}

bool errorcheck(FINGER& finger){
    //Check if pin is in use
    if(gpio_is_requested(finger.GPIOPIN) < 0){
        cerr << "Requested pin " << finger.GPIOPIN << " is currently in use, releasing it now." << endl;
        ugpio_free(finger.GPIOPIN);
        if((gpio_request(finger.GPIOPIN, NULL) < 0){
            cerr << "Error releasing pin " << finger.GPIOPIN << endl;
            return false;
        }
        else{
            return true;
        }
    }
    else if((gpio_request(finger.GPIOPIN, NULL) < 0){
        cerr << "Error releasing pin " << finger.GPIOPIN << endl;
        return false;
    }
    else{
        return true;
    }
}

int setpin(FINGER& finger, int direction, int value = 0){
    if(direction == 0){
        gpio_direction_input(finger.GPIOPIN);
        return 0;
    }
    else if(direction == 1){
        if(value == 0 || value == 1){
            gpio_direction_output(finger.GPIOPIN, value);
            return value;
        }
        else{
            return -1
        }
    }
    else{
        return -1;
    }
}

int readpin(FINGER& finger){
    return gpio_get_value(finger.GPIOPIN);
}

int writepin(FINGER& finger, int value){
    if(value == 0 || value == 1){
        ugpio_set_value(finger.GPIOPIN, value);
        return value;
    }
    else{
        return -1;
    }
    
}


#endif