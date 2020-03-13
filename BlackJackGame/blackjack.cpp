//Nico Xia 260770119
#include <stdio.h>
#include <vector>
#include<iostream>
#include <string> 
#include <algorithm>
#include"blackjack.h"
using namespace std;

//--------------Card---------------
Card::Card(Rank r,Type t){
    this->aRank = r;
    this->aType = t;
}

Rank Card::getRank(){ return this->aRank; }


int Card::getValue(){
    int value;
    if(this->aRank==JACK || this->aRank==QUEEN || this->aRank==KING){
        value = 10;
    }
    else{
        //convert char to int 
        value = int(this->aRank) - 48;
    }
    return value;
}

void Card::displayCard(){
    string rank_str;
    string type_str;
    string card_str;
    if(this->aRank == 'T') rank_str == "10"; 
    else rank_str = (this->aRank);
    type_str = (this->aType);
    card_str = rank_str + type_str;
    cout<<card_str;
}

//--------------Hand---------------

void Hand::add(Card c){
    if(c.getRank() == '1') this->num_Aces++;
    (this->hand).push_back(c);
}

void Hand::clear(){
    (this->num_Aces) = 0;
    (this->hand).clear();
    //cout<<"Hand cleared.\n";
}

int Hand::getTotal() const
{
    vector<Card> h = this->hand;
    int sum = 0;
    for (Card c: h)
    {
        sum += c.getValue();
    }
    int countA = this->num_Aces;
    while (sum != 21 && countA > 0)
    {
        if (sum <= 11)
        {
            sum += 10;
            countA -= 1;
        }
        else break;
    }
    return sum;
}

vector<Card> Hand:: getHand(){
    return this->hand;
}

//--------------Deck---------------
void Deck::populate(){
    vector<Rank> vect1 { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    vector<Type> vect2 { CLUBS, DIAMONDS, HEARTS, SPADES };
    for(Rank r: vect1){
        for(Type t:vect2){
            (this->deck).push_back(Card(r,t));
        }
    }
    //cout<<"Deck populated.\n";
}

void Deck::shuffle(){

    random_shuffle((this->deck).begin(),(this->deck).end());
    //cout<<"Deck shuffled.\n";
}

Card Deck::deal(){
    
        Card c = (this->deck).front();
        (this->deck).erase((this->deck).begin());
        return c;

}

void Deck::clear(){
    (this->deck).clear();
    //cout<<"Deck cleared.\n";
}

//--------------AbstractPlayer-------------
bool AbstractPlayer::isBusted(){
    return hand.getTotal()>21;
}

void AbstractPlayer::displayHand(){
    for (Card c: (this->hand).getHand())
    {
        c.displayCard();
        cout << " ";
    }
    cout<<"["<<(this->hand).getTotal()<<"]";
}

//--------------HumanPlayer---------------
bool HumanPlayer::isDrawing() const{
    cout<<"Do you want to draw ? (y/n)\n";
    string ans;
    cin>>ans;
    if (ans == "y") return true;
    else if (ans == "n") return false;
}

void HumanPlayer::announce(winner w)
{
    if (w == PLAYER) cout << "Player wins.\n";
    else if (w == CASINO) cout << "Casino Wins.\n";
    else if (w == TIE) cout << "Push: No one wins.\n";
};

//--------------ComputerPlayer---------------
bool ComputerPlayer::isDrawing() const
{
    return hand.getTotal() <= 16;
};

//--------------BlackJackGame---------------
void BlackJackGame::play(){
    //create Deck
    m_deck.populate();
    
    m_deck.shuffle();
    
    m_casino.hand.clear();
    
    // Computer is dealt and open one cards
    m_casino.hand.add(m_deck.deal());
    cout << "Casino: ";
    m_casino.displayHand();
    cout << endl;
    //Player is dealt and open two cards
    HumanPlayer player;
    player.hand.add(m_deck.deal());
    player.hand.add(m_deck.deal());
    cout << "Player: ";
    player.displayHand();
    cout << endl;

    //player draw cards 
    while(player.isDrawing()){
        // Player is dealt
        player.hand.add(m_deck.deal());
        cout << "Player: ";
        player.displayHand();
        cout << endl;
        //check busted or not 
        if (player.isBusted())
        {
            cout << "Player busts.\n";
            player.announce(CASINO);
            m_deck.clear();
            m_casino.hand.clear();
            return;
        }
    }
    //if player reaches 21 or (s)he doesn't want to draw more
    // then computer draw cards 
    while(m_casino.isDrawing())
    {
        m_casino.hand.add(m_deck.deal());
        cout << "Casino: ";
        m_casino.displayHand();
        cout << endl;
    }
    //check busted or not
    if (m_casino.isBusted()) player.announce(PLAYER);
    else{
        //check values
        int dp = (21 - player.hand.getTotal()); //dp = value difference between player and 21
        int dc = (21 - m_casino.hand.getTotal()); //dc = value difference between casino and 21

        if (dp > dc) player.announce(CASINO);
        else if (dc > dp) player.announce(PLAYER);
        else if (dp == dc) player.announce(TIE);
    }
    m_casino.hand.clear();
    m_deck.clear();
}
