/* func_80172E20 — shared body (overlay slot 0x80128158, h_exact 946b56ed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80127508;
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
void func_80172E20(u8 * a0)
{
    Unkstruct_801202A0 *p = (Unkstruct_801202A0 *)D_80127508;
    u16 sp10[3];
    sp10[0] = p->unk4.i.hi.u;
    sp10[1] = p->unk8.i.hi.u;
    sp10[2] = p->unkC.i.hi.u;
    if (func_80171AB0(a0, sp10) == 0) {
        func_80171A1C((u8 *)a0);
        func_80174650(a0);
    }
}
