// @class: regalloc-order
// @stuck: none — MATCH (312/312, relocation-masked)

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef short          s16;
typedef int            s32;

typedef struct { u16 f0; s16 f2; } Prim4;
typedef struct { s16 x; s16 y; } Hw4;
typedef struct { s32 f0; u32 *f4; s32 f8; s32 fC; s32 f10; } Rec20;
typedef struct { u8 d[0x60]; } Blk60;
typedef struct { u8 d[0x20]; } Blk20;

extern void  func_80140E6C(void);
extern void  func_80140F00(void);
extern s32  *func_80140958(s32 *, s32, s32);
extern s32  *func_80141100(s32 *);
extern s16   func_8014168C(s16);
extern s32   func_8013FFD8(s32, s32, s32 *);
extern void  func_80024054(s32, void *);
extern s32  *func_800D2650(s32 *, void *, s32, s32, s32, s32);
extern void  func_8005A600(s32, s32, s32, s32, s32);
extern s32   func_800D27DC(s32, s32 *, void *, s32, s32);
extern s32  *func_800D29F8(s32, s32, void *, s32, s32);
extern s32  *func_80137D08(s32 *, void *, s32);
extern s32  *func_8013AB54(s32 *, u32 *, s32, s32);

extern s32    D_801151D0;
extern u16    D_8011511A;
extern s16    D_80115128;
extern Hw4    D_8011516A[];
extern u8     D_80078EC0;
extern u16    D_800B9A02;
extern Rec20  D_800AE7B8[];
extern Blk60  D_8018751C[];
extern Blk20  D_8018781C[];
extern Prim4  D_8018791C[];
extern Prim4  D_8018798C[];
extern Prim4 *D_80187A80[];
extern s32    D_80187AA0[];
extern s32    D_80187AC0[];
extern s16    D_80187E94;
extern s16    D_80187E96;

void func_8013FAF8(s16 arg0, s16 arg1) {
    u8 sp18[72];
    s32 sp60[2];
    s32 *ot;
    s16 i;
    s16 j;
    s32 flag;
    s32 addr;
    Prim4 *p;
    s32 r;
    s32 t;
    s16 *pp;
    s32 flag2;
    register s32 flag3 __asm__("$18");

    func_80140E6C();
    func_80140F00();
    ot = func_80140958((s32 *)D_801151D0, arg0, arg1);
    if (D_8011511A < 6) {
        ot = func_80141100(ot);
    }
    for (i = arg0; i < arg1; i++) {
        if (i == D_8011511A || i == 2 || i == 4) {
            flag = 0;
        } else {
            flag = 0xFF;
        }
        p = &D_8018791C[i];
        if (i != 5) {
            if (i == 2) {
                addr = D_80187AC0[D_80115128];
            } else {
                addr = D_80187AA0[i];
            }
        } else {
            addr = func_8013FFD8(2, func_8014168C(2), sp60);
        }
        func_80024054(addr, sp18);
        ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, 1,
                           flag != 0 ? 0x585858 : 0x808080);
        p = D_80187A80[i];
        j = 0;
        if (p != 0) {
            if (i == 2 && D_80115128 != 0) {
                p = D_8018798C;
            }
            flag2 = flag;
            for (;;) {
                r = func_8013FFD8(i, j++, sp60);
                if (r == 0) {
                    break;
                }
                if (r < 0) {
                    func_80024054(r, sp18);
                    t = 1;
                    if (i == 0 && (D_80078EC0 & 0x7F) == j) {
                        t = 0xB6;
                    }
                    if (flag2 != 0) {
                        sp60[0] += -0x282828;
                    }
                    ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, t, sp60[0]);
                }
                p++;
            }
        }
        func_8005A600((s32)ot, 0, 0, 0x15, 0);
        flag3 = flag;
        *ot = 0x2000000;
        *ot = (D_800AE7B8[D_800B9A02].f4[2] & 0xFFFFFF) | 0x2000000;
        D_800AE7B8[D_800B9A02].f4[2] =
            (D_800AE7B8[D_800B9A02].f4[2] & 0xFF000000) | ((u32)ot & 0xFFFFFF);
        ot = func_800D29F8(flag3,
                           func_800D27DC(flag3 != 0, ot + 10, &D_8018751C[i], 8, D_8011516A[i].x),
                           &D_8018781C[i], 2, D_8011516A[i].x);
    }
    pp = &D_80187E94;
    if (*pp == 0xE) {
        ot = func_80137D08(ot, &D_800AE7B8[D_800B9A02], 2);
    }
    if (*pp != 0 && D_80187E96 != 0) {
        ot = func_8013AB54(ot, D_800AE7B8[D_800B9A02].f4 + 2, (s32)(pp - 2), 0x8000);
    }
    D_801151D0 = (s32)ot;
}
