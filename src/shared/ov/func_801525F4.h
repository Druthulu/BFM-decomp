/* func_801525F4 — shared body (overlay slot 0x80128158, h_exact 5dc4521e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801470AC(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80153C18();
void func_801525F4(s32 a0)
{
    s32 v1;
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(s8 *)(a0 + 0xA8) = 0x20;
    func_80154A74(a0, 0x11);
    func_801553C0(a0);
    func_801470AC((s32 *)a0);
    func_801472B4((void *)a0);
    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(a0 + 0x3E) = 0;
    *(s16 *)(a0 + 0x40) = 0;
    *(s16 *)(a0 + 0x42) = 0;
    *(s8 *)(a0 + 0xDD) = 0;
    *(s16 *)(a0 + 0x3C) = *(u16 *)(a0 + 0x3C) & 0xFFFE;
    *(s16 *)(v1 + 0x10) = 0;
    *(s16 *)(a0 + 0x60) = 0x1000;
    *(s16 *)(a0 + 0x62) = 0x1000;
    *(s16 *)(a0 + 0x64) = 0x1000;
    func_801477E8((s32 *)a0, 0);
    func_80153C18(a0);
}
