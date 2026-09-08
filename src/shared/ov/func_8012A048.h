/* func_8012A048 — shared body (overlay slot 0x80128158, h_exact dee370ac). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
void func_8012A048(void *a0, s32 a1, u8 a2) {
    *(s32 *)((s32)a0 + 0x0) = a1;
    *(u8 *)((s32)a0 + 0x4) = a2;
    *(s32 *)((s32)a0 + 0x9C) = 0;
    *(s16 *)((s32)a0 + 0xA0) = 0;
    *(s16 *)((s32)a0 + 0xA2) = 0;
    D_80126940 = D_80126B5E;
    D_80126942 = D_80126B62;
    D_80126944 = D_80126B66;
}
