/* func_80187E78 — shared body (overlay slot 0x80128158, h_exact e97c35bd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_801C6FB4;
extern s32 D_801C6FBC;
void func_80187E78(s32 a0)
{
    s32 val;
    *(s32*)(a0 + 0x8) += 0x100000;
    val = func_8004787C(*(s16*)(*(s32*)(a0 + 0x20) + 0x12));
    *(s32*)(a0 + 0x4) -= val << 8;
    val = func_80047948(*(s16*)(*(s32*)(a0 + 0x20) + 0x12));
    *(s32*)(a0 + 0xC) -= val << 8;
    if (--*(s16*)(a0 + 0xFE) == 0) {
        *(s16*)(a0 + 0x2) = 6;
        func_8012D5E4(a0, (s32)&D_801C6FB4, (s32)&D_801C6FBC, 0xF);
        *(s16*)(a0 + 0xFE) = 8;
    }
}
