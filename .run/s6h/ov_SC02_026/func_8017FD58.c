/* func_8017FD58 -- ov_SC02_026 / ov_SC02_026_jr_8017C180
 * TU-verbatim decls (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c):
 *   extern u8 D_801202A0[];                                     (line 387, 586)
 *   extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);   (line 592)
 *   extern s32 func_80047948(s32 a0);                           (line 2206)
 *   extern s32 func_8004787C(s32 a0);                           (line 2207)
 * Not in this TU: func_8012B6D4 (fleet-standard sig), D_801A9EB8 (2-entry fn-ptr
 * table in ov_SC02_026 tail.data: func_80180B0C / func_80180B90).
 */

extern u8 D_801202A0[];
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void (*D_801A9EB8[])(void *);

void func_8017FD58(void *arg0) {
    typedef struct {
        u16 x;   /* 0x00 */
        u16 y;   /* 0x02 */
        u16 z;   /* 0x04 */
        u16 w;   /* 0x06 */
    } V4_8017FD58;                 /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
    typedef struct {
        u16 f0;                    /* 0x00 */
        u16 f2;                    /* 0x02 */
        u16 f4;                    /* 0x04 */
        u16 x;                     /* 0x06 */
        u16 f8;                    /* 0x08 */
        u16 y;                     /* 0x0A */
        u16 fC;                    /* 0x0C */
        u16 z;                     /* 0x0E */
        u8  p10[0x10];
        s32 f20;                   /* 0x20 */
        u8  p24[0x34];
        s32 f58;                   /* 0x58 */
        u8  p5C[8];
        s32 f64;                   /* 0x64 */
        u8  p68[0x10C - 0x68];
    } Ent_8017FD58;                /* stride 0x10C, 0x60 entries (0x6480) */

    /* Two further V4 slots the original body declared ahead of `pos` but that
     * this function never reads: the target frame is 0x50 with locals at
     * 0x10..0x37 and the first live vector at 0x20, i.e. 0x10 bytes of stack
     * precede `pos`. Dropping them yields a 0x40 frame and shifts every sp
     * displacement by 0x10 (36 mismatches). */
    V4_8017FD58 unused[2];
    V4_8017FD58 pos;
    V4_8017FD58 tmp;
    V4_8017FD58 dst;
    Ent_8017FD58 *p;
    Ent_8017FD58 *e;
    s32 i;
    s32 ang;

    p = (Ent_8017FD58 *)arg0;
    D_801A9EB8[p->f2](p);
    e = (Ent_8017FD58 *)D_801202A0;
    for (i = 0; i < 0x60; i++, e++) {
        if (e->f0 == 0x12C) {
            pos.x = e->x;
            pos.y = e->y;
            pos.z = e->z;
            ang = func_8012B6D4((s16 *)&p->f4, (s16 *)&e->f4);
            if (*(s16 *)(p->f64 + 0xFC) < 0) {
                ang -= 0x400;
            } else {
                ang += 0x400;
            }
            ang &= 0xFFF;
            pos.x -= func_8004787C(ang) >> 8;
            pos.z -= func_80047948(ang) >> 8;
            tmp.x = e->x;
            tmp.y = e->y;
            tmp.z = e->z;
            dst = tmp;
            if (func_80135888(p->f20, p->f58, (s32)&pos, (s32)&dst) != 0) {
                e->x = pos.x;
                e->z = pos.z;
            }
        }
    }
}
