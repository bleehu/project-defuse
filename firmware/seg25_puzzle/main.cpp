#include "pico/stdlib.h"

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

int main() 
{

    setup_display_gpio();

    write_to_display(0, 0b100000000000000000000000);

    while (true)
    {
        write_to_display(0, 0b00110011'00010001'00000000);
        sleep_ms(1);
        write_to_display(1, 0b11001111'00000001'00000000);
        sleep_ms(1);
        write_to_display(2, 0b00001111'00000000'00000000);
        sleep_ms(1);
        write_to_display(3, 0b00001111'00000000'00000000);
        sleep_ms(1);
        write_to_display(4, 0b11111111'00000000'00000000);
        sleep_ms(1);
        write_to_display(5, 0b00000000'01000100'00000100);
        sleep_ms(1);
        write_to_display(6, 0b00000000'00000000'00000000);
        sleep_ms(1);
    }
}
