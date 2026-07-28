/* func_80177B5C (ov_SC01_077) — NEAR: 147/147 ins, closeness 11 (match_one).
 * GPU SPRT-chain builder: 2 lead sprites, a 3-iteration digit loop, 2 tail sprites.
 * Registers ALL match; stack frame + all 6 callee saves match; TAIL region is byte-exact.
 * Residual = 11 pure sched-order swaps in 3 spots:
 *   [18-21] prologue: gcc emits `lui s2,0x300` (c3) before the loop-mask `lui/ori t8`; target reversed.
 *   [24-27] prologue: `lui t0,0x300` (ca) lands 3 slots early (target puts it after the `lw` of arg5).
 *   [86-89] loop: gcc reassociates `cl | (X | 0x4000)` -> `(cl|0x4000) | X`, so it emits
 *           ori/sll/addiu/or instead of the target's sll/addiu/ori/or. Not defeatable via
 *           temps, tie-barriers, volatile barriers, operand swap, or << vs * (all tried).
 * Levers that got it here (all byte-measured): 12 register pins; K&R-wide params with explicit
 * (s16) casts; "raw copy then narrow in place" for arg3/arg5; mk1/cc1 explicit prologue constants;
 * ca pinned to $t0 (this alone moved the whole t-reg file into place: 101 -> 75);
 * value-temp + tie/volatile barrier + delayed store for each packet's word-2;
 * keep-alive asm on tr/xr at the end (stops in-place clobber of $s5/$s1).
 */
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

/* derived from asm %hi/%lo refs (sig_hints.data was empty):
   lbu $t9, %lo(D_8018A300)($at) with $at = %hi(D_8018A300) + (s16)param3  */
extern u8 D_8018A300[];

/* caller decl (src/ov_SC01_077/ov_SC01_077_jr_801734BC.c:3068):
   extern u32 *func_80177B5C(u32 *a0, s32 a1, s32 a2, s32 a3, s32 a4);  */
u32 *func_80177B5C(p, bits, tbli, x, y)
u32 *p;
u32 bits;
s32 tbli;
s32 x;
s32 y;
{
    register u32 bb __asm__("$14");
    u32 *q;
    register u32 v __asm__("$25");
    register u32 cl __asm__("$3");
    register u32 cs __asm__("$5");
    register u32 ca __asm__("$8");
    s16 i;
    u32 mk1;
    u32 cc1;
    u32 flag;
    u32 nn;
    register u32 n __asm__("$7");
    register u32 t __asm__("$13");
    u32 col;
    u32 uv;
    u32 tt;
    u32 nv;
    u32 x1;
    u32 x2;
    u32 w;
    u32 g;
    u32 w3;
    register u32 yr __asm__("$16");
    register u32 yt __asm__("$4");
    register u32 tr __asm__("$21");
    register u32 xr __asm__("$17");
    register u32 c3 __asm__("$18");
    register s32 ff __asm__("$19");
    register s32 two __asm__("$20");

    yt = y;
    tr = tbli;
    __asm__("" : "=r"(tr) : "0"(tr));
    xr = x;
    __asm__("" : "=r"(xr) : "0"(xr));
    mk1 = 0xFFFFFF;
    cc1 = 0x74808080;
    bb = bits;
    t = x + 0xE;
    flag = 0x1000000;
    i = 0;
    two = 2;
    ff = 255;
    c3 = 0x3000000;
    ca = 0x3000000;
    v = D_8018A300[(s16)tbli];

    p[0] = ((u32)(p - 5) & mk1) | ca;
    x1 = (x - 3) & 0xFFFF;
    x2 = (x + 5) & 0xFFFF;
    p[1] = cc1;
    yr = yt;
    __asm__("" : "=r"(yr) : "0"(yr));
    yt = (s16)yt;
    cs = (yt + 1) << 16;
    w = cs | x1;
    __asm__("" : "=r"(w) : "0"(w));
    cl = ((v << 6) | 0x4016) << 16;
    p[2] = w;
    p[3] = cl | 0x1800;
    p += 5;
    p[0] = ((u32)(p - 5) & mk1) | ca;
    p[1] = cc1;
    p[2] = cs | x2;
    p[3] = cl | 0x1808;
    p += 5;

    q = p;
    yt = yt << 16;
    {
        for (; i < 3; i++) {
            nn = (bb << 16) >> 28;
            n = nn;
            if (((nn != 0) || (i == two)) || (i == ff)) {
                flag = 0;
            }
            q[0] = ((u32)(q - 5) & 0xFFFFFF) | c3;
            q[2] = (yt | (t & 0xFFFF)) | flag;
            col = 0x74808080;
            q[1] = col;
            q[3] = cl | (((n * 8) + 8) | 0x4000);
            q += 5;
            t += 8;
            bb <<= 4;
        }
    }
    p = q;

    __asm__("" : "=r"(v) : "0"(v));
    g = ((u32)(p - 5) & 0xFFFFFF) | 0x3000000;
    __asm__ __volatile__("");
    cs = yr << 16;
    p[0] = g;
    w3 = cs | ((xr + 0x2A) & 0xFFFF);
    __asm__ __volatile__("");
    cl = ((v << 6) | 0x4016) << 16;
    uv = ((s16)tr) << 4;
    p[2] = w3;
    tt = uv | 0x1000;
    p[1] = col;
    p[3] = cl | tt;
    p += 5;
    p[0] = ((u32)(p - 5) & 0xFFFFFF) | 0x3000000;
    __asm__ __volatile__("");
    cs = cs | ((xr + 0x32) & 0xFFFF);
    uv = uv | 0x1008;
    cl = cl | uv;
    p[1] = col;
    p[2] = cs;
    p[3] = cl;
    p += 5;
    __asm__("" :: "r"(tr), "r"(xr));
    return p;
}
