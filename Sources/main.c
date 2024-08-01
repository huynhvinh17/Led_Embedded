#define uint32 unsigned int

void delay(volatile uint32 count)
{
    while (count--)
    {
    }
}

void portC_init()
{
    /** Supply clock for port C*/
    *(uint32 *)0x40048038 |= 1 << 11;
}

void portD_init()
{
    /** supply clock for port E */
    *(uint32 *)0x40048038 |= 1 << 12;
}

void portE_init()
{
    /** supply clock for port E */
    *(uint32 *)0x40048038 |= 1 << 13;
}

void config_PTC3()
{
    volatile uint32 *ptr = (uint32 *)0x4004B00C;
    /** clear muxing */
    *ptr &= ~(7 << 8);

    /** Set muxing is GPIO mode */
    *ptr |= (1 << 8);

    /** Enable internal pull up resistor */
    *ptr |= (1 << 1);

    /** Select pull up resistor */
    *ptr |= (1 << 0);

    /** config PTC3 is input */
    *(uint32 *)0x400FF094 &= ~(1 << 3);
}

void config_PTC12()
{
    volatile uint32 *ptr = (uint32 *)0x4004B030;
    /** clear muxing */
    *ptr &= ~(7 << 8);

    /** Set muxing is GPIO mode */
    *ptr |= (1 << 8);

    /** Enable internal pull up resistor */
    *ptr |= (1 << 1);

    /** Select pull up resistor */
    *ptr |= (1 << 0);

    /** config PTC12 is input */
    *(uint32 *)0x400FF094 &= ~(1 << 12);
}

void config_PTD5()
{
    /** Clear muxing */
    *(uint32 *)0x4004C014 &= ~(7 << 8);

    /** Set muxing is GPIO mode */
    *(uint32 *)0x4004C014 |= 1 << 8;

    /** config PTD5 is output */
    *(uint32 *)0x400FF0D4 = (1 << 5);
}

void config_PTE29()
{
    /** clear muxing */
    *(uint32 *)0x4004D074 &= ~(7 << 8);

    /** Set muxing is GPIO mode */
    *(uint32 *)0x4004D074 |= (1 << 8);

    /** Config PTE29 is output */
    *(uint32 *)0x400FF114 |= (1 << 29);
}

void is_buttonPress()
{
    volatile uint32 *ptrLedRed = (uint32 *)0x400FF100;
    volatile uint32 *ptrLedGreen = (uint32 *)0x400FF0C0;

    if ((((*(uint32 *)0x400FF090) & (1 << 3))) == 0)
    {
        *ptrLedRed &= ~(1 << 29);
        delay(10000000 / 2);
    }
    else
    {
        *ptrLedRed |= (1 << 29);
    }

    if ((((*(uint32 *)0x400FF090) & (1 << 12))) == 0)
    {
        *ptrLedGreen &= ~(1 << 5);
        delay(10000000 / 2);
    }
    else
    {
        *ptrLedGreen |= (1 << 5);
    }
}

int main(void)
{
    portC_init();
    portD_init();
    portE_init();
    config_PTC3();
    config_PTC12();
    config_PTD5();
    config_PTE29();

    while (1)
    {
        is_buttonPress();
    }

    return 0;
}
