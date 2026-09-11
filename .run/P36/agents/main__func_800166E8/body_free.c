void func_800166E8(void *a0, s32 a1) {
    s32 local_buffer[2];
    s32 v0;
    s32 v1;


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
