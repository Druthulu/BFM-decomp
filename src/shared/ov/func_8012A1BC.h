/* func_8012A1BC — shared body (overlay slot 0x80128158, h_exact 497f8cc9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012A1BC(void) {
    extern s16 D_80120218;
    extern s16 D_80120222;
    extern s16 D_80120224;
    extern s16 D_80120226;
    extern s16 D_80120228;
    extern s16 D_8012022A;
    extern s16 D_8012029A;
    extern s32 D_80120200, D_80120204, D_80120208, D_8012020C;
    extern s16 D_80120210;
    extern s16 D_80120220;
    extern s32 D_80120294;
    extern s16 D_80120298;
    extern s32 D_80126950, D_80126954, D_80126958, D_8012695C;
    extern Blk8 D_80126960, D_80126968;
    extern u16 D_80126970, D_80126972, D_80126974, D_80126976, D_80126978, D_8012697A;
    extern s32 D_801269E4;
    extern u16 D_801269E8, D_801269EA;
    register s32 r2 __asm__("$2"), r3 __asm__("$3"), r4 __asm__("$4"), r5 __asm__("$5");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
    u16 r6, r7;
    s32 r8;
    u16 r9, r10;
    r2 = D_80120200; r3 = D_80120204; r4 = D_80120208; r5 = D_8012020C;
    r6 = (*(u16 *)&D_80120228); r7 = (*(u16 *)&D_8012022A); r8 = D_80120294; r9 = (*(u16 *)&D_80120298); r10 = (*(u16 *)&D_8012029A);
    D_80126950 = r2; D_80126954 = r3; D_80126958 = r4; D_8012695C = r5;
    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)
    D_80126960 = (*(Blk8 *)&D_80120210);
    r2 = (*(u16 *)&D_80120220); r3 = (*(u16 *)&D_80120222); r4 = (*(u16 *)&D_80120224); r5 = (*(u16 *)&D_80120226);
    D_80126968 = (*(Blk8 *)&D_80120218);
    D_80126978 = r6; D_8012697A = r7; D_801269E4 = r8; D_801269E8 = r9; D_801269EA = r10;
    D_80126970 = r2; D_80126972 = r3; D_80126974 = r4; D_80126976 = r5;
}
