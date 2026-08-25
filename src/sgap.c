#include "common.h"

/* libspu SpuWrite: clamp the transfer size to 0x7EFF0, hand off to the writer
 * func_8003AE14; if the transfer flag D_8006B584 is clear, clear the status
 * word D_8006B580. Returns the (possibly clamped) size. */
s32 SpuWrite(addr, size)
s32 addr;
s32 size;
{
    extern void func_8003AE14(s32 addr, s32 size);
    extern s32 D_8006B584;
    extern s32 D_8006B580;

    if ((u32)size > 0x7EFF0) {
        size = 0x7EFF0;
    }
    func_8003AE14(addr, size);
    if (D_8006B584 == 0) {
        D_8006B580 = 0;
    }
    return size;
}
