/* func_8012F8C8 — shared body (overlay slot 0x80128158, h_exact 9dff3451). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012F8C8(u8* arg0) {
    *(u8*)(arg0 + 0xC1) = 7;
    if (*(u32*)(arg0 + 0xB4) & 0x80) {
        ((void (*)(void*, void*, s32))func_80131170)(arg0, D_8017EE40, 0xB);
    }
    ((void (*)(void*, s32))func_80131CA8)(arg0, 0x16);
}
