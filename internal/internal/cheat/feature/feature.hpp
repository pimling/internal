#pragma once

#include <vector>
#include <memory>

#include "context.hpp"

class c_feature
{
protected:
	inline static std::vector<c_feature*> m_features{ };

public:
	virtual void run( const std::shared_ptr<c_context>& context ) = 0;

	static void run_features( const std::shared_ptr<c_context>& context )
	{
		for ( auto& f : m_features )
			f->run( context );
	}
};