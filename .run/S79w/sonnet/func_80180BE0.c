typedef struct { u8 b[12]; } Blk12_80180BE0;

void func_80180BE0(s32 arg0, s32 arg1, s16 *arg2)
{
    s32 pad;
    s32 idx = arg1;
    u32 v;
    register u32 w asm("$2");
    u32 t4;
    u32 t5;
    u8 *p;
    register s16 *out asm("$8");

    __asm__("" :: "r"(&pad));
    v = *(u32 *)(*(s32 *)(arg0 + 0x90) + (*(s32 *)(arg0 + 0x94) << 3));
    if ((v & 0x1000000) != 0) {
        out = arg2;
        __asm__ __volatile__("" : "=r"(out) : "0"(out));
        p = (u8 *)((v & 0xFEFFFFFF) + idx * 8);
        out[0] = *(s8 *)(p + 3);
        out[1] = *(s8 *)(p + 4);
        out[2] = *(s8 *)(p + 5);
        w = *(u32 *)p;
        t4 = *(u8 *)(p + 1) | ((w & 0xF) << 8);
        t5 = ((w >> 16) & 0xFF) | ((w & 0xF0) << 4);
        out[4] = t4;
        out[5] = t5;
        out[3] = *(u16 *)(p + 6);
    } else {
        out = arg2;
        __asm__ __volatile__("" : "=r"(out) : "0"(out));
        *(Blk12_80180BE0 *)out = *(Blk12_80180BE0 *)(v + idx * 12);
    }
}
