#include <stdio.h>
#include <stdint.h>

#define SIZE 8

uint8_t buf[SIZE];
uint8_t head = 0;
uint8_t tail = 0;
uint8_t count = 0;

void init()
{
    head = 0;
    tail = 0;
    count = 0;
}

// check buffer is full or not
int isFull()
{
    if (count == SIZE)
        return 1;
    else
        return 0;
}

// check buffer is empty or not
int isEmpty()
{
    if (count == 0)
        return 1;
    else
        return 0;
}

// write one byte in buffer
int write_data(uint8_t data)
{
    if (isFull())
        return 0;

    buf[head] = data;
    // using & instead of % because % is slow in MCU, and SIZE is 8 so it will work
    head = (head + 1) & (SIZE - 1);
    count++;
    return 1;
}

// read one byte from buffer
int read_data(uint8_t *data)
{
    if (isEmpty())
        return 0;

    *data = buf[tail];
    tail = (tail + 1) & (SIZE - 1);
    count--;
    return 1;
}

int main()
{
    uint8_t d;
    int i;

    init();

    // first writing 8 bytes from A to H
    for (i = 0x41; i <= 0x48; i++)
    {
        write_data(i);
        printf("[WRITE] 0x%02X -> OK (count=%d)", i, count);
        if (isFull())
            printf(" FULL");
        printf("\n");
    }

    // trying 9th byte, it will fail because buffer is full
    if (write_data(0x99) == 0)
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");

    // reading 3 bytes
    for (i = 0; i < 3; i++)
    {
        read_data(&d);
        printf("[READ] -> 0x%02X (count=%d)\n", d, count);
    }

    // now writing 3 new bytes I J K
    for (i = 0x49; i <= 0x4B; i++)
    {
        write_data(i);
        printf("[WRITE] 0x%02X -> OK (count=%d)\n", i, count);
    }

    // reading all remaining bytes
    while (isEmpty() == 0)
    {
        read_data(&d);
        printf("[READ] -> 0x%02X (count=%d)\n", d, count);
    }

    // now buffer is empty, reading will fail
    if (read_data(&d) == 0)
        printf("[READ] (empty) -> FAIL (buffer empty)\n");

    return 0;
}
