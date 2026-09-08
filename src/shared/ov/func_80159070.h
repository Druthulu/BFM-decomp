/* func_80159070 — shared body (overlay slot 0x80128158, h_exact ed5b882c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);
extern u8 D_80110C94[];
extern u8 D_80110CD4[];
void func_80159070(void *a0) {
    s32 obj;
    s32 r;
    s32 v;
    u8 *tbl;
    obj = *(s32 *)((u8 *)a0 + 0x20);
    *(u16 *)(obj + 0x12) = (*(u16 *)(obj + 0x12) + 0x16) & 0xFFF;
    r = func_801399F0(*(s32 *)((u8 *)a0 + 0x198));
    *(s16 *)((u8 *)a0 + 0x244) = r;
    if ((s16)r != 0) {
        func_80139914(*(s32 *)((u8 *)a0 + 0x198));
        v = *(s16 *)((u8 *)a0 + 0x244);
        *(s32 *)((u8 *)a0 + 0x198) = 0;
        switch (v) {
        default:
        case 1:
            tbl = D_80110C94;
            break;
        case 2:
            tbl = D_80110CD4;
            break;
        }
        *(s32 *)((u8 *)a0 + 0x198) = func_8013767C((s32)tbl);
        func_80146CA0(a0);
    }
}
