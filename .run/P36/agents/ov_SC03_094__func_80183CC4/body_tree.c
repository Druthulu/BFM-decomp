void func_80183CC4(a0, a1)
s16 *a0;
s32 a1;
{
    u8 *sub;
    register u8 *v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)

    v0 = func_801290DC(0x44, (u8 *)a0);
    if (v0 != NULL) {
        sub = *(u8 **)((s32)v0 + 0x20);
        *(u32 *)((s32)sub + 0x20) = (u32)&D_801AE958;
        *(u16 *)((s32)sub + 0x28) = 0x290;
        *(u16 *)((s32)sub + 0x2A) = 0x1A0;
        *(u8 *)((s32)sub + 0x27) = 0x70;
        *(u16 *)((s32)sub + 0x1A) = 1;
        *(u16 *)((s32)sub + 0x18) = 1;
        *(u32 *)((s32)sub + 0x4) |= 0x50000000;
        *(u32 *)((s32)v0 + 0x1C) = 1;
        s0 = a1;
        v1 = s0;
        *(u32 *)((s32)v0 + 0x2C) = s0;
        *(u8 *)((s32)sub + 0x26) = v1;
        *(u8 *)((s32)sub + 0x25) = v1;
        *(u8 *)((s32)sub + 0x24) = v1;
    } else {
        v0 = NULL;
    }
    __asm__ volatile("" : : "r"(v0));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
}
