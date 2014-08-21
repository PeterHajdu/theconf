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

  Describe( parsing_a_stream )
  {
    void SetUp()
    {
      test_stream.str( configuration_string );
      the::conf::parse( test_stream );
    }

    It( should_be_able_to_clear_configuration )
    {
      the::conf::clear();
      AssertThat( the::conf::has( "dog" ), Equals( false ) );
    }

    It( can_parse_istreams )
    {
      AssertThat( the::conf::get_value( "dog" ), Equals( "food" ) );
    }

    It( chops_off_whitespaces_from_key_and_value )
    {
      AssertThat( the::conf::get_value( "cat" ), Equals( "stupid" ) );
    }

    It( can_check_if_a_key_value_pair_exist )
    {
      AssertThat( the::conf::has( "mouse" ), Equals( false ) );
      AssertThat( the::conf::has( "dog" ), Equals( true ) );
    }

    It( should_not_create_key_value_by_accessing_it )
    {
      the::conf::get_value( "mouse" );
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
      AssertThat( the::conf::get_value( "bug" ), Equals( "" ) );
    }

    It( can_set_a_value )
    {
      const std::string key( "lion" );
      const std::string value( "potatoe" );
      AssertThat( the::conf::has( key ), Equals( false ) );
      the::conf::set_value( key, value );
      AssertThat( the::conf::get_value( key ), Equals( value ) );
    }

    It( can_retrieve_a_value_with_a_given_type )
    {
      the::conf::set_value( "pen", "10" );
      AssertThat( the::conf::get<int>( "pen" ), Equals( 10 ) );
    }

    It( can_set_a_value_with_arbitrary_type )
    {
      the::conf::set( "pen", 5 );
      AssertThat( the::conf::get_value( "pen" ), Equals( "5" ) );
    }
    std::stringstream test_stream;
  };

  Describe( parsing_command_line_arguments )
  {
    void SetUp()
    {
      the::conf::clear();
      const std::vector< std::string > parameters{ "apple", "apple", "--dog", "--cat", "mouse", "--help" };
      the::conf::parse( parameters );
    }

    It( can_parse_standalone_parameters )
    {
      AssertThat( the::conf::has( "dog" ), Equals( true ) );
      AssertThat( the::conf::get< std::string >( "dog" ), Equals( "" ) );
    }

    It( can_parse_standalone_parameters_at_the_end_of_the_list )
    {
      AssertThat( the::conf::has( "help" ), Equals( true ) );
    }

    It( can_parse_key_value_pairs )
    {
      AssertThat( the::conf::get<std::string>( "cat" ), Equals( "mouse" ) );
    }

    It( does_not_add_values_as_keys )
    {
      AssertThat( the::conf::has( "mouse" ), Equals( false ) );
    }

    It( should_not_do_anything_with_values_without_keys )
    {
      AssertThat( the::conf::has( "apple" ), Equals( false ) );
    }

  };

};

