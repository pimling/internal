#include "../../feature.hpp"

class c_aim : public c_feature
{
public:
	c_aim( )
	{
		m_features.emplace_back( this );
	}

	void run( const std::shared_ptr<c_context>& context ) override
	{
		const auto mc = c_minecraft::get( );
	}
};

inline auto g_aim = c_aim{ };