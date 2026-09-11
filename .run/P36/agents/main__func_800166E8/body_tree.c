void func_800166E8(void *a0, s32 a1) {
    s32 local_buffer[2];
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 v1;

    __asm__ volatile("");  // Barrier to force stack allocation first  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)

    if (a1 == 0)
        goto skip;

    v0 = a1 - 1;
    v1 = -1;

    do {
        *(u8 *)a0 = 0;
        v0--;
        a0 = (void *)((s32)a0 + 1);
    } while (v0 != v1);

skip:
    return;
}
