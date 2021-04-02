#ifndef CONTROLCAR
#define CONTROLCAR

class car
{
    private: 
        
    public:
        void motorsSetup(const int PinRF, const int PinRB, const int PinLF, const int PinLB);
        void forwardDrive();
        void backwardDrive();
        void rightTurn(float intensity);
        void leftTurn(float intensity);
        void speedTune(float desVelocity);
        void pivot(int direction); // 0 - right, 1 - left
};

#endif