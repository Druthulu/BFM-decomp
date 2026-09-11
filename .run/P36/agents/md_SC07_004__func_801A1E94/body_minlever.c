void func_801A1E94(void)
{
    register s32 arg __asm__("$4");  // !FAKE: pin $4 — the caller's argument read by a function the TU declares (void): no pass can supply it: the incoming $a0 is only named by a PARAMETER (function.c:3157 assign_parms); a SIGNATURE lever (fix = `(s32 a0)` + the TU externs/callers, signature.diff), parked for the structs phase (P36 S104 e1 minimum-lever)
    s32 a0 = arg;
    s32 *sp = &D_801BF01C;

    func_8001C924(*(s32 *)(a0 + 0x20), sp);
    func_80132288(&D_801F8724, &D_801AFB58, *sp);
    *(s16 *)(a0 + 0xA) = -0x240;
    *(s16 *)(a0 + 0xE) = 0x30;
    *(s32 *)(a0 + 0xD4) = func_801A8528(a0);
    func_80178B18(a0, (s32)&D_801AFCF8);
    *(s32 *)(a0 + 0x1C) = 0x60;
    *(s16 *)(a0 + 0x100) = 0xFF;
    *(s16 *)(a0 + 0x84) = 0;
    func_8012AD44((s32 *)a0, 0xE);
}
