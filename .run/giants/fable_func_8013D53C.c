#include "common.h"

typedef struct { u8 b[9]; } S9;   /* 9-byte, align-1 -> unaligned block copy */

typedef struct {
    u16 cmd;        /* 0x0 */
    u16 pad2;       /* 0x2 */
    u16 pad4;       /* 0x4 */
    u16 pad6;       /* 0x6 */
    s16 w;          /* 0x8 */
    s16 h;          /* 0xA */
    u16 *data;      /* 0xC */
} Cmd;              /* 0x10 */

extern s32 D_801D95A0;
extern u8 D_80078EAF;
extern s32 D_801D9588;

extern u8 D_80187484[];   /* stride 12 */
extern u8 D_80187488[];
extern u8 D_8018748C[];
extern S9 D_8018744C[];    /* stride 9 */

extern u8 D_801DAABA;
extern u8 D_801DAB2E;
extern u8 D_801DA9C2;
extern u8 D_801DAA9C;
extern u8 D_801DA998;
extern u8 D_801DA9C1;

extern S9 D_801DA9B8;
extern S9 D_801DAA78;

extern s32 D_801DAAA0;
extern s32 D_801D959C;
extern s32 D_801D9598;
extern s32 D_801D9594;
extern s32 D_801D9580;
extern s32 D_801D958C;
extern s32 D_801D9590;

extern s32 *D_801D9570;
extern Cmd *D_801D957C;
extern s32 D_801D95A8;
extern s32 *D_801D9578;
extern s32 D_801D95AC;
extern s32 D_801D95B0;
extern s32 D_801D95B4;

void func_8013D53C(Cmd *arg0) {
    s32 s0v;
    s32 t9v;
    s32 t8v;
    u8 b0, b1, b2;
    u8 pad[8];   /* dead BLKmode local: frame 0x10 -> 0x18, zero code */

    if (!(D_801D95A0 & 1)) {
        D_801D9588 = 1;
    } else {
        D_801D9588 = D_80078EAF;
    }

    b0 = D_80187484[D_801D9588 * 12];
    D_801DAABA = b0;
    D_801DAB2E = b0;
    b1 = D_80187488[D_801D9588 * 12];
    D_801DA9C2 = b1;
    D_801DAA9C = b1;
    b2 = D_8018748C[D_801D9588 * 12];
    D_801DA998 = b2;
    D_801DA9C1 = b2;

    D_801DA9B8 = D_8018744C[D_801D9588];
    D_801DAA78 = *(S9 *)(&D_801DA998 + 0x20);  /* same addr as D_801DA9B8; distinct sym defeats cse, keeps %hi/%lo */

    D_801DAAA0 = 1;
    D_801D959C = -1;
    D_801D9598 = 0;
    D_801D9594 = -1;
    D_801D9580 = 0;
    D_801D958C = 0;
    D_801D9590 = 0;

    if ((D_801D95A0 & 2) && (D_801D9588 == 4)) {
        s0v = D_801D9570[18];
        t9v = D_801D9570[19];
        t8v = D_801D9570[20];
    } else {
        s32 *p = (s32 *)(D_801D9588 * 12 + (s32) D_801D9570);  /* block-local: local-alloc ties sum into mul chain */
        s0v = p[0];
        t9v = p[1];
        t8v = p[2];
    }

    D_801D957C = arg0;
    if (arg0 != 0) {
        if (D_801D95A8 != 0) {
            s32 *p = (s32 *)(D_801D9588 * 12 + (s32) D_801D9578);
            D_801D95AC = p[0];
            D_801D95B0 = p[1];
            D_801D95B4 = p[2];
        } else {
            while ((arg0->cmd & 0xFFFF) != 0xFF) {
                if ((arg0->cmd & 0xFFFF) == 9) {
                    s32 n;
                    s32 i;
                    u16 *src;
                    u16 *dst;
                    n = arg0->w * arg0->h;
                    i = 0;
                    src = arg0->data;
                    __asm__("" :: "r"(src));  /* +2 refs on src (depth-2): keeps src above i, below the mfhi temp */
                    dst = src + n;
                    if (n > 0) {
                        do {
                            u16 px;
                            s32 r, g, b, out;
                            __asm__("" :: "r"(i));  /* +3 refs on i (depth-3): lifts i over dst in the $t2 race */
                            px = *src;
                            r = ((px & 0x1F) * s0v) / 2560;
                            g = (((px & 0x3E0) * t9v) / 2560) & 0x3E0;
                            b = (((px & 0x7C00) * t8v) / 2560) & 0x7C00;
                            out = r | g | b | (px & 0x8000);
                            if (out == 0 && px != 0) {
                                out = 0x8000;
                            }
                            *dst = out;
                            dst++;
                            i++;
                            src++;
                        } while (i < n);
                    }
                }
                arg0++;
            }
        }
    }
}
