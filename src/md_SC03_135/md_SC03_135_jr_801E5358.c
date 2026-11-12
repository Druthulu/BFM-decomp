#include "common.h"

extern s32 func_801E288C(void);
extern s32 guess_GetStoryProgress(void);
extern void func_801E2980(s32 arg0, s32 arg1);
extern void func_801E28D0(void);
extern void func_801E295C(void);
extern s16 func_801E2970(void);
extern u16 guess_g_MenuFrameCounter;
extern unsigned short guess_g_MenuStep;
extern void (*D_801E65D0[])(void);
extern void func_80141C04(void);
extern void func_801E29F8(void);
extern void func_801E2BC4(void);
extern void func_801E2BE0(void);
extern void func_801E2CC0(void);
extern void func_800D2624(void);
extern void func_801E2CDC(void);
extern s32 guess_SjisToGlyphCodes(u8 *, u8 *);
extern u32 *func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern u8 *func_800D27DC(s32, s32, void *, s16, s32);
extern u32 *func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801E3830(s32, s16, s16, s16, s32 *);
extern s32 func_801E3540(s32 ot, u8 *s, s16 c);
extern u32 guess_IntToBcd_4(s32 a0, s32 a1);
extern void func_801E4890(void);
extern void func_801E48B8(s32 arg0);
extern void func_8014B00C(s32 arg0);
extern void func_80029344(void);
extern void func_801E4BA4(void);
extern u8 *D_80126B10;
extern u8 D_801E6644[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);
extern int func_801E4BCC(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801E4C24(void);
extern void func_800D1E28(void);
extern s32 guess_RequestSound(s32, s32);
extern void func_8001BFD0(void);
extern s32 guess_GetGameVarByte(s32);
extern s32 func_80029524(void);
extern void func_800D0C48(s32);
extern s32 func_801E4C9C(s32 param_1);
extern s32 func_800D1EBC(void);
extern void func_801E4D3C(void);
extern void func_801E4D5C(void *a0);
extern s32 func_801E4D98(void *a0);
extern void func_801E4E04(void *a0);
extern void func_80171A1C(void*);
extern void func_801E4E40(void);
extern s32 func_80171D78(u32, void *);
extern void func_801E4E68(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801E4ED0(void *arg0);
extern void func_801E4F28(void);
extern void func_801E4F30(void *a0);
extern void func_801E4F6C(void *a0);
extern void func_801E4F8C(u32 arg0);
extern void func_801E4FF4(void);
extern void guess_SetMainCameraHandler(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E50C0(void *a0);
extern void func_801E4FFC(void);
extern void func_801E5124(s32 param_1, s16 *param_2);
extern void func_801E50FC(s32 param_1);
extern u16  guess_GetPadPressed(s32 *a0);
extern s32  guess_EaseToward(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);
extern s32 func_801E531C(void);
extern s32 guess_RequestResourceLoad(u32, u32, void *, u32, u32);
extern void func_801E5324(void);







extern u8 *D_80126B10;
extern u8 D_801E672C[];
extern u8 D_801E6798[];
extern u8 D_801E67B0[];
extern s32 func_801789AC(u8 *a0);
extern void func_80178CBC(u8 *a0, u8 *a1);
extern s16 func_80185B78(void);
extern void func_80185B88(s32 a0);
extern void func_80174438(s32 a0);
extern void func_801E2864(void);
extern s32 func_801E288C(void);

void func_801E5358(u8 *a0) {
    switch (((Unkstruct_801E5358 *)a0)->unk34) {
    case 0:
        switch (func_801789AC(a0)) {
        case 2:
            func_80178CBC(a0, D_801E6798);
            ((Unkstruct_801E5358 *)a0)->unk34 = 0;
            break;
        case 1:
            ((Unkstruct_801E5358 *)a0)->unk34 = 2;
            func_80185B88(4);
            break;
        case 3:
            func_80178CBC(a0, D_801E67B0);
            ((Unkstruct_801E5358 *)a0)->unk34 = 3;
            break;
        }
        break;
    case 1:
        break;
    case 2:
        if (func_80185B78() != 0) {
            func_801E2864();
            ((Unkstruct_801E5358 *)a0)->unk34 = 4;
        } else {
            func_80178CBC(a0, D_801E672C);
            ((Unkstruct_801E5358 *)a0)->unk34 = 0;
        }
        break;
    case 3:
        if (func_801789AC(a0) != 0) {
            func_80174438((*(s32 *)&D_80126B10));
            ((Unkstruct_801E5358 *)a0)->unk34 = 1;
        }
        break;
    case 4:
        if (((s16 (*)(void))func_801E288C)() != 0) {
            ((Unkstruct_801E5358 *)a0)->unk34 = 2;
            func_80185B88(4);
        }
        break;
    }
}




void func_801E54A4(void *a0) {

    extern void (*D_801E67E0[])(void);
    D_801E67E0[((Unkstruct_80126B58 *)a0)->unk2]();
}


#include "common.h"

void func_801E54E0(void) {
    extern s32 D_801EAC6C;
    D_801EAC6C = 0;
}




void func_801E54F0(void) {

    extern s32 D_801EAC6C;
    D_801EAC6C = 1;
}




s32 func_801E5504(void) {

    extern s32 D_801EAC6C;
    return D_801EAC6C;
}


s32 func_801E5514(void) {
    extern s32 guess_GetStoryProgress(void);
    extern s32 guess_TestGameFlag(s32);
    extern u8 D_801E67E8[];
    extern u8 D_801E6828[];
    extern s32 D_801E256C;
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
        p = D_801E256C;
        v = (s32)&D_801E67E8;
    } else {
        p = D_801E256C;
        v = (s32)&D_801E6828;
    }
    ((Unkstruct_801E5514 *)p)->unk4 = v;
    return v;
}


extern s32 guess_GetStoryProgress(void);
extern s32 guess_TestGameFlag(s32);

void func_801E559C(void) {
    extern s32 D_801E256C;
    extern u8 D_801E68BC[];
    extern u8 D_801E68F0[];

    s32 t;
    s32 flag;

    t = guess_GetStoryProgress();
    if ((u32)(t - 200) < 100u) {
        flag = 0;
    } else if (t < 300 || (guess_TestGameFlag(250) & 0xFF) == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag) {
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)D_801E68BC;
    } else {
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)D_801E68F0;
    }
}


