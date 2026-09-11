void func_801AB818(void *a0) {
    u8 *s1 = *(u8 **)((s32)a0 + 0x24);

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        U16x2N tmp;

        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_801A8440((s32)a0);

        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) -= 0x370;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);

        /* tmp is stored twice and the target keeps both stores: the addend read between them resets flow.c's
         * last_mem_set; as ((s32 *)a0)[12] it is an in-struct access, which sched1 hoists above the frame store. */
        *(s32 *)&tmp = *(s32 *)(s1 + 0);
        *(s32 *)&tmp += ((s32 *)a0)[12];
        *(U16x2N *)(s1 + 0) = tmp;
    } else {
        func_801292C8((u8 *)a0);
    }
}
