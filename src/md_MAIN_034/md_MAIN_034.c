#include "common.h"

/* HOISTED (S56): defined here rather than beside func_800CC4E8 because
 * func_800CC310 splices EARLIER in address order and declares externs of this
 * type; strip_provided_typedefs removes the draft's own copy as "already
 * provided", so the surviving definition must precede every use in the file. */
typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} Quad4_800CCB14;

#include "common.h"

extern s16 D_800CC9E8;
extern s16 D_800CC9EA;
extern s16 D_800CC9F0;
extern s16 D_800CC9F2;
extern u16 D_800B99DA;
extern s32 D_800CC9EC;
extern s32 D_800CC9F4;
extern s32 D_800CCB18;
extern s32 D_800A2B78;
extern void func_800CB00C();

/* func_800CAE88 -- two independent "blink" oscillators, then a tail call.
 *
 * NOTE ON THE SIGNATURE (byte-load-bearing, do not "simplify"): p1/p2 are
 * unmodified pass-through arguments to func_800CB00C.  They emit ZERO
 * instructions (the outgoing `move $a1,$a1` / `move $a2,$a2` are self-copies
 * and are deleted), but their allocnos hold copy-preferences on $a1/$a2 for
 * the whole function, which is what pushes the D_800CC9EC/D_800CC9F4 flag
 * allocno off $a1 and onto $a3 (greg: "74 conflicts: 72 74 2 3 29", no
 * preference of its own -> plain ascending first-fit).  Dropping either
 * parameter moves the flag one slot down ($a2 with 2 args, $t0 with 4) --
 * both measured.
 *
 * NOTE ON v0in: the function reads $v0 on entry without ever setting it
 * (`andi $v0,$v0,1` is the first instruction after the prologue), so the
 * original source read an uninitialised value here.  The register pin
 * reproduces it exactly.
 */
void func_800CAE88(s32 *arg0, s32 p1, s32 p2) {
    s32 v0in;
    s32 flag1;
    s32 flag2;
    s32 temp;

    if (!(v0in & 1)) {
        flag1 = D_800CC9EC;
        if (flag1 == 0) {
            D_800CC9E8++;
            D_800CC9EA++;
            if (D_800CC9EA >= 0x200)
                D_800CC9EC = 1;
        } else {
            D_800CC9E8--;
            D_800CC9EA--;
            if (D_800CC9E8 <= 0)
                D_800CC9EC = flag1 ^ 1;
        }
        if (!(D_800B99DA & 1)) {
            flag2 = D_800CC9F4;
            if (flag2 == 0) {
                D_800CC9F0++;
                D_800CC9F2++;
                if (D_800CC9F2 >= 0x200)
                    D_800CC9F4 = 1;
            } else {
                D_800CC9F0--;
                D_800CC9F2--;
                if (D_800CC9F0 <= 0)
                    D_800CC9F4 = flag2 ^ 1;
            }
        }
    }
    temp = *arg0;
    D_800CCB18 = temp;
    D_800A2B78 = (temp >> 28) & 7;
    func_800CB00C(arg0, p1, p2);
}


INCLUDE_RODATA("asm/md_MAIN_034/nonmatchings/md_MAIN_034", D_800CAE08);

#include "common.h"

typedef void (*Fn7_800CB00C)(void *, void *, void *, void *, s32, s32, s32);

void func_800CB00C(s32 arg0, s32 arg1, s32 arg2)
{
    /* §203/§20 callee-decl recovery, draft-text tier: these seven callees are
     * DEFINED later in this same TU with pointer return types whose typedefs are
     * also declared later, so a file-scope `extern` here is a hard
     * `conflicting types` error and the canonical prototypes cannot be spelled
     * before their typedefs exist.  gcc-2.7.2 demotes the same clash to a
     * warning when the forward declaration sits at BLOCK scope, and every call
     * is cast to the byte-target's own signature, so codegen is unchanged. */
    extern void func_800CB1F8();
    extern void func_800CB3C0();
    extern void func_800CBA18();
    extern void func_800CB5D0();
    extern void func_800CB7BC();
    extern void func_800CBC2C();
    extern void func_800CBE28();

    s32 v0;
    s32 a3;
    s32 s3;
    s32 s2;
    s32 s1;
    u32 s6;
    u32 code;
    s32 s0;

    v0 = *(s32 *)(arg0 + 8);
    a3 = *(s32 *)(arg0 + 0xC);
    s3 = *(s32 *)v0;
    s2 = *(s32 *)(v0 + 8);
    s1 = *(s32 *)(v0 + 0x10);

    do {
        s6 = *(u32 *)a3;
        s0 = *(s32 *)(a3 + 4);
        a3 += 8;
        code = s6 >> 24;
        switch ((code & 0xFC) - 0x20) {
        case 0:
            ((Fn7_800CB00C)func_800CB1F8)((void *)s1, (void *)s3, (void *)s2,
                                          (void *)a3, s0, arg2,
                                          *(s32 *)(arg1 + 4));
            s1 += s0 << 4;
            break;
        case 8:
            ((Fn7_800CB00C)func_800CB3C0)((void *)s1, (void *)s3, (void *)s2,
                                          (void *)a3, s0, arg2,
                                          *(s32 *)(arg1 + 4));
            s1 += (s0 * 5) << 2;
            break;
        case 12:
            ((Fn7_800CB00C)func_800CBA18)((void *)s1, (void *)s3, (void *)s2,
                                          (void *)a3, s0, arg2,
                                          *(s32 *)(arg1 + 4));
            s1 += s0 << 5;
            break;
        case 16:
            ((Fn7_800CB00C)func_800CB5D0)((void *)s1, (void *)s3, (void *)s2,
                                          (void *)a3, s0, arg2,
                                          *(s32 *)(arg1 + 4));
            s1 += (s0 * 5) << 2;
            break;
        case 24:
            ((Fn7_800CB00C)func_800CB7BC)((void *)s1, (void *)s3, (void *)s2,
                                          (void *)a3, s0, arg2,
                                          *(s32 *)(arg1 + 4));
            s1 += (s0 * 3) << 3;
            break;
        case 20:
            ((Fn7_800CB00C)func_800CBC2C)((void *)s1, (void *)s3, (void *)s2,
                                          (void *)a3, s0, arg2,
                                          *(s32 *)(arg1 + 4));
            s1 += (s0 * 7) << 2;
            break;
        case 28:
            ((Fn7_800CB00C)func_800CBE28)((void *)s1, (void *)s3, (void *)s2,
                                          (void *)a3, s0, arg2,
                                          *(s32 *)(arg1 + 4));
            s1 += (s0 * 9) << 2;
            break;
        }
        a3 = (s6 & 0xFFFFFF) | (s32)0x80000000;
    } while ((s6 & 0xFFFFFF) != 0);
}


