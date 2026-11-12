/* func_801788B8 — shared body (overlay slot 0x80128158, h_exact 3555a568). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_SpawnActor(s32 arg0, s32 arg1, s32 arg2);
extern void guess_SetObjectPosAndYaw(s32 a0, s32 a1);
extern void guess_UpdateActorModelMatrix(s32 a0);
s32 func_801788B8(s32 arg0, s32 arg1) {
    s32 iVar1;
    u16 buf[4];
    iVar1 = guess_SpawnActor(0x83, (s32)*(s16 *)((u8 *)arg0 + 0x70), 0);
    if (iVar1 == 0) {
        return 0;
    }
    *(s32 *)((u8 *)iVar1 + 0x64) = arg0;
    buf[0] = *(u16 *)((u8 *)arg0 + 0x6);
    buf[1] = *(u16 *)((u8 *)arg0 + 0xA);
    buf[2] = *(u16 *)((u8 *)arg0 + 0xE);
    if (*(s32 *)((u8 *)arg0 + 0x20) != 0) {
        buf[3] = *(u16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x20)) + 0x12);
    } else {
        buf[3] = 0;
    }
    guess_SetObjectPosAndYaw(iVar1, (s32)buf);
    guess_UpdateActorModelMatrix(iVar1);
    *(s32 *)((u8 *)iVar1 + 0xDC) = arg1;
    return iVar1;
}
