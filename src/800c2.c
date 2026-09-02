#include "common.h"

#include "common.h"

struct Rec {
    char *name;         /* 0x00 */
    u8 pad04[0x30];     /* 0x04 */
    s32 (*callback)();  /* 0x34 */
    u8 pad38[0x18];     /* 0x38 */
};

extern u8 D_80078CE0[];
extern s32 D_80078CD8;
extern s32 func_8005C4DC();
extern s32 firstfile2();
extern void func_80062144();

s32 func_80061FA8(char *name, s32 mode)
{
    u8 *src;
    u8 *dst;
    struct Rec *base;
    struct Rec *rec;
    u32 n;
    s32 found;

    src = (u8 *)name;
    dst = D_80078CE0;
    while ((s8)*src > ':') {
        *dst++ = *src++;
    }
    *dst = 0;

    n = *(u32 *)0x154 / 80;
    base = *(struct Rec **)0x150;
    for (rec = base; rec < base + n; rec++) {
        if (rec->name != NULL && func_8005C4DC(rec->name, D_80078CE0) == 0) {
            D_80078CD8 = (s32)rec->callback;
            found = 1;
            goto done;
        }
    }
    found = 0;
done:
    if (found == 0) {
        return 0;
    }

    n = *(u32 *)0x154 / 80;
    base = *(struct Rec **)0x150;
    for (rec = base; rec < base + n; rec++) {
        if (rec->name != NULL && func_8005C4DC(rec->name, D_80078CE0) == 0) {
            rec->callback = (s32 (*)())func_80062144;
            break;
        }
    }
    return firstfile2(name, mode);
}


INCLUDE_ASM("asm/nonmatchings/800c2", func_80062144);
