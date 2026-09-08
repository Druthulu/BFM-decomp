/* func_801319E0 — shared body (overlay slot 0x80128158, h_exact 8f5613a8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131CA8(int a0, int a1);
extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);
void func_801319E0(s32 arg0) {
    /* arg0 stays in $s0 (callee-saved) across all three calls -- live across each jal,
     * so clean C allocates it there naturally (no register pin needed). */
    if (((s32 (*)(int, int))func_80131CA8)(arg0, 0x11) == 0) {
        if (*(s32 *)(arg0 + 0x78) != 0) {
            func_8002A04C(arg0);
        }
        func_8012C218((void *)arg0);
    }
}
