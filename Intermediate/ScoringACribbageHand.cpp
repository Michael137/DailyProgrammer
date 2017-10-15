/*
URL: https://www.reddit.com/r/dailyprogrammer/comments/75p1cs/20171011_challenge_335_intermediate_scoring_a/
Info:
    1 Deck=52 cards
    Rounds: deal,discard,play (can earn points),show (can earn points)
    Players hand: 4 cards + 1 face-up card
    Show round: player scores points based on cards owned
    Point rules:
        sum(cards)==15 -> 2 points
        3 consecutive -> 3 points
        4 consecutive -> 4 points
        5 consecutive -> 5 points
        2 of a kind -> 2
        3 of a kind -> 6
        4 of a kind -> 12
        4 cards of same suit (cant include face-up card) -> 4
        5 cards of same suit (can include face-up card) -> 5
        Jack of same suit as face-up card -> 1 point

        NB: cards can be used more than once for each combo
    Input:
        array<card, 5> (fifth is face-up)
        Card:
            +Rank (int/char) (Ace == 1, lowest card)
            +Suit (char)
            -toString()->string(Rank + Suit)
    Output:
        Score of hand (int)

    Sample:
        Input->Output:
            5D,QS,JC,KH,AC->10
            8C,AD,10C,6H,7S->7
            AC,6D,5C,10C,8C->4
*/
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

static const std::map<char, int> CardRanks{
    {'A', 1},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
};

class Card {
private:
    std::string rank_suit_;
    bool face_up_;
    int rank_;
    char suit_;

public:
    Card() : rank_suit_(), face_up_(), rank_(), suit_() {};
    Card(std::string rank_suit, bool face_up) : rank_suit_(std::move(rank_suit)), face_up_(face_up) {
        std::size_t sz = rank_suit_.size();
        if(sz < 2 || sz > 3) {
            throw("Combination of rank (A,2,3...J,Q,K) and suit (H,C,S,D) is invalid.\nFormat should be: <suit><rank>");
        };

        suit_ = rank_suit_.back();

        const std::string str = rank_suit_.substr(0, sz-1);
        if( str.find_first_not_of("0123456789") == std::string::npos ) {
            rank_ = std::stoi(str);
        } else {
            rank_ = (CardRanks.find(str.front()))->second;
        };
    };

    const int Rank() const { return rank_; }
    const char Suit() const { return suit_; }
    const std::string& RankSuit() const { return rank_suit_; }
    const std::string GetSuitName() const {
        switch (suit_) {
            case 'H':
                return "Hearts";
            case 'S':
                return "Spades";
            case 'C':
                return "Clubs";
            case 'D':
                return "Diamonds";
        };

        throw("Wrong suit. Something went wrong...");
    };
    const bool IsFaceUp() const { return face_up_; }

    friend std::ostream& operator<<(std::ostream& os, const Card& crd) {
        os << crd.RankSuit();
    };
};

struct Rule {
    int points;

    Rule() : points() {};
    virtual ~Rule();
    virtual int operator()(const std::vector<Card>& v) const=0;
};

struct Consecutive : public Rule {
    Consecutive() : Rule() {};

    int operator()(const std::vector<Card>& v) {
        return 0;
    };
};

int main(int argc, char const *argv[]) {
    Card crd("5H", false);

    std::cout << crd << ": " << crd.GetSuitName() << std::endl;

    return 0;
}
