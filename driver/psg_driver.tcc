//          Copyright Jean Pierre Cimalando 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "psg_driver.h"
#include <cassert>

inline PSG_Driver::PSG_Driver()
{
    psg_t *psg = &psg_;
    PSG_Reset(psg);
}

inline void PSG_Driver::set_volume(unsigned ch, unsigned value)
{
    psg_t *psg = &psg_;
    assert(ch < 4);
    assert(value < 16);
    PSG_Write(psg, 0x90|(ch << 5)|(15 - value));
}

inline void PSG_Driver::set_wave(unsigned ch, unsigned freq)
{
    psg_t *psg = &psg_;
    assert(ch < 3);
    assert(freq < 1024);
    PSG_Write(psg, 0x80|(ch << 5)|(freq & 0x0f));
    PSG_Write(psg, (freq >> 4) & 0x3f);
}

inline void PSG_Driver::set_noise(unsigned fb, unsigned nf)
{
    psg_t *psg = &psg_;
    unsigned ch = 3;
    assert(fb < 2);
    assert(nf < 4);
    PSG_Write(psg, 0x80|(ch << 5)|(fb << 2)|nf);
}

inline void PSG_Driver::cycle()
{
    psg_t *psg = &psg_;
    PSG_Cycle(psg);
}

inline uint16_t PSG_Driver::get_outputs()
{
    psg_t *psg = &psg_;
    return PSG_Read(psg);
}

inline float PSG_Driver::get_sample()
{
    psg_t *psg = &psg_;
    float sample;
    PSG_GetSample(psg, &sample);
    return sample;
}
