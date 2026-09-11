void func_8002AF70(void *a0, u32 a1) {
    Blk16 *src = (Blk16 *)a0;
    u32 val = a1;
    register Blk16 *dest __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    Blk16 *end;

    __asm__(  // !FAKE: instruction lui — NEEDED DIFFERS (P36 rung B tus9)
        "lui %0, %%hi(D_80075CC0)\n\taddiu %0, %0, %%lo(D_80075CC0)"
        : "=r"(dest)
        : "r"(val)
    );

    func_80016714(dest, 0x300);
    end = src + 0x2D0 / 0x10;

    do {
        *dest = *src;
        src++;
        dest++;
    } while (src != end);

    __asm__ volatile("" : "=r"(src) : "0"(src));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)

    *(Blk12 *)dest = *(Blk12 *)src;

    D_80076040 = val;
}
