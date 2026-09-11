void func_8002AF70(void *a0, u32 a1) {
    typedef struct {
        u32 w[0x2DC / 4];
    } Blk2DC;

    func_80016714(D_80075CC0, 0x300);
    *(Blk2DC *)D_80075CC0 = *(Blk2DC *)a0;
    D_80076040 = a1;
}
