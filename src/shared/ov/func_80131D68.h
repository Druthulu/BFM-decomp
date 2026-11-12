/* guess_HandleActorEventDefault — shared body (overlay slot 0x80128158, h_exact 4640feb0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 guess_CallActorEventHandler();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
extern s32 func_8002A04C(s32 a0);
extern void guess_FreeActor(void *a0);
/* guess_HandleActorEventDefault: common reply to event a1 & 0xFF: 2/0x1B switch the object to state 0x12; 0x1A/0x1C run its 0x11 handler, else free it
 * Confidence low, code inference: c = a1 & 0xFF: 2, 0x1B -> func_80131E00(a0, 0x12); 0x1A, 0x1C -> guess_CallActorEventHandler(a0, 0x11) or guess_FreeActor(a0)
 * Names ledger: config/names.tsv guess_HandleActorEventDefault */
int guess_HandleActorEventDefault(int a0, int a1)
{
    s32 s0 = a0;
    s32 c = a1 & 0xFF;
    if (c == 2 || c == 0x1B) {
        func_80131E00((struct S80131E00 *)s0, 0x12);
        return 1;
    }
    if (c == 0x1A || c == 0x1C) {
        if (((s32 (*)(int, int))guess_CallActorEventHandler)(s0, 0x11) != 0) {
            return 1;
        }
        if (*(s32 *)(s0 + 0x78) != 0) {
            func_8002A04C(s0);
        }
        guess_FreeActor((void *)s0);
        return 1;
    }
    return 0;
}
