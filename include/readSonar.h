#ifndef readSonar
#define readSonar

class sonar
{
    private:
        long duritation;
        float distance;

    public:
        static void sonarSetup(const int trigPin, const int echoPin);
        float read(const int trigPin, const int echoPin);
        static void hazard(int distance, const int ledPin, const int minDist);
        float microSecondsToCentimeters(long microseconds);
        long timeTravel(const int echoPin, const int trigPin);
};

#endif