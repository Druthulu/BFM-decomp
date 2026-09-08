/* func_80142740 — shared body (overlay slot 0x80128158, h_exact 3ec3edde). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012AD50(void *a0);
void func_80142740(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_8012AD50)(param_1);
    }
}
