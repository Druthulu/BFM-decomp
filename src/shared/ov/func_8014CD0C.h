/* func_8014CD0C — shared body (overlay slot 0x80128158, h_exact bd738852). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014CF04(s32 a0, s32 a1, void *a2);
extern int func_8014CD80(s32 a0, u16 *a1, u16 *a2);
void func_8014CD0C(u8 *a0) {
    u16 sp10[3];
    u16 sp18[3];
    u16 b;
    u16 c;
    u16 d;
    b = *(u16 *)(a0 + 0x6);
    sp18[0] = b;
    sp10[0] = b;
    c = *(u16 *)(a0 + 0xA);
    sp10[1] = c - 3;
    d = *(u16 *)(a0 + 0xE);
    sp18[1] = c + 5;
    sp18[2] = d;
    sp10[2] = d;
    if (*(s32 *)(a0 + 0x174) == 0) {
        func_8014CF04((s32)a0, sp10, sp18);
    } else {
        func_8014CD80((s32)a0, sp10, sp18);
    }
}
