/* func_80170374 — shared body (overlay slot 0x80128158, h_exact d314b53f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C168(s32 *a0, s32 a1);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_80171928(void *a0);
extern void *D_8011F738;
void func_80170374(u8 * a0)
{
    s16 sp[4];
    s32 v0;
    v0 = func_8014C168(a0, (s32)D_8011F738);
    sp[0] = *(u16 *)(v0 + 0x6);
    sp[1] = *(u16 *)(v0 + 0xA);
    sp[2] = *(u16 *)(v0 + 0xE);
    if (func_80171AB0((s32)a0, sp) == 0) {
        func_80171928(a0);
    }
}