#include "common.h"

/* ---- PsyQ inline GTE macros (same spellings as the matched siblings
 *      func_800CBA18 / func_800CBC2C in this TU) ---- */

#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_f3(r0) __asm__ volatile (      \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 12( %0 );"                         \
    "swc2 $14, 16( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (          \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

/* ---- types ------------------------------------------------------------- */
typedef struct { s16 vx, vy, vz, pad; } SVEC8_800CB1F8;   /* 0x08 */

/* face record, 0x10 bytes; word 1 is the face base colour */
typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 rgb;
    /* 0x08 */ u16 n0;
    /* 0x0A */ u16 v0;
    /* 0x0C */ u16 v1;
    /* 0x0E */ u16 v2;
} Face10_800CB1F8;                                         /* 0x10 */

typedef struct {          /* flat tri packet, 0x14 bytes */
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgb0;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u32 xy1;
    /* 0x10 */ u32 xy2;
} F3P_800CB1F8;                                           /* 0x14 */

extern s16 D_800C7C74;      /* double-buffer parity index */
extern u32 D_800CC9F8;      /* flat colour used when func_800CC0A0() says so */

extern s32 func_800CC0A0(void *prim);
extern void func_800CC110(s32 ot, s32 otz, s32 shift, void *prim, u32 code);

F3P_800CB1F8 *func_800CB1F8(Face10_800CB1F8 *f, SVEC8_800CB1F8 *verts,
                            SVEC8_800CB1F8 *norms, F3P_800CB1F8 *prims,
                            s32 count, s32 shift, s32 ot)
{
    struct { s32 flag, opz; } g;
    F3P_800CB1F8 *prim;

    prim = &prims[D_800C7C74];

    for (; count != 0; count--, f++, prim += 2) {
        gte_ldv3(&verts[f->v0], &verts[f->v1], &verts[f->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.opz);
            if (g.opz > 0) {
                gte_stsxy3_f3(prim);
                gte_avsz3();
                gte_stotz(&g.opz);
                if (func_800CC0A0(prim) != 0) {
                    prim->rgb0 = D_800CC9F8;
                } else {
                    gte_ldrgb(&f->rgb);
                    gte_ldv0(&norms[f->n0]);
                    gte_nccs();
                    gte_strgb(&prim->rgb0);
                }
                func_800CC110(ot, g.opz, shift, prim, 0x4000000);
            }
        }
    }

    return prim;
}


#include "common.h"

/* func_800CB3C0 — md_MAIN_034 — flat-quad (POLY_F4 / OT tag 0x05000000)
 * emitter with flat NCCS lighting.  Structural twin of func_800CB7BC in this
 * same TU (the GT4 emitter): identical control flow, but a 0x18 flat packet
 * with ONE colour word and a single NCCS instead of the NCCT+NCCS pair.
 *
 * Register map read off the target .s:
 *   $s5 = face                 $s0 = &face->n0 giv (a0+8, stride 0x14)
 *   $s3 = vtx                  a2 (nrm) spilled to 0x20(sp), reloaded in the
 *                              NCCS arm only
 *   $s1 = pkt (a3 + D_800C7C74*0x18, stride 0x30 = 2 packets)
 *   $s2 = &pkt->rgb0 giv (pkt+4)
 *   $s4 = loop counter (stack arg 4)
 *   $s7 = &g.flag (sp+0x18)    $s6 = &g.opz (sp+0x1C)
 *   $fp = ~0x1000, hoisted (used by both flag tests)
 */

/* ---- PsyQ inline_c.h GTE macros (same spellings as the matched siblings) -- */
#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (          \
    "swc2 $14, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_f4(r0) __asm__ volatile (      \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 12( %0 );"                         \
    "swc2 $14, 16( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (          \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

/* ---- types ------------------------------------------------------------- */
typedef struct { s16 vx, vy, vz, pad; } SVEC8_800CB3C0;   /* 0x08 */

typedef struct {          /* face record, 0x14 bytes */
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 rgb;
    /* 0x08 */ u16 n0;
    /* 0x0A */ u16 v0;
    /* 0x0C */ u16 v1;
    /* 0x0E */ u16 v2;
    /* 0x10 */ u16 v3;
    /* 0x12 */ u16 pad12;
} FaceF4_800CB3C0;                                        /* 0x14 */

typedef struct {          /* flat quad packet, 0x18 bytes */
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgb0;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u32 xy1;
    /* 0x10 */ u32 xy2;
    /* 0x14 */ u32 xy3;
} PktF4_800CB3C0;                                         /* 0x18 */

extern s16 D_800C7C74;      /* double-buffer parity index */
extern u32 D_800CC9FC;      /* flat colour used when func_800CC0A0() says so */

