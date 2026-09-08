/* func_80154190 — shared body (overlay slot 0x80128158, h_exact 66eda991). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154418(void *a0);
void func_80154190(u8 *a0, s32 a1) {
    s32 v1 = *(s32 *)((a1 << 2) + *(s32 *)(a0 + 0xB0));
    *(s16 *)(a0 + 0xBA) = 1;
    *(s16 *)(a0 + 0xB8) = 1;
    *(s8 *)(a0 + 0xBC) = 0;
    *(s8 *)(a0 + 0xBD) = 0;
    *(s8 *)(a0 + 0xDC) = 0;
    *(s32 *)(a0 + 0xB4) = v1;
    func_80154418((void *)a0);
}
