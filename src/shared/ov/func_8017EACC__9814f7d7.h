/* func_8017EACC — shared body (overlay slot 0x80128158, h_exact 9814f7d7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017EACC(s32 *a0) {
    s32 *s0 = a0;
    s32 result;
    u16 temp;

    func_8017EC2C((s32)a0);

    if ((*(u16 *)((char *)s0 + 0xB8) & 0x8000) != 0) {
        if (func_801399F0(s0[0x198 / 4]) != 0) {
            func_80139914(s0[0x198 / 4]);
            result = func_8013767C((s32)D_80183080);
            temp = *(u16 *)((char *)s0 + 0xBA);
            s0[0x198 / 4] = result;
            *(u16 *)((char *)s0 + 0xB8) = temp;
            func_80171990((u8 *)s0);
        }
    }
}
