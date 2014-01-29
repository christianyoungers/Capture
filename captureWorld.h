#ifndef CAPTURE_WORLD
#define CAPTURE_WORLD

#include "headers.h"

class CaptureWorld
{
public:
     CaptureWorld();
     ~CaptureWorld();
     void colorPath(int xCoord, int yCoord);
     void whiteOut();
     void explode();
     void events();
     void logic();
     void render();
     bool isRunning() { return m_isRunning; }   

     
      
private:     
     bool m_isRunning;
     SDL_Event m_event;
     Block* m_blocks[XDIM][YDIM];
     PlayerOne* m_playerOne;
     PlayerTwo* m_playerTwo;
     int m_nPlayers;
     int m_xClick;
     int m_yClick;
     bool m_leftClick;
     bool m_p1Turn;
     bool m_p2Turn;
     
};

#endif
