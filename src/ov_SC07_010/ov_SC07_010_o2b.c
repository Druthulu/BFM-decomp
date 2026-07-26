#include "common.h"
#include "../shared/engine_core.h"

extern void func_80016714(void *a0, s32 a1);

void func_8013C98C(void) {

    extern s32 D_801A6AA0;
    extern s32 D_801269D4;
    extern s32 D_801269C8;
    func_80016714(&D_801A6AA0, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


extern void func_80019064(void *a0);

void func_8013C9C4(void * arg0)
{

    extern M2C_UNK D_80062BC0;
    extern s32 D_801A6AA0;
    extern s8 D_801A6AA4;
    extern s8 D_801A6AA5;
    D_801A6AA0 = arg0;
    D_801A6AA4 = 0;
    D_801A6AA5 = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}



void func_8013CA14(void)
{

    extern s32 D_801A6AA0;
    extern s8 D_801A6AA4;
    extern s8 D_801A6AA5;
    extern s32 D_801269C8;
    extern s32 D_801269D4;
  int *base = &D_801A6AA0;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801A6AA5;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801A6AA4)) * 2) + D_801A6AA0);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801A6AA5 = (unsigned char) p[1];
      D_801A6AA4 = D_801A6AA4 + 1;
      if (D_801A6AA5 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801A6AA4 = 0;
        *base = 0;
      }
    }
    else
    {
      D_801A6AA5 = c - 1;
    }
  }
  return;
}




void func_8013CABC(void) {

    extern s32 D_801A6AC4;
    extern s32 D_801A6AB8;
    extern s32 D_801A6ABC;
    extern s32 D_801A6AC8;
    D_801A6AC4 = 1;
    D_801A6AB8 = 1;
    D_801A6ABC = 0;
    D_801A6AC8 = 1;
}




void func_8013CAE8(void) {

    extern s32 D_801A6AB8;
    extern s32 D_801A6ABC;
    extern s32 D_801A6AC0;
    extern s32 D_801A6AC4;
    extern s32 D_801A6AC8;
    D_801A6AB8 = 1;
    D_801A6AC4 = 0;
    D_801A6ABC = 0;
    D_801A6AC0 = -1;
    D_801A6AC8 = 0;
}




void func_8013CB20(void)
{

    extern s32 D_801A6AC4;
    extern s32 D_801A6AC8;
    extern s32 D_801A6AF0;
    extern s32 D_801A6AF4;
    D_801A6AF0 = D_801A6AC8;
    D_801A6AF4 = D_801A6AC4;
    D_801A6AC8 = 1;
    D_801A6AC4 = 0;
}




void func_8013CB5C(void) {

    extern s32 D_801A6AF0;
    extern s32 D_801A6AF4;
    extern s32 D_801A6AC8;
    extern s32 D_801A6AC4;
    D_801A6AC8 = D_801A6AF0;
    D_801A6AC4 = D_801A6AF4;
}




extern s16 currentLocationId;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

