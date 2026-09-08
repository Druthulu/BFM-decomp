/* func_80172D14 — shared body (overlay slot 0x80128158, h_exact 6aa89ac7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
extern s16 D_80126B30;
void func_80172D14(u8 * a0)
{
    if (func_80171AB0(a0, &D_80126B30) == 0) {
        func_80171A1C((u8 *)a0);
        func_80174650(a0);
    }
}