#include "common.h"







extern s32 func_801E288C(void);
extern s32 guess_GetStoryProgress(void);
extern void func_801E2980(s32 arg0, s32 arg1);
extern void func_801E28D0(void);
extern void func_801E295C(void);
extern s16 func_801E2970(void);
extern u16 guess_g_MenuFrameCounter;
extern unsigned short guess_g_MenuStep;
extern void (*D_801E65D0[])(void);
extern void func_80141C04(void);
extern void func_801E29F8(void);
extern void func_801E2BC4(void);
extern void func_801E2BE0(void);
extern void func_801E2CC0(void);
extern void func_800D2624(void);
extern void func_801E2CDC(void);
extern s32 guess_SjisToGlyphCodes(u8 *, u8 *);
extern u32 *func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern u8 *func_800D27DC(s32, s32, void *, s16, s32);
extern u32 *func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801E3830(s32, s16, s16, s16, s32 *);
extern s32 func_801E3540(s32 ot, u8 *s, s16 c);
extern u32 guess_IntToBcd_4(s32 a0, s32 a1);
extern void func_801E4890(void);
extern void func_801E48B8(s32 arg0);
extern void func_8014B00C(s32 arg0);
extern void func_80029344(void);
extern void func_801E4BA4(void);
extern u8 *D_80126B10;
extern u8 D_801E6644[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);
extern int func_801E4BCC(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801E4C24(void);
extern void func_800D1E28(void);
extern s32 guess_RequestSound(s32, s32);
extern void func_8001BFD0(void);
extern s32 guess_GetGameVarByte(s32);
extern s32 func_80029524(void);
extern void func_800D0C48(s32);
extern s32 func_801E4C9C(s32 param_1);
extern s32 func_800D1EBC(void);
extern void func_801E4D3C(void);
extern void func_801E4D5C(void *a0);
extern s32 func_801E4D98(void *a0);
extern void func_801E4E04(void *a0);
extern void func_80171A1C(void*);
extern void func_801E4E40(void);
extern s32 func_80171D78(u32, void *);
extern void func_801E4E68(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801E4ED0(void *arg0);
extern void func_801E4F28(void);
extern void func_801E4F30(void *a0);
extern void func_801E4F6C(void *a0);
extern void func_801E4F8C(u32 arg0);
extern void func_801E4FF4(void);
extern void guess_SetMainCameraHandler(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E50C0(void *a0);
extern void func_801E4FFC(void);
extern void func_801E5124(s32 param_1, s16 *param_2);
extern void func_801E50FC(s32 param_1);
extern u16  guess_GetPadPressed(s32 *a0);
extern s32  guess_EaseToward(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);
extern s32 func_801E531C(void);
extern s32 guess_RequestResourceLoad(u32, u32, void *, u32, u32);
extern void func_801E5324(void);

extern s32 guess_GetStoryProgress(void);
extern s32 guess_TestGameFlag(s32 arg);
extern void guess_SetGameFlag(s32 a0, s32 a1);

#define SHARED_FN func_801E5624
#include "../shared/multi/cls_546048ffa222.h"
#undef SHARED_FN


extern s32 guess_GetStoryProgress(void);
extern s32 guess_TestGameFlag(s32 arg);
extern s32 func_80184428(void);
extern s32 func_801844F8(void);
extern s32 func_8018456C(void);
extern void func_801845C8(void);

void func_801E56A8(s32 a0) {
    extern s32 D_801E6754[];
    extern s32 D_801E6768[];
    extern s32 D_801E6784[];
    extern s32 D_801E6DF4;
    extern s32 D_801E6E40;

    s32 flag;

    s32 v1 = guess_GetStoryProgress();

    if (v1 < 0x258) {
        s32 u = guess_GetStoryProgress();

        if ((u32)(u - 0xC8) >= 0x64) {
            if (u >= 0x12C) {
                if (guess_TestGameFlag(0xFA) & 0xFF) {
                    goto zero;
                }
            } else {
                goto one;
            }
        } else {
            goto zero;
        }
        flag = 1;
        goto eval;
    zero:
        flag = 0;
        goto eval;
    one:
        flag = 1;
    eval:
        if (flag != 0) {
            s32 v0 = func_80184428();
            ((Unkstruct_801E56A8 *)a0)->unkE4 = D_801E6754[v0];
        } else {
            s32 w = guess_GetStoryProgress();
            if ((u32)w < 0x12C) {
                ((Unkstruct_801E56A8 *)a0)->unkE4 = (s32)&D_801E6DF4;
            } else {
                ((Unkstruct_801E56A8 *)a0)->unkE4 = (s32)&D_801E6E40;
            }
        }
    } else if (v1 < 0x384) {
        s32 v0 = func_801844F8();
        ((Unkstruct_801E56A8 *)a0)->unkE4 = D_801E6768[v0];
    } else {
        s32 v0 = func_8018456C();
        ((Unkstruct_801E56A8 *)a0)->unkE4 = D_801E6784[v0];
        func_801845C8();
    }
}



extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern void guess_StartActorSequence(s32 a0, s32 a1);
extern void guess_SetObjectPosAndYaw(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801E57C4(void *a0) {
    extern s32 D_801CEA24;
    extern s32 D_801BEAF8;
    extern s32 D_801E669C;
    extern s32 D_801E66CC;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))guess_AllocModelObject)();
    ((Unkstruct_800B5CB8 *)a0)->unk20 = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
    } else {
        guess_InitModelObject(v0, (s32)&D_801CEA24);
        ptr = ((Unkstruct_800B5CB8 *)a0)->unk68;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        guess_StartActorSequence((s32)a0, (s32)&D_801BEAF8);
        guess_SetObjectPosAndYaw((s32)a0, (s32)&D_801E669C);
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
        func_80178B18((s32)a0, (s32)&D_801E66CC);
    }
}


