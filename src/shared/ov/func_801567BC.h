/* func_801567BC — shared body (overlay slot 0x80128158, h_exact bec5d9c6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_8011DAD8[];
extern s32 D_801151E0[];
extern s32 func_8014C568(s16 *a0, s16 *a1);
void func_801567BC(s32 a0) {
    s32 obj = a0;
    s32 i = 0;
    u8 *q = D_8011DAD8;
    s32 *p = D_801151E0;
    do {
        if (*p & 1) {
            *(s16 *)(*(s32 *)(obj + 0x20) + 0x12) =
                ((s32 (*)(void *, void *))func_8014C568)((void *)obj, q);
        }
        q += 8;
        i += 1;
        p += 1;
    } while ((u32)i < 3);
}
