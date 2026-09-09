/* func_80166054 — shared body (overlay slot 0x80128158, h_exact a4984404). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80166054(s32 arg0) {
    extern void func_80149374(s32 a0, s32 a1);
    extern s32 func_8004787C(s32 a0);
    extern s32 func_80047948(s32 a0);
    extern void func_800D1FC8(s32 a0, s32 a1);
    extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
    extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
    extern void func_801661CC(s32 a0);
    extern void func_80146C3C();
    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
    s32 param_1; /* $s2 */
    register s32 s0 __asm__("$16");      /* $s0 */  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1)
    register s32 s1 __asm__("$17");      /* $s1 */  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers1)
    s32 r0;      /* $s3 */
    s32 r1;      /* $s4 */
    s32 v1;
    s32 iVar2;
    s32 iVar3;
    register u32 fld __asm__("$2"); /* $v0 */  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
    s32 v0;
    s32 r2;  /* $a1 */
    register s32 a0 __asm__("$4");  /* $a0 */  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
    param_1 = arg0;
    s0 = *(s32 *)(param_1 + 0x34);
    func_80149374(s0, param_1 + 4);
    v1 = *(s32 *)(param_1 + 0x2c);
    if (v1 != 0) {
        s1 = 8;
        if (v1 != 3) {
            s0 = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) << 16;
        } else {
            fld = *(s32 *)(param_1 + 0x30);
            s0 = fld & 0xfff;
            s1 = (fld >> 12) & 0xf;
            s0 = s0 << 16;
        }
        s0 = s0 >> 16;
        iVar2 = func_8004787C(s0);
        r0 = iVar2 << s1;
        r1 = -r0;
        iVar3 = func_80047948(s0);
        r2 = iVar3 << s1;
        a0 = -r2;
        if (*(s32 *)(param_1 + 0x2c) == 2) {
            r1 = r0;
            a0 = r2;
        }
        *(s32 *)(param_1 + 0x10) = r1;
        *(s32 *)(param_1 + 0x18) = a0;
    }
    *(s32 *)(param_1 + 0x14) = 0xffff0000;
    func_800D1FC8(param_1, 6);
    v0 = func_800D21C4(param_1, D_800D387C, 0x9c);
    if (v0 != 0) {
        s32 uVar1;
        *(s32 *)(param_1 + 0x20) = v0;
        *(u32 *)(v0 + 4) = *(u32 *)(v0 + 4) | 0x50000040;
        if (*(s32 *)(param_1 + 0x2c) != 3) {
            uVar1 = 0x2000;
        } else {
            uVar1 = *(u16 *)(param_1 + 0x32);
        }
        *(u16 *)(v0 + 0x18) = uVar1;
        __asm__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)
        *(u16 *)(v0 + 0x1a) = *(u16 *)(v0 + 0x18);
        func_80128EA8(v0, param_1 + 0x24, (s32)D_800D3888);
        func_801661CC(param_1);
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}
