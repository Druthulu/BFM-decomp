/* func_8012A094 — shared body (overlay slot 0x80128158, h_exact 133fc0f6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *memcpy(void *, const void *, unsigned int);
void func_8012A094(s32 a0) {
    *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0xC);
    *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x14);
    memcpy((void *)(a0 + 0x18), (void *)(a0 + 0x20), 8);
    *(u16 *)(a0 + 0x28) = *(u16 *)(a0 + 0x2E);
    *(u16 *)(a0 + 0x2A) = *(u16 *)(a0 + 0x30);
    *(u16 *)(a0 + 0x2C) = *(u16 *)(a0 + 0x32);
}
