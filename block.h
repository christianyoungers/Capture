#ifndef BLOCK
#define BLOCK

#include "headers.h"

class Block
{
public:
     Block(int xCoord, int yCoord);
     bool isOn() { return m_on; }
     bool turnOff() { m_on = false; }     
     void draw();     
     void yellow() { m_r = 255; m_g = 255; m_b = 0; }
     bool isYellow() { return m_r == 255 && m_g == 255 && m_b == 0; }
     void green() { m_r = 0; m_g = 255; m_b = 0; }
     void white() { m_r = 255; m_g = 255; m_b = 255; }

private: 
     int m_xCoord;
     int m_yCoord;
     int m_x;
     int m_y;
     int m_dim;
     bool m_on;
     int m_r;
     int m_g;
     int m_b;
               
};

#endif
