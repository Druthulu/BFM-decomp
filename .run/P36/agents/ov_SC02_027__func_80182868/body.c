void func_80182868(void *a0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern s32 func_80029178(s32);
    extern void func_80182A44(void *a0);

    extern s32 D_801ACD58;
    extern s32 D_801AB660[];
    extern Stride8_u16_80182868 D_801AB670[];
    extern Stride8_u16_80182868 D_801AB672[];
    extern Stride8_u16_80182868 D_801AB674[];
    extern Stride8_s16_80182868 D_801AB676[];
    extern s16 D_801AB624[];

    s32 v0;
    s16 state;
    s16 i;
    s16 id;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)&D_801ACD58);

    *(u32 *)(*(s32 *)((s32)a0 + 0x20) + 0x28) = 0x2000200;

    *(u32 *)((s32)a0 + 0x58) = (s32)D_801AB660 | 0x10000000;

    *(u8 *)((s32)a0 + 0x75) = 0;
    if (*(s16 *)((s32)a0 + 0x70) == 1) {
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x80000000;
        *(u16 *)((s32)a0 + 0x5C) = 0;
    } else {
        *(u16 *)((s32)a0 + 0x5C) = 0xCC00;
    }

    *(s16 *)((s32)a0 + 0x6) = D_801AB670[*(s16 *)((s32)a0 + 0x70)].v;
    *(s16 *)((s32)a0 + 0xA) = D_801AB672[*(s16 *)((s32)a0 + 0x70)].v;
    *(s16 *)((s32)a0 + 0xE) = D_801AB674[*(s16 *)((s32)a0 + 0x70)].v;
    func_80182A44(a0);

    if (*(s16 *)((s32)a0 + 0x70) == 3) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0x800;
    }

    if ((func_80029178(0xAE) & 0xFF) == 0) {
        return;
    }

    if (D_801AB624[0] != 0) {
        state = *(s16 *)((s32)a0 + 0x70);
        i = 0;
        for (;;) {
            id = D_801AB624[i + 1];
            if (id == state) {
                if (id >= 2) {
                    if (D_801AB676[id].v != 0) {
                        *(s16 *)((s32)a0 + 0x6) -= 0x200;
                    } else {
                        *(s16 *)((s32)a0 + 0x6) += 0x200;
                    }
                }
            }
            i += 2;
            if (D_801AB624[i] == 0) {
                break;
            }
        }
    }
}
