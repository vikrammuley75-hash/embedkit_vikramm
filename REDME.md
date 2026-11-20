# EmbedKit_Vikram_Muley

## Ring Buffer (Circular Buffer) – Embedded C

This project implements a fixed-size ring buffer for `uint8_t` data,
commonly used in embedded systems (e.g., UART RX buffering).

### Features
- Buffer size: 8 bytes
- No data overwrite when full
- Safe read/write with error handling
- Optimized wrap-around using bitwise AND

### Build
```bash
gcc -Wall -std=c99 ringbuf.c -o ringbuf
