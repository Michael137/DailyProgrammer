#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

std::vector<long> read_input()
{
	std::string input;
	std::vector<long> nums;
	std::getline( std::cin, input );

	bool inDigit = false;
	std::string digit;
	for( char c : input ) {
		if( isdigit( c ) ) {
			inDigit = true;
			digit += c;
		} else {
			if( !digit.empty() )
				nums.push_back( std::stoi( digit, nullptr, 0 ) );
			inDigit = false;
			digit.clear();
		}
	}

	if( !digit.empty() ) nums.push_back( std::stoi( digit, nullptr, 0 ) );

	return nums;
}

template<typename Num>
auto compute_ducci_seq( std::vector<Num> nums,
					   std::vector<std::vector<Num>> history )
{
	if( std::all_of( nums.begin(), nums.end(),
					 []( Num n ) { return n == 0; } ) )
		return 1;

	if( !std::none_of( history.begin(), history.end(),
					   [&nums]( auto v ) { return v == nums; } ) )
		return 1;
	history.push_back( nums );
	Num i = 0;
	Num oldFirst = nums[0];
	while( 1 ) {
		if( i == nums.size() - 1 ) {
			nums[i] = std::abs( nums[i] - oldFirst );
			break;
		}
		nums[i] = std::abs( nums[i + 1] - nums[i] );

		i++;
	}

	std::cout << "[";
	for( auto& elem : nums )
		std::cout << " " << elem << " ";

	std::cout << "]" << std::endl;

	return 1 + compute_ducci_seq( nums, history );
}

int main()
{
	std::cout << compute_ducci_seq( read_input(), {} ) << std::endl;
	return 0;
}
