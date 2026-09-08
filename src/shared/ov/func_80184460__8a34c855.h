/* func_80184460 — shared body (overlay slot 0x80128158, h_exact 8a34c855). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_80183E20(void *arg0);
void func_80184460(void *arg0) {
    s32 v1;
    v1 = *(s32 *)((char *)arg0 + 0xCC);
    *(s32 *)((char *)v1 + 0xB0) = 2;
    if (func_80184BAC(6, 0x14) != 0) {
        func_80183E20(arg0);
    }
}
