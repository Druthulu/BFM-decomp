/* func_801730FC — shared body (overlay slot 0x80128158, h_exact 5beb8dad). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171A1C(u8 *a0);
extern void func_80147060(u8 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern s32 func_80174650(s32);
extern s16 D_80126B30;
void func_801730FC(struct S801730FC *a0) {
    if (a0->unkB8 & 0x8000) {
        func_80171A1C((u8 *)a0);
        if (D_80126B30 != 0) {
            func_80147060(a0);
            func_80154150(a0, 0);
        }
        func_80174650((s32)a0);
    }
}
