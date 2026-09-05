/* func_80185810 (ov_SC03_105 / ov_SC03_105_jr_80181C84) -- 489 ins.
 *
 * VERDICT: compiler-emitted C, NOT hand-written asm.  Regular gcc-2.7.2 -O2
 * prologue/epilogue ($s0-$s4 + $ra saved at 0x68..0x7C, frame 0x80), an
 * if/else diamond with a `j` over the else arm, jal-with-delay-slot call
 * sequences, load-delay nops, and every COP2 instruction arrives through the
 * same PsyQ inline-asm gte_* macros the matched neighbours in this TU use
 * (gte_SetRotMatrix/gte_SetTransMatrix are already #defined at line 4120 of
 * the TU).  splat's "/* Handwritten function *\/" banner only records that the
 * subseg contains cop2 opcodes the disassembler flags, not hand asm.
 *
 * STATUS: NEAR -- 489/489 instructions, function-wide instruction multiset
 * IDENTICAL to the target; residual is sched1 ordering + the register file
 * rotation it drags along, in three windows (see the drafting note).
 *
 * The three zero-byte `__asm__ __volatile__("")` fences are cookbook 194-A
 * scheduling fences (ASM_INPUT => sched.c:1953 barrier, zero bytes emitted).
 * They took the residual from 80 -> 37 masked mismatches; placements were
 * found by brute force (~3600 match_one compiles over statement orders x
 * fence masks).  Delete them and the count goes back to 80.
 */
#ifndef BFM_ENGINE_TYPES_H
typedef struct { short m[3][3]; long t[3]; } MATRIX_80188114;
#endif /* BFM_ENGINE_TYPES_H */

extern u8 D_800AF630[];
extern MATRIX_80188114 D_801BC9B4;
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern u8 D_801BA6B0;
extern void func_80185FB4(s32 a0, s32 a1, s32 a2);
extern void func_8001F730(s32 a0, void *a1, void *a2);

#ifndef gte_SetRotMatrix
#define gte_SetRotMatrix(r0) __asm__ volatile (          \
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
#endif
#ifndef gte_SetTransMatrix
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
#endif
#ifndef gte_ldclmv
#define gte_ldclmv(r0) __asm__ volatile (                \
    "lhu $12, 0( %0 );"                                  \
    "lhu $13, 6( %0 );"                                  \
    "lhu $14, 12( %0 );"                                 \
    "mtc2 $12, $9;"                                      \
    "mtc2 $13, $10;"                                     \
    "mtc2 $14, $11"                                      \
    : : "r"( r0 ) : "$12", "$13", "$14" )
#endif
#ifndef gte_stclmv
#define gte_stclmv(r0) __asm__ volatile (                \
    "mfc2 $12, $9;"                                      \
    "mfc2 $13, $10;"                                     \
    "mfc2 $14, $11;"                                     \
    "sh $12, 0( %0 );"                                   \
    "sh $13, 6( %0 );"                                   \
    "sh $14, 12( %0 )"                                   \
    : : "r"( r0 ) : "$12", "$13", "$14", "memory" )
#endif
#ifndef gte_ldlvnl
#define gte_ldlvnl(r0) __asm__ volatile (                \
    "lhu $13, 4( %0 );"                                  \
    "lhu $12, 0( %0 );"                                  \
    "sll $13, $13, 16;"                                  \
    "or $12, $12, $13;"                                  \
    "mtc2 $12, $0;"                                      \
    "lwc2 $1, 8( %0 )"                                   \
    : : "r"( r0 ) : "$12", "$13" )
#endif
#ifndef gte_stlvnl
#define gte_stlvnl(r0) __asm__ volatile (                \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
    : : "r"( r0 ) : "memory" )
#endif
#ifndef gte_ldv0
#define gte_ldv0(r0) __asm__ volatile (                  \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    : : "r"( r0 ) )
#endif
#ifndef gte_ldv3
#define gte_ldv3(r0, r1, r2) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 );"                                  \
    "lwc2 $2, 0( %1 );"                                  \
    "lwc2 $3, 4( %1 );"                                  \
    "lwc2 $4, 0( %2 );"                                  \
    "lwc2 $5, 4( %2 )"                                   \
    : : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#endif
#ifndef gte_rtir
#define gte_rtir() __asm__ volatile ("nop;nop;mvmva 1, 0, 3, 3, 0")
#endif
#ifndef gte_rt
#define gte_rt() __asm__ volatile ("nop;nop;mvmva 1, 0, 0, 0, 0")
#endif
#ifndef gte_rtps
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#endif
#ifndef gte_rtpt
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#endif
#ifndef gte_stsxy
#define gte_stsxy(r0) __asm__ volatile (                 \
    "swc2 $14, 0( %0 )" : : "r"( r0 ) : "memory" )
