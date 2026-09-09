/* func_80169A4C — shared body (overlay slot 0x80128158, h_exact 99f67073). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);
s32 func_80169A4C(s32 a0, s32 a1) {
    void *arg0 = (void *)a0;
    void *arg1 = (void *)a1;
    u8 buf[0x5C];               /* spans $sp+0x10 .. $sp+0x6B */
    u8 *p = buf + 0x38;          /* $sp+0x48, passed to first 3 calls */
    u8 v1;
    s8 v0;
    u16 t2c;
    u8 *q;    /* $sp+0x68, first call a0 */
    s32 m5;   /* -5 -> $v1 */
    s32 p5;   /* 5  -> $v0 */
    q = buf + 0x58;
    __asm__("" : : "r"(q));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
    m5 = -5;
    __asm__("" : : "r"(m5));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
    p5 = 5;
    *(s16 *)(buf + 0x18) = p5;   /* 0x28 */
    *(s16 *)(buf + 0x10) = p5;   /* 0x20 */
    *(s16 *)(buf + 0x1a) = p5;   /* 0x2A */
    *(s16 *)(buf + 0x0a) = p5;   /* 0x1A */
    *(s16 *)(buf + 0x08) = m5;   /* 0x18 */
    *(s16 *)(buf + 0x00) = m5;   /* 0x10 */
    *(s16 *)(buf + 0x12) = m5;   /* 0x22 */
    *(s16 *)(buf + 0x02) = m5;   /* 0x12 */
    *(s16 *)(buf + 0x1c) = 0;    /* 0x2C */
    *(s16 *)(buf + 0x14) = 0;    /* 0x24 */
    *(s16 *)(buf + 0x0c) = 0;    /* 0x1C */
    *(s16 *)(buf + 0x04) = 0;    /* 0x14 */
    v1 = *(u8 *)((u8 *)arg0 + 0x30);
    *(s32 *)(buf + 0x30) = 0x50000000;  /* 0x40 */
    v0 = (s8)(v1 >> 2);
    *(u8 *)(buf + 0x2e) = v1;     /* 0x3E */
    *(u8 *)(buf + 0x2a) = v1;     /* 0x3A */
    *(u8 *)(buf + 0x26) = v1;     /* 0x36 */
    *(u8 *)(buf + 0x22) = v1;     /* 0x32 */
    *(s8 *)(buf + 0x2d) = v0;     /* 0x3D */
    *(s8 *)(buf + 0x29) = v0;     /* 0x39 */
    *(s8 *)(buf + 0x25) = v0;     /* 0x35 */
    *(s8 *)(buf + 0x21) = v0;     /* 0x31 */
    *(s8 *)(buf + 0x2c) = v0;     /* 0x3C */
    *(s8 *)(buf + 0x28) = v0;     /* 0x38 */
    *(s8 *)(buf + 0x24) = v0;     /* 0x34 */
    *(s8 *)(buf + 0x20) = v0;     /* 0x30 */
    t2c = *(u16 *)((u8 *)arg0 + 0x2c);
    *(u16 *)(q + 0x02) = t2c;  /* 0x6A */
    *(u16 *)(q + 0x00) = t2c;  /* 0x68 */
    func_80017DC4(q, p);
    func_80048EAC(arg1, p);
    *(s32 *)(buf + 0x4c) = (s32)*(s16 *)((u8 *)arg0 + 6);   /* 0x5C */
    *(s32 *)(buf + 0x50) = (s32)*(s16 *)((u8 *)arg0 + 0xa); /* 0x60 */
    *(s32 *)(buf + 0x54) = (s32)*(s16 *)((u8 *)arg0 + 0xe); /* 0x64 */
    func_80017758(buf + 0x00, p);
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
