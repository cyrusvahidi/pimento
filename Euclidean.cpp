#include "Euclidean.h"
#include <math.h>

Euclidean::Euclidean() {
	steps = 16;
	pulses = 0;
	rotation = 0;

  curIndex = 0;

  pattern = new int[MAX_STEPS];
}

void Euclidean::update() 
{
  int f = floor(steps / pulses);
  for (int i = 0; i < steps; i++)
  {
    pattern[i] = 0;
  }
  int idx = 0;
  for (int i = 0; i < pulses; i++)
  {
    pattern[idx] = 1;  
    idx += f;
  }

}

void Euclidean::update1()
{
  int bucket = 0;
  for (int i = 0; i < steps; i++) 
  {
    bucket += pulses;
    if (bucket >= steps) 
    {
      bucket -= steps;
      pattern[i] = 1;
    } else {
      pattern[i] = 0;
    }
  }
}

int Euclidean::cycle() 
{
  int pulse = pattern[curIndex];
  curIndex = (curIndex + 1) % steps;
  return pulse;
}

void Euclidean::setSteps(int _steps)
{
  steps = _steps;
}

void Euclidean::setPulses(int _pulses)
{
  if (_pulses != pulses)
  {
    if (_pulses >= steps) 
    {
      pulses = steps;
    } else {
      pulses = _pulses;
    }
    this->update1();
  }

}

void Euclidean::setRotation(int _rotation)
{
  if (_rotation >= steps) 
  {
    rotation = steps;
  } else {
    rotation = _rotation;
  }
}

Euclidean::~Euclidean()
{
  delete pattern;
}
