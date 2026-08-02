void func_801843AC(void *a0) {
    extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32 a0, s32 a1);
    extern void func_80131E00(void *a0, s32 a1);
    extern s32 D_801BCF28;
    extern s32 D_801AF7F0;
    extern s32 D_801AF688;

    u16 buf[8];
    register u16 v0 __asm__("$2");
    register u16 v1 __asm__("$3");
    register u16 a2 __asm__("$6");

    v0 = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)(&buf[0]) = v0;
    *(u16 *)(&buf[4]) = v0;

    v1 = *(u16 *)((s32)a0 + 0xA);
    v0 = v1 - 8;
    *(u16 *)(&buf[1]) = v1;
    *(u16 *)(&buf[5]) = v1;

    a2 = *(u16 *)((s32)a0 + 0xE);
    v1 = v1 + 8;
    *(u16 *)(&buf[1]) = v0;
    *(u16 *)(&buf[5]) = v1;
    *(u16 *)(&buf[2]) = a2;
    *(u16 *)(&buf[6]) = a2;

    if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) != 0) {
        func_80131E00(a0, 6);
    } else {
        func_8012A828((s32)a0, (s32)&D_801BCF28);
        *(u16 *)((s32)a0 + 0x2) = 1;
        *(u16 *)((s32)a0 + 0x5C) = (u16)0xAA10;
        *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801AF7F0;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(s32 *)((s32)a0 + 0x58) = (s32)&D_801AF688 | 0x40000000 | 0x20000000;
        *(s16 *)((s32)a0 + 0x88) = *(u16 *)((s32)a0 + 0x6);
        *(s16 *)((s32)a0 + 0x8A) = *(u16 *)((s32)a0 + 0xA);
        *(s16 *)((s32)a0 + 0x8C) = *(u16 *)((s32)a0 + 0xE);
    }
}
