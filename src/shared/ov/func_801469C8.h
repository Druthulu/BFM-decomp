/* func_801469C8 — shared body (overlay slot 0x80128158, h_exact 887af675). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 D_8011D030;
s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8) {
    int count;
    int p;
    int end;
    count = 0;
    p = (int)&D_8011D030;
    end = p + 0xA50;
    if ((u32)p < (u32)end) {
        int key = a0 & 0xFFFF;
        do {
            if (*(u16 *)(p + 0x0) == key) {
                count++;
            }
            p += 0x58;
        } while ((u32)p < (u32)end);
    }
    if ((u32)count < (u32)arg8) {
        return func_80146A6C(a0 & 0xFFFF, a1, (s16)a2, (s16)a3, (s16)arg5, arg6, arg7);
    }
    return 0;
}
