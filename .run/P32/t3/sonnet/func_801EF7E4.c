extern s32 func_80178970(s32 *a0);
extern void func_80178D18(u8 *a0);
extern void func_80178CBC(s32, s32);
extern s32 func_801789AC(s32 a0);
extern void func_80185874(short *a0);
extern void func_80029124(s32, s32);

extern short D_801F09D4;
extern short D_801F099C;
extern short D_801F0A3C;
extern short D_801F0A0C;

void func_801EF7E4(u8 *a0) {
    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
    case 3:
        if (func_80178970((s32 *)a0)) {
            func_80178D18((u8 *)a0);
            func_80185874((short *)a0);
        }
        break;
    case 1:
    case 2: {
        s32 v0 = func_801789AC((s32)a0);
        if (v0 != 0) {
            if (v0 == 1) {
                func_80029124(0xDF, 1);
                if (*(u16 *)((s32)a0 + 0x34) == 1) {
                    func_80178CBC((s32)a0, (s32)&D_801F09D4);
                } else {
                    func_80178CBC((s32)a0, (s32)&D_801F099C);
                }
            } else {
                func_80029124(0xE0, 1);
                if (*(u16 *)((s32)a0 + 0x34) == 1) {
                    func_80178CBC((s32)a0, (s32)&D_801F0A3C);
                } else {
                    func_80178CBC((s32)a0, (s32)&D_801F0A0C);
                }
            }
            *(u16 *)((s32)a0 + 0x34) = 3;
        }
        break;
    }
    }
}
