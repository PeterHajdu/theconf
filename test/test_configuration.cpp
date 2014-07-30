#include <theconf/configuration.hpp>
#include <igloo/igloo_alt.h>
using namespace igloo;

namespace
{
const char* configuration_string(
    "dog=food\n"
    "cat = stupid\n"
    "bee foo\n"
    "=fly\n"
    "bug=\n"
    );
}

Describe( a_configuration )
{
  void SetUp()
  {
    test_stream.str( configuration_string );
    the::conf::parse( test_stream );
  }

  It( can_parse_istreams )
  {
    AssertThat( the::conf::get( "dog" ), Equals( "food" ) );
  }

  It( chops_off_whitespaces_from_key_and_value )
  {
    AssertThat( the::conf::get( "cat" ), Equals( "stupid" ) );
  }

  It( can_check_if_a_key_value_pair_exist )
  {
    AssertThat( the::conf::has( "mouse" ), Equals( false ) );
    AssertThat( the::conf::has( "dog" ), Equals( true ) );
  }

  It( should_not_create_key_value_by_accessing_it )
  {
    the::conf::get( "mouse" );
    AssertThat( the::conf::has( "mouse" ), Equals( false ) );
  }

  It( should_skip_lines_without_the_separator )
  {
    AssertThat( the::conf::has( "bee foo" ), Equals( false ) );
  }

  It( should_skip_lines_without_key )
  {
    AssertThat( the::conf::has( "" ), Equals( false ) );
  }

  It( should_parse_empty_value )
  {
    AssertThat( the::conf::has( "bug" ), Equals( true ) );
    AssertThat( the::conf::get( "bug" ), Equals( "" ) );
  }

  std::stringstream test_stream;
};

