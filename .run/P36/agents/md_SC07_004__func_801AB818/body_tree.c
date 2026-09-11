void func_801AB818(void *a0) {
    u8 *s1 = *(u8 **)((s32)a0 + 0x24);

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        U16x2N tmp;
        s32 cur;
        s32 addend;

        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_801A8440((s32)a0);

        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) -= 0x370;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);

        cur = *(s32 *)(s1 + 0);
        addend = *(s32 *)((s32)a0 + 0x30);
        *(s32 *)&tmp = cur;
        /* §22-ADDENDUM: a plain memory clobber, not `volatile`. It defeats
         * flow.c's last_mem_set dead-store rule so the FIRST store to the
         * temp survives, without pinning either store's schedule. Without
         * it the target's `sw $v0,0x10($sp)` at idx 24 is deleted. */
        __asm__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)
        *(s32 *)&tmp = cur + addend;
        *(U16x2N *)(s1 + 0) = tmp;
    } else {
        func_801292C8((u8 *)a0);
    }
}
