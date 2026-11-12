/* func_80142E38 — shared body (overlay slot 0x80128158, h_exact 600b7ab2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80142E38(int param_1)
{
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))guess_AllocModelObject)();
    if (iVar2 == 0) {
        ((void (*)(int))guess_FreeActorDuringSpawn)(param_1);
    } else {
        ((void (*)(int, void *))guess_InitModelObjectKind3)(iVar2, &D_8017FF1C);
        sVar1 = (*(unsigned short *)(param_1 + 0x70) & 0xf) * 0x600 + 0x1200;
        *(short *)(iVar2 + 0x1a) = sVar1;
        *(short *)(iVar2 + 0x18) = sVar1;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}
