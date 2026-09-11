void func_8002AF70(void *a0, u32 a1) {
    Blk16 *src = (Blk16 *)a0;
    u32 val = a1;
    Blk16 *dest;
    Blk16 *end;

    dest = (s32)&D_80075CC0;

    func_80016714(dest, 0x300);
    end = src + 0x2D0 / 0x10;

    do {
        *dest = *src;
        src++;
        dest++;
    } while (src != end);


    *(Blk12 *)dest = *(Blk12 *)src;

    D_80076040 = val;
}
