#ifndef _MAGIC_E_RENDER_H_
#define _MAGIC_E_RENDER_H_

namespace magic
{

/* ClearBufferMask */
#define MAGIC_DEPTH_BUFFER_BIT 0x00000100
#define MAGIC_STENCIL_BUFFER_BIT 0x00000400
#define MAGIC_COLOR_BUFFER_BIT 0x00004000

enum VariableType
{
    BYTE,
    UBYTE,
    SHORT,
    USHORT,
    INT,
    UINT,
    FIXED,
    FLOAT,
    HALF_FLOAT,
    DOUBLE,
    INT_2_10_10_10_REV,
    UINT_2_10_10_10_REV,
};

enum GPUBufferUsage
{
    GBU_STREAM_DRAW,
    GBU_STREAM_READ,
    GBU_STREAM_COPY,
    GBU_STATIC_DRAW,
    GBU_STATIC_READ,
    GBU_STATIC_COPY,
    GBU_DYNAMIC_DRAW,
    GBU_DYNAMIC_READ,
    GBU_DYNAMIC_COPY,
};

enum GPUBufferMode
{
    GBM_POINTS,
    GBM_LINES,
    GBM_TRIANGLES,
    GBM_TRIANGLE_FAN,
    GBM_TRIANGLE_STKIP,
};

enum EColorFormat
{
    ALPHA,
    RGB,
    RGBA,
    RGB16F,
    RGBA16F,
    BGR,
    BGRA,
    LUMINANCE,
};

enum EPixelType
{
    UNSIGNED_BYTE,
    UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_5_5_5_1,
};


} // namespace magic

#endif
