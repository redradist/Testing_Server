#ifndef CRC16_H
#define CRC16_H

#include <stdint.h>

typedef union
{
    int16_t word;
    uint8_t byte[2];
} DowbleByteType;

namespace SenseSystem
{
    void CRC16(uint8_t temp);
    unsigned short CalcCRC16(uint8_t *str, uint16_t size);
}

#endif // CRC16_H