void func_8013CB84(void) {

    extern u8 D_80078EAF;
    extern s32 D_801A6AC8;
    extern s32 D_801A6AC0;
    extern s32 D_801A6AC4;
    extern s32 D_801A6AB8;
    extern s32 D_801A6ABC;
    extern s32 D_801A6ACC;
    extern s32 D_801A6AD8;
    extern s32 D_801A6AE0;
    extern s32 D_801A94B8;
    extern s32 D_801A9438;
    extern s32 D_801A942C[];
    extern u8 D_801A93F9;
    extern u8 D_801A9546;
    extern u8 D_801A94B4;
    extern Rec12 D_80182928[];
    extern Rec9 D_801828F0[];
    extern u8 D_801A9490;  /* canonical (§8d); Rec9 block-move via cast-at-use */
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_801A94B8 = 0;
    if (D_801A6AC8 == 0 && s0 != D_801A6AC0) {
        ta = D_80182928[s0].a;
        tb = D_80182928[s0].b;
        tc = D_80182928[s0].c;
        D_801A6AC0 = s0;
        D_801A93F9 = tc;
        D_801A9546 = ta;
        D_801A94B4 = tb;
        *(Rec9 *)&D_801A9490 = D_801828F0[s0];
        D_801A6AC4 = 1;
        D_801A6AB8 = 1;
        if (D_801A6AD8 & 2) {
            if (s0 == 4) { D_801A942C[0] = 0x100; D_801A9438 = 0x80; }
            if (s0 == 0) { D_801A942C[0] = 0x100; D_801A9438 = 0; }
        }
    }
    if (D_801A6AC4 != 0) {
        t = D_801A6AB8 - 1;
        D_801A6AB8 = t;
        if (t == 0) {
            if (D_801A6AC8 == 0) {
                if ((D_801A6AD8 & 2) && s0 == 4) {
                    if (D_801A6AE0 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_801A6AE0 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_801A6AB8 = 2;
                if (D_801A6AC4 != 0) {
                    if (D_801A6AD8 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_801A9438;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_801A9438;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_801A6AD8 & 2) {
                    if (s0 == 4) D_801A9438 = 0;
                    if (s0 == 0) D_801A9438 = 0x80;
                }
            } else {
                if (D_801A6AE0 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_801A6AB8 = 1;
            }
        }
    }
    D_801A6ACC = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_801A6AC4 != 0) D_801A6ACC = D_801A6ABC;
            else D_801A6ACC = 0x1F;
        } else if (s0 == 4) {
            if (D_801A6AC4 != 0) D_801A6ACC = 0x1F - D_801A6ABC;
            else D_801A6ACC = 0;
        }
    }
}




void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_801A93F0;
    extern u8 D_801A93F1;
    extern u8 D_801A93F2;
    extern u8 D_801A93F3;
    extern u8 D_801A93F4;
    extern u8 D_801A93F5;
    extern u8 D_801A93F6;
    extern u8 D_801A93F7;
    extern u8 D_801A93F8;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801A93F0; t1 = D_801A93F1; t2 = D_801A93F2;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801A93F3; t1 = D_801A93F4; t2 = D_801A93F5;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801A93F6; t1 = D_801A93F7; t2 = D_801A93F8;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern void func_8013D9B0();

void func_8013D064(void)
{

    extern s32 D_801A6AD0;
    extern s32 D_801A6AB8;
    extern s32 D_801A6AD4;
    extern s32 D_801A6AC4;
    if (D_801A6AD0 != 0) {
        if (D_801A6AD0 != 2) {
            if (((D_801A6AD0 < 3) && (D_801A6AD0 == 1)) &&
                (D_801A6AD4 = D_801A6AD4 + 1, 0x23a < D_801A6AD4)) {
                D_801A6AB8 = D_801A6AD0;
                D_801A6AD0 = 2;
            }
        } else {
            D_801A6AB8 = D_801A6AB8 + -1;
            if (D_801A6AB8 == 0) {
                D_801A6AB8 = D_801A6AD0;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801A6AC4 == 0) {
                    D_801A6AD0 = D_801A6AD0 + 1;
                }
            }
        }
    }
    return;
}



extern void func_8013D9B0();

s32 func_8013D13C(void) {

    extern s32 D_801A6AC4;
    func_8013D9B0();
    return D_801A6AC4;
}




void func_8013D164(void) {

    extern s32 D_801A6AD0;
    D_801A6AD0 = 1;
}



void func_8013D178(void) {

    extern u8 D_801A93F0;
    extern u8 D_801A93F1;
    extern u8 D_801A93F2;
    extern u8 D_801A93F3;
    extern u8 D_801A93F4;
    extern u8 D_801A93F5;
    extern u8 D_801A93F6;
    extern u8 D_801A93F7;
    extern u8 D_801A93F8;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_801A93F0; v = *p; t = D_801A9490;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F1; v = *p; t = D_801A9491;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F2; v = *p; t = D_801A9492;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F3; v = *p; t = D_801A9493;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F4; v = *p; t = D_801A9494;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F5; v = *p; t = D_801A9495;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F6; v = *p; t = D_801A9496;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F7; v = *p; t = D_801A9497;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F8; v = *p; t = D_801A9498;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}




// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)


