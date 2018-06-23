#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool follows( std::string_view str )
{
	std::size_t found = str.find( "ei", 0 );

	while( found != std::string::npos ) {
		if( found == 0 || std::tolower( str.at( found - 1 ) ) != 'c' )
			return false;

		found = str.find( "ei", std::min( found + 1, str.size() ) );
	}

	return str.find( "cie", 0 ) == std::string::npos;
}

int main( int argc, char* argv[] )
{
	if( argc > 1 ) {
		std::cout << ( ( follows( std::string( argv[1] ) ) ) ? "true"
															 : "false" )
				  << std::endl;
		return 0;
	}

	std::vector<std::string> cases = {
		"receive",	 "fahrenheit", "believe", "a",	  "zombie",
		"transceiver", "veil",		 "icier",   "ciecei", "either"};

	for( auto& str : cases )
		std::cout << str
				  << ( follows( str ) ? " follows rule"
									  : " does not follow rule" )
				  << std::endl;

	return 0;
}
