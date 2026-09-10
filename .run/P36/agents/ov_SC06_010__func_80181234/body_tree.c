void aF8017ED80(void *param_1) {
    u8 *a0 = (u8 *)param_1;
    s32 pad_[4];
    s32 iVar2;
    u32 uVar1;

    if (*(u16 *)(a0 + 0x0) != 0) {
        iVar2 = *(s32 *)(a0 + 0xCC);
        *(u16 *)(iVar2 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(iVar2 + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(iVar2 + 0xC) = *(u16 *)(a0 + 0xE);
        *(u16 *)(iVar2 + 0x10) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10);
        *(u16 *)(iVar2 + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + *(u16 *)(a0 + 0xFC);
        *(u16 *)(iVar2 + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14);
        *(u16 *)(iVar2 + 0x18) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(u16 *)(iVar2 + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
        *(u16 *)(iVar2 + 0x1C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C);
        if (*(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) < 0) {
            register u32 val __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
            val = *(u32 *)(iVar2 + 0x4);
            uVar1 = val | 0x80000000;
        } else {
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus7)
            uVar1 = *(u32 *)(iVar2 + 0x4) & 0x7FFFFFFF;
        }
        *(u32 *)(iVar2 + 0x4) = uVar1;

        iVar2 = *(s32 *)(a0 + 0xD0);
        *(u16 *)(iVar2 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(iVar2 + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(iVar2 + 0xC) = *(u16 *)(a0 + 0xE);
        *(u16 *)(iVar2 + 0x10) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10);
        *(u16 *)(iVar2 + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + *(u16 *)(a0 + 0xFE);
        *(u16 *)(iVar2 + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14);
        *(u16 *)(iVar2 + 0x18) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(u16 *)(iVar2 + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
        *(u16 *)(iVar2 + 0x1C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C);
        if (*(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) < 0) {
            register u32 val __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
            val = *(u32 *)(iVar2 + 0x4);
            uVar1 = val | 0x80000000;
        } else {
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus7)
            uVar1 = *(u32 *)(iVar2 + 0x4) & 0x7FFFFFFF;
        }
        *(u32 *)(iVar2 + 0x4) = uVar1;
    }
}
