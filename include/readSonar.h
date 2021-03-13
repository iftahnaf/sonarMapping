#ifndef readSonar
#define readSonar

class sonar
{
    private:
        long duritation;
        float distance;

    public:
        float microSecondsToCentimeters(long microseconds);
        long timeTravel(const int echoPin, const int trigPin);
};

#endif