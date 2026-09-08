/* func_80157CCC — shared body (overlay slot 0x80128158, h_exact cd768a06). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801553A8(s32 *a0);
void func_80157CCC(s32 a0) {
    s32 s0 = a0;
    *(u8 *)(s0 + 0x223) = 0x10;
    *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) & ~2;
    func_80154A74(s0, 0x11);
    func_801553C0(s0);
    func_801553A8((s32 *)s0);
}
