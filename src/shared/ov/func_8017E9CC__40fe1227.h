/* func_8017E9CC — shared body (overlay slot 0x80128158, h_exact 40fe1227). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017E9CC(u8 *a0) {
    s32 v0;
    func_8017EC2C((s32)a0);
    v0 = *(s32 *)(a0 + 0x200) - 1;
    *(s32 *)(a0 + 0x200) = v0;
    if (v0 == -1) {
        func_80171990(a0);
    }
}
