#ifndef readSonar
#define readSonar

class sonar
{
    private:
        long duritation;
        double distance;

    public:
        static void sonarSetup(const int trigPin, const int echoPin);
        double read(const int trigPin, const int echoPin);
        static void hazard(int distance, const int ledPin, const int minDist);
};

#endif