//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// cast_plus
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#define c_cast const_cast
#define s_cast static_cast
#define d_cast dynamic_cast
#define c_cast const_cast
#define r_cast reinterpret_cast
#define b_cast std::bit_cast
#define i_cast cxx::implicit_cast
#define p_cast cxx::promote_cast

//----------------------------------------------------------------

namespace cxx {

template< typename T >
constexpr T implicit_cast( std::type_identity_t< T > value ) {
	return value;
}

//----------------------------------------------------------------

template< typename T >
constexpr T implicit_cast( const std::type_identity_t< T >& value ) {
	return value;
}

//----------------------------------------------------------------

template< typename T > struct promote_type;

template<> struct promote_type< bool > { using type = uint8_t; };
template<> struct promote_type< int8_t > { using type = int16_t; };
template<> struct promote_type< uint8_t > { using type = uint16_t; };
template<> struct promote_type< int16_t > { using type = int32_t; };
template<> struct promote_type< uint16_t > { using type = uint32_t; };
template<> struct promote_type< int32_t > { using type = int64_t; };
template<> struct promote_type< uint32_t > { using type = uint64_t; };
template<> struct promote_type< int64_t > { using type = int64_t; };
template<> struct promote_type< uint64_t > { using type = uint64_t; };
template<> struct promote_type< float > { using type = float; };
template<> struct promote_type< double > { using type = long double; };

template< typename T >
using promote_type_t = promote_type< T >::type;

//----------------------------------------------------------------

template< typename T, typename Tmax > struct promote_type_max;

template< typename Tmax > struct promote_type_max< bool, Tmax > { using type = uint8_t; };
template< typename Tmax > struct promote_type_max< int8_t, Tmax > { using type = int16_t; };
template< typename Tmax > struct promote_type_max< uint8_t, Tmax > { using type = uint16_t; };
template< typename Tmax > struct promote_type_max< int16_t, Tmax > { using type = int32_t; };
template< typename Tmax > struct promote_type_max< uint16_t, Tmax > { using type = uint32_t; };
template< typename Tmax > struct promote_type_max< int32_t, Tmax > { using type = int64_t; };
template< typename Tmax > struct promote_type_max< uint32_t, Tmax > { using type = uint64_t; };
template< typename Tmax > struct promote_type_max< int64_t, Tmax > { using type = int64_t; };
template< typename Tmax > struct promote_type_max< uint64_t, Tmax > { using type = uint64_t; };
template< typename Tmax > struct promote_type_max< float, Tmax > { using type = double; };
template< typename Tmax > struct promote_type_max< double, Tmax > { using type = long double; };

template<> struct promote_type_max< int32_t, int32_t > { using type = int32_t; };
template<> struct promote_type_max< uint32_t, uint32_t > { using type = uint32_t; };
template<> struct promote_type_max< int64_t, int32_t > { using type = int32_t; };
template<> struct promote_type_max< uint64_t, uint32_t > { using type = uint32_t; };
template<> struct promote_type_max< float, float > { using type = float; };
template<> struct promote_type_max< double, float > { using type = float; };

template< typename T, typename Tmax >
using promote_type_max_t = promote_type_max< T, Tmax >::type;

//----------------------------------------------------------------

template< typename T, const size_t max_size > struct promote_type_max_size;

template< const size_t max_size > struct promote_type_max_size< bool, max_size > { using type = uint8_t; };
template< const size_t max_size > struct promote_type_max_size< int8_t, max_size > { using type = int16_t; };
template< const size_t max_size > struct promote_type_max_size< uint8_t, max_size > { using type = uint16_t; };
template< const size_t max_size > struct promote_type_max_size< int16_t, max_size > { using type = int32_t; };
template< const size_t max_size > struct promote_type_max_size< uint16_t, max_size > { using type = uint32_t; };
template< const size_t max_size > struct promote_type_max_size< int32_t, max_size > { using type = int64_t; };
template< const size_t max_size > struct promote_type_max_size< uint32_t, max_size > { using type = uint64_t; };
template< const size_t max_size > struct promote_type_max_size< int64_t, max_size > { using type = double; };
template< const size_t max_size > struct promote_type_max_size< uint64_t, max_size > { using type = double; };
template< const size_t max_size > struct promote_type_max_size< float, max_size > { using type = double; };
template< const size_t max_size > struct promote_type_max_size< double, max_size > { using type = long double; };

template<> struct promote_type_max_size< bool, 32 > { using type = uint8_t; };
template<> struct promote_type_max_size< int8_t, 32 > { using type = int16_t; };
template<> struct promote_type_max_size< uint8_t, 32 > { using type = uint16_t; };
template<> struct promote_type_max_size< int16_t, 32 > { using type = int32_t; };
template<> struct promote_type_max_size< uint16_t, 32 > { using type = uint32_t; };
template<> struct promote_type_max_size< int32_t, 32 > { using type = float; };
template<> struct promote_type_max_size< uint32_t, 32 > { using type = float; };
template<> struct promote_type_max_size< int64_t, 32 > { using type = float; };
template<> struct promote_type_max_size< uint64_t, 32 > { using type = float; };
template<> struct promote_type_max_size< float, 32 > { using type = float; };
template<> struct promote_type_max_size< double, 32 > { using type = float; };

template< typename T, const size_t max_size >
using promote_type_max_size_t = promote_type_max_size< T, max_size >::type;

}

template< typename T >
constexpr cxx::promote_type< T >::type promote_cast( std::type_identity_t< T > value ) {
	return static_cast< cxx::promote_type< T >::type >( value );
}

template< typename T, typename Tmax >
constexpr cxx::promote_type_max< T, Tmax >::type promote_cast_max( std::type_identity_t< T > value ) {
	return static_cast< cxx::promote_type_max< T, Tmax >::type >( value );
}

template< typename T, const size_t max_size >
constexpr cxx::promote_type_max_size< T, max_size >::type promote_cast_max_size( std::type_identity_t< T > value ) {
	return static_cast< cxx::promote_type_max_size< T, max_size >::type >( value );
}

//----------------------------------------------------------------