#endif
#ifndef gte_stsxy0
#define gte_stsxy0(r0) __asm__ volatile (                \
    "swc2 $12, 0( %0 )" : : "r"( r0 ) : "memory" )
#endif
#ifndef gte_stsxy1
#define gte_stsxy1(r0) __asm__ volatile (                \
    "swc2 $13, 0( %0 )" : : "r"( r0 ) : "memory" )
#endif
#ifndef gte_stsz
#define gte_stsz(r0) __asm__ volatile (                  \
    "swc2 $19, 0( %0 )" : : "r"( r0 ) : "memory" )
#endif
#ifndef gte_stflg
#define gte_stflg(r0) __asm__ volatile (                 \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    : : "r"( r0 ) : "$12", "memory" )
#endif
#ifndef gte_stszotz
#define gte_stszotz(r0) __asm__ volatile (               \
    "mfc2 $12, $19;"                                     \
    "nop;"                                               \
    "sra $12, $12, 2;"                                   \
    "sw $12, 0( %0 )"                                    \
    : : "r"( r0 ) : "$12", "memory" )
#endif

void func_80185810(s32 arg0)
{
    /* block-scope copies so the draft compiles standalone under match_one. */
    typedef struct { u16 vx, vy, vz, pad; } UVec;
    typedef struct { u32 addr : 24; u32 len : 8; } Tag;

    UVec sxy[5];
    MATRIX_80188114 m;
    s32 sz;
    s32 flag;
    s32 otz;
    u32 flags;
    s32 obj;
    s32 spr;
    s32 t0;
    s32 tp;
    u32 u;
    u32 v;
    s32 x;
    u32 c;
    u32 tb;
    u32 tpg;
    s32 shf;
    u32 cg;
    u32 cl;
    u8 *pkt;
    u8 *gp;
    Tag *ot;

    gp = D_800AF630;
    flags = *(u32 *)arg0;
    obj = *(s32 *)(arg0 + 0x20);
    spr = *(s32 *)(arg0 + 0x24);

    if (obj != 0) {
        if (flags & 0x800000) {
            gte_SetRotMatrix(&gp[0x18]);
            gte_ldclmv(*(s32 *)(obj + 0x20) + 0x34);
            gte_rtir();
            gte_stclmv(&m.m[0][0]);
            gte_ldclmv(*(s32 *)(*(s32 *)(arg0 + 0x20) + 0x20) + 0x36);
            gte_rtir();
            gte_stclmv(&m.m[0][1]);
            gte_ldclmv(*(s32 *)(*(s32 *)(arg0 + 0x20) + 0x20) + 0x38);
            gte_rtir();
            gte_stclmv(&m.m[0][2]);
            gte_SetTransMatrix(&gp[0x18]);
            gte_ldlvnl(*(s32 *)(*(s32 *)(arg0 + 0x20) + 0x20) + 0x48);
            gte_rt();
            gte_stlvnl(&m.t[0]);
        } else {
            func_80185FB4(*(s32 *)(obj + 0x20), flags, (s32)&m);
            gte_SetRotMatrix(&gp[0x18]);
            gte_ldclmv(&m.m[0][0]);
            gte_rtir();
            gte_stclmv(&m.m[0][0]);
            gte_ldclmv(&m.m[0][1]);
            gte_rtir();
            gte_stclmv(&m.m[0][1]);
            gte_ldclmv(&m.m[0][2]);
            gte_rtir();
            gte_stclmv(&m.m[0][2]);
            gte_SetTransMatrix(&gp[0x18]);
            gte_ldlvnl(&m.t[0]);
            gte_rt();
            gte_stlvnl(&m.t[0]);
        }
        gte_SetRotMatrix(&m);
        gte_SetTransMatrix(&m);
        t0 = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x20) + 0x10;
    } else {
        gte_SetRotMatrix(&gp[0x18]);
        gte_SetTransMatrix(&gp[0x18]);
        t0 = arg0 + 4;
    }

    gte_ldv0(arg0 + 0x14);
    gte_rtps();
    gte_stsxy(&sxy[0]);
    gte_stsz(&sz);

    x = *(s16 *)&sxy[0].vx;
    if (x < 0) {
        x = -x;
    }
    if (x >= 0xC9) {
        return;
    }
    x = *(s16 *)&sxy[0].vy;
    if (x < 0) {
        x = -x;
    }
    if (x >= 0xA1) {
        return;
    }

    D_801BC9B4.m[0][0] = *(u16 *)(arg0 + 0xC);
    D_801BC9B4.m[1][1] = *(u16 *)(arg0 + 0xE);
    gte_SetRotMatrix(&D_801BC9B4);
    gte_SetTransMatrix(&D_801BC9B4);

    sxy[3].vx = *(u16 *)(spr + 8) + *(u16 *)(arg0 + 0x1C);
    sxy[3].vy = *(u16 *)(spr + 0xA) + *(u16 *)(arg0 + 0x1E);
    sxy[3].vz = sz;
    sxy[4].vx = *(u8 *)(spr + 2);
    sxy[4].vy = *(u8 *)(spr + 3);
    sxy[4].vz = sz;

    gte_ldv3(&sxy[3], &sxy[4], &sxy[4]);
    gte_rtpt();
    gte_stsxy0(&sxy[1]);
    gte_stsxy1(&sxy[2]);
    gte_stflg(&flag);
    gte_stszotz(&otz);

    if (flag & ~0x1000) {
        return;
    }

    tp = (flags >> 24) & 3;
    tpg = (tp & 3) << 7;
    pkt = D_800A5E60;
    D_800A5E60 = pkt + 0x28;
    pkt[3] = 9;
    pkt[7] = 0x2C;
    tb = *(u16 *)&gp[0xA3D2];
    __asm__ __volatile__("");
    u = *(u16 *)(spr + 4);
    v = *(u16 *)(spr + 6);
    pkt[7] = 0x2E;
    *(u16 *)(pkt + 0x16) = tpg | ((((flags >> 28) & 3) & 3) << 5) |
                           ((v & 0x100) >> 4) | ((u & 0x3C0) >> 6) | ((v & 0x200) << 2);
    pkt[7] |= (flags & 0x40) >> 6;
    __asm__ __volatile__("");
    v = (u16)v;
    shf = 2 - tp;
    ot = (Tag *)&D_800A6610[tb << 14];
    u -= (*(u16 *)(pkt + 0x16) & 0xF) << 6;
    __asm__ __volatile__("");
    u <<= shf;
    pkt[0xC] = u;
    if (*(u16 *)(pkt + 0x16) & 0x10) {
        v -= 0x100;
    }
    pkt[0xD] = v;
    pkt[0x14] = pkt[0xC] + *(u8 *)(spr + 2) - 1;
    pkt[0x15] = pkt[0xD];
    pkt[0x1C] = pkt[0xC];
    pkt[0x1D] = pkt[0xD] + *(u8 *)(spr + 3) - 1;
    pkt[6] = 0x80;
    pkt[5] = 0x80;
    pkt[4] = 0x80;
    pkt[0x24] = pkt[0x14];
    pkt[0x25] = pkt[0x1D];

    *(u16 *)(pkt + 8) = sxy[0].vx + sxy[1].vx;
    __asm__ __volatile__("");
    *(u16 *)(pkt + 0xA) = sxy[0].vy + sxy[1].vy;
    *(u16 *)(pkt + 0x10) = *(u16 *)(pkt + 8) + sxy[2].vx;
    *(u16 *)(pkt + 0x12) = *(u16 *)(pkt + 0xA);
    *(u16 *)(pkt + 0x1A) = *(u16 *)(pkt + 0xA) + sxy[2].vy;
    *(u16 *)(pkt + 0x18) = *(u16 *)(pkt + 8);
    __asm__ __volatile__("");
    *(u16 *)(pkt + 0x20) = *(u16 *)(pkt + 0x10);
    *(u16 *)(pkt + 0x22) = *(u16 *)(pkt + 0x1A);

    if (D_801BA6B0 == 0) {
        c = *(u8 *)(spr + 1);
        cl = (c + 0x100) << 6;
        if (c < 0xE0) {
            *(u16 *)(pkt + 0xE) = cl | 0x16;
        } else {
            *(u16 *)(pkt + 0xE) = cl | 0x10;
        }
    } else {
        cg = D_801BA6B0;
        cl = (cg + 0x100) << 6;
        if (cg < 0xE0) {
            *(u16 *)(pkt + 0xE) = cl | 0x16;
        } else {
            *(u16 *)(pkt + 0xE) = cl | 0x10;
        }
    }

    if ((flags & 0x300000) == 0x200000) {
        func_8001F730(t0, &sxy[0], pkt);
    }

    ((Tag *)pkt)->addr = ot[otz + 1].addr;
    ot[otz + 1].addr = (u32)pkt;
}
