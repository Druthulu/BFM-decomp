/* func_801300F4 — shared body (overlay slot 0x80128158, h_exact 9a31add0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_StartActorSequenceById(s32, s32);
extern s32 guess_DistSqToPlayer(s32);
extern s32 guess_PlayActorSound(void *a0);
extern s32 guess_CallActorEventHandler();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
void func_801300F4(s32 a0) {
    s32 done = 0;
    s32 r;
    *(u8 *)(a0 + 0xC1) = 0xD;
    if ((*(u32 *)(a0 + 0xB4) & 0x2000) != 0) {
        *(u16 *)(a0 + 0x5C) = 0;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(u16 *)(a0 + 0x98) = 0;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        r = guess_StartActorSequenceById(a0, 0x27);
        if (r != 0) {
            *(u8 *)(a0 + 0xC3) = 1;
        } else {
            *(u8 *)(a0 + 0xC3) = 0;
        }
        r = guess_DistSqToPlayer(a0);
        if (r < 0x9000) {
            r = ((s32 (*)(s32, s32))guess_PlayActorSound)(a0, 0x30);
            done = 1;
            if (r != 0) goto skip;
            ((s32 (*)(s32, s32))guess_PlayActorSound)(a0, 0x31);
        } else {
            r = ((s32 (*)(s32, s32))guess_PlayActorSound)(a0, 0x31);
            done = 1;
            if (r != 0) goto skip;
            ((s32 (*)(s32, s32))guess_PlayActorSound)(a0, 0x30);
        }
        done = 1;
    }
skip:
    r = ((s32 (*)(s32, s32))guess_CallActorEventHandler)(a0, 0x25);
    if (r != 0) {
        done = 1;
    }
    if (!done) {
        ((void (*)(s32, s32))func_80131E00)(a0, 6);
    }
}
