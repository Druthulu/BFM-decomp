/* func_80188748 — shared body (overlay slot 0x80128158, h_exact 326f37d3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80188748(void *a0) {
        s32 *p = *(s32 **)((s32)a0 + 0x20);
        p[1] = p[1] | 0x58000000;
        *(s16 *)((s32)p + 0x1E) = 0;
        *(s16 *)((s32)p + 0x18) = 0;
        *(s16 *)((s32)p + 0x1A) = 0;
        *(s16 *)((s32)p + 0x1C) = 0;
        *(s32 *)((s32)a0 + 0x2C) = 0x400;
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }
