s16 func_800D1658(s32 arg0) {
    extern int func_800291B4(int);
    extern void func_800291A0(int, int);
    extern void func_8002D4C8(int, int);
    extern s16 D_8010EDEC;
    int v;
    short ret;
    int id;
    int slot;

    slot = (arg0 & 0xFF) + 0x2F;
    id = func_800291B4(slot) & 0xFF;
    if (id == 0) {
        return 0;
    }
    v = *(s16 *)((u8 *)&D_8010EDEC + id * 0xC);
    ret = v;
    if (v > 0 || ((u16)ret == 0x8000 && id != 0x27)) {
        func_800291A0(slot, 0);
        func_8002D4C8(0x462, 0);
        ret = 1;
    } else {
        ret = 0;
        func_8002D4C8(0x45F, 0);
    }
    return ret;
}
