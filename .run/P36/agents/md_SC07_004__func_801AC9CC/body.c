void func_801AC9CC(void *arg0) {
    void *temp_a0;
    s16 sp10[4];
    s16 a3;
    s32 v1;

    temp_a0 = *(void **)((u8 *)arg0 + 0x20);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
        *(void **)((u8 *)arg0 + 0x20) = NULL;
    }
    sp10[0] = *(u16 *)((u8 *)arg0 + 0x6);
    sp10[1] = *(u16 *)((u8 *)arg0 + 0xA);
    sp10[2] = *(u16 *)((u8 *)arg0 + 0xE);
    a3 = *(s16 *)((u8 *)arg0 + 0x30);
    if (a3 == 0) {
        a3 = 6;
    }
    *(s32 *)((u8 *)arg0 + 0x2C) = func_8017D7D4(sp10, NULL, (u8 *)arg0 + 0x34, (s8)a3);
    v1 = *(s16 *)((u8 *)arg0 + 0x32);
    if (v1 == 0) {
        *(s32 *)((u8 *)arg0 + 0x1C) = 0x10;
    } else {
        *(s32 *)((u8 *)arg0 + 0x1C) = v1;
    }
    *(u16 *)((u8 *)arg0 + 0x2) += 1;
}
