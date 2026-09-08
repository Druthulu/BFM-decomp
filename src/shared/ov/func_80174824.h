/* func_80174824 — shared body (overlay slot 0x80128158, h_exact 0c985c28). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern s32 func_80174888(void *a0);
void func_80174824(void) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_80174888, 0x1000000);
}
