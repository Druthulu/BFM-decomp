/* func_80148648 — shared body (overlay slot 0x80128158, h_exact 935427e6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800B9A64;
extern s32 func_80014DC0();
extern s32 func_80014D68();
extern s32 func_80014D94();
extern s32 func_80014CF8();
extern void func_800120DC();
extern s32 func_800CF8B4();
void func_80148648(s32 a0, s32 a1) {
    s32 v;
    if (D_800B9A64 == 0) {
        s32 b = a1 & 0xFF;
        *(u8 *)(a0 + 0xA9) = func_80014DC0(b);
        *(s16 *)(a0 + 0xAA) = func_80014D68(b);
        *(s16 *)(a0 + 0xAC) = func_80014D94(b);
        {
            s32 r4 = func_80014CF8(b, 4);
            s32 r5 = func_80014CF8(b, 5);
            *(s16 *)(a0 + 0xAE) = (r4 & 0xFF) | ((r5 & 0xFF) << 8);
        }
    } else {
        *(u8 *)(a0 + 0xA9) = 0x41;
        func_800120DC(a0 + 0xAA, a0 + 0xAC);
    }
    if (*(u8 *)(a0 + 0x1C5) != 0) {
        *(s16 *)(a0 + 0xAA) = 0;
        *(s16 *)(a0 + 0xAC) = 0;
        *(u16 *)(a0 + 0xAE) = 0x8080;
    }
    if (func_800CF8B4() == 0) {
        u16 mode = *(u16 *)(a0 + 0x0);
        if (mode != 0x1E && mode != 0x1A) {
            *(s16 *)(a0 + 0xAA) = 0;
            *(s16 *)(a0 + 0xAC) = 0;
            *(u16 *)(a0 + 0xAE) = 0x8080;
        }
    }
    {
        s32 act = *(u8 *)(a0 + 0xA9);
        if (act == 0x53 || (act >= 0x54 && act == 0x73)) {
            if ((*(u16 *)(a0 + 0xAA) & 0xF000) != 0) {
                *(u8 *)(a0 + 0xA9) = 0x41;
            }
        }
    }
    if (*(s32 *)(a0 + 0x1B0) != 0) {
        s32 vAA = *(u16 *)(a0 + 0xAA);
        s32 vAE = *(u16 *)(a0 + 0xAE);
        s32 vAC = *(u16 *)(a0 + 0xAC);
        s32 t;
        t = ((vAA & 0x2000) << 2) | ((vAA & 0x8000) >> 2);
        t = t | (vAA & 0x5FFF);
        *(s16 *)(a0 + 0xAA) = t;
        t = ((vAC & 0x2000) << 2) | ((vAC & 0x8000) >> 2);
        t = t | (vAC & 0x5FFF);
        *(s16 *)(a0 + 0xAC) = t;
        if ((vAE & 0xFF) != 0x80) {
            vAE = (~(vAE & 0xFF) & 0xFF) | (vAE & 0xFF00);
        }
        *(s16 *)(a0 + 0xAE) = vAE;
    }
}
