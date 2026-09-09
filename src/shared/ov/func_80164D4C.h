/* func_80164D4C — shared body (overlay slot 0x80128158, h_exact b1e906d1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80164E40(void);
extern void func_80146CA0(void *a0);
void func_80164D4C(void *arg0) {
    s32 a;
    register s32 iVar3 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers1)
    s16 sVar1;
    a = (s32)arg0;
    iVar3 = *(s32 *)(a + 0x20);
    if (((s32 (*)(void))func_80164E40)() != 0) {
        func_80146CA0((void *)a);
    } else {
        sVar1 = *(s16 *)(iVar3 + 0x1a) + 0x100;
        *(s16 *)(iVar3 + 0x1a) = sVar1;
        *(s16 *)(iVar3 + 0x18) = sVar1;
    }
}
