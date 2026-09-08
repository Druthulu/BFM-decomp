/* func_80147DC0 — shared body (overlay slot 0x80128158, h_exact 423ef84e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
void func_80147DC0(s32 a0, s32 a1) {
    s32 pad[4];
    s32 buf[8];
    s32 q = *(s32 *)(a0 + 0x20);
    func_80013F3C((s32)buf);
    func_800126C4((s32)buf, *(s16 *)(q + 0x10));
    func_80012558((s32)buf, *(s16 *)(q + 0x12));
    func_800123F0((s32)buf, *(s16 *)(q + 0x14));
    func_800484EC((s32)buf, a0 + 0x24, a1);
}
