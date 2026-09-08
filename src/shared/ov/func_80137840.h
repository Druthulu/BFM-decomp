/* func_80137840 — shared body (overlay slot 0x80128158, h_exact 387fc747). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80139634(void *);
extern void func_80139DC8(void);
void func_80137840(s32 a0) {
    s32 s0 = a0;
    *(u8 *)(s0 + 0xC) = 1;
    *(u8 *)(s0 + 0x23) = 1;
    *(s16 *)(s0 + 0x1A) = 1;
    *(s16 *)(s0 + 0x2A) = 0x1000;
    *(s16 *)(s0 + 0x28) = 0x1000;
    *(s16 *)(s0 + 0x2C) = 0x24;
    *(s16 *)(s0 + 0x2E) = 3;
    *(s16 *)(s0 + 0x4) = 0;
    *(s16 *)(s0 + 0x6) = 0;
    *(s16 *)(s0 + 0x1C) = 0;
    *(s16 *)(s0 + 0x10) = 0;
    *(s16 *)(s0 + 0x14) = 0;
    *(s16 *)(s0 + 0x12) = 0;
    *(s16 *)(s0 + 0x16) = 0;
    *(s16 *)(s0 + 0x30) = 0;
    *(s16 *)(s0 + 0x32) = 0;
    *(s16 *)(s0 + 0x34) = 0;
    *(s16 *)(s0 + 0x36) = 0;
    *(u8 *)(s0 + 0x22) = 0;
    *(u8 *)(s0 + 0x20) = 0;
    *(s32 *)(s0 + 0x40) = 0;
    *(s8 *)(s0 + 0x1F) = -1;
    *(s16 *)(s0 + 0x44) = 0;
    *(s16 *)(s0 + 0x46) = 0;
    *(s16 *)(s0 + 0x48) = 0;
    *(s16 *)(s0 + 0x4A) = 0;
    func_80139634((void *)s0);
    *(u8 *)(s0 + 0xD) = 0;
    func_80139DC8();
}
