/* func_8016FAC0 — shared body (overlay slot 0x80128158, h_exact 81a39fc4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801719A4(int a0, int a1);
extern s32 func_80171990(u8 *a0);
extern void func_8016FB10(void *a0);
void func_8016FAC0(u8 *a0) {
    u8 *v1;
    *(s16 *)(a0 + 0x136) = 2;
    v1 = *(u8 **)(a0 + 0x20);
    *(s16 *)(a0 + 0x132) = *(u16 *)(v1 + 0x12);
    func_801719A4((int)a0, 2);
    func_80171990(a0);
    func_8016FB10(a0);
}
