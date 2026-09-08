/* func_80168B70 — shared body (overlay slot 0x80128158, h_exact 93d5fccd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80168B70(s32 a0)
{
    s32 v0;
    s32 *ptr = (s32 *)a0;
    v0 = ptr[7] - 1;
    ptr[7] = v0;
    if (v0 != -1) {
        func_80168BDC(a0, 9, 3, 1);
    } else {
        func_80168BDC(a0, 9, 2, 1);
        func_80146C3C((u8 *)a0);
    }
}
