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
#include <iostream>

class Card {
private:
    std::string rank_suit_, rank_;
    char suit_;

public:
    Card() : rank_suit_(), rank_(), suit_() {};
    explicit Card(std::string rank_suit) : rank_suit_(std::move(rank_suit)) {
        std::size_t sz = rank_suit_.size();
        if(sz < 2 || sz > 3) {
            throw("Combination of rank (A,2,3...J,Q,K) and suit (H,C,S,D) is invalid.\nFormat should be: <suit><rank>");
        };

        suit_ = rank_suit_.back();
        rank_ = rank_suit_.substr(0, sz-1);
    };

    const std::string& Rank() const { return rank_; }
    const char& Suit() const { return suit_; }
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

    friend std::ostream& operator<<(std::ostream& os, const Card& crd) {
        os << crd.RankSuit();
    };
};

int main(int argc, char const *argv[]) {
    Card crd("5H");

    std::cout << crd << ": " << crd.GetSuitName() << std::endl;

    return 0;
}
