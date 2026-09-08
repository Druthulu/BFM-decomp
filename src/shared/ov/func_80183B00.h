/* func_80183B00 — shared body (overlay slot 0x80128158, h_exact 94d66b29). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8018E8A0[])(void);
void func_80183B00(void *a0) {
    D_8018E8A0[*(u16 *)((s32)a0 + 0x2)]();
}
