//          Copyright Jean Pierre Cimalando 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

extern "C" {
#include "ym7101psg.h"
}

class PSG_Driver {
public:
    PSG_Driver();

    void set_volume(unsigned ch, unsigned value);
    void set_wave(unsigned ch, unsigned freq);
    void set_noise(unsigned fb, unsigned nf);

    void cycle();
    uint16_t get_outputs();
    float get_sample();

private:
    psg_t psg_;
};

#include "psg_driver.tcc"
