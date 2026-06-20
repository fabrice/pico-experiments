//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// instance_registry
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include <cstdint>
#include <map>
#include <limits>

//----------------------------------------------------------------

template< typename instance_ptr_t >
class instance_registry {

private:

	// https://cppreference.com/cpp/container/map
	std::map< uint, instance_ptr_t > _registry {};

public:

	//------------------------------------------------------------

	static instance_registry* make() {
		auto that = new instance_registry();
		return that;
	}

	//------------------------------------------------------------

	static instance_registry* make( size_t slots ) {
		auto that = new instance_registry();
		return that;
	}

	//------------------------------------------------------------

	instance_registry() = default;

	~instance_registry() = default;

	//------------------------------------------------------------

	/*! get_free_instance_num()
	* \brief pour obtenir un numéro d'instance libre
	* \return numéro d'instance libre
	*/
	uint get_free_instance_num() const {
		uint instance_num = 0;

		for ( const auto& [key, value] : _registry ) {
			if ( (value == nullptr) or (key > instance_num) ) return instance_num;
			if ( key == instance_num ) ++ instance_num;
		}

		return instance_num;
	}

	//------------------------------------------------------------

	/*! get_instance()
	* \brief pour obtenir l'instance
	* \param instance_num numéro d'instance
	* \return instance ou nullptr
	*/
	instance_ptr_t get_instance( uint instance_num ) const noexcept {
		auto pair = _registry.find( instance_num );
		if ( pair == _registry.end() ) return nullptr;

		return pair->second;
	}

	//------------------------------------------------------------

	void set_instance( uint instance_num, instance_ptr_t that ) {
		// TODO: check for get_instance() != nullptr
		_registry[ instance_num ] = that;
	}

	//------------------------------------------------------------

	void erase_instance( uint instance_num ) {
		_registry.erase( instance_num );
	}

	//------------------------------------------------------------

	void delete_instance( uint instance_num ) {
		auto pair = _registry.find( instance_num );
		if ( pair == _registry.end() ) return;

		if ( pair->second != nullptr ) delete pair->second;
		_registry.erase( pair );
	}

	//------------------------------------------------------------

	/*! get_instance()
	* \brief pour obtenir le numéro d'instance
	* \param that instance
	* \return numéro d'instance ou < uint >::max()
	*/
	uint get_instance_num( instance_ptr_t that ) const noexcept {
		for ( const auto& [key, value] : _registry ) {
			if ( value == that ) return key;
		}

		return std::numeric_limits< uint >::max();
	}

	//------------------------------------------------------------

};

//----------------------------------------------------------------
