// @class: struct
// @stuck: none — MATCH
#include "common.h"

typedef struct {
    u8  b0;
    u8  b1;
    u8  b2;
    u8  type;
    u32 w1;
    u32 w2;
} T3Reloc; /* 0xC */

void func_8013C414(s32 param_1, s32 param_2)
{
    s32 base10;      /* 0x00 */
    s32 p;           /* 0x04 */
    s32 q;           /* 0x08 */
    s32 base4008;    /* 0x0C */
    s32 lo;          /* 0x10 */
    u32 i;           /* 0x14 */
    s32 unused;      /* 0x18 */
    s32 base8;       /* 0x1C */
    T3Reloc *r;      /* 0x20 */
    T3Reloc *s;      /* 0x24 */

    if (*(s32 *)(param_2 + 4) == 0) {
        base10 = param_2 + 0x10;
        base4008 = param_1 + 0x4008;
        lo = *(s32 *)(param_2 + 0xC) + base10;
        base8 = param_1 + 8;
        p = base10;
        for (i = 0; i < *(u32 *)(param_2 + 8); i++) {
            *(s32 *)p = *(s32 *)p + base8;
            if (*(s32 *)(p + 4) != 0) {
                *(s32 *)(p + 4) = *(s32 *)(p + 4) + base10;
                q = *(s32 *)(p + 4);
                *(s32 *)q = *(s32 *)q + q;
                *(s32 *)(q + 0x14) = *(s32 *)(q + 0x14) + q;
                r = (T3Reloc *)*(s32 *)(q + 0x14);
                *(s32 *)(q + 0x18) = *(s32 *)(q + 0x18) * 0xC + *(s32 *)(q + 0x14);
                s = (T3Reloc *)*(s32 *)(q + 0x18);
                while (r < s) {
                    switch (r->type) {
                    case 0x24:
                    case 0x2C:
                    case 0x34:
                    case 0x3C:
                        if ((*(u32 *)r) & 0x800000) {
                            (*(u32 *)r) = ((*(u32 *)r) & 0x7FFFFF) + lo;
                        } else {
                            (*(u32 *)r) = ((*(u32 *)r) & 0xFFFFFF) + base4008;
                        }
                        break;
                    case 0x26:
                    case 0x2E:
                    case 0x36:
                    case 0x3E:
                        if ((*(u32 *)r) & 0x800000) {
                            (*(u32 *)r) = ((*(u32 *)r) & 0x7FFFFF) + lo;
                        } else {
                            (*(u32 *)r) = ((*(u32 *)r) & 0xFFFFFF) + base4008;
                        }
                        break;
                    }
                    r++;
                }
            }
            p = p + 0xC;
        }
        *(s32 *)(param_2 + 4) = 1;
        p = param_2 + 0x10;
        for (i = 0; i < *(u32 *)(param_2 + 8); i++) {
            if (*(s32 *)(p + 8) == 0) {
                *(s32 *)(p + 8) = *(s32 *)(*(s32 *)p);
            }
            p = p + 0xC;
        }
    } else {
        p = param_2 + 0x10;
        for (i = 0; i < *(u32 *)(param_2 + 8); i++) {
            *(s32 *)(*(s32 *)p) = *(s32 *)(p + 8);
            p = p + 0xC;
        }
    }
}
