#include "jvm.hpp"
#include "../other/util/lazy.hpp"
#include "../other/memory/memory.hpp"
#include "../game/modules/modules.hpp"
#include "types/classloaderdata.hpp"
#include "types/instanceklass.hpp"

// you can do this many different ways, this is one i thought of immediately 
// so if its not optimal implement a better one yourself lol
void c_jvm::find_minecraft_class( c_instanceklass* klass )
{
	static auto possible_classes = std::vector<c_instanceklass*>{ };

	m_loaded_classes.emplace_back( klass );

	if ( !klass->methods( ) || klass->methods( )->length( ) <= 0 )
		return;
	
	const auto constants = klass->constants( );

	if ( !constants )
		return;

	const auto tags = constants->tags( );

	if ( !tags || !tags->data( ) || tags->length( ) <= 0 )
		return;

	for ( auto i = 0; i < tags->length( ); i++ )
	{
		const auto tag = tags->get( i );

		if ( tag != 0x1 ) // string
			continue;

		const auto tag_value = constants->at<c_symbol*>( i )->to_string( );

		if ( tag_value.find( xors( "Pre render" ) ) != std::string::npos )
		{
			m_mc_class = klass; // we have found the minecraft class - hurrah!
			return;
		}
	}
}

void c_jvm::init( )
{  
	const auto offset = c_modules::m_jvm->pattern_scan( { 0x48, 0x8b, 0x05, 0xff, 0xff, 0xff, 0xff, 0x48, 0x85, 0xc0, 0x74, 0xff, 0x33, 0xc9, 0x66 } ) + 0x3;
	const auto addr = offset + *reinterpret_cast< std::uint32_t* >( offset ) + sizeof( std::uint32_t );

	c_classloaderdatagraph::m_head = *reinterpret_cast< c_classloaderdata** >( addr );

	for ( auto node = c_classloaderdatagraph::m_head; node; node = node->next( ) )
	{
		for ( auto klass = node->klass( ); klass; klass = klass->next_link( ) )
		{
			if ( !klass->is_instance( ) )
				continue;

			m_loaded_classes.emplace_back( klass );

			if ( !m_mc_class )
				find_minecraft_class( klass );
		}
	}
}