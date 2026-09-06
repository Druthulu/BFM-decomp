/* func_80185810 (ov_SC03_105, sub ov_SC03_105_jr_80181C84) -- 489 ins.
 *
 * S85 hand pass, row (d): §501-N port of the BANKED same-shape cousin
 * ov_SC02_027:func_80180B3C (src/ov_SC02_027/ov_SC02_027_jr_8017D898.c:4810)
 * onto the S83 Fable draft (.run/P32/t5x/fable/func_80185810.c, DIFF 13).
 * Everything outside the packet-fill window is the Fable draft verbatim.
 *
 * The cousin's window spelling (fence-free): the v coordinate is loaded into a
 * $7-pinned variable and masked into a FRESH single-set `v = y & 0xFFFF` (a hard
 * register hides nonzero_bits from combine, so the andi survives and, being a
 * single set, is birthing-boosted -- no anti-dependence starvation, no fence);
 * `c40 = (w & 0x40) >> 6` pinned $2; `shift = 2 - tp` early and unpinned; a
 * fresh `u` from the $4-pinned x; the v0 store through an if/else copy `vv`.
 */

#ifndef BFM_ENGINE_TYPES_H
typedef struct { short m[3][3]; long t[3]; } MATRIX_80188114;
#endif

extern u8 D_800AF630[];
extern MATRIX_80188114 D_801BC9B4;
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern u8 D_801BA6B0;
extern void func_80185FB4(s32 a0, s32 a1, s32 a2);
extern void func_8001F730(s32 a0, void *a1, void *a2);

#define gte_SetRotMatrix_85810(r0) __asm__ volatile (    \
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

#define gte_SetTransMatrix_85810(r0) __asm__ volatile (  \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldclmv_85810(r0) __asm__ volatile (          \
    "lhu $12, 0( %0 );"                                  \
    "lhu $13, 6( %0 );"                                  \
    "lhu $14, 12( %0 );"                                 \
    "mtc2 $12, $9;"                                      \
    "mtc2 $13, $10;"                                     \
    "mtc2 $14, $11"                                      \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_rtir_85810() __asm__ volatile ("nop;nop;mvmva 1, 0, 3, 3, 0")

#define gte_stclmv_85810(r0) __asm__ volatile (          \
    "mfc2 $12, $9;"                                      \
    "mfc2 $13, $10;"                                     \
    "mfc2 $14, $11;"                                     \
    "sh $12, 0( %0 );"                                   \
    "sh $13, 6( %0 );"                                   \
    "sh $14, 12( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14", "memory" )

#define gte_ldlvl_85810(r0) __asm__ volatile (           \
    "lhu $13, 4( %0 );"                                  \
    "lhu $12, 0( %0 );"                                  \
    "sll $13, $13, 16;"                                  \
    "or $12, $12, $13;"                                  \
    "mtc2 $12, $0;"                                      \
    "lwc2 $1, 8( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13" )

#define gte_rt_85810() __asm__ volatile ("nop;nop;mvmva 1, 0, 0, 0, 0")

#define gte_stlvnl_85810(r0) __asm__ volatile (          \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_ldv0_85810(r0) __asm__ volatile (            \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )

#define gte_rtps_85810() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy_85810(r0) __asm__ volatile (           \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_stsz_85810(r0) __asm__ volatile (            \
    "swc2 $19, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_ldv3_85810(r0, r1, r2) __asm__ volatile (    \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 );"                                  \
    "lwc2 $2, 0( %1 );"                                  \
    "lwc2 $3, 4( %1 );"                                  \
    "lwc2 $4, 0( %2 );"                                  \
    "lwc2 $5, 4( %2 )"                                   \
    :                                                    \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt_85810() __asm__ volatile ("nop;nop;rtpt")

#define gte_stsxy0_85810(r0) __asm__ volatile (          \
    "swc2 $12, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_stsxy1_85810(r0) __asm__ volatile (          \
    "swc2 $13, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_stflg_85810(r0) __asm__ volatile (           \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )

#define gte_stszotz_85810(r0) __asm__ volatile (         \
    "mfc2 $12, $19;"                                     \
    "nop;"                                               \
    "sra $12, $12, 2;"                                   \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )

