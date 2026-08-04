// func_8018EDB0 — ov_SC06_032 / ov_SC06_032_jr_8017C24C
// Sibling of func_8018F060 (ov_SC06_018 / ov_SC06_018_jr_8017C24C, banked MATCH, same jr group
// "jr_8017C24C"). The .s is byte-identical in structure to the banked sibling: same prologue
// (func_8004914C/func_800491AC on ((s32*)param_1)[8]+0x34), same two 3-iteration RotTransSV loops
// (src[i].vx/vy from a per-overlay SVEC array selected by (param_2&1)*3, vz = -param_3[0] then
// -param_3[1]), same B4 spill-copy of param_4 into pkt[8] + pkt[9]=0x50000000, same DRAW() GTE
// macro (gte_ldv3/rtpt/stflg/stsxy3/ldv0/rtps/stflg/or-flags/stsxy/avsz4/stotz + OT-range guarded
// func_80017254 insert) repeated 3x with the shared D_800AF630+0x18 draw-mode calls. Only the
// per-overlay source-vector symbol differs (D_801CC7FC here vs D_801D1228 there); all other data
// symbols (D_800AF630, D_800B9A02, D_800A651C, D_800AE610) and callees are declared identically to
// the banked sibling, verbatim (S34/S36: reuse the byte-proven declaration + expression forms).
//
// DECLARATION SURFACE (whole-TU one-pass grep, D2):
//   * func_8004914C(void *a0) / func_800491AC(void *a0) / RotTransSV(void*,void*,void*) are ALL
//     already `extern` at this TU's file scope (lines 2637-2639) — do NOT redeclare here.
//   * D_800B9A02 is `extern short D_800B9A02;` at file scope (line 2451/2453) — do NOT redeclare;
//     unsigned access is forced at the USE with `*(u16 *)&D_800B9A02` (TU's own canonical spelling,
//     already used at TU lines 2842/6033).
//   * D_800AF630, D_800A651C, D_800AE610, func_80017254, D_801CC7FC appear nowhere else in this TU
//     — declare fresh, matching the banked sibling's exact canonical shapes.
//   * func_8018EDB0 has no caller anywhere in src/ (INCLUDE_ASM stub only) — signature unconstrained.

typedef struct { u16 vx, vy, vz, pad; } SVEC_8018EDB0;       /* u16 source vec -> lhu */
typedef struct { s16 vx, vy, vz, pad; } SVECTOR_8018EDB0;    /* 8 bytes, align 2 */
typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_8018EDB0;
typedef struct { u8 d[4]; } __attribute__((packed, aligned(1))) B4_8018EDB0;

extern void func_80017254(void *a0);
extern SVEC_8018EDB0 D_801CC7FC[];
extern short D_800B9A02;
extern u8 D_800A651C[];
extern u8 D_800AE610[];
extern u8 D_800AF630[];

#define gte_ldv0(r0) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" "lwc2 $1, 4( %0 )" : : "r"( r0 ) )
#define gte_ldv3(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" "lwc2 $1, 4( %0 );" "lwc2 $2, 0( %1 );" \
    "lwc2 $3, 4( %1 );" "lwc2 $4, 0( %2 );" "lwc2 $5, 4( %2 )" \
    : : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_stsxy(r0) __asm__ volatile ( \
    "swc2 $14, 0( %0 )" : : "r"( r0 ) : "memory" )
#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );" "swc2 $13, 0( %1 );" "swc2 $14, 0( %2 )" \
    : : "r"( r0 ), "r"( r1 ), "r"( r2 ) : "memory" )
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_stotz(r0) __asm__ volatile ( \
    "swc2 $7, 0( %0 )" : : "r"( r0 ) : "memory" )
#define gte_stflg(r0) __asm__ volatile ( \
    "cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"( r0 ) : "$12", "memory" )

