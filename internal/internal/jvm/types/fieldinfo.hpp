#pragma once

#include "symbol.hpp"
#include "constantpool.hpp"

class c_fieldinfo
{
	enum field_offset
	{
        access_flags_offset = 0,
        name_index_offset = 1,
        signature_index_offset = 2,
        initval_index_offset = 3,
        low_packed_offset = 4,
        high_packed_offset = 5,
        field_slots = 6
	};

    unsigned short m_shorts[ field_slots ];
    
public:
    c_fieldinfo* from_field_array( c_array<unsigned short>* fields, const int index )
    {
        return reinterpret_cast< c_fieldinfo* >( fields->addr_get( index ) * field_slots );
    }

    unsigned short name_index( )
    {
        return m_shorts[ name_index_offset ];
    }

    unsigned short signature_index( )
    {
        return m_shorts[ signature_index_offset ];
    }

    unsigned short initval_index( )
    {
        return m_shorts[ initval_index_offset ];
    }

    c_symbol* name( c_constantpool* cp )
    {
        return cp->at<c_symbol*>( this->name_index( ) );
    }

    c_symbol* signature( c_constantpool* cp )
    {
        return cp->at<c_symbol*>( this->signature_index( ) );
    }
};