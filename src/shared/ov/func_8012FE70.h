/* func_8012FE70 — shared body (overlay slot 0x80128158, h_exact 684e947e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131E00(Unkstruct_801202A0 *a0, s32 a1);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern s32 guess_CallActorEventHandler(int);
void func_8012FE70(s32 a0) {
    s32 v1 = *(s32 *)(a0 + 0xC4);
    *(u8 *)(a0 + 0xC1) = 9;
    if (v1 & 2) {
        *(u8 *)(a0 + 0xC1) = 1;
        KR_AS(s32, guess_CallActorEventHandler)(a0, 3);
    } else if (v1 & 1) {
        func_80131E00((Unkstruct_801202A0 *)a0, 1);
    } else {
        if (*(s32 *)(a0 + 0xB4) & 0x200) {
            func_80131170(a0, 0, 0);
        }
        KR_AS(s32, guess_CallActorEventHandler)(a0, 0x1E);
    }
}
