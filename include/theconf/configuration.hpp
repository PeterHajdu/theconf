#pragma once

#include <istream>
#include <string>

namespace the
{

namespace conf
{

void parse( std::istream& );
const std::string& get( const std::string& key );
bool has( const std::string& key );

}

}

