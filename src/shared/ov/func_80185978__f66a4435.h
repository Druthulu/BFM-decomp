/* func_80185978 — shared body (overlay slot 0x80128158, h_exact f66a4435). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_801B8788[];
extern s32 D_801B8748[][2];
void func_80185978(s32 a0) {
    *(s16 *)(a0 + 0x2) = 3;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 2;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = D_801B8748[D_801B8788[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x84) = 0;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
}
