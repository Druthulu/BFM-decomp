/* func_80144988 — shared body (overlay slot 0x80128158, h_exact 5a76fee4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80144988(s32 a0) {
    s32 t;
    *(u16*)(a0 + 0xA) = *(u16*)(a0 + 0xA) - 0x40;
    *(s32*)(a0 + 0x10) = *(s32*)(*(s32*)(a0 + 0x64) + 0x10);
    *(s32*)(a0 + 0x14) = *(s32*)(*(s32*)(a0 + 0x64) + 0x14);
    t = *(s32*)(*(s32*)(a0 + 0x64) + 0x18);
    *(u16*)(a0 + 0x2) = *(u16*)(a0 + 0x2) + 1;
    *(s32*)(a0 + 0x18) = t;
}
