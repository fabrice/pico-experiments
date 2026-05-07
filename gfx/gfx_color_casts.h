//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_casts
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "gfx_types.h"
#include <cmath>

//----------------------------------------------------------------

namespace gfx {

//----------------------------------------------------------------

template< typename from_t, typename to_t >
to_t component_cast( from_t component );

//----------------------------------------------------------------
// any to itself

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires( std::is_same_v< from_t, to_t > ) {
	return component;
}

//----------------------------------------------------------------
// bool to any integer

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires (std::is_same_v< from_t, bool > && std::is_integral_v< to_t > && !std::is_same_v< to_t, bool >) {
	return component ? std::numeric_limits< to_t >::max() : static_cast< to_t >( 0 );
}

//----------------------------------------------------------------
// bool to any floating point

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires (std::is_same_v< from_t, bool > && std::is_floating_point_v< to_t >) {
	return component ? static_cast< to_t >( 1.0 ) : static_cast< to_t >( 0.0 );
}

//----------------------------------------------------------------
// any integer to bool

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires (std::is_integral_v< from_t > && !std::is_same_v< from_t, bool > && std::is_same_v< to_t, bool >) {
	return component >= (std::numeric_limits< from_t >::max() / static_cast< from_t>( 2 ));
}

//----------------------------------------------------------------
// any unsigned integer to any unsigned integer

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires (std::is_integral_v< from_t > && std::is_unsigned_v< from_t > && !std::is_same_v< from_t, bool > && std::is_integral_v< to_t > && std::is_unsigned_v< to_t > && !std::is_same_v< to_t, bool > && !std::is_same_v< from_t, to_t >) {
	if constexpr ( sizeof(from_t) > sizeof(to_t) ) {
		// demotion
		return static_cast< to_t >( component / (static_cast< from_t >(std::numeric_limits< from_t >::max()) / static_cast< from_t >(std::numeric_limits< to_t >::max())) );
	}
	else {
		// promotion
		return static_cast< to_t >( component * (static_cast< to_t >(std::numeric_limits< to_t >::max()) / static_cast< to_t >(std::numeric_limits< from_t >::max())) );
	}
}

//----------------------------------------------------------------
// any integer to any floating point

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires (std::is_integral_v< from_t > && !std::is_same_v< from_t, bool > && std::is_floating_point_v< to_t >) {
	return static_cast< to_t >( component ) / static_cast< to_t >(std::numeric_limits< from_t >::max());
}

//----------------------------------------------------------------
// any floating point to bool

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires (std::is_floating_point_v< from_t > && std::is_same_v< to_t, bool >) {
	return component >= static_cast< from_t >( 0.5 );
}

//----------------------------------------------------------------
// any floating point to any integer

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires (std::is_floating_point_v< from_t > && std::is_integral_v< to_t > && !std::is_same_v< to_t, bool>) {
	return static_cast< to_t >( std::round( component * static_cast< from_t >( std::numeric_limits< to_t >::max() ) ) );
}

//----------------------------------------------------------------
// any floating point to any floating point

template< typename from_t, typename to_t >
constexpr to_t component_cast( from_t component )
		requires (std::is_floating_point_v< from_t > && std::is_floating_point_v< to_t > && !std::is_same_v< from_t, to_t>) {
	return static_cast< to_t >( component );
}

//----------------------------------------------------------------

}

//----------------------------------------------------------------