void func_8013D330(void) {

    extern u8 D_801A94D2;
    extern u8 D_801A9546;
    extern u8 D_801A93FA;
    extern u8 D_801A94B4;
    extern u8 D_801A93D8;
    extern u8 D_801A93F9;
    extern s32 D_801A94B8;
    if ((D_801A94D2 & 0xff) != D_801A9546) {
        D_801A94D2 = ((D_801A94D2 & 0xff) < D_801A9546) ? (D_801A94D2 + 1) : (D_801A94D2 - 1);
    }
    if ((D_801A93FA & 0xff) != D_801A94B4) {
        D_801A93FA = ((D_801A93FA & 0xff) < D_801A94B4) ? (D_801A93FA + 1) : (D_801A93FA - 1);
    }
    if ((D_801A93D8 & 0xff) != D_801A93F9) {
        D_801A93D8 = ((D_801A93D8 & 0xff) < D_801A93F9) ? (D_801A93D8 + 1) : (D_801A93D8 - 1);
    }
    D_801A94B8 = 1;
}



// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)




extern void func_8013D53C();
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{

    extern u8 D_80078E78[];
    extern void *D_801A6AA8;
    extern void *D_801A6AAC;
    extern void *D_801A6AB0;
    extern s32 D_801A6AD8;
    extern s32 D_801A6ADC;
    extern s32 D_801A6AE0;
    extern s32 D_801A942C[];
    extern u8 D_80182800[];
    extern u8 D_801828A8[];
    extern u8 D_80182758[];
    extern u8 D_80182854[];
    extern u8 D_801828D4[];
    extern u8 D_801827AC[];
    u8 *p = D_80078E78;

    D_801A6AD8 = param_2;
    D_801A6ADC = (param_2 >> 2) & 3;
    D_801A6AE0 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801A6AA8 = D_80182800;
        D_801A6AAC = D_801828A8;
        D_801A6AB0 = D_80182758;
    } else {
        D_801A6AA8 = D_80182854;
        D_801A6AAC = D_801828D4;
        D_801A6AB0 = D_801827AC;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_801A6AE0 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801A6AD8 & 2) != 0) {
            D_801A942C[0] = 0x140;
            D_801A942C[3] = 0x80;
            if (p[0x37] == 4) {
                D_801A942C[0] = 0x140;
                D_801A942C[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801A942C[0] = 0x140;
                D_801A942C[3] = 0x80;
            }
        }
    }
}



   /* 9-byte, align-1 -> unaligned block copy */








