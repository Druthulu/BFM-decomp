/* func_8014A59C — shared body (overlay slot 0x80128158, h_exact ab964bfa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EBF;
extern s32 func_80029178(s32 arg);
void func_8014A59C(s32 a0) {
    s32 r;
    s32 add;
    if (*(u32 *)(a0 + 0x44) & 1) {
        if ((*(u16 *)(a0 + 0xAA) & 8) != 0) {
            r = func_80029178(0x20);
            add = 3;
            if ((r & 0xFF) != 0) {
                add = 6;
            }
            D_80078EBF = D_80078EBF + add;
            if (0x80 < D_80078EBF) {
                __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B headers1)
                D_80078EBF = 0x80;
            }
        }
    } else {
        D_80078EBF = 0;
    }
}
