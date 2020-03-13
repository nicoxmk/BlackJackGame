//Nico Xia 260770119
#include <stdio.h>
#include<iostream>
#include <string> 
#include<vector>
#include <algorithm>
#include"blackjack.h"
using namespace std;

int main()
{
    cout<<"\tWelcome to the COMP322 Blackjack Game!"<<endl<<endl;
    
    BlackJackGame game;
    //the main loop of the game
    bool playAgain = true;
    char answer = 'y';
    while(playAgain){
        game.play();
    
        //check whether the player would like to play another round
        cout<<"Would you like another round?(y/n)";
        cin>>answer;
        cout<<endl<<endl;
        playAgain = (answer == 'y' ? true:false);
    }
    cout<<"Game Over!";
    return 0;
}
