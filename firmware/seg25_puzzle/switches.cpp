#include "switches.h"


const uint switch_SER_OUT = 12;
const uint switch_SH_LD = 13;
const uint switch_CLK = 14;
const uint switch_CLK_INH = 15;

void init_switches()
{
    gpio_init(switch_SER_OUT);
    gpio_init(switch_SH_LD);
    gpio_init(switch_CLK);
    gpio_init(switch_CLK_INH);

    gpio_set_dir(switch_SER_OUT, GPIO_IN);
    gpio_set_dir(switch_SH_LD, GPIO_OUT);
    gpio_set_dir(switch_CLK, GPIO_OUT);
    gpio_set_dir(switch_CLK_INH, GPIO_OUT);

    // Disable clock inhibit
    gpio_put(switch_CLK_INH, 0);

    // Put shift/load signal in default state
    gpio_put(switch_SH_LD, 1);
}

uint16_t read_switches()
{
    gpio_put(switch_CLK, 0);

    // Capture the data
    gpio_put(switch_SH_LD, 0);
    gpio_put(switch_SH_LD, 1);

    uint16_t result = 0;
    for (uint8_t i = 0; i < 16; ++i)
    {
        gpio_put(switch_CLK, 1);
        gpio_put(switch_CLK, 0);

        // Invert, since an up switch produces a 0
        if (!gpio_get(switch_SER_OUT))
        {
            result |= 1 << i;
        }
    }

    return result;
}
