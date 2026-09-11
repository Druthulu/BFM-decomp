void func_80180E24(void *a0)
{
    void *s1;
    void *s2;
    void *s0;
    s32 t;
    s32 v0;
    s32 *p;
    s16 out[4];

    s1 = a0;
    s2 = *(void **)((u8 *)s1 + 0x2C);          /* +0x2C: owner record */
    v0 = *(u16 *)((u8 *)s1 + 0x2);             /* +0x02: state word   */

    if (v0 == 0) {
        s0 = (u8 *)s1 + 0x24;                  /* +0x24: 4-word scratch */
        *(s32 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x20) = (s32)&D_801890BC;
        *(u8 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x27) = 0x43;

        /* one shared base for the 0x1A/0x18 pair (§193-E: naming it collapses
         * the two CSE intervals into the single `lw $v1,0x20($s1)` reload) */
        p = *(s32 **)((u8 *)s1 + 0x20);
        *(u16 *)((u8 *)p + 0x1A) = 0x2800;
        *(u16 *)((u8 *)p + 0x18) = 0x2800;

        func_80128EA8(*(s32 *)((u8 *)s1 + 0x20), (s32)s0, (s32)&D_801890C8);

        *(u16 *)((u8 *)s1 + 0x2) = *(u16 *)((u8 *)s1 + 0x2) + 1;
        func_80128ED8(*(s32 *)((u8 *)s1 + 0x20), (s32 *)s0);
        *(s32 *)((u8 *)s1 + 0x1C) = 0;         /* +0x1C: frame timer */
    }

    t = *(s32 *)((u8 *)s1 + 0x1C) + 1;
    *(s32 *)((u8 *)s1 + 0x1C) = t;

    /* duplicated call+return in both arms; cross_jump merges the scheduled
     * common SUFFIX into the target's one shared block (§193-C / law 22) */
    if (t >= 0x16) {
        func_801292C8((u8 *)s1);
        return;
    }
    if (*(s16 *)((u8 *)s2 + 0x36) != *(s16 *)((u8 *)s1 + 0x30)) {
        func_801292C8((u8 *)s1);
        return;
    }

    if (t < 4) {
        v0 = (t * 5) << 9;                     /* 0xA00 per frame ramp */
        p = *(s32 **)((u8 *)s1 + 0x20);
    } else {
        p = *(s32 **)((u8 *)s1 + 0x20);
        v0 = 0x2800;
    }

    *(u16 *)((u8 *)p + 0x1A) = v0;
    *(u16 *)((u8 *)p + 0x18) = v0;
                                                * pair FIRST in its block so the
                                                * next call's arg setup cannot
                                                * float above it (required --
                                                * removing it costs 6 ins) */

    func_8012F214((s32)s2, (s32)&D_801890D0, (s32)out);
    *(u16 *)((u8 *)s1 + 0x6) = out[0];
    *(u16 *)((u8 *)s1 + 0xA) = out[1];
    *(u16 *)((u8 *)s1 + 0xE) = out[2];

    *(u16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x2C) = 0xC040;
}
