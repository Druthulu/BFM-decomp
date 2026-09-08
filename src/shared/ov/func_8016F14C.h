/* func_8016F14C — shared body (overlay slot 0x80128158, h_exact edf31e68). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80148634(void *a0);
void func_8016F14C(void *a0) {
    s32 v1 = *(s32 *)((u8 *)a0 + 0x1F8);
    s32 fp = v1 & 0x80FFFFFF;
    if (v1 != 0) {
        if (v1 & 0x1000000) {
            func_80148634(a0);
        }
        ((void (*)(void *))fp)(a0);
    }
}
