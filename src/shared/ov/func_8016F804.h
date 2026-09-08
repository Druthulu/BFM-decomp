/* func_8016F804 — shared body (overlay slot 0x80128158, h_exact 230a3ff4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171928(void *);
void func_8016F804(void *a0) {
    if (*(u8 *)((s32)a0 + 0x1C2) != 0) {
        *(u8 *)((s32)a0 + 0x1C2) = 0;
        func_80171928(a0);
    }
}
