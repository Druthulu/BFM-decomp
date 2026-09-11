/* func_80169584 — shared body (overlay slot 0x80128158, h_exact c462f0a5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80017758(void *a0, void *a1);
void func_80169584(s32 param_1) {
    u8 buf[0x60];   /* spans $sp+0x10 .. (named local_<0x78-off>) */
    s32 v1;
    s32 v0;
    s32 s0;   /* param_1 + 0x38, held across both calls */
    *(s16 *)(buf + 0x00) = 7;     /* 0x10 = local_68 */
    *(s16 *)(buf + 0x18) = -7;    /* 0x28 = local_50 */
    *(s16 *)(buf + 0x10) = 0;     /* 0x20 = local_58 */
    *(s16 *)(buf + 0x08) = 0;     /* 0x18 = local_60 */
    *(s16 *)(buf + 0x0a) = 2;     /* 0x1A = local_5e */
    *(s16 *)(buf + 0x1a) = 0;     /* 0x2A = local_4e */
    *(s16 *)(buf + 0x02) = 0;     /* 0x12 = local_66 */
    *(s16 *)(buf + 0x12) = -2;    /* 0x22 = local_56 */
    *(s16 *)(buf + 0x1c) = 0;     /* 0x2C = local_4c */
    *(s16 *)(buf + 0x14) = 0;     /* 0x24 = local_54 */
    *(s16 *)(buf + 0x0c) = 0;     /* 0x1C = local_5c */
    *(s16 *)(buf + 0x04) = 0;     /* 0x14 = local_64 */
    *(u8 *)(buf + 0x22) = 0;      /* 0x32 = local_46 */
    *(u8 *)(buf + 0x20) = 0;      /* 0x30 = local_48 */
    *(u8 *)(buf + 0x2e) = 0;      /* 0x3E = local_3a */
    *(u8 *)(buf + 0x2c) = 0;      /* 0x3C = local_3c */
    *(u8 *)(buf + 0x2d) = 0;      /* 0x3D = local_3b */
    *(u8 *)(buf + 0x21) = 0;      /* 0x31 = local_47 */
    if (*(s32 *)(param_1 + 0x2c) == 0) {
        v1 = -0x40 - (*(s32 *)(param_1 + 0x1c) << 4);
        v0 = ((u32)(v1 & 0xff)) >> 2;
        *(s8 *)(buf + 0x29) = v1;    /* 0x39 = local_3f */
        *(s8 *)(buf + 0x25) = v1;    /* 0x35 = local_43 */
        *(s8 *)(buf + 0x2a) = v0;    /* 0x3A = local_3e */
        *(s8 *)(buf + 0x26) = v0;    /* 0x36 = local_42 */
    } else {
        v1 = -0x40 - (*(s32 *)(param_1 + 0x1c) << 4);
        v0 = ((u32)(v1 & 0xff)) >> 2;
        *(s8 *)(buf + 0x29) = v1;    /* 0x39 */
        *(s8 *)(buf + 0x25) = v1;    /* 0x35 */
        *(s8 *)(buf + 0x2a) = v1;    /* 0x3A */
        *(s8 *)(buf + 0x26) = v1;    /* 0x36 */
    }
    do { *(s8 *)(buf + 0x28) = v0;        /* 0x38 = local_40 */ } while (0);  // !FAKE: do-while — a LOOP-note scheduling barrier (sched.c:2058-2074; P36 R7)
    *(s8 *)(buf + 0x24) = v0;        /* 0x34 = local_44 */
    *(s32 *)(buf + 0x30) = 0x50000000;   /* 0x40 = local_38 */
    s0 = param_1 + 0x38;
    *(s32 *)(param_1 + 0x4c) = (s32)*(s16 *)(param_1 + 0x06);
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x0a);
    *(s32 *)(param_1 + 0x54) = (s32)*(s16 *)(param_1 + 0x0e);
    func_80017758(buf + 0x00, (void *)s0);
    *(s16 *)(buf + 0x02) = 7;     /* 0x12 = local_66 */
    *(s16 *)(buf + 0x1a) = -7;    /* 0x2A = local_4e */
    *(s16 *)(buf + 0x08) = 2;     /* 0x18 = local_60 */
    *(s16 *)(buf + 0x12) = 0;     /* 0x22 = local_56 */
    *(s16 *)(buf + 0x0a) = 0;     /* 0x1A = local_5e */
    *(s16 *)(buf + 0x18) = 0;     /* 0x28 = local_50 */
    *(s16 *)(buf + 0x00) = 0;     /* 0x10 = local_68 */
    *(s16 *)(buf + 0x10) = -2;    /* 0x20 = local_58 */
    func_80017758(buf + 0x00, (void *)s0);
}
