#pragma once

#include <string_view>

#include "../util/xors.hpp"

#define hashxor( s ) ( c_hash::fnv( xors( s ) ) )

class c_hash
{
	inline static constexpr auto m_basis = 0x8adf9ed5;
	inline static constexpr auto m_prime = 0x60561129;

public:
	using hash_t = size_t;

	static constexpr hash_t fnv( const std::string_view str )
	{
		hash_t res = m_basis;

		for ( auto i = 0; i < str.size( ); i++ )
			res = ( res ^ str[ i ] ) * m_prime;

		return res;
	}
};