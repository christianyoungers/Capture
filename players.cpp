#include "headers.h"

Player::Player(int xCoord, int yCoord)
     : m_xCoord(xCoord), m_yCoord(yCoord), m_on(true) 
{}

void Player::move(int xCoord, int yCoord)
{
     m_xCoord = xCoord;
     m_yCoord = yCoord;
}

//////////////////////////////////////////////////////////////

PlayerOne::PlayerOne(int xCoord, int yCoord)
     : Player(xCoord, yCoord)
{}
 
void PlayerOne::draw()
{
     if ( isOn() )
     {
	  int x = xCoord() * BLOCKDIM;
	  int y = yCoord() * BLOCKDIM;

	  //blue color
	  glColor4ub(0, 0, 255, 255);

	  //two rectangles that make an X
	  glBegin(GL_QUADS);
	  glVertex2f(x + (BLOCKDIM/5),   y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*2/5), y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*4/5), y + (BLOCKDIM*4/5));
	  glVertex2f(x + (BLOCKDIM*3/5), y + (BLOCKDIM*4/5));

	  glVertex2f(x + (BLOCKDIM*3/5), y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*4/5), y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*2/5), y + (BLOCKDIM*4/5));
	  glVertex2f(x + (BLOCKDIM/5),   y + (BLOCKDIM*4/5));
	  glEnd();
     }
}

//////////////////////////////////////////////////////////////

PlayerTwo::PlayerTwo(int xCoord, int yCoord)
     : Player(xCoord, yCoord)
{}
 
void PlayerTwo::draw()
{
     if ( isOn() )
     {
	  int x = xCoord() * BLOCKDIM;
	  int y = yCoord() * BLOCKDIM;

	  //red color
	  glColor4ub(255, 0, 0, 255);

	  //four rectangles to make an O
	  glBegin(GL_QUADS);
	  glVertex2f(x + (BLOCKDIM/5),   y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*4/5), y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*4/5), y + (BLOCKDIM*2/5));
	  glVertex2f(x + (BLOCKDIM/5),   y + (BLOCKDIM*2/5));

	  glVertex2f(x + (BLOCKDIM*3/5), y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*4/5), y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*4/5), y + (BLOCKDIM*4/5));
	  glVertex2f(x + (BLOCKDIM*3/5), y + (BLOCKDIM*4/5));

	  glVertex2f(x + (BLOCKDIM/5),   y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*2/5), y + (BLOCKDIM/5));
	  glVertex2f(x + (BLOCKDIM*2/5), y + (BLOCKDIM*4/5));
	  glVertex2f(x + (BLOCKDIM/5),   y + (BLOCKDIM*4/5));

	  glVertex2f(x + (BLOCKDIM/5),   y + (BLOCKDIM*3/5));
	  glVertex2f(x + (BLOCKDIM*4/5), y + (BLOCKDIM*3/5));
	  glVertex2f(x + (BLOCKDIM*4/5), y + (BLOCKDIM*4/5));
	  glVertex2f(x + (BLOCKDIM/5),   y + (BLOCKDIM*4/5));
	  glEnd();
     }
}
