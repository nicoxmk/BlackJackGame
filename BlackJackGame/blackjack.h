//Nico Mingkun Xia
#ifndef _BLACKJACK_
#define _BLACKJACK_
#include <stdio.h>
#include <string> 
#include <algorithm>
using namespace std;

enum Rank { 
    ACE='1', TWO='2', THREE='3', FOUR='4', FIVE='5', SIX='6', 
    SEVEN='7', EIGHT='8', NINE='9', TEN='T', JACK='J', QUEEN='Q', KING='K'
};
enum Type { 
    CLUBS='C', DIAMONDS='D', HEARTS='H', SPADES='S'
};

//--------------Card---------------
class Card{
    private:
        Rank aRank;
        Type aType;
    public:
        Card(Rank r, Type t);
        Rank getRank();
        //Type getType();
        int getValue();
        void displayCard();
};
//--------------Hand---------------
class Hand{
    private:
        vector<Card> hand;
        int num_Aces;
    public:
        vector<Card> getHand();
        void add(Card c);
        void clear();
        //int countAces();
        int getTotal() const;
};
//--------------Deck---------------
class Deck{
    private:
        vector<Card> deck;
    public:
        void populate();
        void shuffle();
        Card deal();
        void clear();
};
//--------------AbstractPlayer-------------
class AbstractPlayer{
    public:
        Hand hand;
        virtual bool isDrawing() const = 0;
        bool isBusted();
        void displayHand();
};

//--------------HumanPlayer---------------
enum winner { PLAYER,CASINO,TIE };

class HumanPlayer:public AbstractPlayer{
    public:
        bool isDrawing() const override; 
        void announce(winner w);
        
};

//--------------ComputerPlayer---------------
class ComputerPlayer : public AbstractPlayer
{
    public:
        bool isDrawing() const override;
};

//--------------BlackJackGame---------------
class BlackJackGame
{
    private:
        Deck m_deck;
        ComputerPlayer m_casino;
    public:
        void play();
        
};

#endif









