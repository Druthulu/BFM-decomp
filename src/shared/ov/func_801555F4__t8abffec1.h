/* func_801555F4 — shared body (overlay slot 0x80128158, h_text 8abffec1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801555F4(void *param_1)
{
    extern void func_80156648(int *a0);
    extern int D_800D4C94;
    extern int D_800D4CE4;
    extern int D_800D4D38;
    extern int D_800D4D88;
    extern int D_800D4E10;
    extern int D_800D4E6C;


    int uVar1;
    unsigned char bVar3;
    int s1;
    unsigned short uVar4;

    ((void(*)(int, int))func_80154A74)(((int)param_1), 0x15);
    if ((*(unsigned int *)(((int)param_1) + 0x44) & 0x200) == 0) {
        if (*(int *)(((int)param_1) + 0x2c) == -0xb0000) {
            uVar1 = ((int(*)(int))func_80029178)(0x82);
            if ((uVar1 & 0xff) != 0) {
                uVar1 = 7;
                goto L_648;
            }
        }
    } else {
        uVar1 = 5;
L_648:
        *(unsigned char *)(((int)param_1) + 0x1aa) = uVar1;
    }
    switch (*(unsigned char *)(((int)param_1) + 0x1aa)) {
    case 0:
    case 1:
        bVar3 = *(unsigned char *)(((int)param_1) + 0x1ab) ^ 1;
        *(unsigned char *)(((int)param_1) + 0x1ab) = bVar3;
        if (bVar3 != 0)
            *(unsigned char *)(((int)param_1) + 0x1aa) = 0;
        else
            *(unsigned char *)(((int)param_1) + 0x1aa) = 1;
        ((void(*)(int *, int))func_80154274)((int *)((int)param_1), (int)&D_800D4C94);
        ((void(*)(int))func_80147324)(0x400);
        ((void(*)(unsigned short))func_80147300)(0x5f3);
        s1 = 0;
        D_8011F730 |= 3;
        func_80146CA0((void *)((int)param_1));
        goto L_7b8;
    case 2:
        ((void(*)(int *, int))func_80154274)((int *)((int)param_1), (int)&D_800D4CE4);
        ((void(*)(int))func_80147324)(0x446);
        ((void(*)(unsigned short))func_80147300)(0x5f3);
        s1 = 1;
        goto L_575c;
    case 3:
        ((void(*)(int *, int))func_80154274)((int *)((int)param_1), (int)&D_800D4D38);
        ((void(*)(int))func_80147324)(0x400);
        ((void(*)(unsigned short))func_80147300)(0x5f3);
        s1 = 2;
        goto L_575c;
    case 4:
        ((void(*)(int *, int))func_80154274)((int *)((int)param_1), (int)&D_800D4D88);
        ((void(*)(unsigned short))func_80147300)(0x5f6);
        s1 = 3;
        func_80146CA0((void *)((int)param_1));
L_575c:
        func_80146CA0((void *)((int)param_1));
        goto L_7b8;
    case 5:
        ((void(*)(int *, int))func_80154274)((int *)((int)param_1), (int)&D_800D4E10);
        s1 = 4;
        uVar4 = 7;
        goto L_7b0;
    case 7:
        ((void(*)(int))func_80147324)(0x7f);
        ((void(*)(unsigned short))func_80147300)(0x5f4);
        ((void(*)(int *, int))func_80154274)((int *)((int)param_1), (int)&D_800D4E6C);
        s1 = 6;
        uVar4 = 8;
L_7b0:
        *(unsigned short *)(((int)param_1) + 2) = uVar4;
        goto L_7b8;
    default:
        ;
    }
L_7b8:
    ((void(*)(int *, int))func_80146E90)((int *)((int)param_1), 0);
    func_80156648((int *)((int)param_1));
    if (s1 >= 0) {
        ((int(*)(int, int, int, int))func_80146994)(4, ((int)param_1), s1, 0);
    }
    ((void(*)(int *))func_801553A8)((int *)((int)param_1));
}
