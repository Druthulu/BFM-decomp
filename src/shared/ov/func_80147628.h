/* func_80147628 — shared body (overlay slot 0x80128158, h_exact f659c94d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80013F3C(s32 a0);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
void func_80147628(s32 a0) {
    s32 s2 = *(s32 *)(a0 + 0x20);
    s32 s1 = s2 + 0x34;
    func_80013F3C(s1);
    func_80012558(s1, *(s16 *)(a0 + 0x102));
    func_800126C4(s1, *(s16 *)(a0 + 0x100));
    func_800123F0(s1, *(s16 *)(a0 + 0x104));
    if (*(u16 *)(a0 + 0x136) & 2) {
        func_80012558(s1, *(s16 *)(a0 + 0x132));
    } else {
        func_80012558(s1, *(s16 *)(s2 + 0x12));
    }
    if (*(u16 *)(a0 + 0x136) & 1) {
        func_800126C4(s2 + 0x34, *(s16 *)(a0 + 0x130));
    } else {
        func_800126C4(s2 + 0x34, *(s16 *)(s2 + 0x10));
    }
    if (*(u16 *)(a0 + 0x136) & 4) {
        func_800123F0(s2 + 0x34, *(s16 *)(a0 + 0x134));
    } else {
        func_800123F0(s2 + 0x34, *(s16 *)(s2 + 0x14));
    }
}
