#include "common.h"

/* GTE macro bodies — verbatim PsyQ inline_c.h spellings, identical to the ones this TU
 * already defines above func_8017C8D0 (guarded so the in-TU copies win). */
#ifndef gte_ldv0
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
#endif

#ifndef gte_ldv3
#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#endif

#ifndef gte_rtps
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#endif
#ifndef gte_rtpt
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#endif

#ifndef gte_stsxy
#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#endif

#ifndef gte_stsxy3
#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )
#endif

#ifndef gte_stszotz
#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )
#endif

#ifndef gte_stflg
#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )
#endif

/* the two singles + avsz4/stotz this function needs and the TU does not yet spell */
#ifndef gte_stsxy0_8017DC80
#define gte_stsxy0_8017DC80(r0) __asm__ volatile (        \
    "swc2 $12, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#endif
#ifndef gte_stsxy1_8017DC80
#define gte_stsxy1_8017DC80(r0) __asm__ volatile (        \
    "swc2 $13, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#endif
#ifndef gte_avsz4_8017DC80
#define gte_avsz4_8017DC80() __asm__ volatile ("nop;nop;avsz4")
#endif
#ifndef gte_stotz_8017DC80
#define gte_stotz_8017DC80(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#endif


typedef struct {
    u8  t0, t1, t2, len;    /* 0x00 */
    u8  r0, g0, b0, code;   /* 0x04 */
    s16 x0, y0;             /* 0x08 */
    u8  r1, g1, b1, p1;     /* 0x0C */
    s16 x1, y1;             /* 0x10 */
    u8  r2, g2, b2, p2;     /* 0x14 */
    s16 x2, y2;             /* 0x18 */
    u8  r3, g3, b3, p3;     /* 0x1C */
    s16 x3, y3;             /* 0x20 */
} G4_8017DC80;                       /* 0x24 */

typedef struct {
    u8  t0, t1, t2, len;    /* 0x00 */
    u8  r0, g0, b0, code;   /* 0x04 */
    s16 x0, y0;             /* 0x08 */
    u8  r1, g1, b1, p1;     /* 0x0C */
    s16 x1, y1;             /* 0x10 */
} G2_8017DC80;                       /* 0x14 */

