/* func_801898BC — shared body (overlay slot 0x80128158, h_exact 00c057a5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801EAC94;
extern u8 D_801EAC95;
extern u8 D_801EAC96;
void func_801898BC(void *a0) {
    s16 *p;
    s32 t;
    u8 v;
    p = *(s16 **)((s32)a0 + 0x20);
    if (*(s16 *)((s32)p + 0x18) > 0x800) {
        *(s16 *)((s32)p + 0x18) = *(s16 *)((s32)p + 0x18) - 0x200;
    }
    if (*(s16 *)((s32)p + 0x1A) > 0x800) {
        *(s16 *)((s32)p + 0x1A) = *(s16 *)((s32)p + 0x1A) - 0x200;
    }
    t = *(s32 *)((s32)a0 + 0x1C) + 1;
    *(s32 *)((s32)a0 + 0x1C) = t;
    if (t & 0x10) {
        v = ((t & 0xF) >> 1) + 9;
    } else {
        v = 0x10 - ((t & 0xF) >> 1);
    }
    D_801EAC94 = v * 12;
    D_801EAC95 = v * 4;
    D_801EAC96 = v * 4;
}
