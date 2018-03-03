//https://www.reddit.com/r/dailyprogrammer/comments/759fha/20171009_challenge_335_easy_consecutive_distance/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

int main(int argc, char const* argv[])
{

    int seqs = 0,
        seqs_len = 0;

    std::cin >> seqs >> seqs_len;

    for (int i = 0; i < seqs; i++) {
        //Lazy copying of input into array...
        std::vector<int> distances;
        std::vector<std::pair<int, int>> dist_pairs;
        copy_n(std::istream_iterator<int>(std::cin), seqs_len, std::back_inserter(distances));

        for (int j = 0; j < distances.size(); j++) {
            dist_pairs.push_back({ distances[j], j });
        }

        struct {
            bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const { return lhs.first < rhs.first; }
        } cmp;
        std::sort(dist_pairs.begin(), dist_pairs.end(), cmp);

        double sum = 0;
        for (int k = 0; k < dist_pairs.size() - 1; k++) {
            if (dist_pairs[k].first - dist_pairs[k + 1].first == -1) {
                sum += std::abs(dist_pairs[k].second - dist_pairs[k + 1].second);
            }
        }

        std::cout << sum << std::endl;
    }

    return 0;
}
