/* func_801733FC — shared body (overlay slot 0x80128158, h_exact 3e4f0095). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801734BC(s32 a0, s32 a1);
void func_801733FC(s32 a0, s32 a1) {
    extern struct S80126B38 D_80126B38;
    extern s16 D_80126B3E;
    extern s16 D_80126B40;
    func_801734BC(a0, a1);
    D_80126B38 = *(struct S80126B38 *)a1;
    D_80126B3E = 1;
    D_80126B40 = 1;
}
