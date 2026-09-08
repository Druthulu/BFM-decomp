/* func_80151238 — shared body (overlay slot 0x80128158, h_exact 2530eaf2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
void func_80151238(void *a0) {
    s16 v0 = *(s16 *)((s32)a0 + 0xF2);
    if (v0 != 0) {
        func_8014ACE8(a0, 5, (s32)v0 & 0x7FFF);
    }
}
