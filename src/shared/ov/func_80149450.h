/* func_80149450 — shared body (overlay slot 0x80128158, h_exact bef71548). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F038(int param_1, short *param_2, short *param_3);
void func_80149450(s32 a0, s16 *a1) {
    s16 *s0 = a1;
    s16 sp10[3];
    s16 sp18[3];
    sp18[0] = *(u16 *)((char *)s0 + 0x2);
    sp18[1] = *(u16 *)((char *)s0 + 0x6);
    sp18[2] = *(u16 *)((char *)s0 + 0xA);
    ((void (*)(s32, s32, s32))func_8012F038)(*(s32 *)(a0 + 0x20) + 0x34, (s32)sp18, (s32)sp10);
    *(s16 *)((char *)s0 + 0x2) = *(u16 *)((char *)sp10 + 0x0);
    *(s16 *)((char *)s0 + 0x6) = *(u16 *)((char *)sp10 + 0x2);
    *(s16 *)((char *)s0 + 0xA) = *(u16 *)((char *)sp10 + 0x4);
}
