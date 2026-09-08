/* func_80151C54 — shared body (overlay slot 0x80128158, h_exact 1902c5e6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_8014BD60(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801470AC(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80153C18();
void func_80151C54(s32 a0)
{
    s32 s0 = a0;
    /* `!= 1 && == 0x11` (not the simplified `== 0x11`) is load-bearing: it is what
     * emits the beq-1 / bne-0x11 pair, with the 0x11 constant in the beq delay slot. */
    if (*(u8 *)(s0 + 0xDD) != 1 && *(u8 *)(s0 + 0xDD) == 0x11) {
        func_8014BD60(s0, *(s16 *)(s0 + 0xF2));
    } else {
        func_8014BC44(s0, *(s16 *)(s0 + 0xF2));
    }
    *(s8 *)(s0 + 0xA8) = 0x20;
    func_80154A74(s0, 0x11);
    func_801553C0(s0);
    func_801470AC((s32 *)s0);
    func_801472B4((void *)s0);
    *(s16 *)(s0 + 0x3E) = 0;
    *(s16 *)(s0 + 0x40) = 0;
    *(s16 *)(s0 + 0x42) = 0;
    *(s8 *)(s0 + 0xDD) = 0;
    *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    *(s16 *)(s0 + 0x60) = 0x1000;
    *(s16 *)(s0 + 0x62) = 0x1000;
    *(s16 *)(s0 + 0x64) = 0x1000;
    func_801477E8((s32 *)s0, 0);
    func_80153C18(s0);
}
