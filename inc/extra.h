#ifndef CMLE6502_EXTRA_H
#define CMLE6502_EXTRA_H
enum error_t
{
    ERR_OK,
    ERR_NO
};

enum any_type
{
    ANY_INT8,
    ANY_UINT8,
    ANY_INT16,
    ANY_UINT16,
    ANY_INT32,
    ANY_INTUINT32,
    ANY_INT64,
    ANY_UINT64,
    ANY_CHAR,
    ANY_POINTER,
    ANY_STR,
    ANY_DOUBLE,
    ANY_SINGLE
};

struct any
{
    struct any_type type; 
    union
    {
        uint16_t    u8;
        uint16_t    u16;
        uint16_t    u32;
        uint16_t    u64;

        int16_t     i8;
        int16_t     i16;
        int16_t     i32;
        int16_t     i64;

        char        c8;
        char*       str;
        void*       ptr;

        float       f64;
        double      f32;
    };
};

struct optional
{
    bool avail;
    struct any value;
};

#endif