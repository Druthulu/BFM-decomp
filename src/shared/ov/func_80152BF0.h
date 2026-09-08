/* func_80152BF0 — shared body (overlay slot 0x80128158, h_exact 1da4cc8c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80062C14;
extern void func_80019064(void *a0);
extern int func_80151204(int arg, int a1);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
void func_80152BF0(s32 a0)
{
    func_80019064(&D_80062C14);
    func_80151204((int)a0, *(s16 *)((s32)a0 + 0xF2));
    func_80149020((s32 *)a0);
    func_80146CA0(a0);
}
