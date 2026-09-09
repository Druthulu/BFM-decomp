/* func_80186CE8 — shared body (overlay slot 0x80128158, h_exact da9c4677). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012A828(s32, void *);
extern void func_8012B200(u8 *a0);
extern s16 D_801E0294[];
extern M2C_UNK D_8018AF28;
extern u8 D_8018F39C[];
void func_80186CE8(s32 a0) {
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers2)
    s32 v1;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C214(v0, (s32)D_801E0294);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0xDC, 0xB8);
    v0 = *(u16 *)(a0 + 0x5C);
    v1 = (s32)D_8018F39C;
    *(s32 *)(a0 + 0x58) = v1;
    v0 = v0 | 0xC00;
    *(u16 *)(a0 + 0x5C) = (u16)v0;
    func_8012A828(a0, &(*(s32 *)&D_8018AF28));
    func_8012B200((u8 *)a0);
    v0 = *(u16 *)(a0 + 0x2);
    v0 = v0 + 1;
    *(u16 *)(a0 + 0x2) = (u16)v0;
}
