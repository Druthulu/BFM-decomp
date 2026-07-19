typedef unsigned int uint;

typedef struct {
    int field0;   /* 0x0 */
    int field4;   /* 0x4 */
    int field8;   /* 0x8 */
    int fieldC;   /* 0xc */
} S1;

typedef struct {
    unsigned char b0;    /* 0x0 */
    unsigned char b1;    /* 0x1 */
    unsigned char b2;    /* 0x2 */
    unsigned char type;  /* 0x3 */
    unsigned char pad[8];/* 0x4 - 0xb */
} Elem;                  /* size 0xc */

extern short D_801DA9A0;
extern short D_801DA9A2;
extern short D_801DA9A4;
extern short D_801DA9A6;

void func_8013BD74(S1 *param_1, int param_2) {
    int *piVar1;      /* 0x0  */
    int *local_2c;    /* 0x4  */
    int local_28;     /* 0x8  */
    int pad_c;        /* 0xc  */
    int pad_10;       /* 0x10 */
    Elem *local_1c;   /* 0x14 */
    Elem *puVar2;     /* 0x18 */
    int pad_1c;       /* 0x1c */
    int base;         /* 0x20 */

    D_801DA9A0 = 0xff60;
    D_801DA9A2 = 0xff88;
    D_801DA9A4 = 0x140;
    D_801DA9A6 = 0xf0;
    param_1->field8 = param_2;
    param_1->fieldC = param_2 + 8;
    base = param_2 + 0x4008;
    if (*(char *)(param_2 + 4) == '\0') {
        local_2c = (int *)param_1->fieldC;
        for (local_28 = 0; local_28 < 0x1000; ++local_28) {
            if (*local_2c != 0) {
                *local_2c = *local_2c + param_1->fieldC;
                piVar1 = (int *)*local_2c;
                *piVar1 = *piVar1 + (int)piVar1;
                piVar1[5] = piVar1[5] + (int)piVar1;
                local_1c = (Elem *)piVar1[5];
                piVar1[6] = piVar1[6] * 0xc + piVar1[5];
                puVar2 = (Elem *)piVar1[6];
                while (local_1c < puVar2) {
                    switch (local_1c->type) {
                    case 0x24:
                    case 0x2c:
                    case 0x34:
                    case 0x3c:
                        *(uint *)local_1c = (*(uint *)local_1c & 0xffffff) + base;
                        break;
                    case 0x26:
                    case 0x2e:
                    case 0x36:
                    case 0x3e:
                        *(uint *)local_1c = (*(uint *)local_1c & 0xffffff) + base;
                        break;
                    }
                    ++local_1c;
                }
            }
            ++local_2c;
        }
        *(unsigned char *)(param_2 + 4) = 1;
    }

}
