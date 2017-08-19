/*
* @file botTemplate.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-02-04
* Template for users to create their own bots
*/

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <cstdlib>
using namespace std;
using namespace Desdemona;

class MyBot: public OthelloPlayer
{
    public:
        /**
         * Initialisation routines here
         * This could do anything from open up a cache of "best moves" to
         * spawning a background processing thread. 
         */
        MyBot( Turn turn );
		//double evaluation_function(const OthelloBoard& present_board,Turn myturn,Turn botturn,Move move);

        /**
         * Play something 
         */
        virtual Move play( const OthelloBoard& board );
    private:
};

MyBot::MyBot( Turn turn )
    : OthelloPlayer( turn )
{
}

double evaluation_function(const OthelloBoard& present_board,Turn myturn,Turn botturn,Move move)
{
	Coin temp_board[8][8];
	Turn my_color=myturn;
	int i,j,k;
	for(i=0;i<8;++i)
	{
		for(j=0;j<8;++j)
			temp_board[i][j]=present_board.get(i,j);
	}
	temp_board[move.x][move.y]=myturn;
	int x,y,my_coins=0,bot_coins=0,my_front_coins=0,bot_front_coins=0,my_corner_coins=0,bot_corner_coins=0;
	int X[8]={-1, -1, 0, 1, 1, 1, 0, -1};
	int Y[8]={0, 1, 1, 1, 0, -1, -1, -1};
	int HEF[8][8]={{20, -3, 11, 8, 8, 11, -3, 20},{-3, -7, -4, 1, 1, -4, -7, -3},{11, -4, 2, 2, 2, 2, -4, 11},{8, 1, 2, -3, -3, 2, 1, 8},{8, 1, 2, -3, -3, 2, 1, 8},{11, -4, 2, 2, 2, 2, -4, 11},{-3, -7, -4, 1, 1, -4, -7, -3},{20, -3, 11, 8, 8, 11, -3, 20}};
	double stability_factor=0.0,parity=0.0,front_stability=0.0,corner_occupancy=0.0,corner_closeness=0.0,mobility=0.0;
	double evf_value;
	for(i=0;i<8;++i)
	{
		for(j=0;j<8;++j)
		{
			if(temp_board[i][i]==myturn)
			{
				stability_factor+=HEF[i][j];
				++my_coins;
			}
			if(temp_board[i][i]==botturn)
			{
				stability_factor-=HEF[i][j];
				++bot_coins;
			}
			
		}
	}
	for(i=0;i<8;++i)
	{
		for(j=0;j<8;++j)
		{
			
			if(temp_board[i][j]==EMPTY)
			{
				for(k=0; k<8; k++) {
					x = i + X[k]; y = j + Y[k];
					if(x >= 0 && x < 8 && y >= 0 && y < 8 && temp_board[x][y] == EMPTY) 
					{
					if(temp_board[i][j] == my_color) 							
						my_front_coins++;
					else 
						bot_front_coins++;
					break;
					}
				}
			}
		}
	}
	int total_coins,total_front_coins;
	total_coins=my_coins+bot_coins;
	total_front_coins=my_front_coins+bot_front_coins;
	if(total_coins!=0)
	{
		parity = 100.0 * (my_coins-bot_coins)/(total_coins);
	}	
	else 
		parity = 0;

	my_coins = bot_coins = 0;

	if(total_front_coins!=0)
	{
		front_stability = (100.0 * (bot_front_coins-my_front_coins))/(total_front_coins);
	}
	else
		 front_stability = 0;

	
	if(temp_board[0][0] == myturn) my_corner_coins++;
	else if(temp_board[0][0] == botturn) bot_corner_coins++;
	if(temp_board[0][7] == myturn) my_corner_coins++;
	else if(temp_board[0][7] == botturn) bot_corner_coins++;
	if(temp_board[7][0] == myturn) my_corner_coins++;
	else if(temp_board[7][0] == botturn) bot_corner_coins++;
	if(temp_board[7][7] == myturn) my_corner_coins++;
	else if(temp_board[7][7] == botturn) bot_corner_coins++;
	
	total_coins=my_corner_coins + bot_corner_coins;
	corner_occupancy = (100.0 * (my_corner_coins - bot_corner_coins))/(total_coins);
	
	//Corner Closeness starts
	
	if(temp_board[0][0] == EMPTY)
	{
		if(temp_board[0][1] == myturn) my_coins++;
		else if(temp_board[0][1] == botturn) bot_coins++;
		if(temp_board[1][1] == myturn) my_coins++;
		else if(temp_board[1][1] == botturn) bot_coins++;
		if(temp_board[1][0] == myturn) my_coins++;
		else if(temp_board[1][0] == botturn) bot_coins++;
	}

	if(temp_board[0][7] == EMPTY)
	 {
		if(temp_board[0][6] == myturn) my_coins++;
		else if(temp_board[0][6] == botturn) bot_coins++;
		if(temp_board[1][6] == myturn) my_coins++;
		else if(temp_board[1][6] == botturn) bot_coins++;
		if(temp_board[1][7] == myturn) my_coins++;
		else if(temp_board[1][7] == botturn) bot_coins++;
	}

	if(temp_board[7][0] == EMPTY)
	 {
		if(temp_board[7][1] == myturn) my_coins++;
		else if(temp_board[7][1] == botturn) bot_coins++;
		if(temp_board[6][1] == myturn) my_coins++;
		else if(temp_board[6][1] == botturn) bot_coins++;
		if(temp_board[6][0] == myturn) my_coins++;
		else if(temp_board[6][0] == botturn) bot_coins++;
	}
	if(temp_board[7][7] == EMPTY)
	 {
		if(temp_board[6][7] == myturn) my_coins++;
		else if(temp_board[6][7] == botturn) bot_coins++;
		if(temp_board[6][6] == myturn) my_coins++;
		else if(temp_board[6][6] == botturn) bot_coins++;
		if(temp_board[7][6] == myturn) my_coins++;
		else if(temp_board[7][6] == botturn) bot_coins++;
	}
        total_coins=my_coins+bot_coins;
	corner_closeness = 100.0 * (bot_coins - my_coins)/(total_coins);
	//Corner Closeness starts

	my_coins=0,bot_coins=0;

	//Mobility starts
        my_coins=(present_board.getValidMoves(myturn)).size();
	bot_coins=(present_board.getValidMoves(botturn)).size();
	total_coins=my_coins+bot_coins;
	if(total_coins!=0)
		mobility = (100.0 * (my_coins-bot_coins))/(total_coins);
	else
       	        mobility = 0;
	//Mobility ends

	my_coins=0,bot_coins=0;
	
	evf_value=(10.0 * parity) + (800.0 * corner_occupancy) + (400.0 * corner_closeness) + (80.0 * mobility) + (75.0 * front_stability) + (10.0 * stability_factor);
	
	return evf_value;
}

Move MyBot::play( const OthelloBoard& board )
{
    list<Move> moves = board.getValidMoves( turn );
    int size = moves.size();
    list<Move>::iterator it = moves.begin();
    Move curr_mov = *it;
	Turn botturn;
	//MyBot mybot;
	if(turn == RED)
		botturn=BLACK;
	else if(turn == BLACK)
		botturn = RED;
	
    int max_evf_value=evaluation_function(board,turn,botturn,curr_mov);
	int pre_evf_value;
    for(int i=0; i < size; it++, i++)
	{
		pre_evf_value=evaluation_function(board,turn,botturn,*it);
		if(pre_evf_value > max_evf_value)
		{
			max_evf_value = pre_evf_value;
			curr_mov = *it;
		}
	}

    return *it;
}

// The following lines are _very_ important to create a bot module for Desdemona

extern "C" {
    OthelloPlayer* createBot( Turn turn )
    {
        return new MyBot( turn );
    }

    void destroyBot( OthelloPlayer* bot )
    {
        delete bot;
    }
}


