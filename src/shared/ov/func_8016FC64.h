/* func_8016FC64 — shared body (overlay slot 0x80128158, h_exact c687a553). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171928(void *a0);
void func_8016FC64(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x20);
    u16 v0 = *(u16 *)((s32)a0 + 0x132);
    *(s16 *)((s32)a0 + 0x136) = 0;
    *(s16 *)(v1 + 0x12) = v0;
    func_80171928(a0);
}
