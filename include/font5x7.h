#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef font5X7_H
#define font5X7_H

#define font5X7_WIDTH 5
#define font5X7_HEIGHT 7

static uint8_t const font5x7[] PROGMEM = {
    0x00, 0x00, // size
    0x05, // width
    0x07, // height
    0x20, // first char
    0x60, // char count
    
    // font data
    0x00, 0x00, 0x00, 0x00, 0x00, // 32
    0x00, 0x00, 0x5F, 0x00, 0x00, // 33
    0x00, 0x07, 0x00, 0x07, 0x00, // 34
    0x14, 0x7F, 0x14, 0x7F, 0x14, // 35
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // 36
    0x23, 0x13, 0x08, 0x64, 0x62, // 37
    0x36, 0x49, 0x55, 0x22, 0x50, // 38
    0x00, 0x05, 0x03, 0x00, 0x00, // 39
    0x00, 0x1C, 0x22, 0x41, 0x00, // 40
    0x00, 0x41, 0x22, 0x1C, 0x00, // 41
    0x14, 0x08, 0x3E, 0x08, 0x14, // 42
    0x08, 0x08, 0x3E, 0x08, 0x08, // 43
    0x00, 0x50, 0x30, 0x00, 0x00, // 44
    0x08, 0x08, 0x08, 0x08, 0x08, // 45
    0x00, 0x60, 0x60, 0x00, 0x00, // 46
    0x20, 0x10, 0x08, 0x04, 0x02, // 47
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 48
    0x00, 0x42, 0x7F, 0x40, 0x00, // 49
    0x42, 0x61, 0x51, 0x49, 0x46, // 50
    0x21, 0x41, 0x45, 0x4B, 0x31, // 51
    0x18, 0x14, 0x12, 0x7F, 0x10, // 52
    0x27, 0x45, 0x45, 0x45, 0x39, // 53
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 54
    0x01, 0x71, 0x09, 0x05, 0x03, // 55
    0x36, 0x49, 0x49, 0x49, 0x36, // 56
    0x06, 0x49, 0x49, 0x29, 0x1E, // 57
    0x00, 0x36, 0x36, 0x00, 0x00, // 58
    0x00, 0x56, 0x36, 0x00, 0x00, // 59
    0x08, 0x14, 0x22, 0x41, 0x00, // 60
    0x14, 0x14, 0x14, 0x14, 0x14, // 61
    0x00, 0x41, 0x22, 0x14, 0x08, // 62
    0x02, 0x01, 0x51, 0x09, 0x06, // 63
    0x32, 0x49, 0x79, 0x41, 0x3E, // 64
    0x7E, 0x11, 0x11, 0x11, 0x7E, // 65
    0x7F, 0x49, 0x49, 0x49, 0x36, // 66
    0x3E, 0x41, 0x41, 0x41, 0x22, // 67
    0x7F, 0x41, 0x41, 0x22, 0x1C, // 68
    0x7F, 0x49, 0x49, 0x49, 0x41, // 69
    0x7F, 0x09, 0x09, 0x09, 0x01, // 70
    0x3E, 0x41, 0x49, 0x49, 0x78, // 71
    0x7F, 0x08, 0x08, 0x08, 0x7F, // 72
    0x00, 0x41, 0x7F, 0x41, 0x00, // 73
    0x20, 0x40, 0x41, 0x3F, 0x01, // 74
    0x7F, 0x08, 0x14, 0x22, 0x41, // 75
    0x7F, 0x40, 0x40, 0x40, 0x40, // 76
    0x7F, 0x02, 0x0C, 0x02, 0x7F, // 77
    0x7F, 0x04, 0x08, 0x10, 0x7F, // 78
    0x3E, 0x41, 0x41, 0x41, 0x3E, // 79
    0x7F, 0x09, 0x09, 0x09, 0x06, // 80
    0x3E, 0x41, 0x51, 0x21, 0x5E, // 81
    0x7F, 0x09, 0x19, 0x29, 0x46, // 82
    0x46, 0x49, 0x49, 0x49, 0x31, // 83
    0x01, 0x01, 0x7F, 0x01, 0x01, // 84
    0x3F, 0x40, 0x40, 0x40, 0x3F, // 85
    0x1F, 0x20, 0x40, 0x20, 0x1F, // 86
    0x3F, 0x40, 0x38, 0x40, 0x3F, // 87
    0x63, 0x14, 0x08, 0x14, 0x63, // 88
    0x07, 0x08, 0x70, 0x08, 0x07, // 89
    0x61, 0x51, 0x49, 0x45, 0x43, // 90
    0x00, 0x7F, 0x41, 0x41, 0x00, // 91
    0x02, 0x04, 0x08, 0x10, 0x20, // 92
    0x00, 0x41, 0x41, 0x7F, 0x00, // 93
    0x04, 0x02, 0x01, 0x02, 0x04, // 94
    0x40, 0x40, 0x40, 0x40, 0x40, // 95
    0x00, 0x02, 0x04, 0x08, 0x00, // 96
    0x20, 0x54, 0x54, 0x54, 0x78, // 97
    0x7F, 0x48, 0x44, 0x44, 0x38, // 98
    0x38, 0x44, 0x44, 0x44, 0x20, // 99
    0x38, 0x44, 0x44, 0x48, 0x7F, // 100
    0x38, 0x54, 0x54, 0x54, 0x18, // 101
    0x08, 0x7E, 0x09, 0x01, 0x02, // 102
    0x0C, 0x52, 0x52, 0x52, 0x3E, // 103
    0x7F, 0x08, 0x04, 0x04, 0x78, // 104
    0x00, 0x44, 0x7D, 0x40, 0x00, // 105
    0x20, 0x40, 0x44, 0x3D, 0x00, // 106
    0x7F, 0x10, 0x28, 0x44, 0x00, // 107
    0x00, 0x41, 0x7F, 0x40, 0x00, // 108
    0x7C, 0x04, 0x18, 0x04, 0x78, // 109
    0x7C, 0x08, 0x04, 0x04, 0x78, // 110
    0x38, 0x44, 0x44, 0x44, 0x38, // 111
    0x7C, 0x14, 0x14, 0x14, 0x08, // 112
    0x08, 0x14, 0x14, 0x18, 0x7C, // 113
    0x7C, 0x08, 0x04, 0x04, 0x08, // 114
    0x48, 0x54, 0x54, 0x54, 0x20, // 115
    0x04, 0x3F, 0x44, 0x40, 0x00, // 116
    0x3C, 0x40, 0x40, 0x20, 0x7C, // 117
    0x1C, 0x20, 0x40, 0x20, 0x1C, // 118
    0x3C, 0x40, 0x30, 0x40, 0x3C, // 119
    0x44, 0x28, 0x10, 0x28, 0x44, // 120
    0x0C, 0x50, 0x50, 0x50, 0x3C, // 121
    0x44, 0x64, 0x54, 0x4C, 0x44, // 122
    0x00, 0x08, 0x36, 0x41, 0x00, // 123
    0x00, 0x00, 0x7F, 0x00, 0x00, // 124
    0x00, 0x41, 0x36, 0x08, 0x00, // 125
    0x08, 0x04, 0x08, 0x10, 0x08, // 126
    0x00, 0x00, 0x00, 0x00, 0x00 // 127
    
};

#endif