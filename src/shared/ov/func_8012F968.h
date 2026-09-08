/* func_8012F968 — shared body (overlay slot 0x80128158, h_exact 8f98afeb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801151D4;
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_80131A34(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_80131CA8(s32 a0, s32 a1);
void func_8012F968(s32 param_1) {
    s32 iVar3;
    s32 iVar2;
    u32 uVar4;
    struct { s16 a; s16 b; s16 c; } sp;
    iVar3 = D_801151D4;
    *(u8 *)(param_1 + 0xc1) = 0x12;
    if ((*(u32 *)(param_1 + 0xb4) & 0x10000) != 0) {
        sp.a = *(s32 *)(iVar3 + 0x5c);
        sp.b = *(s32 *)(iVar3 + 0x60);
        sp.c = *(s32 *)(iVar3 + 0x64);
        iVar2 = *(s32 *)(param_1 + 0x20);
        *(s16 *)(param_1 + 0x5c) = 0;
        *(s16 *)(param_1 + 0x54) = 0;
        *(s16 *)(param_1 + 0x52) = 0;
        *(s16 *)(param_1 + 0x50) = 0;
        *(s16 *)(iVar2 + 0x14) = 0;
        *(s16 *)(iVar2 + 0x10) = 0;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = ((s16 (*)(s32, s32))func_8012B744)(param_1 + 4, (s32)&sp);
        *(s32 *)(param_1 + 0x1c) = 0x2d;
        if (*(u32 *)(param_1 + 0x58) != 0) {
            uVar4 = *(u32 *)(param_1 + 0x58) & 0xfffffff | 0x80000000;
            *(s16 *)(param_1 + 0xac) =
                (s16)((s32)*(s16 *)(uVar4 + 8) + (s32)*(s16 *)(uVar4 + 10) >> 1);
        } else {
            *(s16 *)(param_1 + 0xac) = 0;
        }
        *(s32 *)(param_1 + 0x10) =
            ((*(s32 *)(iVar3 + 0x5c) - (s32)*(s16 *)(param_1 + 6)) * 0x10000) / 0x1e;
        *(s32 *)(param_1 + 0x14) =
            (((*(s32 *)(iVar3 + 0x60) - (s32)*(s16 *)(param_1 + 10)) -
              (s32)*(s16 *)(param_1 + 0xac)) * 0x10000) / 0x1e;
        *(s32 *)(param_1 + 0x18) =
            ((*(s32 *)(iVar3 + 0x64) - (s32)*(s16 *)(param_1 + 0xe)) * 0x10000) / 0x1e;
        *(s16 *)(param_1 + 0x98) = 0;
        if (func_80131A34(param_1, 0x24) == 0) {
            *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) & 0xfffffffb;
            if (func_80131A34(param_1, 0x20) != 0) {
                *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) | 4;
            } else {
                *(s16 *)(param_1 + 0x98) = 0;
            }
        }
        ((void (*)(s32, s32))func_8012C588)(0x289, param_1);
    }
    func_80131CA8(param_1, 0x35);
}
