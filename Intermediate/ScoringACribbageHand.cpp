/*
URL: https://www.reddit.com/r/dailyprogrammer/comments/75p1cs/20171011_challenge_335_intermediate_scoring_a/
Run: g++ .\ScoringACribbageHand.cpp -std=c++1y -o out3
Info:
    1 Deck=52 cards
    Rounds: deal,discard,play (can earn points),show (can earn points)
    Players hand: 4 cards + 1 face-up card
    Show round: player scores points based on cards owned
    Point rules:
        sum(any cards)==15 -> 2 points each
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
#include <numeric>
#include <functional>
#include <unordered_map>
#include <iterator>
#include <sstream>

static const std::map<char, int> CardRanks {
    {'A', 1},
    {'J', 10},
    {'Q', 10},
    {'K', 10},
};

static const std::map<char, int> CardOrders {
    {'A', 0},
    {'J', 1},
    {'Q', 2},
    {'K', 3},
};

class Card {
private:
    std::string rank_suit_;
    bool face_up_;
    int rank_;
    char suit_;

public:
    Card() : rank_suit_(), face_up_(), rank_(), suit_() {};
    Card(std::string rank_suit, bool face_up=false) : rank_suit_(std::move(rank_suit)), face_up_(face_up) {
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

    friend void swap(Card& lhs, Card& rhs) noexcept {
        using std::swap;

        swap(lhs.rank_suit_,rhs.rank_suit_);
        swap(lhs.face_up_,rhs.face_up_);
        swap(lhs.rank_,rhs.rank_);
        swap(lhs.suit_,rhs.suit_);
    }

    Card(const Card& rhs) : rank_suit_(rhs.rank_suit_),
                            face_up_(rhs.face_up_),
                            rank_(rhs.rank_),
                            suit_(rhs.suit_) {};

    Card& operator=(Card rhs) {
        swap(*this, rhs);

        return *this;
    }

    Card(Card&& rhs) : Card() {
        swap(*this, rhs);
    }

    const int Rank() const { return rank_; }
    const char Suit() const { return suit_; }
    const std::string RankToString() { return rank_suit_.substr(0, rank_suit_.size()-1); }
    const int RankToOrder() {
        auto order = CardOrders.find(rank_suit_[0]);
        if(order != std::end(CardOrders))
            return rank_ + order->second;
        else
            return rank_;
    }
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
    void IsFaceUp(bool b) { face_up_=b; }

    Card& operator+=(const Card& rhs) {
        (*this).rank_ += rhs.rank_;

        return *this;
    }

    friend bool operator==(const Card& lhs, const Card& rhs) {
        return lhs.Rank() == rhs.Rank();
    }

    friend Card operator+(Card lhs, const Card& rhs) {
        lhs += rhs;

        return lhs;
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& crd) {
        os << crd.rank_suit_;

        return os;
    };

    friend std::istream& operator>>(std::istream& is, Card& crd) {
        std::string input;
        is >> input;
        crd = Card(input);

        return is;
    }
};

struct Rule {
    Rule() {};
    virtual ~Rule() {};
    virtual int operator()(std::vector<Card>& v) const=0;
};

struct Consecutive : public Rule {
    Consecutive() : Rule() {};
    ~Consecutive() {};
    int operator()(std::vector<Card>& v) const {
        std::sort(v.begin(), v.end(), [](Card& lhs, Card& rhs) {
            return lhs.RankToOrder() < rhs.RankToOrder();
        });

        int consec = 1;
        int ctr = 0;
        for(auto& crd : v) {
            Card* next_crd_p = (&crd + 1);
            if( ctr < v.size() - 1
                && crd.RankToOrder() + 1 == next_crd_p->RankToOrder()) {
                    consec++;
            }
            ctr++;
        }

        return (consec > 2) ? consec : 0;
    };
};

struct CardSum : public Rule {
private:
    int sum_condition_;

    int SumOfSubsets_(std::vector<Card> v, int ctr, int sz, int sum = 0) const {
        int points = 0;
        if(ctr > sz) {
            return (sum == sum_condition_) ? points+2 : points;
        }

        points += SumOfSubsets_(v, ctr+1, sz, sum + v[ctr].Rank());
        points += SumOfSubsets_(v, ctr+1, sz, sum);
        return points;
    }

public:
    explicit CardSum(int sum_condition) : Rule(), sum_condition_(sum_condition) {};
    ~CardSum() {};

    int operator()(std::vector<Card>& v) const {
        return SumOfSubsets_(v, 0, 5);
    };
};

struct OfAKind : public Rule {
    OfAKind() : Rule() {};
    ~OfAKind() {};
    int operator()(std::vector<Card>& v) const {
        std::unordered_map<std::string, int> ctr_map;
        for(auto& crd : v) {
            std::string crd_rank = crd.RankToString();
            auto it(ctr_map.find(crd_rank));
            if(it != ctr_map.end()) {
                it->second++;
            } else {
                ctr_map[crd_rank] = 1;
            }
        }

        return std::accumulate(ctr_map.begin(), ctr_map.end(), 0, [](int culum, std::pair<const std::string, int>& elem) {
            int occ = elem.second;
            return culum + ((occ > 2) ? occ * 3 : ((occ == 2) ? occ : 0));
        });
    };
};

struct SameSuit : public Rule {
    SameSuit() : Rule() {};
    ~SameSuit() {};
    int operator()(std::vector<Card>& v) const {
        std::map<char, int> counts;
        char face_up_rank;

        std::for_each(v.begin(), v.end(), [&counts,&face_up_rank](Card crd) {
            if(!crd.IsFaceUp())
                counts[crd.Suit()]++;
            else
                face_up_rank = crd.Suit();
        });

        std::pair<char, int> x = *(std::max_element(counts.begin(), counts.end(),
                                    [](const std::pair<char, int>& p1, const std::pair<char, int>& p2) {
                                        return p1.second < p2.second; }));

        if( x.second >= 4 )
            return (x.first == face_up_rank) ? 5 : 4;
        else
            return 0;
    };
};

struct JackFaceupSuit : public Rule {
    JackFaceupSuit() : Rule() {};
    ~JackFaceupSuit() {};

    int operator()(std::vector<Card>& v) const {
        auto face_up_crd = std::find_if(v.begin(), v.end(), [](Card crd) {
            return crd.IsFaceUp();
        });

        char face_up_suit = (*face_up_crd).Suit();

        return std::accumulate(v.begin(),v.end(), 0, [face_up_suit  ](int culum, Card& crd){
            if(!crd.IsFaceUp() && crd.RankToString() == "J" && crd.Suit() == face_up_suit)
                return ++culum;
            else
                return culum;
        });
    }
};

int main(int argc, char const *argv[]) {
    std::cout << "Enter 'q' to exit." << '\n';

    int num_of_cards = 5;
    Consecutive cons_rule;
    CardSum sum_rule(15);
    OfAKind of_a_kind_rule;
    SameSuit same_suit_rule;
    JackFaceupSuit jack_face_up_suit_rule;

    while(1) {
        std::vector<Card> v;
        std::string input;
        std::cin >> input;

        if(input == "q")
            break;

        std::replace(input.begin(),input.end(),',', ' ');

        std::stringstream ss(input);

        copy_n(std::istream_iterator<Card>(ss), num_of_cards, std::back_inserter(v));
        v[4].IsFaceUp(true);

        std::cout << cons_rule(v) + sum_rule(v) + of_a_kind_rule(v) + same_suit_rule(v) + jack_face_up_suit_rule(v) << std::endl;
    }

    return 0;
}
