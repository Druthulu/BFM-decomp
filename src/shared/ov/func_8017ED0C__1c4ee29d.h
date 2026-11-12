/* func_8017ED0C — shared body (overlay slot 0x80128158, h_exact 1c4ee29d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017ED0C(s32 self) {
    extern void guess_AddVertSpeed(s32 a0, s32 a1);
    extern void guess_ApplyVertSpeed(s32 a0);
    extern void func_80161450(void *a0);
    extern void func_80147060(u8 *a0);
    extern void func_80171928(void *a0);

    guess_AddVertSpeed(self, 0x1A000);
    guess_ApplyVertSpeed(self);
    if (((((s32 (*)(void *))func_80161450)((void *)self)) & 5) == 0) {
        return;
    }
    func_80147060((u8 *)self);
    func_80171928((void *)self);
}