void func_8013D53C(void *arg0v) {

    extern Rec9 D_801828F0[];
    extern Rec12 D_80182928[];
    extern s32 D_801A6AD8;
    extern u8 D_80078EAF;
    extern s32 D_801A6AC0;
    extern u8 D_801A94D2;
    extern u8 D_801A9546;
    extern u8 D_801A93FA;
    extern u8 D_801A94B4;
    extern u8 D_801A93D8;
    extern u8 D_801A93F9;
    extern u8 D_801A9490;
    extern s32 D_801A94B8;
    extern s32 D_801A6AD4;
    extern s32 D_801A6AD0;
    extern s32 D_801A6ACC;
    extern s32 D_801A6AB8;
    extern s32 D_801A6AC4;
    extern s32 D_801A6AC8;
    extern void *D_801A6AA8;
    extern s32 D_801A6AE0;
    extern void *D_801A6AB0;
    Cmd_8013D53C *arg0 = arg0v;

    extern u8 D_8018292C[];
    extern u8 D_80182930[];
    extern unsigned char D_801A93F0;
    extern s16 *D_801A6AB4;
    extern s32 D_801A6AE4;
    extern s32 D_801A6AE8;
    extern s32 D_801A6AEC;
    s32 s0v;
    s32 t9v;
    s32 t8v;
    u8 b0, b1, b2;
    u8 pad[8];   /* dead BLKmode local: frame 0x10 -> 0x18, zero code */

    if (!(D_801A6AD8 & 1)) {
        D_801A6AC0 = 1;
    } else {
        D_801A6AC0 = D_80078EAF;
    }

    b0 = ((u8 *)D_80182928)[D_801A6AC0 * 12];
    D_801A94D2 = b0;
    D_801A9546 = b0;
    b1 = D_8018292C[D_801A6AC0 * 12];
    D_801A93FA = b1;
    D_801A94B4 = b1;
    b2 = D_80182930[D_801A6AC0 * 12];
    D_801A93D8 = b2;
    D_801A93F9 = b2;

    (*(S9 *)&D_801A93F0) = ((S9 *)D_801828F0)[D_801A6AC0];
    (*(S9 *)&D_801A9490) = *(S9 *)(&D_801A93D8 + 0x18);  /* same addr as (*(S9 *)&D_801A93F0); distinct sym defeats cse, keeps %hi/%lo */

    D_801A94B8 = 1;
    D_801A6AD4 = -1;
    D_801A6AD0 = 0;
    D_801A6ACC = -1;
    D_801A6AB8 = 0;
    D_801A6AC4 = 0;
    D_801A6AC8 = 0;

    if ((D_801A6AD8 & 2) && (D_801A6AC0 == 4)) {
        s0v = (*(s32 * *)&D_801A6AA8)[18];
        t9v = (*(s32 * *)&D_801A6AA8)[19];
        t8v = (*(s32 * *)&D_801A6AA8)[20];
    } else {
        s32 *p = (s32 *)(D_801A6AC0 * 12 + (s32) (*(s32 * *)&D_801A6AA8));  /* block-local: local-alloc ties sum into mul chain */
        s0v = p[0];
        t9v = p[1];
        t8v = p[2];
    }

    (*(Cmd_8013D53C * *)&D_801A6AB4) = arg0;
    if (arg0 != 0) {
        if (D_801A6AE0 != 0) {
            s32 *p = (s32 *)(D_801A6AC0 * 12 + (s32) (*(s32 * *)&D_801A6AB0));
            D_801A6AE4 = p[0];
            D_801A6AE8 = p[1];
            D_801A6AEC = p[2];
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




// @class: schedule
// @stuck: none — MATCH (45 ins, match_one verified)

extern void func_800599B8(s32 a0, s32 a1);

void func_8013D8FC(void)
{

    extern s16 *D_801A6AB4;
    register s16 *psVar3 __asm__("$17");
    register s16 *psVar2 __asm__("$16");
    register s32 c9 __asm__("$19");
    register s32 cff __asm__("$18");
    u16 sVar1;
    s16 buf[4];

    psVar3 = D_801A6AB4;
    if (psVar3 != (s16 *)0x0 && (sVar1 = (u16)*psVar3, sVar1 != 0xff)) {
        c9 = 9;
        cff = 0xff;
        psVar2 = psVar3 + 5;
        do {
            if (sVar1 == c9) {
                s32 arg2 = *(s32 *)(psVar2 + 1) + psVar2[-1] * 2;
                buf[0] = psVar2[-3];
                buf[1] = psVar2[-2];
                buf[2] = psVar2[-1];
                buf[3] = *psVar2;
                func_800599B8((s32)buf, arg2);
            }
            psVar3 = psVar3 + 8;
            sVar1 = (u16)*psVar3;
            psVar2 = psVar2 + 8;
        } while (sVar1 != cff);
    }
}


extern void func_800599B8(s32 a0, s32 a1);
#define gte_ldIR0z()   __asm__ __volatile__("mtc2 $0, $8")
#define gte_ldrgb(p)   __asm__ __volatile__("lwc2 $6, 0(%0)"  :: "r"(p) : "memory")
#define gte_ldIRGB(p)  __asm__ __volatile__("lwc2 $28, 0(%0)" :: "r"(p) : "memory")
#define gte_dpcl()     __asm__ __volatile__("nop\n\tnop\n\tdpcl")
#define gte_stORGB(p)  __asm__ __volatile__("swc2 $29, 0(%0)" :: "r"(p) : "memory")

void func_8013D9B0(int param_1)
{

    extern void *D_801A6AAC;
    extern s16 *D_801A6AB4;
    extern s32 D_801A6AC4;
    extern s32 D_801A6ACC;

    u8 buf[0x20];
    register s32 uVar13 __asm__("$16");
    register u16 *psVar14 __asm__("$17");
    register u16 *psVar15 __asm__("$18");
    register s32 uVar16 __asm__("$19");
    register void *r0 __asm__("$20");
    register u16 *puVar10 __asm__("$11");
    register u16 *puVar9 __asm__("$10");
    register s32 iVar11 __asm__("$13");
    register s32 iVar12 __asm__("$14");
    u16 sVar4;
    register u32 uVar5 __asm__("$3");
    register u32 uVar7 __asm__("$6");
    register u32 uVar1 __asm__("$7");
    register u32 uVar6 __asm__("$4");
    register u32 uVar8 __asm__("$8");
    register u32 uVar3 __asm__("$9");

    psVar15 = (*(u16 * *)&D_801A6AB4);
    if (psVar15 != 0) {
        sVar4 = *psVar15;
        *(u32 *)(buf + 8) = (*(u32 * *)&D_801A6AAC)[param_1];
        D_801A6ACC = -1;
        uVar16 = 0;
        if (sVar4 != 0xff) {
            r0 = buf + 8;
            psVar14 = psVar15 + 6;
            do {
                iVar11 = 0;
                if (sVar4 == 9) {
                    *(s16 *)(buf + 0) = psVar14[-4];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 2) = psVar14[-3];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 4) = psVar14[-2];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 6) = psVar14[-1];
                    __asm__ __volatile__("" ::: "memory");
                    {
                        register s32 mw __asm__("$3") = (s32)((s16 *)psVar14)[-2];
                        register s32 mh __asm__("$2") = (s32)((s16 *)psVar14)[-1];
                        iVar12 = mw * mh;
                    }
                    uVar13 = 0;
                    puVar10 = *(u16 **)psVar14;
                    {
                        register s32 boff __asm__("$2") = iVar12 * 2;
                        register u16 *pi __asm__("$5");
                        pi = (u16 *)((s32)puVar10 + boff);
                        __asm__ __volatile__("" : "=r"(pi) : "0"(pi));
                        puVar9 = pi;
                    }
                    if (0 < iVar12) {
                        do {
                            register u32 pix __asm__("$2");
                            register u32 out __asm__("$2");
                            u32 result;
                            *(u32 *)(buf + 0xc) = (u32)*puVar10;
                            pix = (u32)*puVar9;
                            uVar5 = pix & 0x1f;
                            uVar7 = pix & 0x3e0;
                            uVar1 = pix & 0x7c00;
                            {
                                void *p1;
                                register void *pa __asm__("$2");
                                register void *pb __asm__("$12");
                                __asm__ __volatile__("");
                                p1 = buf + 0xc;
                                __asm__ __volatile__("" : "=r"(p1) : "0"(p1));
                                gte_ldIR0z();
                                gte_ldrgb(r0);
                                gte_ldIRGB(p1);
                                gte_dpcl();
                                pa = buf + 0x10;
                                __asm__ __volatile__("" : "=r"(pa) : "0"(pa));
                                pb = pa;
                                gte_stORGB(pb);
                            }
                            out = *(u32 *)(buf + 0x10);
                            uVar6 = out & 0x1f;
                            uVar8 = out & 0x3e0;
                            uVar3 = out & 0x7c00;
                            if (uVar5 != uVar6) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar5 < (s32)uVar6) uVar5 = uVar5 + 1;
                                c = (s32)uVar6 < (s32)uVar5;
                                if (c) uVar5 = uVar5 - 1;
                            }
                            if (uVar7 != uVar8) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar7 < (s32)uVar8) uVar7 = uVar7 + 0x20;
                                c = (s32)uVar8 < (s32)uVar7;
                                if (c) uVar7 = uVar7 - 0x20;
                            }
                            if (uVar1 != uVar3) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar1 < (s32)uVar3) uVar1 = uVar1 + 0x400;
                                c = (s32)uVar3 < (s32)uVar1;
                                if (c) uVar1 = uVar1 - 0x400;
                            }
                            result = uVar5 | uVar7 | uVar1 | (*(u32 *)(buf + 0xc) & 0x8000);
                            if (result == 0 && *(u32 *)(buf + 0xc) != 0) {
                                result = 0x8000;
                            }
                            *puVar9 = (u16)result;
                            puVar9 = puVar9 + 1;
                            iVar11 = iVar11 + 1;
                            puVar10 = puVar10 + 1;
                        } while (iVar11 < iVar12);
                    }
                    if (uVar13 != 0) {
                        ((void (*)(void *))func_800599B8)(buf);
                    }
                    uVar16 = uVar16 | uVar13;
                }
                psVar15 = psVar15 + 8;
                sVar4 = *psVar15;
                psVar14 = psVar14 + 8;
            } while (sVar4 != 0xff);
        }
        D_801A6AC4 = uVar16;
    }
    return;
}



// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801A6AB0)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.


extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{

    extern void *D_801A6AB0;
    extern s16 *D_801A6AB4;
    extern s32 D_801A6AC4;
    extern s32 D_801A6AE4;
    extern s32 D_801A6AE8;
    extern s32 D_801A6AEC;
    int *p;
    int x, y, z;
    int flag;

    if (D_801A6AB4 != 0) {
        D_801A6AC4 = 0;
        p = (int *)(param_1 * 12 + (int)D_801A6AB0);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801A6AE4 != x) {
            flag = 1;
            if (D_801A6AE4 < x) {
                if (x - D_801A6AE4 < 5) {
                    D_801A6AE4 = x;
                } else {
                    D_801A6AE4 = D_801A6AE4 + 4;
                }
            } else {
                if (D_801A6AE4 - x < 5) {
                    D_801A6AE4 = x;
                } else {
                    D_801A6AE4 = D_801A6AE4 - 4;
                }
            }
        }
        if (D_801A6AE8 != y) {
            flag = 1;
            if (D_801A6AE8 < y) {
                if (y - D_801A6AE8 < 5) {
                    D_801A6AE8 = y;
                } else {
                    D_801A6AE8 = D_801A6AE8 + 4;
                }
            } else {
                if (D_801A6AE8 - y < 5) {
                    D_801A6AE8 = y;
                } else {
                    D_801A6AE8 = D_801A6AE8 - 4;
                }
            }
        }
        if (D_801A6AEC != z) {
            flag = 1;
            if (D_801A6AEC < z) {
                if (z - D_801A6AEC < 5) {
                    D_801A6AEC = z;
                } else {
                    D_801A6AEC = D_801A6AEC + 4;
                }
            } else {
                if (D_801A6AEC - z < 5) {
                    D_801A6AEC = z;
                } else {
                    D_801A6AEC = D_801A6AEC - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801A6AC4 = flag;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013DD68);



s32 func_8013E054(void) {

    extern s32 D_801A6ACC;
    return D_801A6ACC;
}


DEFINE_func_8013E064()  /* dedup: shared engine-core @0x8013e064 (src/shared) */


DEFINE_func_8013E0FC()  /* dedup: shared engine-core @0x8013e0fc (src/shared) */


DEFINE_func_8013E194()  /* dedup: shared engine-core @0x8013e194 (src/shared) */


DEFINE_func_8013E22C()  /* dedup: shared engine-core @0x8013e22c (src/shared) */


DEFINE_func_8013E298()  /* dedup: shared engine-core @0x8013e298 (src/shared) */


DEFINE_func_8013E2C4()  /* dedup: shared engine-core @0x8013e2c4 (src/shared) */


DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013e370 (src/shared) */


DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013e410 (src/shared) */


DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013e448 (src/shared) */


DEFINE_func_8013E4B4()  /* dedup: shared engine-core @0x8013e4b4 (src/shared) */


DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013e558 (src/shared) */


DEFINE_func_8013E588()  /* dedup: shared engine-core @0x8013e588 (src/shared) */



extern void func_80029444(void);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);


void func_8013E5E8(void)
{

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_80183374[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_80183374[D_80115112];
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}


DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013e67c (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern s16 currentLocationId;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

void func_8013E6AC(void) {

    extern u8 D_80078EC0;
    extern u16 D_8011511A;
    extern u16 D_80115124;
    extern u8 D_80115148[];
    extern u8 D_80115140[];
    extern s32 D_80183360;
    extern u16 D_80115110;
    extern s32 D_80115188;
    extern s16 D_80183338;
    extern s16 D_8018333A;
    extern unsigned short D_80115112;
    short i;

    func_8013E83C();
    D_8011511A = 0;
    D_80115124 = D_80078EC0;
    for (i = 0; i < 8; i++) {
        *(s16 *)((char *)&D_80115148 + (i << 1)) = 0;
        D_80115140[i] = 0;
    }
    if (!((u32)func_80029504() < 5 || currentLocationId == 0x302A || currentLocationId == 0x3073)) {
        register s32 *ep __asm__("$8");
        register s32 *fp __asm__("$9");
        fp = (s32 *)&D_80115110;
        ep = (s32 *)&D_80183360;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_80183338 = 2;
        D_8018333A = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_8018333A = 0;
        D_80183338 = 0;
        D_80115112 = 6;
    }
}


DEFINE_func_8013E814()  /* dedup: shared engine-core @0x8013e814 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (direct u16 global reads fold to lui/lhu; scheduler hoists the D_8011511A read above the prologue, reproduced by -O2)

void func_8013E83C() {

    extern u16 D_80115110;
    extern u16 D_8011511A;
    extern int func_80029178(int);
    extern void func_8002D4C8(int, int);
    extern void func_80141C0C(int);
    extern unsigned short D_80115118;
    extern unsigned short D_80115128;
    extern unsigned short D_8011512E;
    extern unsigned int D_80115130;
    extern unsigned short D_80115158;
    extern unsigned short D_8011515A;
    extern unsigned short D_8011515C;
    extern unsigned short D_8011515E;
    extern unsigned short D_80115162;
    extern unsigned short D_80115166;
    extern void * D_801A6B00;
    extern void * D_801A6B04;
    extern unsigned char D_80182FD8;
    extern unsigned char D_80182FF0;
    extern unsigned char D_80183064;
    extern unsigned char D_8018306C;

    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((func_80029178(0x1c) & 0xFF) == 0) {
        D_801A6B00 = &D_80182FD8;
        D_801A6B04 = &D_80183064;
    } else {
        D_801A6B00 = &D_80182FF0;
        D_801A6B04 = &D_8018306C;
    }

    D_8011515A = 0x104;
    D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;

    if (D_80115110 == 3) {
        func_8002D4C8(0x46e, 0);
    } else {
        func_80141C0C(0);
    }
}



// @class: schedule
// @stuck: none — MATCH (63 ins). The idx-32+ residual was a THIRD held base pointer for the
// D_80115188 store: the draft's `((Cell*)&D_80115188)[i].v = v` allocates a pointer, so gcc kept
// three bases (D_80115110/D_80183360/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_80183360 -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{

    extern u8 D_80078EC0;
    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_80183360;
    extern void func_80139954(void);
    extern void func_8014AA28(void);
    extern s32 func_800D0488(s32);
    extern void func_80141C0C(s32);

    s16 *p = &(*(s16*)&D_80115124);
    s16 i;
    s32 v;
    s16 m;

    D_800B9A15 = 0;
    func_80139954();
    if (D_80078EC0 != *p) {
        func_8014AA28();
        if ((D_80078EC0 & 0x7F) != 0) {
            m = D_80078EC0 & 0x7F;
            *p = m;
            if (m == 0 || func_800D0488(m) == 0)
                goto loop;
        }
    }
    *p = 0;
loop:
    for (i = 0; i < 5; i++) {
        s32 *q = &((s32 *)&D_80115110)[i];
        v = ((s32 *)&D_80183360)[i] >> 6;
        q[0x16] = v;
        *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
    }
    func_80141C0C(7);
    (*(u16*)&D_80115112) = 4;
}


DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013ea54 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (sVar2 pinned to $v0 forces in-place sll/sra sign-ext scratch)


extern s32 func_80141C50(void);
extern s32 func_8013F350(void);   /* §30#2 widened: def returns live $v0; callers discard */
extern void func_8013FAF8(s16 a0, s16 a1);
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern unsigned char *func_80141CA4(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013E958(void);


void func_8013EB7C(void) {

    extern short D_800B9A02;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern u16 D_8011511A;
    extern u16 D_8011511E;
    extern short D_80115128;
    extern unsigned short D_80115112;
    extern s16 D_8011512A;
    extern s32 D_80115130;
    extern unsigned char D_8018333C;
    s32 sp10[2];
    short sVar1;
    register short sVar2 __asm__("$2");
    s32 a0v;
    s32 iVar4;

    if ((s16)func_80141C50() == 0) {
        D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
        sVar1 = ((short (*)(void))func_8013F350)();
        if (D_8011511A >= 4) {
            func_8013FAF8((s16)D_8011511A, (s16)(D_8011511A + 1));
        }
        func_8013FAF8(0, 5);
        if (D_8011511A == 5) {
            sVar2 = ((short (*)(s32))func_8014168C)(2);
            a0v = 2;
        } else {
            sVar2 = ((short (*)(s32))func_8014168C)((s16)D_8011511A);
            a0v = (s16)D_8011511A;
        }
        iVar4 = func_8014032C(a0v, sVar2);
        if (iVar4 != 0) {
            s32 *p130 = &D_80115130;
            if (iVar4 != *p130) {
                *p130 = iVar4;
                func_80139954();
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_8018333C));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_8018333C));
            }
            (*(unsigned short *)&D_80115112) -= 1;
        } else {
            if ((D_8011511E & 0x800) != 0 || D_8011512A != 0) {
                func_8013E958();
            }
        }
    }
    (void)sp10;
}


DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ed6c (src/shared) */


extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_8018333A` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_80183338` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.




s32 func_8013EE10() {

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern s16 D_80183338;
    extern s16 D_8018333A;
    extern unsigned char D_8018333C;
    extern E4 aD80115188[] __asm__("D_80115188");
    extern E4 D_80115168[];
    extern unsigned short D_80115118;

    short i;
    u16 *p;
    u16 old;
    s16 *r;
    u16 *c;
    s32 sp10[2];

    D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
    func_8013FAF8(0, 5);
    for (i = 0; i < 5; i++) {
        s32 t = D_80115168[i].f0 * 3 >> 2;
        aD80115188[i].f0 = t;
        D_80115168[i].f0 = D_80115168[i].f0 - t;
    }
    r = &D_8018333A;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_80183338 = (u16)D_80183338 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8018333C);
        for (i = 0; i < 5; i++) {
            s32 *q = (s32 *)((char *)p - 8);
            *(s32 *)((char *)&q[i] + 0x78) = 0;
            D_80115168[i].f0 = 0;
        }
        c = &D_80115112;
        *c += 1;
    }
    (void)sp10;
}












