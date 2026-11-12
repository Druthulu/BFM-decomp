/* func_80157A8C — shared body (overlay slot 0x80128158, h_exact fcbffb31). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80161D20();
extern void guess_SpawnSmallObjectType2(s32 a0, s32 a1);
void func_80157A8C(s32 a0) {
    func_80161D20(a0, *(u16 *)(a0 + 0x16E));
    guess_SpawnSmallObjectType2(a0, 1);
}
