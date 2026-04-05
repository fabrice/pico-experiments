//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// pointers_plus
//
//----------------------------------------------------------------

inline bool is_null( const void* pointer ) {
	return pointer == nullptr;
}

//----------------------------------------------------------------

inline bool is_not_null( const void* pointer ) {
	return !(pointer == nullptr);
}

//----------------------------------------------------------------
