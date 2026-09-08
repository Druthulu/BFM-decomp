/* func_80143B6C — shared body (overlay slot 0x80128158, h_exact 0911480d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
s32 func_80143B6C(s32 arg0, s32 arg1) {
    s32 iVar1;
    iVar1 = func_8012C658(0x1C, arg1, arg0);
    if (((iVar1 != 0) && (*(s32*)(arg0 + 0x20) != 0)) && (arg1 == 0)) {
        *(s16*)(iVar1 + 0xFC) = *(u16*)(*(s32*)(arg0 + 0x20) + 0x12);
    }
    return iVar1;
}
