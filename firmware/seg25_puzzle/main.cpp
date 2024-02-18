#include "pico/stdlib.h"

#include "display.h"


const uint switch_SER_OUT = 12;
const uint switch_SH_LD = 13;
const uint switch_CLK = 14;
const uint switch_CLK_INH = 15;

void setup_switch_gpio()
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

uint16_t read_switch()
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

uint16_t xorshift_state = 1;

uint16_t xorshift()
{
    xorshift_state ^= xorshift_state << 7;
    xorshift_state ^= xorshift_state >> 9;
    xorshift_state ^= xorshift_state << 8;
    return xorshift_state;
}

void update_display_from_switches(uint16_t switches)
{
    switch (switches)
    {
    case 0:
    {
        update_display("HELLO!");
        break;
    }
    case 1:
    {
        update_display(u"ABCDEF");
        break;
    }
    case 2:
    {
        update_display(u"GHIJKL");
        break;
    }
    case 3:
    {
        update_display(u"MNOPQR");
        break;
    }
    case 4:
    {
        update_display(u"STUVWX");
        break;
    }
    case 5:
    {
        update_display(u"YZ0123");
        break;
    }
    case 6:
    {
        update_display(u"456789");
        break;
    }
    case 7:
    {
        update_display(u"!@#$%^");
        break;
    }
    case 8:
    {
        update_display(u"&*()_+");
        break;
    }
    case 9:
    {
        update_display(u"`~-=");
        break;
    }
    case 10:
    {
        update_display(u"<>[]{}");
        break;
    }
    case 11:
    {
        update_display(u"/|\\?");
        break;
    }
    case 12:
    {
        update_display(u"βΓΣδζλ");
        break;
    }
    case 13:
    {
        update_display(u"μΞΠπσΨ");
        break;
    }
    case 14:
    {
        update_display(u"א");
        break;
    }

    case 0xFFFF:
    {
        Display d;

        // Turn all segments on
        for (uint8_t digit = 0; digit < 7; ++digit)
        {
            d.digits[digit] = 0xFFFFFF;
        }
        update_display(d);
        break;
    }
    default:
    {
        Display d;

        // Generate some pseudorandom data seeded from the switch state
        xorshift_state = switches;
        for (uint8_t digit = 0; digit < 7; ++digit)
        {
            d.digits[digit] = xorshift() | (xorshift() << 16);
        }

        update_display(d);

        break;
    }
    }

}


int main()
{
    setup_switch_gpio();

    init_display();

    while (true)
    {
        auto switches = read_switch();

        update_display_from_switches(switches);

        sleep_ms(10);
    }
}
