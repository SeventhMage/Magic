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

} // namespace magic

#endif
