/* func_801708B0 — shared body (overlay slot 0x80128158, h_exact 07865805). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801484B0(s32 a0, s32 a1);
extern void func_80149350(s32 arg0);
extern s32 func_8014C168(s32*, s32);
extern void func_80171928(void *a0);
void func_801708B0(void* a0)
{
    extern void *D_8011F738;
    u16 sp10[4];
    u16 sp18[4];
    short *r;
    func_801484B0((s32)&sp10, (s32)&sp18);
    ((void (*)(s32, void *, void *))func_80149350)((s32)a0, &sp10, &sp10);
    r = (short *)((s32 (*)(s32, s32))func_8014C168)((s32)a0, (*(s32 *)&D_8011F738));
    r[3] = sp10[0];
    r[5] = sp10[1];
    r[7] = sp10[2];
    func_80171928((void *)a0);
}
