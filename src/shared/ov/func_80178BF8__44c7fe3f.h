/* func_80178BF8 — shared body (overlay slot 0x80128158, h_exact 44c7fe3f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80178BF8()
{
    extern void func_8017B1D8(void);
    extern short D_8018FB24;
    extern int D_8018F918;
    extern short D_8018F928;
    extern short D_8018F924;
    extern short D_8018F920;
    extern short D_8018F91C;
    extern int D_8018F9CC;
    extern int D_8018F930;
    extern s16 D_8018F910;
    extern short D_8018F908;
    extern short D_8018F90C;
    extern int D_8018FA80;
    extern unsigned int D_8018F980;
    extern unsigned short D_8018F906;

    unsigned short *puVar1;
    int iVar2;
    unsigned int *puVar3;

    iVar2 = 9;
    puVar3 = &D_8018F980;
    D_8018FB24 = 0;
    D_8018F918 = 0;
    D_8018F928 = 0;
    D_8018F924 = 0;
    D_8018F920 = 0;
    D_8018F91C = 0;
    D_8018F9CC = 1;
    D_8018F930 = 0;
    (*(short *)&D_8018F910) = 0;
    do {
        *puVar3 = 0;
        iVar2 = iVar2 + -1;
        puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
    iVar2 = 0x1ff;
    puVar1 = &D_8018F906;
    do {
        *puVar1 = 0;
        iVar2 = iVar2 + -1;
        puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
    D_8018F908 = 0;
    D_8018F90C = 0;
    ((void (*)(int *, int))func_80016714)(&D_8018FA80, 0x14);
    func_8017B1D8();
}