void *func_801E585C(void) {
    extern u8 D_80078EB1;
    extern u8 guess_g_PlayerRecord[];
    extern u32 D_801E6C68;
    extern u32 D_801E6D8C;
    extern s32 D_801EADF0;
    extern void func_801E5A7C(void);
    extern s32 guess_GetStoryProgress(void);
    extern s32 func_801E5A1C(s32, s32, s32);
    extern void func_801E5A34(s32, s32, s32);
    extern void guess_SetGameFlag(s32 a0, s32 a1);
    extern void func_801E5AAC(void);
    extern void func_801E5AFC(void);
    extern void func_801E5B3C(s32 a0);
    extern SV4_md_SC03_135_801E585C D_801EAC70;
    s32 v;
    u8 *p;

    p = guess_g_PlayerRecord;
    func_801E5A7C();
    v = guess_GetStoryProgress();

    if (v >= 0xC8) {
        if (v < 0x258) {
            if (func_801E5A1C(D_80078EB1, 0xD, 0x18)) {
                if ((u32)(v - 0x136) < 0x46) {
                    func_801E5A34(0xA, (s32)&D_801E6C68, (s32)func_801E5AFC);
                    guess_SetGameFlag(0x112, 1);
                } else {
                    func_801E5A34(0xA, 0, 0);
                }
            } else {
                func_801E5A34(0xA, 0, 0);
            }
            if (func_801E5A1C(p[0x39], 0xD, 0x18)) {
                if ((u32)(v - 0x136) < 0x46) {
                    func_801E5A34(0xB, (s32)&D_801E6D8C, (s32)func_801E5B3C);
                } else {
                    func_801E5A34(0xB, 0, 0);
                }
            } else {
                func_801E5A34(0xB, 0, 0);
            }
        } else {
            func_801E5A34(0xA, 0, 0);
            func_801E5A34(0xB, 0, 0);
        }
    } else {
        func_801E5A34(0xA, 0, 0);
        func_801E5A34(0xB, 0, 0);
    }
    func_801E5AAC();
    if (D_801EADF0 == 0) {
        return 0;
    }
    return &D_801EAC70;
}


