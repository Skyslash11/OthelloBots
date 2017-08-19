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
int eval2(const OthelloBoard& board,Turn turn )
{
	//cout<< board.getBlackCount()-board.getRedCount()<<"\n";
	return board.getBlackCount()-board.getRedCount();


}


int fulleval1(const OthelloBoard& board,int depth,int count, Turn t1,Move ret){

			
		if (board.getValidMoves(RED).size()+board.getValidMoves(BLACK).size()==0)
		{
			return eval2(board,t1);
		}

		

      if (t1==BLACK)
	  {

			Turn t2= RED;
			list<Move> moves = board.getValidMoves(t1 );
			list<Move>::iterator it = moves.begin();
			//Move ret;
			Move t=*it;
			
			//cout<<"\nzz-"<<moves.size()<<endl;
			int a=-1;
		
    		for(int i=0; i < moves.size(); it++, i++)
			{
				OthelloBoard temp;
				temp=board;
				t=*it;//cout<<"hi1";
				temp.makeMove(t1,t);
				//cout<<"hi2";
				count=fulleval1(temp,depth+1,count,t2,ret);
				if(count>a)
				{
					if(depth==0)
						ret=t;
					
					a=count;
				}
					
				//alpha=max(alpha,alphabeta(temp,depth-1,alpha,beta,t2);
				
			}
			return a;
   				
         
	}
      else
	  {
         	Turn t2= BLACK;
			list<Move> moves = board.getValidMoves( t1 );
			list<Move>::iterator it = moves.begin();
			//Move ret;
			Move t=*it;
			
			//cout<<"\nrr"<<moves.size()<<endl;
			int b=1;
    		for(int i=0; i < moves.size(); it++, i++)
			{
				OthelloBoard temp ;
				temp=board;
				t=*it;
				temp.makeMove(t1,t);
				count=fulleval1(temp,depth+1,count,t2,ret);
				if(count<b)
				{
					if(depth==0)
						ret=t;
					b=count;
				}
					
				//alpha=max(alpha,alphabeta(temp,depth-1,alpha,beta,t2);
				
			}
			return b;
		}
}


Move MyBot::play( const OthelloBoard& board )
{
    list<Move> moves = board.getValidMoves( turn );
    //int randNo = rand() % moves.size();
    list<Move>::iterator bt = moves.begin();
	list<Move>::iterator ct = moves.begin();

	Move ret=*bt;
	//board.print();
	/*if(board.getRedCount()+board.getBlackCount()>54)
	{
		fulleval1(board,0,0,turn,ret);
		return ret;
	}*/




	int black1,black2,red1,red2;

	Move cchk = *bt;

	OthelloBoard tempboard;
	black2 = -10;
	red2=-10;
	int score;
	int move_sizze = moves.size();
	for(int i=0; i < move_sizze; bt++, i++)
	{	
		score=0;
		cchk=*bt;
		
		if ((cchk.x == 1) || (cchk.x == 6) || (cchk.y == 1) || (cchk.y == 6))
		{
			score = 2;
		}
		if ((cchk.x == 0) || (cchk.x == 7) || (cchk.y == 0) || (cchk.y == 7))
		{
			score = 5;
		}

		if ((cchk.x == 1 && cchk.y == 1) || (cchk.x == 1 && cchk.y == 6) || (cchk.x == 6 && cchk.y == 1) || (cchk.x == 6 && cchk.y == 6)) 
		{
			score = -6;
		}	

		if ((cchk.x == 0 && cchk.y == 1) || (cchk.x == 1 && cchk.y == 0) || (cchk.x == 6 && cchk.y == 0) || (cchk.x == 0 && cchk.y == 6)) 
		{
			score = -3;
		}	
		if ((cchk.x == 7 && cchk.y == 1) || (cchk.x == 1 && cchk.y == 7) || (cchk.x == 6 && cchk.y == 7) || (cchk.x == 7 && cchk.y == 6)) 
		{
			score = -3;
		}	
		if ((cchk.x == 2 && cchk.y == 2) || (cchk.x == 2 && cchk.y == 5) || (cchk.x == 5 && cchk.y == 2) || (cchk.x == 5 && cchk.y == 5)) 
		{
			score = 2;
		}
		if ((cchk.x == 1 && cchk.y == 3) || (cchk.x == 3 && cchk.y == 1) || (cchk.x == 4 && cchk.y == 1) || (cchk.x == 1 && cchk.y == 4)) 
		{
			score = 1;
		}
		if ((cchk.x == 3 && cchk.y == 6) || (cchk.x == 6 && cchk.y == 3) || (cchk.x == 4 && cchk.y == 6) || (cchk.x == 6 && cchk.y == 4)) 
		{
			score = 1;
		}
		if ((cchk.x == 0 && cchk.y == 0) || (cchk.x == 0 && cchk.y == 7) || (cchk.x == 7 && cchk.y == 0) || (cchk.x == 7 && cchk.y == 7)) 
		{
			score = 25;
		}
		if (board.get(0,0)== turn){
			if ((cchk.x == 0 && cchk.y == 1) || (cchk.x == 1 && cchk.y == 0) || (cchk.x == 1 && cchk.y == 1) ) 
			{
				score = 5;
			}
		}
		if (board.get(0,7)== turn){
			if ((cchk.x == 0 && cchk.y == 6) || (cchk.x == 1 && cchk.y == 7) || (cchk.x == 1 && cchk.y == 6) ) 
			{
				score = 5;
			}
		}
		if (board.get(7,0)== turn){
			if ((cchk.x == 6 && cchk.y == 1) || (cchk.x == 6 && cchk.y == 0) || (cchk.x == 7 && cchk.y == 1) ) 
			{
				score = 5;
			}
		}
		if (board.get(7,7)== turn){
			if ((cchk.x == 6 && cchk.y == 6) || (cchk.x == 7 && cchk.y == 6) || (cchk.x == 6 && cchk.y == 7) ) 
			{
				score = 5;
			}
		}




		tempboard = board;
	 	if (turn==BLACK)
		{	
			tempboard.makeMove(turn,*bt);
			black1 = tempboard.getBlackCount();
			if((black1 + score) > black2)
			{
				black2=black1+score;
				ct=bt;
			}
		}
		else if (turn==RED)
		{
			tempboard.makeMove(turn,*bt);
			red1 = tempboard.getRedCount();
			if((red1 + score) > red2)
			{
				red2=red1+score;
				ct=bt;
			}	
		}  

		
	}
	if (turn==BLACK)
		{		
				//cout<<"score:--->>++==>>:"<<black2<<"\n";
		}
		else if (turn==RED)
		{
				//cout<<"score:--->>++==>>:"<<red2<<"\n";
		}  

	
	//board.print();
    return *ct;
	
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


