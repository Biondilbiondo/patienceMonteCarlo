#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

const string suits[4] = { "hearts", "diamonds", "clubs", "spades"};

class Card{
private:
  int rank;
  int suit;

public:
  Card( int r = 1, string s = suits[0] ){
    if( setCard( r, s ) )
      cout << "The requested card could not be generated. Generating Ace of Hearts instead.\a\n";
      setCard( 1, "hearts");
  }

  int setCard( int r, string s ){
    if( r > 0 && r <= 10 )
      rank = r;
    else{
      cout << "Trying to assign a rank outside the allowed range.\a\n";
      return 1;
    }
    suit = 0;

    for( int i = 0; i < 4; i++ )
      if( s.compare(suits[i]) == 0)
        suit = i+1;

    if( suit == 0 ){
      suit = 1;
      cout << "Trying to assign a suit not allowed, suit is now " << suits[0] << ".\a\n";
      return 1;
    }
    return 0;
  }

  string getSuit( void ){
    if( !isNone() )
      return suits[suit-1];
    else
      return "none";
  }

  int getSuitN( void ){
    return suit;
  }

  int getRank( void ){
    return rank;
  }

  void printCard( void ){
    if( !isNone() )
      cout << getRank() << " of " << getSuit() << "\n";
  }

  void setNone( void ){
    rank = 0;
    suit = 0;
  }

  bool isNone( void ){
    if( rank == 0 && suit == 0 )
      return true;
    else
      return false;
  }
};

class Deck{
private:
  Card cards[40];
public:
  Deck( void ){
    for( int j = 0; j < 4; j++ )
      for( int i = 1; i <= 10; i++ )
        cards[ j*10 + i - 1].setCard( i, suits[j] );
  }

  void printDeck( void ){
    for( int i = 0; i < 40; i++ )
      cards[i].printCard();
  }

  Card pop( void ){
    for( int i = 39; i >= 0; i-- ){
      if( !cards[i].isNone() ){
        Card c = cards[i];
        cards[i].setNone();
        return c;
      }
    }
  }

};

int main( void ){
  Deck d;
  d.printDeck();
  return 0;
}
