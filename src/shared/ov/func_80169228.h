/* func_80169228 — shared body (overlay slot 0x80128158, h_exact fedcb0b4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);
s32 func_80169228(void)
{
    register s32 a0v __asm__("$4");
    s32 arg0 = a0v;
    u8 buf[0x60];               /* $sp+0x10 .. $sp+0x6F */
    register u8 *p __asm__("$16");   /* $sp+0x48 (matrix, a1 to the calls) -> $s0 */
    s32 col;
    s16 base;
    s16 v;
    /* first-draw SVECTOR verts — source order == target store order */
    *(s16 *)(buf + 0x08) = -5;   /* 0x18 */
    *(s16 *)(buf + 0x00) = -5;   /* 0x10 */
    *(s16 *)(buf + 0x18) = 5;    /* 0x28 */
    *(s16 *)(buf + 0x10) = 5;    /* 0x20 */
    *(s16 *)(buf + 0x12) = -5;   /* 0x22 */
    *(s16 *)(buf + 0x02) = -5;   /* 0x12 */
    *(s16 *)(buf + 0x1a) = 5;    /* 0x2A */
    *(s16 *)(buf + 0x0a) = 5;    /* 0x1A */
    *(s16 *)(buf + 0x1c) = 0;    /* 0x2C */
    *(s16 *)(buf + 0x14) = 0;    /* 0x24 */
    *(s16 *)(buf + 0x0c) = 0;    /* 0x1C */
    *(s16 *)(buf + 0x04) = 0;    /* 0x14 */
    /* colors */
    if ((*(u32 *)(arg0 + 0x2c) & 2) == 0) {
        col = -0x40 - (*(s32 *)(arg0 + 0x1c) << 4);
        *(u8 *)(buf + 0x21) = *(u8 *)(buf + 0x22) =
        *(u8 *)(buf + 0x25) = *(u8 *)(buf + 0x26) =
        *(u8 *)(buf + 0x29) = *(u8 *)(buf + 0x2a) =
        *(u8 *)(buf + 0x2d) = *(u8 *)(buf + 0x2e) = col;
        *(u8 *)(buf + 0x20) = *(u8 *)(buf + 0x24) =
        *(u8 *)(buf + 0x28) = *(u8 *)(buf + 0x2c) = col;
    } else {
        col = -0x40 - (*(s32 *)(arg0 + 0x1c) << 4);
        *(u8 *)(buf + 0x20) = *(u8 *)(buf + 0x24) =
        *(u8 *)(buf + 0x2a) = *(u8 *)(buf + 0x2e) = 0x20;
        *(u8 *)(buf + 0x21) = *(u8 *)(buf + 0x25) =
        *(u8 *)(buf + 0x29) = *(u8 *)(buf + 0x2d) = col;
        *(u8 *)(buf + 0x29) = *(u8 *)(buf + 0x2d) = 0x20;
    }
    *(s32 *)(buf + 0x30) = 0x50000000;   /* 0x40 tag */
    base = 0x800;
    if (*(u32 *)(arg0 + 0x2c) & 1) base = 0x4cc;
    v = base + (*(s32 *)(arg0 + 0x1c) << 7);
    *(u16 *)(buf + 0x5c) = v;   /* 0x6C */
    *(u16 *)(buf + 0x5a) = v;   /* 0x6A */
    *(u16 *)(buf + 0x58) = v;   /* 0x68 */
    p = buf + 0x38;
    func_80017DC4(buf + 0x58, p);
    func_80048EAC((void *)(arg0 + 0x38), p);
    *(s32 *)(buf + 0x4c) = (s32)*(s16 *)(arg0 + 6);    /* 0x5C */
    *(s32 *)(buf + 0x50) = (s32)*(s16 *)(arg0 + 0xa);  /* 0x60 */
    *(s32 *)(buf + 0x54) = (s32)*(s16 *)(arg0 + 0xe);  /* 0x64 */
    func_80017758(buf + 0x00, p);
    /* second-draw SVECTOR verts */
    *(s16 *)(buf + 0x00) = -7;   /* 0x10 */
    *(s16 *)(buf + 0x10) = 0;    /* 0x20 */
    *(s16 *)(buf + 0x08) = 0;    /* 0x18 */
    *(s16 *)(buf + 0x18) = 7;    /* 0x28 */
    *(s16 *)(buf + 0x1a) = 0;    /* 0x2A */
    *(s16 *)(buf + 0x02) = 0;    /* 0x12 */
    *(s16 *)(buf + 0x0a) = 7;    /* 0x1A */
    *(s16 *)(buf + 0x12) = -7;   /* 0x22 */
    func_80017758(buf + 0x00, p);
}
