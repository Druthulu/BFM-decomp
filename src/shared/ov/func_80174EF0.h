/* func_80174EF0 — shared body (overlay slot 0x80128158, h_exact bfc27ca5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012A018(s32 a, s32 b);
extern s32 D_8012697C;
extern u16 D_80126980;
extern s32 func_80174F28(void *a0);
void func_80174EF0(s32 a0, s16 a1) {
    D_8012697C = a0;
    D_80126980 = a1;
    func_8012A018((s32)func_80174F28, 1);
}