extern s32 func_800CC0A0(void *prim);
extern void func_800CC110(s32 ot, s32 otz, s32 shift, void *prim, u32 code);

PktF4_800CB3C0 *func_800CB3C0(FaceF4_800CB3C0 *face, SVEC8_800CB3C0 *vtx,
                              SVEC8_800CB3C0 *nrm, PktF4_800CB3C0 *prims,
                              s32 count, s32 shift, s32 ot)
{
    struct { s32 flag, opz; } g;
    PktF4_800CB3C0 *pkt;

    pkt = &prims[D_800C7C74];

    for (; count != 0; count--, face++, pkt += 2) {
        gte_ldv3(&vtx[face->v0], &vtx[face->v1], &vtx[face->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.opz);
            if (g.opz > 0) {
                gte_stsxy3_f4(pkt);
                gte_ldv0(&vtx[face->v3]);
                gte_rtps();
                gte_stflg(&g.flag);
                if (!(g.flag & ~0x1000)) {
                    gte_stsxy(&pkt->xy3);
                    gte_avsz4();
                    gte_stotz(&g.opz);
                    if (func_800CC0A0(pkt) != 0) {
                        pkt->rgb0 = D_800CC9FC;
                    } else {
                        gte_ldrgb(&face->rgb);
                        gte_ldv0(&nrm[face->n0]);
                        gte_nccs();
                        gte_strgb(&pkt->rgb0);
                    }
                    func_800CC110(ot, g.opz, shift, pkt, 0x05000000);
                }
            }
        }
    }

    return pkt;
}


#include "common.h"

