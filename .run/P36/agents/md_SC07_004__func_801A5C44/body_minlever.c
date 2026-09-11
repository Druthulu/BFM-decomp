void func_801A5C44(void) {
    register s32 arg __asm__("$4");  // !FAKE: pin $4 — the caller's argument read by a function the TU declares (void): no pass can supply it: the incoming $a0 is only named by a PARAMETER (function.c:3157 assign_parms); a SIGNATURE lever (fix = `(s32 a0)` + the TU externs/callers, signature.diff), parked for the structs phase (P36 S104 e1 minimum-lever)
    s32 a0 = arg;
    s32 s2 = *(s32 *)(a0 + 0xCC);
    s32 s1 = *(s32 *)(a0 + 0xD4);

    *(s16 *)(s2 + 0x18) = *(u16 *)(s1 + *(s16 *)(a0 + 0x70) * 4) + (func_8004787C(*(s16 *)(a0 + 0x100)) >> 4);
    *(s16 *)(s2 + 0x1A) = *(u16 *)(s1 + *(s16 *)(a0 + 0x70) * 4 + 2) + (func_8004787C(*(s16 *)(a0 + 0x100) + 0x800) >> 4);
    *(u16 *)(a0 + 0x100) += 0x40;
}