s32 func_801E5998(s32 a0) {
    extern s32 D_801EADF0;
    extern s32 D_801EAC78;
    extern s32 D_801EAC74;
    s32 s0;
    s32 v0;
    s32 v1;
    s32 limit;
    func_801E585C();
    s0 = a0;
    v0 = D_801EADF0;
    if (v0 > 0) {
        v1 = 0;
        limit = v0 * 16;
        do {
            if (*(s32 *)((s32)&D_801EAC78 + v1) == s0) {
                return *(s32 *)((s32)&D_801EAC74 + v1);
            }
            v1 += 16;
        } while (v1 < limit);
    }
    return 0;
}


#define SHARED_FN func_801E5A1C
#include "../shared/multi/cls_cc0ff9ac8bfb.h"
#undef SHARED_FN


void func_801E5A34(s32 a0, s32 a1, s32 a2) {
    extern s32 D_801EADF0;
    extern s32 D_801EAC74[][4];
    extern s32 D_801EAC78[][4];
    extern s32 D_801EAC7C[][4];
    s32 n = D_801EADF0;
    D_801EAC78[n][0] = a0;
    D_801EAC74[n][0] = a1;
    D_801EAC7C[n][0] = a2;
    D_801EADF0 = n + 1;
}


extern s32 D_801EAC70;
extern s32 D_801EADF0;
extern void guess_ZeroMemory(void *a0, s32 a1);

void func_801E5A7C(void) {
    guess_ZeroMemory(&D_801EAC70, 0x180);
    D_801EADF0 = 0;
}


void func_801E5AAC(void)
{
    extern s32 D_801EAC70;
    extern s32 D_801EADF0;
    Node_801E5AAC *p;
    s32 i;

    p = (Node_801E5AAC *)&D_801EAC70;
    for (i = 0; i < D_801EADF0 - 1; ) {
        p->next = (s32)(p + 1);
        i++;
        p = p + 1;
    }
}


extern s32 guess_GetStoryProgress(void);
extern void guess_SetGameFlag(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

#define SHARED_FN func_801E5AFC
#include "../shared/multi/cls_8287928f61de.h"
#undef SHARED_FN


extern s32 guess_GetStoryProgress(void);
extern void guess_SetGameFlag(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

#define SHARED_FN func_801E5B3C
#include "../shared/multi/cls_bfe826a314ed.h"
#undef SHARED_FN


