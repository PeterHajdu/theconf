#pragma once

#include <istream>
#include <string>
#include <sstream>

namespace the
{

namespace conf
{

void parse( std::istream& );
void clear();
bool has( const std::string& key );
const std::string& get_value( const std::string& key );
void set_value( const std::string& key, const std::string& value );

template < typename T >
T get( const std::string& key )
{
  std::stringstream ss( get_value( key ) );
  T return_value;
  ss >> return_value;
  return return_value;
}

template < typename T >
void set( const std::string& key, const T& value )
{
  std::stringstream ss;
  ss << value;
  set_value( key, ss.str() );
}

}

}