void func_8017DC80(void)
{
    extern void *func_80010A08(s32);
    extern void func_80052E38(void *);
    extern u8 D_800AF648;
    extern u8 D_800A6610[];
    extern s32 D_8019B7B8;
    extern short D_800B9A02;

    struct {
        u32 flag;               /* sp+0x10 */
        s32 sxy0;               /* sp+0x14 */
        s32 sxy1;               /* sp+0x18 */
        s32 sxy2;               /* sp+0x1C */
        u32 flag2;              /* sp+0x20 */
        s32 sxy3;               /* sp+0x24 */
        u32 otz;                /* sp+0x28 */
        u32 pad;                /* sp+0x2C */
        s32 i;                  /* sp+0x30 */
        u32 slack[5];           /* sp+0x34 */
    } g;

    u8 *r;
    u32 ot;
    G4_8017DC80 *poly;
    G2_8017DC80 *line;
    u8 *q;
    register s32 n __asm__("$16");
    register u32 otz __asm__("$17");
    register u32 otsh __asm__("$4");
    register u32 mlo __asm__("$19");
    register u32 mhi __asm__("$23");
    s32 mode;
    register s32 adj __asm__("$4");
    s32 t;
    register s32 w __asm__("$3");
    s32 x0;
    register s32 x1 __asm__("$3");
    s32 x2;
    s32 x3;
    s32 cc;

    r = (u8 *)&D_8019B7B8;
    mlo = 0xFFFFFF;
    mhi = 0xFF000000;
    g.i = 0;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    func_80052E38(&D_800AF648);

    do {
        w = *(u16 *)r;
        if ((w & 0xFF) >= 2) {
            n = (s32)((u32)w >> 8);
            if ((*(u16 *)(r + 0xA) & 0x1000) == 0) {
                poly = (G4_8017DC80 *)func_80010A08(0x24);
                poly->len = 8;
                poly->code = 0x38;
                gte_ldv3(r + 4, r + 0xC, r + 0x14);
                gte_rtpt();
                gte_stflg(&g.flag);
                gte_stsxy3(&g.sxy0, &g.sxy1, &g.sxy2);
                gte_ldv0(r + 0x1C);
                gte_rtps();
                gte_stflg(&g.flag2);
                g.flag = g.flag | g.flag2;
                gte_stsxy(&g.sxy3);
                gte_avsz4_8017DC80();
                gte_stotz_8017DC80(&g.otz);
                if ((g.flag & 0xFFFFEFFF) == 0) {
                    mode = *(s16 *)(r + 0xA);
                    otz = g.otz;
                    adj = mode & 0xC000;
                    if (adj != 0) {
                        t = mode & 0xFFF;
                        if (adj == 0xC000) {
                            otz -= t;
                            if ((s32)otz < 0) {
                                otz = 0;
                            }
                        } else {
                            otz += t;
                        }
                    }
                    if (otz < 0x1000) {
                        x0 = g.sxy0;
                        poly->x0 = x0;
                        x1 = g.sxy1;
                        poly->y0 = x0 >> 16;
                        poly->x1 = x1;
                        x2 = g.sxy2;
                        poly->y1 = x1 >> 16;
                        poly->x2 = x2;
                        x3 = g.sxy3;
                        poly->y2 = x2 >> 16;
                        poly->x3 = x3;
                        poly->y3 = x3 >> 16;
                        if (*(u32 *)(r + 0x34) != 0) {
                            cc = r[0x25];
                            poly->r1 = cc;
                            poly->r0 = cc;
                            cc = r[0x27];
                            poly->g1 = cc;
                            poly->g0 = cc;
                            cc = r[0x29];
                            poly->b1 = cc;
                            poly->b0 = cc;
                            cc = *(u8 *)(*(u32 *)(r + 0x34) + 0x25);
                            poly->r3 = cc;
                            poly->r2 = cc;
                            cc = *(u8 *)(*(u32 *)(r + 0x34) + 0x27);
                            poly->g3 = cc;
                            poly->g2 = cc;
                            cc = *(u8 *)(*(u32 *)(r + 0x34) + 0x29);
                            poly->b3 = cc;
                            poly->b2 = cc;
                        } else {
                            cc = r[0x25];
                            poly->r3 = cc;
                            poly->r2 = cc;
                            poly->r1 = cc;
                            poly->r0 = cc;
                            cc = r[0x27];
                            poly->g3 = cc;
                            poly->g2 = cc;
                            poly->g1 = cc;
                            poly->g0 = cc;
                            cc = r[0x29];
                            poly->b3 = cc;
                            poly->b2 = cc;
                            poly->b1 = cc;
                            poly->b0 = cc;
                        }
                        if (n < 4) {
                            poly->code |= 2;
                        }
                        otsh = otz << 2;
                        *(u32 *)poly = (*(u32 *)poly & mhi) | (*(u32 *)(ot + otsh) & mlo);
                        *(u32 *)(ot + otsh) = (*(u32 *)(ot + otsh) & mhi) | ((u32)poly & mlo);
                        if (n < 4) {
                            q = (u8 *)func_80010A08(8);
                            q[3] = 1;
                            *(u32 *)(q + 4) = ((n << 5) & 0x9FF) | 0xE1000000;
                            otsh = otz << 2;
                            *(u32 *)q = (*(u32 *)q & mhi) | (*(u32 *)(ot + otsh) & mlo);
                            *(u32 *)(ot + otsh) = (*(u32 *)(ot + otsh) & mhi) | ((u32)q & mlo);
                        }
                    }
                }
            } else {
                line = (G2_8017DC80 *)func_80010A08(0x14);
                line->len = 4;
                line->code = 0x50;
                gte_ldv3(r + 4, r + 0x14, r + 0x14);
                gte_rtpt();
                gte_stsxy0_8017DC80(&g.sxy0);
                gte_stsxy1_8017DC80(&g.sxy1);
                gte_stflg(&g.flag);
                gte_stszotz(&g.otz);
                if ((g.flag & 0xFFFFEFFF) == 0) {
                    mode = *(s16 *)(r + 0xA);
                    otz = g.otz;
                    adj = mode & 0xC000;
                    if (adj != 0) {
                        t = mode & 0xFFF;
                        if (adj == 0xC000) {
                            otz -= t;
                            if ((s32)otz < 0) {
                                otz = 0;
                            }
                        } else {
                            otz += t;
                        }
                    }
                    if (otz < 0x1000) {
                        x0 = g.sxy0;
                        line->x0 = x0;
                        x1 = g.sxy1;
                        line->y0 = x0 >> 16;
                        line->x1 = x1;
                        line->y1 = x1 >> 16;
                        if (*(u32 *)(r + 0x34) != 0) {
                            line->r0 = r[0x25];
                            line->g0 = r[0x27];
                            line->b0 = r[0x29];
                            line->r1 = *(u8 *)(*(u32 *)(r + 0x34) + 0x25);
                            line->g1 = *(u8 *)(*(u32 *)(r + 0x34) + 0x27);
                            line->b1 = *(u8 *)(*(u32 *)(r + 0x34) + 0x29);
                        } else {
                            cc = r[0x25];
                            line->r1 = cc;
                            line->r0 = cc;
                            cc = r[0x27];
                            line->g1 = cc;
                            line->g0 = cc;
                            cc = r[0x29];
                            line->b1 = cc;
                            line->b0 = cc;
                        }
                        if (n < 4) {
                            line->code |= 2;
                        }
                        otsh = otz << 2;
                        *(u32 *)line = (*(u32 *)line & mhi) | (*(u32 *)(ot + otsh) & mlo);
                        *(u32 *)(ot + otsh) = (*(u32 *)(ot + otsh) & mhi) | ((u32)line & mlo);
                        if (n < 4) {
                            q = (u8 *)func_80010A08(8);
                            q[3] = 1;
                            *(u32 *)(q + 4) = ((n << 5) & 0x9FF) | 0xE1000000;
                            otsh = otz << 2;
                            *(u32 *)q = (*(u32 *)q & mhi) | (*(u32 *)(ot + otsh) & mlo);
                            *(u32 *)(ot + otsh) = (*(u32 *)(ot + otsh) & mhi) | ((u32)q & mlo);
                        }
                    }
                }
            }
        }
        r += 0x38;
        g.i = g.i + 1;
    } while (g.i < 0xC0);
}
