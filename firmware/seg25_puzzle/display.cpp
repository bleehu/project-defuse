#include "display.h"

#include "pico/multicore.h"
#include "pico/mutex.h"


uint32_t char_to_segments(char16_t c)
{
    switch (c)
    {
    case  'A': return 0b11110011'00010001'00000000;
    case  'B': return 0b11111100'01010100'00000000;
    case  'C': return 0b11001111'00000000'00000000;
    case  'D': return 0b11111100'01000100'00000000;
    case  'E': return 0b11001111'00000001'00000000;
    case  'F': return 0b11000011'00000001'00000000;
    case  'G': return 0b11011111'00010000'00000000;
    case  'H': return 0b00110011'00010001'00000000;
    case  'I': return 0b11001100'01000100'00000000;
    case  'J': return 0b00111110'00000000'00000000;
    case  'K': return 0b00000011'00101001'00000000;
    case  'L': return 0b00001111'00000000'00000000;
    case  'M': return 0b00110011'10100000'00000000;
    case  'N': return 0b00110011'10001000'00000000;
    case  'O': return 0b11111111'00000000'00000000;
    case  'P': return 0b11100011'00010001'00000000;
    case  'Q': return 0b11111111'00001000'00000000;
    case  'R': return 0b11100011'00011001'00000000;
    case  'S': return 0b11011100'10010000'00000000;
    case  'T': return 0b11000000'01000100'00000000;
    case  'U': return 0b00111111'00000000'00000000;
    case  'V': return 0b00000011'00100010'00000000;
    case  'W': return 0b00110011'00001010'00000000;
    case  'X': return 0b00000000'10101010'00000000;
    case  'Y': return 0b00000000'10100100'00000000;
    case  'Z': return 0b11001100'00100010'00000000;

    case  '0': return 0b11111111'00100010'00000000;
    case  '1': return 0b00110000'00100000'00000000;
    case  '2': return 0b11101110'00010001'00000000;
    case  '3': return 0b11111100'00010000'00000000;
    case  '4': return 0b00110001'00010001'00000000;
    case  '5': return 0b11001101'00001001'00000000;
    case  '6': return 0b11011111'00010001'00000000;
    case  '7': return 0b11110000'00000000'00000000;
    case  '8': return 0b11111111'00010001'00000000;
    case  '9': return 0b11111101'00010001'00000000;

    case  '!': return 0b00000000'01000100'00000100;
    case  '@': return 0b11101111'01010000'00000000;
    case  '#': return 0b00111100'01010101'00000000;
    case  '$': return 0b11011101'01010101'00000000;
    case  '%': return 0b10011001'01110111'00000000;
    case  '*': return 0b00000000'11111111'00000000;
    case  '(': return 0b00000000'00101000'00000000;
    case  ')': return 0b00000000'10000010'00000000;
    case  '-': return 0b00000000'00010001'00000000;
    case  '=': return 0b00001100'00010001'00000000;
    case  '_': return 0b00001100'00000000'00000000;
    case  '+': return 0b00000000'01010101'00000000;
    case  '<': return 0b00000000'00100100'00000000;
    case  '>': return 0b00000000'10000010'00000000;
    case  '[': return 0b01001000'01000100'00000000;
    case  ']': return 0b10000100'01000100'00000000;

    case  '/': return 0b00000000'00100010'00000000;
    case  '|': return 0b00000000'01000100'00000000;
    case '\\': return 0b00000000'10001000'00000000;
    case  '?': return 0b11100000'00010100'00000100;

    case u'β': return 0b10000111'01000101'00000010;
    case u'Γ': return 0b11000011'00000000'00000000;
    case u'Σ': return 0b11001100'10000010'00000000;
    case u'δ': return 0b11011110'10010001'00000000;
    case u'ζ': return 0b11000110'00100001'00000100;
    case u'λ': return 0b00000000'10001010'00000000;
    case u'μ': return 0b00011110'00000000'00000010;
    case u'Ξ': return 0b11001100'00010001'00000000;
    case u'Π': return 0b11110011'00000000'00000000;
    case u'π': return 0b00000000'00011011'00000000;
    case u'σ': return 0b00000110'00010101'00000000;
    case u'Ψ': return 0b00100001'01010101'00000000;

    case u'א': return 0b00100010'10011001'00000000;
    default:   return 0b11111111'11111111'11111111;
    }
}


Display string_to_display(const char16_t* str)
{
    // Zero-init, so we can just stop when we reach the end of the string
    Display result {};
    for (int i = 0; i < 6; ++i)
    {
        if (str[i] == 0)
        {
            break;
        }
        else
        {
            result.digits[i] = char_to_segments(str[i]);
        }
    }
    return result;
}

