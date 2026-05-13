//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// 10-bit DAC
// tc1321
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware_i2c_plus.h"
#include "wire.h"

//----------------------------------------------------------------

constexpr uint8_t TC1321_ADDRESS { 0x48 }; // 0x90 >> 1


constexpr uint8_t TC1321_REG_DATA { 0x00 }; // param: 10 bits right aligned
constexpr uint8_t TC1321_REG_CONFIG { 0x01 }; // param : 8 bits

//----------------------------------------------------------------

class tc1321 {

private:

    wire* _wire { nullptr };

    uint16_t _vref { 3300 }; // mV

public:

    tc1321() = delete;
    tc1321( uint i2c_num );

    ~tc1321() noexcept;

    bool get_sleep() const;
    void set_sleep();

    uint16_t get_vref() const { return _vref; };
    void set_vref( uint16_t vref ) { _vref = vref; };

    uint16_t get_vout() const;
    void set_vout( uint16_t vout );

};

//----------------------------------------------------------------
