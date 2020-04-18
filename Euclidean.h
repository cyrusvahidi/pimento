#include <Bela.h>

class Euclidean 
{
  public:
    Euclidean();
    ~Euclidean();

    int cycle();
    void update();
    void update1();
    void setSteps(int steps);
    void setPulses(int pulses);
    void setRotation(int rotation);
  private:
    const int MAX_STEPS = 32;
    int steps;
    int pulses;
    int rotation;

    int curIndex;

    int *pattern;
};