// Same implementation as the char16_t* above.
// char will be implicitly cast to char16_t when calling char_to_segments().
Display string_to_display(const char* str)
{
    // Zero-init, so we can just stop when we reach the end of the string
    Display result {};
    for (int i = 0; i < 6; ++i)
    {
        if (str[i] == 0)
        {
            break;
        }
        else
        {
            result.digits[i] = char_to_segments(str[i]);
        }
    }
    return result;
}




const uint tpic_OE = 1;
const uint tpic_SRCK = 2;
const uint tpic_SER_IN = 3;
const uint tpic_CLR = 4;
const uint tpic_RCK = 5;

const uint digit_RCLK = 7;
const uint digit_SRCLR = 8;
const uint digit_OE = 9;
const uint digit_SRCLK = 10;
const uint digit_SER = 11;

void setup_display_gpio()
{
    gpio_init(tpic_OE);
    gpio_init(tpic_SRCK);
    gpio_init(tpic_SER_IN);
    gpio_init(tpic_CLR);
    gpio_init(tpic_RCK);
    gpio_init(digit_RCLK);
    gpio_init(digit_SRCLR);
    gpio_init(digit_OE);
    gpio_init(digit_SRCLK);
    gpio_init(digit_SER);

    gpio_set_dir(tpic_OE, GPIO_OUT);
    gpio_set_dir(tpic_SRCK, GPIO_OUT);
    gpio_set_dir(tpic_SER_IN, GPIO_OUT);
    gpio_set_dir(tpic_CLR, GPIO_OUT);
    gpio_set_dir(tpic_RCK, GPIO_OUT);
    gpio_set_dir(digit_RCLK, GPIO_OUT);
    gpio_set_dir(digit_SRCLR, GPIO_OUT);
    gpio_set_dir(digit_OE, GPIO_OUT);
    gpio_set_dir(digit_SRCLK, GPIO_OUT);
    gpio_set_dir(digit_SER, GPIO_OUT);

    // Disable output on both shift registers
    gpio_put(tpic_OE, 1);
    gpio_put(digit_OE, 1);

    // De-assert clear (active low) on both
    gpio_put(tpic_CLR, 1);
    gpio_put(digit_SRCLR, 1);
}

void write_to_display(uint8_t digitIndex, uint32_t segments)
{
    // Disable output on both shift registers
    gpio_put(tpic_OE, 1);
    gpio_put(digit_OE, 1);


    // Shift out the segments
    gpio_put(tpic_SRCK, 0);
    gpio_put(tpic_RCK, 0);
    for (uint8_t i = 0; i < 24; ++i)
    {
        gpio_put(tpic_SER_IN, (segments >> i) & 1);
        gpio_put(tpic_SRCK, 1);
        gpio_put(tpic_SRCK, 0);
    }
    // Transfer from shift register to output register
    gpio_put(tpic_RCK, 1);
    gpio_put(tpic_RCK, 0);


    // Only light one digit at a time.
    // This is inverted because we're using PNPs
    uint8_t digitWord = ~(1 << (7 - digitIndex));

    // Shift out the digit
    gpio_put(digit_SRCLK, 0);
    for (uint8_t i = 0; i < 8; ++i)
    {
        gpio_put(digit_SER, (digitWord >> i) & 1);
        gpio_put(digit_SRCLK, 1);
        gpio_put(digit_SRCLK, 0);
    }
    // Transfer from shift register to output register
    gpio_put(digit_RCLK, 1);
    gpio_put(digit_RCLK, 0);


    // Enable outputs
    gpio_put(tpic_OE, 0);
    gpio_put(digit_OE, 0);
}

// Data to display, and a mutex to make updates atomic
Display displayData;
mutex_t displayDataMutex;

void core1_display_loop()
{
    while (true)
    {
        mutex_enter_blocking(&displayDataMutex);
        Display localDisplayData = displayData;
        mutex_exit(&displayDataMutex);

        for (int i = 0; i < 7; ++i)
        {
            write_to_display(i, localDisplayData.digits[i]);
            sleep_ms(1);
        }
    }
}

void init_display()
{
    displayData = {};

    mutex_init(&displayDataMutex);

    setup_display_gpio();

    multicore_launch_core1(&core1_display_loop);
}

void update_display(Display display)
{
    mutex_enter_blocking(&displayDataMutex);
    displayData = display;
    mutex_exit(&displayDataMutex);
}

void update_display(const char16_t* str)
{
    update_display(string_to_display(str));
}

void update_display(const char* str)
{
    update_display(string_to_display(str));
}
