/* func_8013C08C — shared body (overlay slot 0x80128158, h_exact f769ff89). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013C0F8(s32 a0);
void func_8013C08C(void *a0, void *a1) {
    void *p = a1;
    ((E_13C08C_8013C08C *)a0)->f8 = a1;
    ((E_13C08C_8013C08C *)a0)->fC = (u8 *)p + 0x14;
    func_8013C0F8((s32)a1);
}
