#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <iostream>

#include "Mech_Factory.h"

class Player {
    public:
        Frame* equippedFrame;
        
        Player() {
            std::cout << "Player Initialized." << std::endl;
        };

        void SetFrame(Frame* frame) {
            this->equippedFrame = frame;
            std::cout << "Frame: " << this->equippedFrame->Name_ << std::endl;
        };

        
};


#endif // PLAYER_CLASS_H