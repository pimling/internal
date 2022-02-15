#pragma once

template<typename T>
class c_array
{
	int m_length;
	T m_data[ 1 ];

public:
	inline int length( )
	{
		return this->m_length;
	}

	inline T* data( )
	{
		return &this->m_data[ 0 ];
	}

	inline T get( const size_t index )
	{
		return this->m_data[ index ];
	}

	inline T addr_get( const size_t index )
	{
		return &this->m_data[ index ];
	}
};