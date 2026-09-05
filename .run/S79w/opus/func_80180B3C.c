#include "common.h"

/* Blk32_80180908 is already declared in this TU (ov_SC02_027_jr_8017D898.c:4623). */

typedef struct { u32 addr : 24; u32 len : 8; } PTag_80180B3C;
typedef struct {
    PTag_80180B3C tag;
    u8 r0, g0, b0, code;
    u16 x0, y0;
    u8 u0, v0;
    u16 clut;
    u16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    u16 x2, y2;
    u8 u2, v2;
    u16 pad2;
    u16 x3, y3;
    u8 u3, v3;
    u16 pad3;
} Ft4_80180B3C;
typedef struct { s16 vx, vy, vz, pad; } SV_80180B3C;
typedef struct { s16 vx, vy; } DV_80180B3C;

#define ADDPRIM_80180B3C(o, p)                                       \
    (((PTag_80180B3C *)(p))->addr = ((PTag_80180B3C *)(o))->addr,   \
     ((PTag_80180B3C *)(o))->addr = (u32)(p))

#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsxy0_80180B3C(r0) __asm__ volatile ( \
    "swc2 $12, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsxy1_80180B3C(r0) __asm__ volatile ( \
    "swc2 $13, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsz_80180B3C(r0) __asm__ volatile (  \
    "swc2 $19, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )
#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

void func_80180B3C(s32 a0)
{
    extern u8 D_800AF630[];
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern Blk32_80180908 D_801DA730;
    extern s16 D_801DA738;

    DV_80180B3C sxy0;
    DV_80180B3C sxy1;
    DV_80180B3C sxy2;
    SV_80180B3C sv;
    SV_80180B3C sv2;
    s32 sz;
    s32 flg;
    s32 otz;

    u8 *p;
    u8 *base;
    u8 *frame;
    register u8 *obj __asm__("$11");
    register u32 w __asm__("$10");
    u32 tp;
    Ft4_80180B3C *pkt;
    u32 *ot;
    register u32 x __asm__("$4");
    register u32 y __asm__("$7");
    u32 b;
    u32 u;
    u32 v;
    s32 shift;
    u32 tpg;
    u32 vv;
    register u32 c40 __asm__("$2");

    p = D_800AF630;
    base = *(u8 **)(a0 + 0x10);
    frame = base + *(s16 *)(a0 + 4) * 12;
    w = *(u32 *)a0;
    obj = *(u8 **)(a0 + 0x14);
    if (*frame == 0xFF) {
        frame = base;
        *(u16 *)(a0 + 4) = 0;
    }
    *(u16 *)(a0 + 4) += 1;

    gte_SetRotMatrix(p + 0x18);
    gte_SetTransMatrix(p + 0x18);

    sv.vx = *(u16 *)(obj + 6);
    sv.vy = *(u16 *)(obj + 0xA);
    sv.vz = *(u16 *)(obj + 0xE);
    sv.vy += 0x20;
    gte_ldv0(&sv);
    gte_rtps();
    gte_stsxy(&sxy0);
    gte_stsz_80180B3C(&sz);

    *(u16 *)&D_801DA730 = *(u16 *)(a0 + 8);
    D_801DA738 = *(u16 *)(a0 + 0xA);
    gte_SetRotMatrix(&D_801DA730);
    gte_SetTransMatrix(&D_801DA730);

    sv.vx = *(u16 *)(frame + 8);
    sv.vy = *(u16 *)(frame + 0xA);
    sv.vz = sz;
    sv2.vx = frame[2];
    sv2.vy = frame[3];
    sv2.vz = sz;
    gte_ldv3(&sv, &sv2, &sv2);
    gte_rtpt();
    gte_stsxy0_80180B3C(&sxy1);
    gte_stsxy1_80180B3C(&sxy2);
    gte_stflg(&flg);
    gte_stszotz(&otz);

    if (flg & 0xFFFFEFFF) {
        return;
    }

    tp = (w >> 24) & 3;
    shift = 2 - tp;
    pkt = (Ft4_80180B3C *)D_800A5E60;
    D_800A5E60 += 0x28;
    pkt->tag.len = 9;
    pkt->code = 0x2C;
    ot = (u32 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    x = *(u16 *)(frame + 4);
    y = *(u16 *)(frame + 6);
    pkt->code |= 2;
    tpg = (tp << 7) | (((w >> 28) & 3) << 5) | ((y & 0x100) >> 4) | ((x & 0x3C0) >> 6);
    tpg |= (y & 0x200) << 2;
    pkt->tpage = tpg;
    c40 = (w & 0x40) >> 6;
    pkt->code |= c40;
    v = y & 0xFFFF;
    u = (x - ((pkt->tpage & 0xF) << 6)) << shift;
    pkt->u0 = u;
    if (!(pkt->tpage & 0x10)) {
        vv = v;
    } else {
        vv = v - 0x100;
    }
    pkt->v0 = vv;
    pkt->u1 = pkt->u0 + frame[2] - 1;
    pkt->v1 = pkt->v0;
    pkt->u2 = pkt->u0;
    pkt->v2 = pkt->v0 + frame[3] - 1;
    pkt->u3 = pkt->u1;
    pkt->v3 = pkt->v2;
    b = frame[1];
    pkt->clut = ((b + 0x100) << 6) | (b < 0xE0 ? 0x16 : 0x10);
    pkt->r0 = pkt->g0 = pkt->b0 = 0x80;

    switch (*(s32 *)(obj + 0x34)) {
    case 0:
        pkt->x0 = sxy0.vx + sxy1.vx * 4;
        pkt->x1 = sxy0.vx;
        pkt->x2 = sxy0.vx;
        pkt->x3 = sxy0.vx + sxy2.vx * 2;
        break;
    case 1:
        pkt->x0 = sxy0.vx;
        pkt->x1 = sxy0.vx + sxy2.vx * 2;
        pkt->x2 = sxy0.vx + sxy1.vx * 4;
        pkt->x3 = sxy0.vx;
        break;
    case 2:
        pkt->x0 = sxy0.vx + sxy1.vx;
        pkt->x1 = pkt->x0 + sxy2.vx;
        pkt->x2 = pkt->x0;
        pkt->x3 = pkt->x1;
        break;
    }
    pkt->y0 = sxy0.vy + sxy1.vy;
    pkt->y2 = pkt->y0 + sxy2.vy;
    pkt->y1 = pkt->y0;
    pkt->y3 = pkt->y2;
    ADDPRIM_80180B3C(&ot[otz + 1], pkt);
}
