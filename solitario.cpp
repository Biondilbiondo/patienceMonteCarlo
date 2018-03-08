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
    if( cardInDeck() == 0 ){
      cout << "The deck is empty!\a\n";
      Card c;
      c.setNone();
      return c;
    }

    for( int i = 39; i >= 0; i-- ){
      if( !cards[i].isNone() ){
        Card c = cards[i];
        cards[i].setNone();
        return c;
      }
    }
  }

  int cardInDeck( void ){
    int i;
    for( i = 0; i < 40; i++ )
      if( cards[i].isNone() )
        return i;
    return i;
  }

  bool solo( bool verbose = false ){
    Deck d = *this;
    Card table[10][4];
    Card hand;

    for( int i = 0; i < 10; i++ )
      for( int j = 0; j < 4; j++ ){
        if( i == 9 ){
          Card c;
          c.setNone();
          table[i][j] = c;
        }
        else
          table[i][j] = d.pop();
      }

    hand = d.pop();

    while( !hand.isNone() ){
      if( verbose ){
        for( int j = 0; j < 4; j++ ){
          for( int i = 0; i < 10; i++ ){
            cout << table[i][j].getRank() << table[i][j].getSuit() << "\t";
          }
          cout << "\n";
        }

        cout << "\nHAND: ";
        hand.printCard();
        cout << "\nDECK:\n";
        d.printDeck();
        cout << "\n_______________________________________\n\n";
      }

      if( hand.getRank() == 10 ){
        table[9][hand.getSuitN() - 1] = hand;
        hand = d.pop();
      }
      else{
        Card c = table[hand.getRank() - 1][hand.getSuitN() - 1];
        table[hand.getRank() - 1][hand.getSuitN() - 1] = hand;
        hand = c;
      }
    }

    bool check = true;
    for( int j = 0; j < 4; j++ ){
      for( int i = 0; i < 10; i++ ){
        check &= (table[i][j].getRank() == i + 1 );
        check &= (table[i][j].getSuitN() == j + 1 );
      }
    }
    return check;

  }
};

int main( void ){
  Deck d;
  if( d.solo() )
    cout << "Success!\n";
  else
    cout << "Failed!\n";
  return 0;
}
