#include "psg_driver.h"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    PSG_Driver drv;

    size_t nsamples = 512;
    double freq = 1000.0;
    double clock = 3579545;

    if (argc > 1)
        nsamples = strtoul(argv[1], nullptr, 0);
    if (argc > 2)
        freq = strtod(argv[2], nullptr);
    if (argc > 3)
        clock = strtod(argv[3], nullptr);

    fprintf(stderr, "Clock %f\n", clock);
    fprintf(stderr, "Note frequency %f\n", freq);

    // n=fc/32f
    unsigned chipdiv = 8/*32*/;
    double realchipfreq = clock / (chipdiv * freq);
    fprintf(stderr, "Chip period %f\n", realchipfreq);
    realchipfreq = round(realchipfreq);
    if (realchipfreq < 0 || realchipfreq >= 1024)
        return 1;
    unsigned chipfreq = (unsigned)realchipfreq;

    //[test]
    drv.set_volume(0, 15);
    drv.set_wave(0, chipfreq);

    drv.set_volume(1, 10);
    drv.set_wave(1, std::min(1023u, (unsigned)(chipfreq * 1.5)));

    drv.set_volume(2, 5);
    drv.set_wave(2, std::min(1023u, (unsigned)(chipfreq * 2.5)));

    drv.set_volume(3, 4);
    drv.set_noise(1, 1);
    //[/test]

    double samplerate = 44100;

    double t = 0;
    size_t currentsamples = 0;
    size_t currentcycles = 0;
    while (currentsamples < nsamples) {
        if (t > 1) {
            if (1) {
                const double psg_vol[16] = {
                    1.0, 0.772, 0.622, 0.485, 0.382, 0.29, 0.229, 0.174, 0.132, 0.096, 0.072, 0.051, 0.034, 0.019, 0.009, 0.0 };
                uint16_t outputs = drv.get_outputs();
                printf("%f", currentsamples / samplerate);
                for (unsigned ch = 0; ch < 4; ++ch) {
                    // printf(" %u", (outputs >> (4 * (3 - ch))) & 0xf);
                    printf(" %f", psg_vol[(outputs >> (4 * (3 - ch))) & 0xf]);
                }
                printf("\n");

                /* plot 'psg.dat' u 1:2 w lines t 'Ch1', '' u 1:3 w lines t 'Ch2', '' u 1:4 w lines t 'Ch3', '' u 1:5 w lines t 'Ch4' */
            }
            else {
                float sample = drv.get_sample();
                printf("%f %f\n", currentsamples / samplerate, sample);
            }
            ++currentsamples;
            t -= 1;
            continue;
        }
        drv.cycle();
        ++currentcycles;
        t += samplerate / clock;
    }

    fprintf(stderr, "Computed %zu cycles\n", currentcycles);

    return 0;
}
