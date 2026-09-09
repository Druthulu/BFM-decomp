/* func_80164930 — shared body (overlay slot 0x80128158, h_exact 98817909). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80164930(s32 param_1) {
    int iVar3 = *(int *)(((int)param_1) + 0x20);
    if (*(int *)(((int)param_1) + 0x50) == 0) {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x100;
        short nv;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + 0x71;
        nv = D_80181E78 - 8;
        D_80181E78 = nv;
        D_80181E76 = nv;
        D_80181E74 = nv;
        if (nv < -0x80) {
            int i, lim;
            Ent_80164930_80164930 *p;
            for (i = 0, lim = 0x19, p = ((Ent_80164930_80164930 *)&D_8011F9D0); i < 0x14; i++) {
                if (p->f0 == lim && p->f50 != 0) {
                    ((void(*)(Ent_80164930_80164930 *))func_80162CCC)(p);
                }
                p++;
            }
            ((void(*)(Ent_80164930_80164930 *))func_80162CCC)((Ent_80164930_80164930 *)((int)param_1));
        } else {
            ((void(*)(int))func_80164ACC)(((int)param_1));
        }
    } else {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x40;
        u16 uVar2;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        uVar2 = *(u16 *)(iVar3 + 0x1a) - 0x200;
        *(u16 *)(iVar3 + 0x1a) = uVar2;
        if ((int)((unsigned)uVar2 << 0x10) < 0) {
            *(short *)(iVar3 + 0x1a) = 0;
        }
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) - 0x71;
    }
}