extern void func_8013FAF8(s16 a0, s16 a1);
extern s32  func_800D0488(s16 a0);
extern void func_800D2624(void);

void func_8013EF88(void)
{

    extern u16 D_80115118;
    extern s16 D_800B9A02;
    extern s32 D_801151D0;
    extern E4  aD80115188[] __asm__("D_80115188");
    extern E4  D_80115168[];
    extern u16 D_80115124;
    extern u16 D_80115114;
    extern u16 D_80115112;
    extern s16 D_8018333A;
    extern s16 D_80183338;
    u16 *p = &D_80115118;
    u16 old = *p;
    short i;

    if (old != 0) {
        u16 nw = old - 1;
        *p = nw;
        if (nw != 0) {
            D_801151D0 = *(s32 *)((char *)&D_80115118 + 0xB0 + (u16)D_800B9A02 * 4);
            func_8013FAF8(0, 5);
            for (i = 0; i < 5; i++) {
                s32 t = aD80115188[i].f0 * 3;
                aD80115188[i].f0 = t;
                D_80115168[i].f0 = D_80115168[i].f0 + t;
            }
            if (D_80115118 < 3) {
                u16 *s = &(*(u16 *)&D_8018333A);
                *s -= 1;
            }
            {
                u16 *w = &(*(u16 *)&D_80183338);
                *w -= 2;
                if ((s16)*w < 0) {
                    *w = 0;
                }
            }
        }
    }

    {
        s16 *pv = &(*(s16 *)&D_80115124);
        if (*pv != 0) {
            if (func_800D0488(*pv) == 0) return;
            *pv = 0;
        }
    }

    if (D_80115118 == 0) {
        if (D_80115114 == ((u16)D_800B9A02 ^ 1)) {
            func_800D2624();
        } else {
            D_80115112 += 1;
        }
    }
}




// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {

    extern unsigned short D_80115118;
    extern unsigned short D_80115112;
    extern u16 D_80115110;
    extern unsigned char D_8018333C;
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8018333C);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013f1bc (src/shared) */


DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013f244 (src/shared) */
