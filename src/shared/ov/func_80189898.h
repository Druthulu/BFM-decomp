/* func_80189898 — shared body (overlay slot 0x80128158, h_exact 5af4cb24). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012E544(s32 a0);
extern s32 func_8012AD50(void *a0);
void func_80189898(void) {
    s32 result = func_8012E544(0x338);
    if (result != 0) {
        func_8012AD50((void *)result);
    }
}
