extern char D_801BD010[8];

void func_8018480C(s32 *arg0) {
    typedef struct {
        u16 f0;
        u16 f1;
        u16 f2;
        u16 pad;
    } LocalStruct;

    LocalStruct local1;
    LocalStruct local2;
    u16 v0, v1, v2;

    v0 = *(u16 *)((u8 *)arg0 + 6);
    local1.f0 = v0;
    local2.f0 = v0;

    v1 = *(u16 *)((u8 *)arg0 + 10);
    local1.f1 = v1;
    local2.f1 = v1;

    v2 = *(u16 *)((u8 *)arg0 + 14);
    v1 = v1 + 8;
    local1.f2 = v2;
    local2.f2 = v2;

    local1.f1 = v1 - 16;
    local2.f1 = v1;

    if ((func_8012CEB0(&local1, &local2, 0) & 0x19) != 0) {
        func_80131E00(arg0, 0x6);
    } else {
        func_8012A828(arg0, (s32)D_801BD010);
        *(u16 *)((u8 *)arg0 + 2) = 6;
        *(u16 *)((u8 *)arg0 + 0x5C) = 0xA810;
    }
}
