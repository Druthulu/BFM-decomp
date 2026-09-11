void func_801800F0(s32 param_1)
{
    extern s32 func_8012CBF4(s32 a0);
    extern s32 func_80143B6C(s32 a0, s32 a1);

    /* block-scope so it cannot collide with engine_types.h's SVECTOR_8016E7C8;
     * the 8-byte (vx,vy,vz,pad) shape is what puts `in` at 0x10(sp) and
     * `out` at 0x18(sp). */
    typedef struct { short vx, vy, vz, pad; } SVec_80181D08;

    s32 sp20;
    s32 ret;
    SVec_80181D08 in;
    SVec_80181D08 out;
    s16 t;

    sp20 = *(s32 *)(param_1 + 0x20);
    ret = func_8004787C((*(s32 *)(param_1 + 0xE4) << 6) & 0x7C0);
    *(s16 *)(sp20 + 0x18) = *(s16 *)(sp20 + 0x1C) = (ret >> 3) + 0xE00;
    *(s16 *)(sp20 + 0x1A) = (ret >> 1) + 0x800;

    if ((func_8012CBF4(param_1) & 0x2000) == 0) {
        goto TAIL;
    }
    *(s16 *)(param_1 + 2) = 1;
    func_80143B6C(param_1, 1);

    in.vx = *(u16 *)(param_1 + 6);
    in.vy = *(u16 *)(param_1 + 0xA);
    in.vz = *(u16 *)(param_1 + 0xE);
    ((void (*)())func_8012EFB8)(&in, &out);

    /* Both `__asm__ __volatile__("")` below are LOAD-BEARING zero-byte
     * cross-jump barriers (cookbook §5a): without them find_cross_jump
     * tail-merges the two sign arms of each |v| < K test (slti+beqz suffix)
     * and the function comes out 11 instructions short.
     * Their PLACEMENT differs on purpose (§5a addendum / reorg stop_search_p):
     *   - vx block: after the inner `goto`, where the target leaves both delay
     *     slots as nop, so halting the eager scan costs nothing;
     *   - vy block: INSIDE the inner `if`, before the `goto`. The vy block's
     *     join label begins with the division's `lui $v0,0xB60B`, which reorg
     *     steals into both incoming branch delay slots; a barrier sitting
     *     between the `beqz` and the `j` blocks that fall-through scan and
     *     yields `beqz TAIL / nop / j CONT / lui` instead of the target's
     *     `bnez CONT / lui / j TAIL / nop`. */
    if (out.vx >= 0) {
        if (out.vx >= 0xB5) {
            goto TAIL;
        }
    } else {
        if (-out.vx >= 0xB5) {
            goto TAIL;
        }
    }
    if (out.vy >= 0) {
        if (out.vy >= 0x8D) {
            goto TAIL;
        }
    } else {
        if (-out.vy >= 0x8D) {
            goto TAIL;
        }
    }

    /* `t` must be s16, not s32: the target sign-extends once (sll/sra 16) for
     * both clamp tests and keeps the RAW value in $a1 (`addu $a1,$v0,$zero`).
     * With an s32 temp gcc coalesces the two and drops that move (-1 ins). */
    t = (out.vx * 64) / 180 + 0x40;
    if (t < 0) {
        t = 0;
    } else if (t >= 0x80) {
        t = 0x7F;
    }
    func_8002D4C8(0x832, (t | 0x2000) & 0xFFFF);

TAIL:
    *(s32 *)(param_1 + 0xE4) += 1;
}