void func_80185810(s32 a0)
{
    typedef struct { u16 vx, vy, vz, pad; } UV_85810;
    typedef struct { short m[3][3]; long t[3]; } MTX_85810;
    typedef struct { u32 addr : 24; u32 len : 8; } PTag_85810;

    UV_85810  v[5];        /* sp+0x10 .. sp+0x37 */
    MTX_85810 m;           /* sp+0x38 */
    long sz;               /* sp+0x58 */
    long flag;             /* sp+0x5C */
    long otz;              /* sp+0x60 */
    u8 *base;
    u8 *p;
    u8 *ob;
    u32 ot16;
    PTag_85810 *q;
    u32 flags;
    s32 spr;
    s32 t0;
    s32 sx;
    s32 sy;
    u32 mode;
    u32 w;
    u32 uu;
    u32 cl;
    u32 c40;
    u32 vm;
    u32 vv;
    u32 u;
    s32 shift;
    u32 tp;
    u16 t20;
    u16 t22;

    base  = D_800AF630;
    flags = *(u32 *)a0;
    spr   = *(s32 *)(a0 + 0x24);

    if (*(s32 *)(a0 + 0x20) != 0) {
        if (flags & 0x800000) {
            gte_SetRotMatrix_85810(base + 0x18);
            gte_ldclmv_85810((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x34));
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][0]);
            gte_ldclmv_85810((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x36));
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][1]);
            gte_ldclmv_85810((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x38));
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][2]);
            gte_SetTransMatrix_85810(base + 0x18);
            gte_ldlvl_85810((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x48));
            gte_rt_85810();
            gte_stlvnl_85810(&m.t[0]);
        } else {
            func_80185FB4(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20), flags, (s32)&m);
            gte_SetRotMatrix_85810(base + 0x18);
            gte_ldclmv_85810(&m.m[0][0]);
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][0]);
            gte_ldclmv_85810(&m.m[0][1]);
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][1]);
            gte_ldclmv_85810(&m.m[0][2]);
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][2]);
            gte_SetTransMatrix_85810(base + 0x18);
            gte_ldlvl_85810(&m.t[0]);
            gte_rt_85810();
            gte_stlvnl_85810(&m.t[0]);
        }
        gte_SetRotMatrix_85810(&m);
        gte_SetTransMatrix_85810(&m);
        t0 = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x10;
    } else {
        gte_SetRotMatrix_85810(base + 0x18);
        gte_SetTransMatrix_85810(base + 0x18);
        t0 = a0 + 4;
    }

    gte_ldv0_85810((u8 *)(a0 + 0x14));
    gte_rtps_85810();
    gte_stsxy_85810(&v[0]);
    gte_stsz_85810(&sz);

    sx = *(s16 *)&v[0].vx;
    if (sx < 0) sx = -sx;
    if (sx >= 0xC9) return;
    sy = *(s16 *)&v[0].vy;
    if (sy < 0) sy = -sy;
    if (sy >= 0xA1) return;

    *(u16 *)&D_801BC9B4 = *(u16 *)(a0 + 0xC);
    *(u16 *)((u8 *)&D_801BC9B4 + 8) = *(u16 *)(a0 + 0xE);
    gte_SetRotMatrix_85810(&D_801BC9B4);
    gte_SetTransMatrix_85810(&D_801BC9B4);

    v[3].vx = *(u16 *)(spr + 8) + *(u16 *)(a0 + 0x1C);
    v[3].vy = *(u16 *)(spr + 0xA) + *(u16 *)(a0 + 0x1E);
    v[3].vz = sz;
    v[4].vx = *(u8 *)(spr + 2);
    v[4].vy = *(u8 *)(spr + 3);
    v[4].vz = sz;

    gte_ldv3_85810(&v[3], &v[4], &v[4]);
    gte_rtpt_85810();
    gte_stsxy0_85810(&v[1]);
    gte_stsxy1_85810(&v[2]);
    gte_stflg_85810(&flag);
    gte_stszotz_85810(&otz);
    if (flag & ~0x1000) return;

    /* ---- the packet-fill window: the cousin's spelling (func_80180B3C) ---- */
    mode = (flags >> 24) & 3;
    shift = 2 - mode;
    p = D_800A5E60;
    D_800A5E60 = p + 0x28;
    w = mode << 7;
    p[3] = 9;
    p[7] = 0x2C;
    ot16 = *(u16 *)(base + 0xA3D2);
    ob = &D_800A6610[ot16 << 14];
    uu = *(u16 *)(spr + 4);
    cl = *(u16 *)(spr + 6);
    p[7] |= 2;
    *(u16 *)(p + 0x16) = w | ((flags >> 23) & 0x60) | ((cl & 0x100) >> 4)
                           | ((uu & 0x3C0) >> 6) | ((cl & 0x200) << 2);
    c40 = (flags & 0x40) >> 6;
    p[7] |= c40;
    vm = cl & 0xFFFF;
    u = (uu - ((*(u16 *)(p + 0x16) & 0xF) << 6)) << shift;
    p[0xC] = u;
    if (!(*(u16 *)(p + 0x16) & 0x10)) {
        vv = vm;
    } else {
        vv = vm - 0x100;
    }
    p[0xD] = vv;
    /* ---- end of the ported window ---- */

    p[0x14] = p[0xC] + *(u8 *)(spr + 2) - 1;
    p[0x15] = p[0xD];
    p[0x1C] = p[0xC];
    p[0x1D] = p[0xD] + *(u8 *)(spr + 3) - 1;
    p[6] = 0x80;
    p[5] = 0x80;
    p[4] = 0x80;
    p[0x24] = p[0x14];
    p[0x25] = p[0x1D];

    *(u16 *)(p + 8)    = v[0].vx + v[1].vx;
    *(u16 *)(p + 0xA)  = v[0].vy + v[1].vy;
    *(u16 *)(p + 0x10) = *(u16 *)(p + 8) + v[2].vx;
    *(u16 *)(p + 0x1A) = *(u16 *)(p + 0xA) + v[2].vy;
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0xA);
    *(u16 *)(p + 0x18) = *(u16 *)(p + 8);
    t20 = *(u16 *)(p + 0x10);
    t22 = *(u16 *)(p + 0x1A);
    tp = D_801BA6B0;
    *(u16 *)(p + 0x20) = t20;
    *(u16 *)(p + 0x22) = t22;

    if (tp == 0) {
        u32 t2 = *(u8 *)(spr + 1);
        u32 tb = (t2 + 0x100) << 6;
        if (t2 < 0xE0) *(u16 *)(p + 0xE) = tb | 0x16;
        else           *(u16 *)(p + 0xE) = tb | 0x10;
    } else {
        u32 tb = (tp + 0x100) << 6;
        { u32 vx; if (tp < 0xE0) vx = tb | 0x16; else vx = tb | 0x10; *(u16 *)(p + 0xE) = vx; }
    }

    if ((flags & 0x300000) == 0x200000) {
        func_8001F730(t0, &v[0], p);
    }

    q = (PTag_85810 *)((otz << 2) + (u32)ob);
    ((PTag_85810 *)p)->addr = q[1].addr;
    q[1].addr = (u32)p;
}