/* ---- PsyQ inline_c.h GTE macros (same spellings as the matched siblings
 *      func_800CBA18 / func_800CBC2C in this TU; the two single-pointer
 *      store macros carry local names so they cannot collide with the
 *      three-pointer gte_strgb3 defined by the func_800CBE28 block) ---- */

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_flat(r0) __asm__ volatile (   \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb3_flat(r0) __asm__ volatile (   \
    "swc2 $20, 4( %0 );"                         \
    "swc2 $21, 12( %0 );"                        \
    "swc2 $22, 20( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

/* ---- types ------------------------------------------------------------- */
typedef struct { s16 vx, vy, vz, pad; } SVEC8_800CB5D0;   /* 0x08 */

/* face record, 0x14 bytes; word 1 is the face base colour */
typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 rgb;
    /* 0x08 */ u16 n0;
    /* 0x0A */ u16 v0;
    /* 0x0C */ u16 n1;
    /* 0x0E */ u16 v1;
    /* 0x10 */ u16 n2;
    /* 0x12 */ u16 v2;
} Face14_800CB5D0;                                        /* 0x14 */

typedef struct {          /* flat gouraud tri packet, 0x1C bytes */
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgb0;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u32 rgb1;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u32 rgb2;
    /* 0x18 */ u32 xy2;
} Prim1C_800CB5D0;                                        /* 0x1C */

extern s16 D_800C7C74;      /* double-buffer parity index */
extern u32 D_800CCA08;      /* flat colour used when func_800CC0A0() says so */

extern s32 func_800CC0A0(void *prim);
extern void func_800CC110(s32 ot, s32 otz, s32 shift, void *prim, u32 code);

Prim1C_800CB5D0 *func_800CB5D0(Face14_800CB5D0 *f, SVEC8_800CB5D0 *verts,
                               SVEC8_800CB5D0 *norms, Prim1C_800CB5D0 *prims,
                               s32 count, s32 shift, s32 ot)
{
    struct { s32 flag, opz; } g;
    Prim1C_800CB5D0 *prim;

    prim = &prims[D_800C7C74];

    for (; count != 0; count--, f++, prim += 2) {
        gte_ldv3(&verts[f->v0], &verts[f->v1], &verts[f->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.opz);
            if (g.opz > 0) {
                gte_stsxy3_flat(prim);
                gte_avsz3();
                gte_stotz(&g.opz);
                if (func_800CC0A0(prim) != 0) {
                    prim->rgb0 = D_800CCA08;
                    prim->rgb1 = D_800CCA08;
                    prim->rgb2 = D_800CCA08;
                } else {
                    gte_ldrgb(&f->rgb);
                    gte_ldv3(&norms[f->n0], &norms[f->n0], &norms[f->n0]);
                    gte_ncct();
                    gte_strgb3_flat(prim);
                }
                func_800CC110(ot, g.opz, shift, prim, 0x6000000);
            }
        }
    }

    return prim;
}


#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (          \
    "swc2 $14, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_gt4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 16( %0 );"                         \
    "swc2 $14, 24( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (          \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb3_gt4(r0) __asm__ volatile (     \
    "swc2 $20, 4( %0 );"                          \
    "swc2 $21, 12( %0 );"                         \
    "swc2 $22, 20( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC8_800CB7BC; /* 0x08 */

typedef struct { u32 unk00; u32 rgb; u16 n0, v0; u16 n1, v1; u16 n2, v2; u16 n3, v3; } FaceGT4_800CB7BC; /* 0x18 */

typedef struct {
    u32 tag;
    u32 rgb0, xy0;
    u32 rgb1, xy1;
    u32 rgb2, xy2;
    u32 rgb3, xy3;
} PktGT4_800CB7BC; /* 0x24 */

extern s16 D_800C7C74;
extern u32 D_800CCA0C;

extern s32 func_800CC0A0(void *prim);
extern void func_800CC110(s32 ot, s32 otz, s32 shift, void *prim, u32 code);

PktGT4_800CB7BC *func_800CB7BC(FaceGT4_800CB7BC *face, SVEC8_800CB7BC *vtx,
                               SVEC8_800CB7BC *nrm, PktGT4_800CB7BC *prims,
                               s32 count, s32 shift, s32 ot)
{
    struct { s32 flag, opz; } g;
    PktGT4_800CB7BC *pkt;

    pkt = &prims[D_800C7C74];

    for (; count != 0; count--, face++, pkt += 2) {
        gte_ldv3(&vtx[face->v0], &vtx[face->v1], &vtx[face->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.opz);
            if (g.opz > 0) {
                gte_stsxy3_gt4(pkt);
                gte_ldv0(&vtx[face->v3]);
                gte_rtps();
                gte_stflg(&g.flag);
                if (!(g.flag & ~0x1000)) {
                    gte_stsxy(&pkt->xy3);
                    gte_avsz4();
                    gte_stotz(&g.opz);
                    if (func_800CC0A0(pkt) != 0) {
                        pkt->rgb0 = D_800CCA0C;
                        pkt->rgb1 = D_800CCA0C;
                        pkt->rgb2 = D_800CCA0C;
                        pkt->rgb3 = D_800CCA0C;
                    } else {
                        gte_ldrgb(&face->rgb);
                        gte_ldv3(&nrm[face->n0], &nrm[face->n0], &nrm[face->n0]);
                        gte_ncct();
                        gte_strgb3_gt4(pkt);
                        gte_ldv0(&nrm[face->n0]);
                        gte_nccs();
                        gte_strgb(&pkt->rgb3);
                    }
                    func_800CC110(ot, g.opz, shift, pkt, 0x08000000);
                }
            }
        }
    }

    return pkt;
}


#include "common.h"

/* func_800CBA18 — md_MAIN_034 — textured-quad (POLY_FT4 / OT tag 0x09000000)
 * emitter with flat NCCS lighting.
 *
 * Fresh crack.  Structural twins already matched in src/800.c:
 *   func_80027D20 / func_80027F4C  -> `prim = &prims[D_800C7C74]; prim += 2;`
 *                                     + `func_80028200(ot, opz, shift, prim, TAG)`
 *                                     (func_800CC110 is this overlay's copy of that)
 *   func_80025EB8                  -> the FT4 packet + `gte_ldrgb(&D_80063880)`
 *                                     hoisted once out of the loop, Prim20 face.
 *
 * Deltas vs. those twins:
 *   - OTZ comes from AVSZ4 (not the STSZ4 min/max ladder).
 *   - the flat colour is chosen by func_800CC0A0(prim): non-zero picks the
 *     constant colour word D_800CCA04, zero runs NCCS on the face normal.
 *
 * Register map read off the target .s:
 *   $s0 = &f->n0 giv (a0+0x14, stride 0x20)   $s1 = prim (a3 + D_800C7C74*0x28,
 *   stride 0x50 = 2 packets)                  $s2 = &prim->rgb giv (prim+4)
 *   $s3 = verts   $fp = norms                 $s4 = loop counter (stack arg 4)
 *   $s5 = &g.otz (sp+0x1C)                    $s6 = &g.flag (sp+0x18)
 *   $s7 = ~0x1000, hoisted (used by both flag tests)
 */

/* ---- PsyQ inline_c.h GTE macros (same spellings as the matched twins) ---- */
#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (          \
    "swc2 $14, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_ft4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 16( %0 );"                         \
    "swc2 $14, 24( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (          \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

/* ---- types ------------------------------------------------------------- */
typedef struct { s16 vx, vy, vz, pad; } SVEC8_800CBA18;   /* 0x08 */

/* face record, 0x20 bytes; only the index half (0x14..) is read here */
typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 uv0;
    /* 0x08 */ u32 uv1;
    /* 0x0C */ u32 uv2;
    /* 0x10 */ u32 uv3;
    /* 0x14 */ u16 n0;
    /* 0x16 */ u16 v0;
    /* 0x18 */ u16 v1;
    /* 0x1A */ u16 v2;
    /* 0x1C */ u16 v3;
    /* 0x1E */ u16 pad1E;
} Face20_800CBA18;                                        /* 0x20 */

typedef struct {          /* libgpu POLY_FT4, 0x28 bytes */
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgb;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u32 uv0;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u32 uv1;
    /* 0x18 */ u32 xy2;
    /* 0x1C */ u32 uv2;
    /* 0x20 */ u32 xy3;
    /* 0x24 */ u32 uv3;
} Ft4_800CBA18;                                           /* 0x28 */

extern s16 D_800C7C74;      /* double-buffer parity index */
extern u32 D_80063880;      /* GTE RGB seed word */
extern u32 D_800CCA04;      /* flat colour used when func_800CC0A0() says so */

extern s32 func_800CC0A0(void *prim);
extern void func_800CC110(s32 ot, s32 otz, s32 shift, void *prim, u32 code);

Ft4_800CBA18 *func_800CBA18(Face20_800CBA18 *f, SVEC8_800CBA18 *verts,
                            SVEC8_800CBA18 *norms, Ft4_800CBA18 *prims,
                            s32 count, s32 shift, u32 *ot)
{
    struct { s32 flag, otz; } g;
    Ft4_800CBA18 *prim;

    prim = &prims[D_800C7C74];
    gte_ldrgb(&D_80063880);

    for (; count != 0; count--, f++, prim += 2) {
        gte_ldv3(&verts[f->v0], &verts[f->v1], &verts[f->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.otz);
            if (g.otz > 0) {
                gte_stsxy3_ft4(prim);
                gte_ldv0(&verts[f->v3]);
                gte_rtps();
                gte_stflg(&g.flag);
                if (!(g.flag & ~0x1000)) {
                    gte_stsxy(&prim->xy3);
                    gte_avsz4();
                    gte_stotz(&g.otz);
                    if (func_800CC0A0(prim)) {
                        prim->rgb = D_800CCA04;
                    } else {
                        gte_ldv0(&norms[f->n0]);
                        gte_nccs();
                        gte_strgb(&prim->rgb);
                    }
                    func_800CC110((s32)ot, g.otz, shift, prim, 0x09000000);
                }
            }
        }
    }

    return prim;
}


#include "common.h"

/* ---- geometry / primitive types local to this draft ---- */
typedef struct { s16 vx, vy, vz, pad; } SVEC2;      /* 0x08 */

typedef struct {                                     /* 0x1C */
    u32 w0;      /* 0x00 */
    u32 w1;      /* 0x04 */
    u32 w2;      /* 0x08 */
    u32 w3;      /* 0x0C */
    u16 n0;      /* 0x10 */
    u16 v0;      /* 0x12 */
    u16 n1;      /* 0x14 */
    u16 v1;      /* 0x16 */
    u16 n2;      /* 0x18 */
    u16 v2;      /* 0x1A */
} FaceT3;

typedef struct {                                     /* 0x28 */
    u32 tag;     /* 0x00 */
    u32 rgb0;    /* 0x04 */
    s16 x0, y0;  /* 0x08 */
    u16 u0, cl;  /* 0x0C */
    u32 rgb1;    /* 0x10 */
    s16 x1, y1;  /* 0x14 */
    u16 u1, tp;  /* 0x18 */
    u32 rgb2;    /* 0x1C */
    s16 x2, y2;  /* 0x20 */
    u16 u2, pd;  /* 0x24 */
} GT3P;

/* ---- PsyQ inline GTE macros (same spellings as the matched func_80027D20) ---- */

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_gt3(r0) __asm__ volatile (    \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 20( %0 );"                        \
    "swc2 $14, 32( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb3_gt3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $20, 0( %0 );"                         \
    "swc2 $21, 0( %1 );"                         \
    "swc2 $22, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

extern s16 D_800C7C74;
extern u32 D_80063884;
extern u32 D_800CCA10;
extern s32 func_800CC0A0(void *prim);
extern void func_800CC110(s32 ot, s32 otz, s32 shift, void *prim, u32 code);

GT3P *func_800CBC2C(FaceT3 *f, SVEC2 *verts, SVEC2 *norms, GT3P *prims,
                    s32 count, s32 shift, s32 ot)
{
    struct { s32 flag, opz; } g;
    GT3P *prim;

    prim = &prims[D_800C7C74];
    gte_ldrgb(&D_80063884);

    for (; count != 0; count--, f++, prim += 2) {
        gte_ldv3(&verts[f->v0], &verts[f->v1], &verts[f->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.opz);
            if (g.opz > 0) {
                gte_stsxy3_gt3(prim);
                gte_avsz3();
                gte_stotz(&g.opz);
                if (func_800CC0A0(prim) != 0) {
                    prim->rgb0 = D_800CCA10;
                    prim->rgb1 = D_800CCA10;
                    prim->rgb2 = D_800CCA10;
                } else {
                    gte_ldv3(&norms[f->n0], &norms[f->n0], &norms[f->n0]);
                    gte_ncct();
                    gte_strgb3_gt3(&prim->rgb0, &prim->rgb1, &prim->rgb2);
                }
                func_800CC110(ot, g.opz, shift, prim, 0x09000000);
            }
        }
    }

    return prim;
}


#include "common.h"

/* ---- PsyQ inline GTE macros (same spellings as the matched func_800262D8 body) ---- */

#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (          \
    "swc2 $14, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_gt4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 20( %0 );"                         \
    "swc2 $14, 32( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (          \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $20, 0( %0 );"                          \
    "swc2 $21, 0( %1 );"                          \
    "swc2 $22, 0( %2 )"                           \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )             \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC8_800CBE28;          /* 0x08 */

typedef struct {                                        /* 0x24 */
    u32 unk00;
    u32 uv0;
    u32 uv1;
    u32 uv2;
    u32 uv3;
    u16 n0, v0;      /* 0x14 / 0x16 */
    u16 n1, v1;      /* 0x18 / 0x1A */
    u16 n2, v2;      /* 0x1C / 0x1E */
    u16 n3, v3;      /* 0x20 / 0x22 */
} FaceGT4_800CBE28;

typedef struct {                                        /* 0x34 */
    u32 tag;
    u32 rgb0, xy0, uv0;   /* 0x04 0x08 0x0C */
    u32 rgb1, xy1, uv1;   /* 0x10 0x14 0x18 */
    u32 rgb2, xy2, uv2;   /* 0x1C 0x20 0x24 */
    u32 rgb3, xy3, uv3;   /* 0x28 0x2C 0x30 */
} PktGT4_800CBE28;

extern u32 D_80063888;
extern s16 D_800C7C74;
extern u32 D_800CCA14;

extern s32 func_800CC0A0(void *pkt);
extern void func_800CC110(s32 ot, s32 otz, s32 shift, void *prim, u32 code);

PktGT4_800CBE28 *func_800CBE28(FaceGT4_800CBE28 *face, SVEC8_800CBE28 *vtx,
                               SVEC8_800CBE28 *nrm, PktGT4_800CBE28 *arg3,
                               s32 count, s32 shift, s32 ot)
{
    long flag;
    long otz;
    PktGT4_800CBE28 *pkt;

    pkt = &arg3[D_800C7C74];

    gte_ldrgb(&D_80063888);

    while (count != 0) {
        gte_ldv3(&vtx[face->v0], &vtx[face->v1], &vtx[face->v2]);
        gte_rtpt();
        gte_stflg(&flag);
        if (!(flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&otz);
            if (otz > 0) {
                gte_stsxy3_gt4(pkt);
                gte_ldv0(&vtx[face->v3]);
                gte_rtps();
                gte_stflg(&flag);
                if (!(flag & ~0x1000)) {
                    gte_stsxy(&pkt->xy3);
                    gte_avsz4();
                    gte_stotz(&otz);
                    if (func_800CC0A0(pkt) != 0) {
                        pkt->rgb0 = D_800CCA14;
                        pkt->rgb1 = D_800CCA14;
                        pkt->rgb2 = D_800CCA14;
                        pkt->rgb3 = D_800CCA14;
                    } else {
                        gte_ldv3(&nrm[face->n0], &nrm[face->n0], &nrm[face->n0]);
                        gte_ncct();
                        gte_strgb3(&pkt->rgb0, &pkt->rgb1, &pkt->rgb2);
                        gte_ldv0(&nrm[face->n0]);
                        gte_nccs();
                        gte_strgb(&pkt->rgb3);
                    }
                    func_800CC110(ot, otz, shift, (void *)pkt, 0x0C000000);
                }
            }
        }
        count--;
        face++;
        pkt += 2;
    }
    return pkt;
}


extern s16 D_800CC9E8;
extern s16 D_800CC9EA;
extern s16 D_800CC9F0;
extern s16 D_800CC9F2;

s32 func_800CC0A0(void *prim)
{
    s32 val;

    val = *(u8 *)((s32)prim + 0xA);
    if (D_800CC9E8 < val && val < D_800CC9EA) {
        goto ret1;
    }
    if (D_800CC9F0 < val && val < D_800CC9F2) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}


void func_800CC110(s32 ot, s32 otz, s32 shift, void *prim, u32 code)
{
    s32 *entry;

    entry = (s32 *)ot + (otz >> shift);
    *(u32 *)prim = (*entry & 0xFFFFFF) | code;
    *entry = (s32)prim & 0xFFFFFF;
}


extern s32 func_800183E0(s32 *a0);
void func_800CC144(void) {

    extern s32 D_800CCA7C;
    func_800183E0(&D_800CCA7C);
}




void func_800CC16C(void *a0) {

    extern void (*D_800CCA18[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CCA18[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CC1E8();
void func_800CC1B0(void *a0) {
    func_800CC1E8(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern void func_801655E4(s32 arg0);
extern void func_801466F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern void func_80147324(s32 arg0);
extern s32 D_80078EC8;

void func_800CC1E8(s32 arg0) {
    func_801655E4(arg0);
    D_80078EC8 = 0x1C2;
    func_801466F0(0x1A, arg0, *(s16 *)(arg0 + 6), *(s16 *)(arg0 + 0xA), *(s16 *)(arg0 + 0xE), 0, 0, 1);
    func_80147324(0xA63);
    *(u8 *)(arg0 + 0x197) += 1;
}


extern void func_801599A4(void);
extern void func_80159B3C(void);
void func_800CC260(s32 a0) {
    func_801599A4();
    ((void (*)(s32))func_80159B3C)(a0);
}


void func_800CC290(void) {
}

void func_800CC298(void *a0) {

    extern u8 D_80078EC1;
    extern void (*D_800CCA24[])(void *);
    extern void func_800CC6A4();
    extern void func_800CC968(void *a0);
    extern void func_800CC9AC(void *a0);
    if (D_80078EC1 != 0x10) {
        func_800CC6A4();
    } else {
        func_800CC968(a0);
        func_800CC9AC(a0);
        D_800CCA24[*(u16 *)((s32)a0 + 0x2)](a0);
    }
}


#include "common.h"

/* NOTE (S56): named for THIS function's own base symbol, not (*(Quad4_800CCAD0 *)&D_800CCB14), so
 * strip_provided_typedefs does not remove it as "already provided" by
 * func_800CC4E8 (banked in the same batch) — whose copy is defined LATER in the
 * file than this function's address-ordered splice point, leaving these externs
 * with no visible type ("parse error before D_800CCAD0").
 * Struct for the 4-byte (unaligned, all-u8) quad block at (*(Quad4_800CCAD0 *)&D_800CCB14) / D_800CCAD4.
 * Whole-struct assignment below reproduces the target's lwl/lwr + swl/swr unaligned
 * word copy (fields are u8, so the struct's natural alignment is 1, matching the
 * "Quad" block-copy idiom noted on the seed_ref twin ov_SC02_011:func_8017FB14). */
typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} Quad4_800CCAD0;

extern void func_80146578(void);
extern void func_8001CD9C(void *a0, void *a1);
extern void func_800233CC(void *a0, u16 a1);
extern void func_80146CA0(void *a0);
extern void func_800CC6A4();   /* TU later defines this void(void) at line 78; call with an
                                 * unspecified-arglist decl here (house style, see func_800CC1E8
                                 * above) avoids a 1-arg-vs-0-arg prototype conflict when this
                                 * function's INCLUDE_ASM slot (earlier in file) is replaced. */

extern Quad4_800CCAD0 D_800CCAD0;   /* struct base passed to func_8001CD9C; D_800CCAD4 below is its +4 quad */
extern Quad4_800CCAD0 D_800CCAD4;
extern Quad4_800CCB14 D_800CCB14;
extern u8 D_800CCB10;
extern u8 D_800CCB11;
extern u8 D_800CCB12;

void func_800CC310(void *a0)
{
    void *s1;
    void *s0;

    s1 = ((void *(*)(void))func_80146578)();
    *(void **)((u8 *)a0 + 0x20) = s1;

    if (s1 != NULL) {
        s0 = &D_800CCAD0;
        func_8001CD9C(s1, s0);
        func_800233CC(s0, 0xC0);

        *(s16 *)((u8 *)s1 + 0x2C) = 1;
        *(s32 *)((u8 *)s1 + 4) |= 0x50000000;
        *(s16 *)((u8 *)s1 + 0x1A) = 0;
        *(s16 *)((u8 *)s1 + 0x18) = 0;
        *(s16 *)((u8 *)s1 + 0x10) = 0;
        *(s16 *)((u8 *)s1 + 0x12) = 0;
        *(s16 *)((u8 *)s1 + 0x14) = 0;

        *(s16 *)((u8 *)a0 + 0x5A) = 0;
        *(s16 *)((u8 *)a0 + 0x58) = 0;
        *(s16 *)((u8 *)a0 + 0x60) = 0;
        *(s16 *)((u8 *)a0 + 0x62) = 0;

        (*(Quad4_800CCAD0 *)&D_800CCB14).f0 = 0x20;
        (*(Quad4_800CCAD0 *)&D_800CCB14).f1 = 0;
        (*(Quad4_800CCAD0 *)&D_800CCB14).f2 = 0x20;
        D_800CCAD4 = (*(Quad4_800CCAD0 *)&D_800CCB14);

        D_800CCB10 = 0xFF;
        D_800CCB11 = 0xFF;
        D_800CCB12 = 0xFF;

        func_80146CA0(a0);
    } else {
        func_800CC6A4(a0);
    }
}




extern void func_800CC6C4(void *a0, void *a1, void *a2, void *a3);
extern void func_80146E90(void *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern u8 D_800CCB10;
extern Quad4_800CCB14 D_800CCB14;

void func_800CC424(void *a0) {
    void *a2 = *(void **)((u8 *)a0 + 0x20);
    *(u16 *)((u8 *)a0 + 0x60) += 0x60;
    *(u16 *)((u8 *)a2 + 0x1A) += 0x200;
    *(u16 *)((u8 *)a2 + 0x18) = *(u16 *)((u8 *)a2 + 0x1A);
    *(u16 *)((u8 *)a0 + 0x5A) += *(u16 *)((u8 *)a0 + 0x60);
    *(u16 *)((u8 *)a0 + 0x58) = *(u16 *)((u8 *)a0 + 0x5A);
    *(u16 *)((u8 *)a2 + 0x10) = (*(u16 *)((u8 *)a2 + 0x10) + 0x9F) & 0xFFF;
    *(u16 *)((u8 *)a2 + 0x12) = (*(u16 *)((u8 *)a2 + 0x12) + 0x71) & 0xFFF;
    func_800CC6C4(a0, &D_800CCB10, &D_800CCB14, (u8 *)a0 + 0x58);
    if (*(s16 *)((u8 *)a0 + 0x5A) >= 0x1001) {
        *(u16 *)((u8 *)a0 + 0x58) = 0x1000;
        *(u16 *)((u8 *)a0 + 0x5A) = 0x1000;
        func_80146E90(a0, 0x20);
        func_80146CA0(a0);
    }
}


#include "common.h"

extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_800CC6C4(void *a0, void *a1, void *a2, void *a3);

extern u8 D_800CCB10;

extern Quad4_800CCB14 D_800CCB14;

void func_800CC4E8(void *a0) {
    void *s1;
    register s32 t __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)

    s1 = *(void **)((u8 *)a0 + 0x20);
    func_80146E98((s32)a0);
    if (*(s32 *)((u8 *)a0 + 0x1c) < 8) {
        t = *(u16 *)((u8 *)a0 + 0x58) - 0x100;
        *(s16 *)((u8 *)a0 + 0x58) = t;
        if ((t << 16) < 0) {
            *(s16 *)((u8 *)a0 + 0x58) = 0;
        }

        t = *(u16 *)((u8 *)a0 + 0x5a) - 0x100;
        *(s16 *)((u8 *)a0 + 0x5a) = t;
        if ((t << 16) < 0) {
            *(s16 *)((u8 *)a0 + 0x5a) = 0;
        }

        t = *(u16 *)((u8 *)s1 + 0x1a) - 0x100;
        *(s16 *)((u8 *)s1 + 0x1a) = t;
        *(s16 *)((u8 *)s1 + 0x18) = t;
        if (*(s16 *)((u8 *)s1 + 0x1a) < 0) {
            *(s16 *)((u8 *)a0 + 0x60) = 0;
            *(s16 *)((u8 *)s1 + 0x1a) = 0;
            *(s16 *)((u8 *)s1 + 0x18) = 0;
            func_80146CA0(a0);
        }
    }

    {
        register u16 x __asm__("$2") = (*(u16 *)((u8 *)s1 + 0x10) + 0x2d) & 0xfff;  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
        u16 y = (*(u16 *)((u8 *)s1 + 0x12) + 0x16) & 0xfff;
        *(u16 *)((u8 *)s1 + 0x10) = x;
        *(u16 *)((u8 *)s1 + 0x12) = y;
        func_800CC6C4(a0, &D_800CCB10, &D_800CCB14, (u8 *)a0 + 0x58);
    }
}


void func_800CC5E4(void *a0) {
    void *a1;
    s32 v0;
    s32 v1;
    s32 t;

    a1 = *(void **)((u8 *)a0 + 0x20);
    *(u16 *)((u8 *)a1 + 0x1E) += 0x200;
    v0 = *(u16 *)((u8 *)a0 + 0x60) + 0xC0;
    *(u16 *)((u8 *)a0 + 0x60) = v0;
    v1 = *(u16 *)((u8 *)a1 + 0x1A) + v0;
    *(u16 *)((u8 *)a1 + 0x1A) = v1;
    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus10)
    t = *(s16 *)((u8 *)a1 + 0x1A);
    *(u16 *)((u8 *)a1 + 0x18) = v1;
    if (t >= 0xC01) {
        *(u16 *)((u8 *)a1 + 0x1A) = 0xC00;
        *(u16 *)((u8 *)a1 + 0x18) = 0xC00;
        func_80146CA0(a0);
    }
}


void func_800CC658(void *a0) {
    void *v1;
    s16 v;

    v1 = *(void **)((u8 *)a0 + 0x20);
    v = *(u16 *)((u8 *)v1 + 0x1E) + 0x80;
    *(u16 *)((u8 *)v1 + 0x1E) = v;
    if (v >= 0x1000) {
        func_800CC6A4(a0);
    }
}


extern void func_80162CCC(void);
void func_800CC6A4(void) {
    func_80162CCC();
}


#include "common.h"

extern void func_800CC7FC(s32 a0, void *a1, void *a2, void *a3, void *a4);

void func_800CC6C4(void *a0, void *a1, void *a2, void *a3) {
    extern s32 D_800CCA9C;
    void *v4;

    v4 = *(void **)((s32)a0 + 0x20);
    *(u16 *)((s32)a3 + 0x6) = *(u16 *)((s32)v4 + 0x12);
    func_800CC7FC((s32)a0, a1, a2, a3, &D_800CCA9C);

    *(u16 *)((s32)a3 + 0x6) = (*(u16 *)((s32)a3 + 0x6) + 0x555) & 0xFFF;
    func_800CC7FC((s32)a0, a1, a2, a3, &D_800CCA9C);

    *(u16 *)((s32)a3 + 0x6) = (*(u16 *)((s32)a3 + 0x6) + 0x555) & 0xFFF;
    func_800CC7FC((s32)a0, a1, a2, a3, &D_800CCA9C);

    *(u16 *)((s32)a3 + 0x6) = *(u16 *)((s32)v4 + 0x10);
    func_800CC7FC((s32)a0, a1, a2, a3, &D_800CCA9C);

    *(u16 *)((s32)a3 + 0x6) = (*(u16 *)((s32)a3 + 0x6) - 0x555) & 0xFFF;
    func_800CC7FC((s32)a0, a1, a2, a3, &D_800CCA9C);

    *(u16 *)((s32)a3 + 0x6) = (*(u16 *)((s32)a3 + 0x6) - 0x555) & 0xFFF;
    func_800CC7FC((s32)a0, a1, a2, a3, &D_800CCA9C);
}


#include "common.h"

typedef struct { char b[4]; } W;
typedef struct { s16 m[9]; s16 pad; s32 t[3]; s32 rest[8]; } Mtx;
typedef struct { s16 x, y, z; } Vec3s;

extern void func_80015978(s32 a0, void *a1);
extern void func_8012EFB8();
extern void func_80013F3C(s32 a0);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80017714();

void func_800CC7FC(s32 a0, void *a1, void *a2, void *a3, void *a4) {
    extern s32 D_800CCA3C;
    extern s32 D_800CCA44;
    extern s32 D_800CCA4C;
    extern s32 D_800CCA54;

    Mtx buf;
    Vec3s v1;
    Vec3s v2;

    *(u32 *)((s32)a4 + 0x30) = 0x50000000;
    *(W *)((s32)a4 + 0x20) = *(W *)a1;
    *(W *)((s32)a4 + 0x24) = *(W *)a1;
    *(W *)((s32)a4 + 0x28) = *(W *)a2;
    *(W *)((s32)a4 + 0x2c) = *(W *)a2;

    func_80015978(a0 + 4, &v1);
    ((void (*)())func_8012EFB8)(&v1, &v1);
    func_80013F3C((s32)&buf);
    func_800123F0((s32)&buf, *(s16 *)((s32)a3 + 6));

    v2.x = *(u16 *)((s32)a3 + 0);
    v2.y = *(u16 *)((s32)a3 + 2);
    v2.z = *(u16 *)((s32)a3 + 4);
    func_80020F34((s32)&buf, (s32)&v2);

    buf.t[0] = v1.x;
    buf.t[1] = v1.y;
    buf.t[2] = v1.z;
    func_8012F14C((s32)&buf, (s32)&D_800CCA3C, (s32)a4);
    func_8012F14C((s32)&buf, (s32)&D_800CCA44, (s32)a4 + 8);
    func_8012F14C((s32)&buf, (s32)&D_800CCA4C, (s32)a4 + 0x10);
    func_8012F14C((s32)&buf, (s32)&D_800CCA54, (s32)a4 + 0x18);

    *(s16 *)((s32)a4 + 4) = 0;
    *(s16 *)((s32)a4 + 0xc) = 0;
    *(s16 *)((s32)a4 + 0x14) = 0;
    *(s16 *)((s32)a4 + 0x1c) = 0;
    func_80017714(a4);
}


void func_800CC968(void *a0) {
    s32 *t = *(s32 **)((u8 *)a0 + 0x4C);
    *(u16 *)((u8 *)a0 + 6) = *(u32 *)((u8 *)*(s32 **)((u8 *)t + 0x20) + 0x48);
    *(u16 *)((u8 *)a0 + 10) = *(u32 *)((u8 *)*(s32 **)((u8 *)t + 0x20) + 0x4C);
    *(u16 *)((u8 *)a0 + 14) = *(u32 *)((u8 *)*(s32 **)((u8 *)t + 0x20) + 0x50);
}


void func_800CC9AC(void *a0) {
    extern u16 D_800B99DA;
    extern Quad4_800CCAD0 D_800CCAD0;
    extern u8 D_800CCAD1;
    extern u8 D_800CCAD2;
    int col;

    col = D_800B99DA & 1;
    if (col != 0) {
        col = 0xFF;
    } else {
        col = 0xEF;
    }
    (*(u8 *)&D_800CCAD0) = col;
    D_800CCAD1 = col;
    D_800CCAD2 = col;
}


INCLUDE_RODATA("asm/md_MAIN_034/nonmatchings/md_MAIN_034", D_800CAE80);
