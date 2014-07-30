#include <theconf/configuration.hpp>
#include <memory>
#include <unordered_map>
#include <locale>
#include <algorithm>

namespace
{

typedef std::unordered_map< std::string, std::string > KeyValueMap;
std::unique_ptr< KeyValueMap > configuration_instance;

KeyValueMap& instance()
{
  if ( !configuration_instance )
  {
    configuration_instance.reset( new KeyValueMap() );
  }

  return *configuration_instance;
}

const char delimiter{ '=' };
const std::string empty_string{};

std::string trim( std::string&& text )
{
  text.erase(
      std::begin( text ),
      std::find_if( std::begin( text ), std::end( text ), std::not1( std::ptr_fun<int, int>( std::isspace ) ) ) );

  text.erase(
      std::find_if( text.rbegin(), text.rend(), std::not1( std::ptr_fun<int, int>( std::isspace) ) ).base(),
      text.end() );

  return text;
}

}

namespace the
{

namespace conf
{

void
parse( std::istream& input )
{
  KeyValueMap& key_value( instance() );
  std::string line;
  while ( std::getline( input, line ) )
  {
    const std::size_t delimiter_position( line.find_first_of( delimiter ) );
    if ( delimiter_position == std::string::npos )
    {
      continue;
    }

    const std::string key( trim( line.substr( 0, delimiter_position ) ) );
    if ( key.empty() )
    {
      continue;
    }

    const std::string value( trim( line.substr( delimiter_position + 1, line.length() - delimiter_position ) ) );
    key_value[ key ] = value;
  }
}

const std::string&
get_value( const std::string& key )
{
  KeyValueMap& key_value( instance() );
  KeyValueMap::const_iterator key_iterator( key_value.find( key ) );
  return
    key_iterator == key_value.end() ?
    empty_string :
    key_iterator->second;
}

bool
has( const std::string& key )
{
  KeyValueMap& key_value( instance() );
  KeyValueMap::const_iterator key_iterator( key_value.find( key ) );
  return key_iterator != key_value.end();
}

void
set_value( const std::string& key, const std::string& value )
{
  KeyValueMap& key_value( instance() );
  key_value[ key ] = value;
}

}

}

