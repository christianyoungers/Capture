#include "headers.h"   

CaptureWorld::CaptureWorld()
     : m_isRunning(true), m_nPlayers(0), m_leftClick(false), m_p1Turn(false), m_p2Turn(false)
{
     //create 2D array of blocks
     for ( int i = 0; i < XDIM; i++ )
	  for ( int j = 0; j < YDIM; j++ )
	       m_blocks[i][j] = new Block(i, j);
}

CaptureWorld::~CaptureWorld()
{
     //delete all blocks
     for ( int i = 0; i < XDIM; i++ )
	  for ( int j = 0; j < YDIM; j++ )
	       delete m_blocks[i][j];

     //delete players
     if ( m_nPlayers == 1 )
	  delete m_playerOne;
     if ( m_nPlayers == 2 )
	  delete m_playerTwo;
}

void CaptureWorld::colorPath(int xCoord, int yCoord)
{
     //right
     for ( int i = xCoord; i < XDIM; i++ )
     {
	  if ( ! m_blocks[i][yCoord]->isOn() )
	       break;
	  m_blocks[i][yCoord]->yellow();
     }

     //left
     for ( int i = xCoord; i >= 0; i-- )
     {
	  if ( ! m_blocks[i][yCoord]->isOn() )
	       break;
	  m_blocks[i][yCoord]->yellow();
     }

     //down
     for ( int i = yCoord; i < YDIM; i++ )
     {
	  if ( ! m_blocks[xCoord][i]->isOn() )
	       break;
	  m_blocks[xCoord][i]->yellow();
     }

     //up
     for ( int i = yCoord; i >= 0; i-- )
     {
	  if ( ! m_blocks[xCoord][i]->isOn() )
	       break;
	  m_blocks[xCoord][i]->yellow();
     }

     //bottom right
     for ( int i = 0; i < XDIM - xCoord && i < YDIM - yCoord; i++ )
     {
	  if ( ! m_blocks[xCoord + i][yCoord + i]->isOn() )
	       break;
	  m_blocks[xCoord + i][yCoord + i]->yellow();
     }

     //top right
     for ( int i = 0; i < XDIM - xCoord && i <= yCoord; i++ )
     {
	  if ( ! m_blocks[xCoord + i][yCoord - i]->isOn() )
	       break;
	  m_blocks[xCoord + i][yCoord - i]->yellow();
     }

     //top left
     for ( int i = 0; i <= xCoord && i <= yCoord; i++ )
     {
	  if ( ! m_blocks[xCoord - i][yCoord - i]->isOn() )
	       break;
	  m_blocks[xCoord - i][yCoord - i]->yellow();
     }

     //bottom left
     for ( int i = 0; i <= xCoord && i < YDIM - yCoord; i++ )
     {
	  if ( ! m_blocks[xCoord - i][yCoord + i]->isOn() )
	       break;
	  m_blocks[xCoord - i][yCoord + i]->yellow();
     }

     //current block green to show turn
     m_blocks[xCoord][yCoord]->green();
}

void CaptureWorld::whiteOut()
{
     //make all blocks white
     for ( int i = 0; i < XDIM; i++ )
	  for ( int j = 0; j < YDIM; j++ )
	       m_blocks[i][j]->white();
}

void CaptureWorld::explode()
{
     //turn off all blocks
     for ( int i = 0; i < XDIM; i++ )
	  for ( int j = 0; j < YDIM; j++ )
	       m_blocks[i][j]->turnOff();
}

void CaptureWorld::events()
{
     //EVENTS
     while ( SDL_PollEvent(&m_event) )
     {
	  //exit button at top of window
	  if ( m_event.type == SDL_QUIT )
	       m_isRunning = false;

	  if ( m_event.type == SDL_KEYUP )
	  {
	       switch ( m_event.key.keysym.sym )
	       {
	       case SDLK_ESCAPE:
		    m_isRunning = false;
		    break;

	       }
	  } 

	  //if mouse left clicked, record data
	  if ( m_event.type == SDL_MOUSEBUTTONDOWN )
	  {
	       m_xClick = m_event.button.x / BLOCKDIM;
	       m_yClick = m_event.button.y / BLOCKDIM;
	       if ( m_event.button.button == SDL_BUTTON_LEFT )
		    m_leftClick = true;
	  }
     }
}

void CaptureWorld::logic()
{
     if ( m_leftClick ) 
     {
	  m_leftClick = false;

	  //if no players on yet, create the first player
	  if ( m_nPlayers == 0 )
	  {
	       m_playerOne = new PlayerOne(m_xClick, m_yClick); 
	       m_nPlayers++;
	       return;
	  }

	  //once the first player has been created, make the second player
	  if ( m_nPlayers == 1 )
	       if ( m_xClick == m_playerOne->xCoord() && 
		    m_yClick == m_playerOne->yCoord() )
		    return;
	       else
	       {
		    m_playerTwo = new PlayerTwo(m_xClick, m_yClick);
		    m_p1Turn = true;
		    m_nPlayers++;
		    return;
	       }

	  //turns
	  if ( m_p1Turn )
	  {
	       //if no yellow block was clicked, instantly return
	       if ( ! m_blocks[m_xClick][m_yClick]->isYellow() )
		    return;

	       //turn off current block player is at
	       m_blocks[m_playerOne->xCoord()][m_playerOne->yCoord()]->turnOff();
	       //then move the player
	       m_playerOne->move(m_xClick, m_yClick);

	       //check if player killed the other player
	       if ( m_playerOne->xCoord() == m_playerTwo->xCoord() &&
		    m_playerOne->yCoord() == m_playerTwo->yCoord() )
	       {
		    explode();
		    m_playerTwo->turnOff();
	       }

	       //reset all blocks to white and change turns
	       whiteOut();
	       m_p1Turn = false;
	       m_p2Turn = true;
	  }
	  else if ( m_p2Turn )
	  {
	       //if no yellow block was clicked, instantly return
	       if ( ! m_blocks[m_xClick][m_yClick]->isYellow() )
		    return;

	       //turn off current block player is at
	       m_blocks[m_playerTwo->xCoord()][m_playerTwo->yCoord()]->turnOff();
	       //then move the player
	       m_playerTwo->move(m_xClick, m_yClick);

	       //check if player killed the other player
	       if ( m_playerOne->xCoord() == m_playerTwo->xCoord() &&
		    m_playerOne->yCoord() == m_playerTwo->yCoord() )
	       {
		    explode();
		    m_playerOne->turnOff();
	       }

	       //reset all blocks to white and change turns
	       whiteOut();
	       m_p1Turn = true;
	       m_p2Turn = false;
	  }
     }

     //color the path of whichever player has their turn
     if ( m_p1Turn )
	  colorPath(m_playerOne->xCoord(), m_playerOne->yCoord());
     else if ( m_p2Turn )
	  colorPath(m_playerTwo->xCoord(), m_playerTwo->yCoord());
}

void CaptureWorld::render()
{
     //RENDERING to the screen
     glClear(GL_COLOR_BUFFER_BIT);
     glPushMatrix(); //start phase
     glOrtho(0, WIDTH, HEIGHT, 0, -1, 1); //Set the matrix
 
     //draw all of the blocks
     for ( int i = 0; i < XDIM; i++ )
	  for ( int j = 0; j < YDIM; j++ )
	       m_blocks[i][j]->draw();

     //draw players if they have been created
     if ( m_nPlayers >= 1 )
	  m_playerOne->draw();
     if ( m_nPlayers >= 2 )
	  m_playerTwo->draw();

     glPopMatrix();  //end phase

     SDL_GL_SwapBuffers();
}
