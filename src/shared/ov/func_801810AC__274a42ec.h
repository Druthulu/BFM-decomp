/* func_801810AC — shared body (overlay slot 0x80128158, h_exact 274a42ec). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801BC5E0[];
void func_801810AC(void *a0)
{
    if (*(s16 *)((s32)a0 + 0x98) != 0) {
        return;
    }
    func_8012A828((s32)a0, D_801BC5E0);
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}
