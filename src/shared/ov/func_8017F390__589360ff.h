/* func_8017F390 — shared body (overlay slot 0x80128158, h_exact 589360ff). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80126B66;
extern s32 D_801270C8;
extern s32 D_801270CC;
extern s32 D_801E8008;
extern char D_801A6534[];
extern char D_801A7054[];
extern char D_8018E6B0[];
extern void func_8012A828(s32 a0, void *a1);
extern s32  func_8012BEE8(s32 a0);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_8012C098(void *a0);
extern void func_8012C218(void *a0);
void func_8017F390(s32 a0)
{
    u16 state;
    u16 t;
    s32 v0;
    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0:
        v0 = (s32) *(s16 *)&D_80126B66 - (s32) *(s16 *)(a0 + 0xE);
        if (v0 < 0) {
            v0 = -v0;
        }
        if (v0 < 0x171) {
            t = state + 1;
            *(u16 *)(a0 + 0x34) = t;
            func_8012A828(a0, &D_801A7054);
            *(s32 *)(a0 + 0x1C) = 0x1E;
        }
        return;
    case 1:
        if (*(s32 *)(a0 + 0x1C) == 0x14) {
            D_801270C8 = 1;
        }
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        t = *(u16 *)(a0 + 0x34) + 1;
        *(u16 *)(a0 + 0x34) = t;
        func_8012A828(a0, &D_801A6534);
        *(s32 *)(a0 + 0x1C) = 0;
        return;
    case 2:
        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
        {
            s32 p20 = *(s32 *)(a0 + 0x20);
            v0 = func_8012B608(*(s16 *)(p20 + 0x12), 0x800, 4);
        }
        {
            s32 p20b = *(s32 *)(a0 + 0x20);
            *(u16 *)(p20b + 0x12) = *(u16 *)(p20b + 0x12) + v0;
        }
        if (*(s32 *)(a0 + 0x1C) >= 8) {
            func_8012B14C(a0, (s32) D_8018E6B0);
            v0 = ((s32 (*)(s32)) func_8012CBA4)(a0);
            D_801E8008 = v0;
            if (v0 == 0 || (v0 & 0x4000) != 0) {
                *(s32 *)(a0 + 4) = *(s32 *)(a0 + 0x38);
                *(s32 *)(a0 + 8) = *(s32 *)(a0 + 0x3C);
                *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
            }
        }
        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x100) {
            switch ((s32)((u32)*(u16 *)(a0 + 0x70) << 0x10) >> 0x18) {
            case 0:
            case 1:
            case 2:
            case 5:
            case 6:
                func_8012C098((void *)a0);
                return;
            case 3:
            case 7:
                func_8012C218((void *)a0);
                break;
            case 4:
                D_801270CC = D_801270CC - 1;
                func_8012C218((void *)a0);
                break;
            }
        }
        return;
    }
}
