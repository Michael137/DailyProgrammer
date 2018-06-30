#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <utility>

std::pair<unsigned int, unsigned int> split( std::string const& str )
{
	std::string::size_type pos = str.find( 'd', 0 );
	return std::make_pair(
		std::stoi( str.substr( 0, pos ), nullptr, 10 ),
		std::stoi( str.substr( pos + 1, std::string::npos ), nullptr, 10 ) );
}

template<typename Out, typename Fun, typename Num>
void fill( Out result, Fun func, Num size )
{
	for( Num i = 0; i < size; ++i )
		*( result++ ) = func();
}

template<typename Num> void roll( Num rolls, Num const sides )
{
	std::mt19937 gen;
	std::uniform_int_distribution<unsigned int> dist( 1, sides );
	auto dice = std::bind( dist, gen );
	std::vector<Num> results;
	fill( std::back_inserter( results ), dice, rolls );

	std::cout << std::accumulate( results.begin(), results.end(), 0,
								  std::plus<Num>() )
			  << ": ";

	for( auto& r : results )
		std::cout << r << " ";

	std::cout << std::endl;
}

int main()
{
	std::string input;
	while( 1 ) {
		getline( std::cin, input );
		auto dice = split( input );
		roll( std::get<0>( dice ), std::get<1>( dice ) );
	}
	return 0;
}
