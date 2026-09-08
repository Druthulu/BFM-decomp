/* func_8017D194 — shared body (overlay slot 0x80128158, h_exact b55f2b3b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
void func_8017D194(void *a0) {
    if (func_80146E98((s32)a0)) {
        func_80146E90((s32 *)a0, 8);
        *(u16 *)((s32)a0 + 0x28) = 0x20;
        *(u16 *)((s32)a0 + 2) += 1;
    }
}
