/* func_80149374 — shared body (overlay slot 0x80128158, h_exact 26721d91). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);
void func_80149374(s32 arg0, s32 arg1)
{
    u64 sp10;
    u64 sp18;
    ((void (*)(s32, void*))func_80015978)(arg1, &sp10);
    {
        void *q = &sp18;
        ((void (*)(s32, void*, void*))func_8012F14C)(*(s32*)(arg0 + 0x20) + 0x34, &sp10, q);
        __asm__ __volatile__("" : "=r"(q));  /* LOAD-BEARING: kills the (plus sp 0x18) CSE class reg; emits 0 bytes */
    }
    ((void (*)(void*, s32))func_80015954)(&sp18, arg1);
}
