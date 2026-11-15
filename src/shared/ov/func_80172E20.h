/* func_80172E20 — shared body (overlay slot 0x80128158, h_exact 946b56ed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80127508;
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
void func_80172E20(u8 * a0)
{
    Unkstruct_8017C218_2 *p = (Unkstruct_8017C218_2 *)D_80127508;
    u16 sp10[3];
    sp10[0] = p->unk6;
    sp10[1] = p->unkA;
    sp10[2] = p->unkE;
    if (func_80171AB0(a0, sp10) == 0) {
        func_80171A1C((u8 *)a0);
        func_80174650(a0);
    }
}