#define DRAW() \
    mb = (u8 *)&D_800AF630; \
    __asm__("" : "=r"(mb) : "0"(mb)); \
    func_8004914C(mb + 0x18); \
    __asm__("" : "=r"(mb) : "0"(mb)); \
    func_800491AC(mb + 0x18); \
    pc = (long *)&pkt[0]; \
    p1 = (long *)&pkt[2]; \
    p2 = (long *)&pkt[4]; \
    p3 = (long *)&pkt[6]; \
    pfl = &flag1; \
    p0 = pc; \
    gte_ldv3(p0, p1, p2); \
    gte_rtpt(); \
    gte_stflg(pfl); \
    __asm__ __volatile__("" :: "r"(pfl)); \
    gte_stsxy3(p0, p1, p2); \
    gte_ldv0(p3); \
    gte_rtps(); \
    gte_stflg(&flag2); \
    flag1 |= flag2; \
    gte_stsxy(p3); \
    gte_avsz4(); \
    gte_stotz(&otz); \
    oz = otz; \
    *(s16 *)((u8 *)pkt + 4) = (s16)oz; \
    if (oz > 0 && flag1 >= 0 && \
        !((u32)&D_800AE610 < (u32)(*(s32 *)((u8 *)&D_800A651C \
            + (*(u16 *)&D_800B9A02) * 0x14) + oz * 4))) { \
        func_80017254(pc); \
    }

void func_8018EDB0(s32 param_1, u32 param_2, u16 *param_3, u32 param_4) {
    u8      dead[0x20];   /* 0x10 : reserved, never referenced (holds the frame at 0xC8) */
    SVECTOR_8018EDB0 scratch;      /* 0x30 */
    B8_8018EDB0 out[6];   /* 0x38 */
    u32     pkt[10];      /* 0x68 : v0..v3 + color(0x88) + code(0x8C) */
    SVECTOR_8018EDB0 rtflag;       /* 0x90 (8 bytes -> 0x94 gap) */
    s32     flag1;        /* 0x98 */
    s32     flag2;        /* 0x9C */
    s32     otz;          /* 0xA0 */
    SVEC_8018EDB0 *src;
    s32 i, oz;
    long *p0, *p1, *p2, *p3, *pfl;
    u8 *mb;
    register long *pc __asm__("$16");

    func_8004914C((void *)(((s32 *)param_1)[8] + 0x34));
    func_800491AC((void *)(((s32 *)param_1)[8] + 0x34));

    src = &D_801CC7FC[(param_2 & 1) * 3];
    for (i = 0; i < 3; i++) {
        scratch.vx = src[i].vx;
        scratch.vy = src[i].vy;
        scratch.vz = -param_3[0];
        RotTransSV(&scratch, &out[i], &rtflag);
    }
    for (i = 0; i < 3; i++) {
        scratch.vx = src[i].vx;
        scratch.vy = src[i].vy;
        scratch.vz = -param_3[1];
        RotTransSV(&scratch, &out[3 + i], &rtflag);
    }

    *(B4_8018EDB0 *)&pkt[8] = *(B4_8018EDB0 *)&param_4;
    pkt[9] = 0x50000000;

    /* face 0: verts 0,1,3,4 */
    *(B8_8018EDB0 *)&pkt[0] = out[0];
    *(B8_8018EDB0 *)&pkt[2] = out[1];
    *(B8_8018EDB0 *)&pkt[4] = out[3];
    *(B8_8018EDB0 *)&pkt[6] = out[4];
    DRAW();

    /* face 1: verts 1,2,4,5 */
    *(B8_8018EDB0 *)&pkt[0] = out[1];
    *(B8_8018EDB0 *)&pkt[2] = out[2];
    *(B8_8018EDB0 *)&pkt[4] = out[4];
    *(B8_8018EDB0 *)&pkt[6] = out[5];
    DRAW();

    /* face 2: verts 2,0,5,3 */
    *(B8_8018EDB0 *)&pkt[0] = out[2];
    *(B8_8018EDB0 *)&pkt[2] = out[0];
    *(B8_8018EDB0 *)&pkt[4] = out[5];
    *(B8_8018EDB0 *)&pkt[6] = out[3];
    DRAW();
}
