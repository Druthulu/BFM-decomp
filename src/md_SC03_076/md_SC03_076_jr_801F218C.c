#include "common.h"

extern void func_801EF750(void);
extern void func_801EF7DC(void);
extern s16 func_801EF7F0(void);
extern s32 func_801EF800(s32 a0, s32 a1);
extern u16 guess_g_MenuFrameCounter;
extern unsigned short guess_g_MenuStep;
extern void (*D_801F3468[])(void);
extern void func_80141C04(void);
extern void func_801EF878(void);
extern void func_801EFA44(void);
extern void func_801EFA60(void);
extern void func_801EFB40(void);
extern void func_800D2624(void);
extern void func_801EFB5C(void);
extern s32 func_80024054(u8 *, u8 *);
extern u32 *func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern u8 *func_800D27DC(s32, s32, void *, s16, s32);
extern u32 *func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801F06B0(s32, s16, s16, s16, s32 *);
extern s32 func_801F03C0(s32 ot, u8 *s, s16 c);
extern u32 func_801F1440(s32 a0, s32 a1);
extern void func_801F14A8(unsigned int val, int n, unsigned short * dst, int flag);
extern void guess_ZeroMemory(void *a0, s32 a1);
extern s32 D_801F9AC4;
extern void func_801F1710(void);
extern void func_801F1738(s32 arg0);
extern void func_8014B00C(s32 arg0);
extern void func_80029344(void);
extern void func_801F1A24(void);
extern u8 D_801F34DC[];
void func_800167B8(int);
void func_80175414(s32 _arg0);
extern int func_801F1A4C(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801F1AA4(void);
extern s32 func_801F1B1C(s32 param_1);
extern s32 func_800D1EBC(void);
extern void func_801F1BAC(void);
extern void func_801F1BCC(void *a0);
extern s32 func_801F1C08(void *a0);
extern void func_801F1C74(void *a0);
extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
extern void func_801F1CB0(void);
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void *);
extern void func_801F1CD8(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_801F1D40(void *arg0);
extern void func_801F1D98(void);
extern void func_801F1DA0(void *a0);
extern void func_801F1DDC(void);
extern void func_801F1DFC(u32 arg0);
extern void func_801F1E64(void);
extern void guess_SetMainCameraHandler(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801F1F30(void *a0);
extern void func_801F1E6C(void);
extern void func_801F1F94(s32 param_1, s16 *param_2);
extern void func_801F1F6C(s32 param_1);
extern u16  guess_GetPadPressed(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);







extern s32 D_80126B10;
extern u8 D_801F35C4[];
extern u8 D_801F3630[];
extern u8 D_801F3648[];
extern s32 func_801789AC(u8 *a0);
extern void func_80178CBC(u8 *a0, u8 *a1);
extern s16 func_80188F10(void);
extern void func_80188F20(s32 a0);
extern void func_80174438(s32 a0);
extern void func_801EF6E4(void);
extern s16 func_801EF70C(void);

void func_801F218C(u8 *a0) {
    switch (((Unkstruct_801F218C *)a0)->unk34) {
    case 0:
        switch (func_801789AC(a0)) {
        case 2:
            func_80178CBC(a0, D_801F3630);
            ((Unkstruct_801F218C *)a0)->unk34 = 0;
            break;
        case 1:
            ((Unkstruct_801F218C *)a0)->unk34 = 2;
            func_80188F20(4);
            break;
        case 3:
            func_80178CBC(a0, D_801F3648);
            ((Unkstruct_801F218C *)a0)->unk34 = 3;
            break;
        }
        break;
    case 1:
        break;
    case 2:
        if (func_80188F10() != 0) {
            func_801EF6E4();
            ((Unkstruct_801F218C *)a0)->unk34 = 4;
        } else {
            func_80178CBC(a0, D_801F35C4);
            ((Unkstruct_801F218C *)a0)->unk34 = 0;
        }
        break;
    case 3:
        if (func_801789AC(a0) != 0) {
            func_80174438(D_80126B10);
            ((Unkstruct_801F218C *)a0)->unk34 = 1;
        }
        break;
    case 4:
        if (func_801EF70C() != 0) {
            ((Unkstruct_801F218C *)a0)->unk34 = 2;
            func_80188F20(4);
        }
        break;
    }
}




void func_801F22D8(void *a0) {

    extern void (*D_801F3678[])(void);
    D_801F3678[((Unkstruct_80126B58 *)a0)->unk2]();
}


void func_801F2314(void) {
    extern s32 D_801F9DD0;
    D_801F9DD0 = 0;
}




void func_801F2324(void) {

    extern s32 D_801F9DD0;
    D_801F9DD0 = 1;
}




s32 func_801F2338(void) {

    extern s32 D_801F9DD0;
    return D_801F9DD0;
}


s32 func_801F2348(void) {
    extern s32 guess_GetStoryProgress(void);
    extern s32 guess_TestGameFlag(s32);
    extern u8 D_801F375C[];
    extern u8 D_801F379C[];
    extern s32 D_801EF3EC;
    s32 x;
    s32 t;
    s32 p;
    s32 v;

    x = guess_GetStoryProgress();
    if ((u32)(x - 200) < 100) {
        t = 0;
    } else if (x < 300 || (guess_TestGameFlag(250) & 0xFF) == 0) {
        t = 1;
    } else {
        t = 0;
    }
    if (t != 0) {
        p = D_801EF3EC;
        v = (s32)&D_801F375C;
    } else {
        p = D_801EF3EC;
        v = (s32)&D_801F379C;
    }
    ((Unkstruct_801E5514 *)p)->unk4 = v;
    return v;
}


s32 func_801F23D0(void) {
    extern s32 guess_GetStoryProgress(void);
    extern s32 guess_TestGameFlag(s32);
    extern u8 D_801F3830[];
    extern u8 D_801F3864[];
    extern s32 D_801EF3EC;
    s32 x;
    s32 t;
    s32 p;
    s32 v;

    x = guess_GetStoryProgress();
    if ((u32)(x - 200) < 100) {
        t = 0;
    } else if (x < 300 || (guess_TestGameFlag(250) & 0xFF) == 0) {
        t = 1;
    } else {
        t = 0;
    }
    if (t != 0) {
        p = D_801EF3EC;
        v = (s32)&D_801F3830;
    } else {
        p = D_801EF3EC;
        v = (s32)&D_801F3864;
    }
    ((Unkstruct_801E5514 *)p)->unk4 = v;
    return v;
}


extern s32 guess_GetStoryProgress(void);
extern s32 guess_TestGameFlag(s32);
extern void guess_SetGameFlag(s32, s32);

#define SHARED_FN func_801F2458
#include "../shared/multi/cls_546048ffa222.h"
#undef SHARED_FN


void func_801F24DC(s32 a0) {
    extern s32 guess_GetStoryProgress(void);
    extern s32 guess_TestGameFlag(s32 arg);
    extern s32 func_801877C0(void);
    extern s32 func_80187890(void);
    extern s32 func_80187904(void);
    extern void func_80187960(void);
    extern s32 D_801F35EC[];
    extern s32 D_801F3600[];
    extern s32 D_801F361C[];
    extern s32 D_801F3D68;
    extern s32 D_801F3DB4;

    s32 v1 = guess_GetStoryProgress();
    if (v1 < 0x258) {
        s32 flag;
        v1 = guess_GetStoryProgress();
        if ((u32)(v1 - 0xC8) >= 0x64U) {
            if (v1 < 0x12C || (guess_TestGameFlag(0xFA) & 0xFF) == 0) {
                flag = 1;
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
        if (flag) {
            ((Unkstruct_801F24DC *)a0)->unkE4 = D_801F35EC[func_801877C0()];
        } else {
            if (guess_GetStoryProgress() < 0x12CU) {
                ((Unkstruct_801F24DC *)a0)->unkE4 = (s32)&D_801F3D68;
            } else {
                ((Unkstruct_801F24DC *)a0)->unkE4 = (s32)&D_801F3DB4;
            }
        }
    } else if (v1 < 0x384) {
        ((Unkstruct_801F24DC *)a0)->unkE4 = D_801F3600[func_80187890()];
    } else {
        ((Unkstruct_801F24DC *)a0)->unkE4 = D_801F361C[func_80187904()];
        func_80187960();
    }
}



extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern void guess_StartActorSequence(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801F25F8(void *a0) {
    extern s32 D_801F968C;
    extern s32 D_801C3790;
    extern s32 D_801F3534;
    extern s32 D_801F3564;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))guess_AllocModelObject)();
    ((Unkstruct_800B5CB8 *)a0)->unk20 = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
    } else {
        guess_InitModelObject(v0, (s32)&D_801F968C);
        ptr = ((Unkstruct_800B5CB8 *)a0)->unk68;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        guess_StartActorSequence((s32)a0, (s32)&D_801C3790);
        func_8012E8E0((s32)a0, (s32)&D_801F3534);
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
        func_80178B18((s32)a0, (s32)&D_801F3564);
    }
}


extern void func_801F28B0(void);
extern s32 guess_GetStoryProgress(void);
extern s32 func_801F2850(s32, s32, s32);
extern void func_801F2868(s32, s32, s32);
extern void func_801F28E0(void);
extern void guess_SetGameFlag(s32 a0, s32 a1);
extern void func_801F2930(void);
extern void func_801F2970(void);

s32 *func_801F2690(void) {
    extern u8 D_80078EB1;
    extern u8 guess_g_PlayerRecord[];
    extern u32 D_801F3BDC;
    extern u32 D_801F3D00;
    extern s32 D_801F9DD4;
    extern s32 D_801F9F54;
    s32 v;
    u8 *p;

    p = guess_g_PlayerRecord;
    func_801F28B0();
    v = guess_GetStoryProgress();

    if (v >= 0xC8) {
        if (v < 0x258) {
            if (func_801F2850(D_80078EB1, 0xD, 0x18)) {
                if ((u32)(v - 0x136) < 0x46) {
                    func_801F2868(0xA, (s32)&D_801F3BDC, (s32)func_801F2930);
                    guess_SetGameFlag(0x112, 1);
                } else {
                    func_801F2868(0xA, 0, 0);
                }
            } else {
                func_801F2868(0xA, 0, 0);
            }
            if (func_801F2850(p[0x39], 0xD, 0x18)) {
                if ((u32)(v - 0x136) < 0x46) {
                    func_801F2868(0xB, (s32)&D_801F3D00, (s32)func_801F2970);
                } else {
                    func_801F2868(0xB, 0, 0);
                }
            } else {
                func_801F2868(0xB, 0, 0);
            }
        } else {
            func_801F2868(0xA, 0, 0);
            func_801F2868(0xB, 0, 0);
        }
    } else {
        func_801F2868(0xA, 0, 0);
        func_801F2868(0xB, 0, 0);
    }
    func_801F28E0();
    if (D_801F9F54 == 0) {
        return 0;
    }
    return &D_801F9DD4;
}


extern s32 *func_801F2690(void);
extern s32 D_801F9F54;
extern s32 D_801F9DDC[];
extern s32 D_801F9DD8[];

s32 func_801F27CC(s32 a0) {
    s32 s0 = a0;
    s32 v0;
    s32 v1;
    ((s32 (*)(void))func_801F2690)();
    v0 = D_801F9F54;
    if (v0 > 0) {
        v1 = 0;
        a0 = v0 << 4;
        do {
            if (*(s32 *)((s32)&D_801F9DDC + v1) == s0) {
                v0 = *(s32 *)((s32)&D_801F9DD8 + v1);
                goto end;
            }
            v1 += 0x10;
        } while (v1 < a0);
    }
    v0 = 0;
end:
    return v0;
}


#define SHARED_FN func_801F2850
#include "../shared/multi/cls_cc0ff9ac8bfb.h"
#undef SHARED_FN


void func_801F2868(s32 arg0, s32 arg1, s32 arg2) {

    extern s32 D_801F9F54;
    extern s32 D_801F9DDC[];
    extern s32 D_801F9DD8[];
    extern s32 D_801F9DE0[];
    s32 i;

    i = D_801F9F54;
    D_801F9DDC[i * 4] = arg0;
    D_801F9DD8[i * 4] = arg1;
    D_801F9DE0[i * 4] = arg2;
    D_801F9F54 = i + 1;
}


extern void guess_ZeroMemory(void *a0, s32 a1);
extern s32 D_801F9DD4;
extern s32 D_801F9F54;

void func_801F28B0(void) {
    guess_ZeroMemory(&D_801F9DD4, 0x180);
    D_801F9F54 = 0;
}


void func_801F28E0(void)
{
    extern s32 D_801F9DD4;
    extern s32 D_801F9F54;
    Node_801F28E0 *p;
    s32 i;

    p = (Node_801F28E0 *)&D_801F9DD4;
    for (i = 0; i < D_801F9F54 - 1; ) {
        p->next = (s32)(p + 1);
        i++;
        p = p + 1;
    }
}


extern s32 guess_GetStoryProgress(void);
extern void func_80029514(s32 arg0);
extern void guess_SetGameFlag(s32 a0, s32 a1);

#define SHARED_FN func_801F2930
#include "../shared/multi/cls_8287928f61de.h"
#undef SHARED_FN


extern s32 guess_GetStoryProgress(void);
extern void guess_SetGameFlag(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

#define SHARED_FN func_801F2970
#include "../shared/multi/cls_bfe826a314ed.h"
#undef SHARED_FN



u8 func_801F29B0(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0x16;
}




extern s32 func_8001ABBC(u32, u32, void *, u32, u32);

s32 func_801F29E0(void) {

    extern u8 D_800AF040[];
    return func_8001ABBC(0, 0, D_800AF040, 0, 0);
}


