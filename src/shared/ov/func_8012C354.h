/* guess_InitActorModel — shared body (overlay slot 0x80128158, h_exact c3abcfd9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001CFDC(s32 a, s32 b);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern u8 D_80078EAE;
/* guess_InitActorModel: sets an actor up from descriptor a1: stores it at +0x78, copies two halfwords, allocates and maps its model when a1+4 is set
 * Confidence medium, xref chain: +0x78 = a1, +0x76 = a1[0] (x24/16 when D_80078EAE == 0), +0x5C = a1[1]; model: guess_AllocModelObject range + guess_InitModelObject
 * Names ledger: config/names.tsv guess_InitActorModel */
s32 guess_InitActorModel(s32 a0, s32 a1) {
    s32 v;
    *(s32*)(a0 + 0x78) = a1;
    if (D_80078EAE == 0) {
        v = (*(s16*)(a1 + 0x0) * 24) / 16;
    } else {
        v = *(u16*)(a1 + 0x0);
    }
    *(s16*)(a0 + 0x76) = v;
    *(s16*)(a0 + 0x5C) = *(u16*)(a1 + 0x2);
    if (*(s32*)(a1 + 0x4) != 0) {
        *(s32*)(a0 + 0x20) = ((s32 (*)(s32, s32))func_8001CFDC)(0x26, 0x85);
        if (*(s32*)(a0 + 0x20) == 0) {
            guess_FreeActorDuringSpawn((void *)a0);
            return 0;
        }
        guess_InitModelObject(*(s32*)(a0 + 0x20), *(s32*)(a1 + 0x4));
    }
    if (*(s32*)(a1 + 0x8) != 0) {
        *(s32*)(a0 + 0x58) = *(s32*)(a1 + 0x8) | 0x60000000;
    }
    return 1;
}
