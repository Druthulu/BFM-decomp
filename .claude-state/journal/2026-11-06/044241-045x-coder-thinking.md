---
ts: 2026-11-06T11:42:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mx64xtfL3r2EvYkGbXA8
---
Baseline 0, 33 insns. Now create a lever-free body. Remove zr pin, both `+ zr` opaque copies, and the memory barrier.

Original:
```c
s32 func_80182334(s32 a0v)
{
    s32 a1;
    register s32 zr __asm__("$0");
    u8 *a2 = D_80126948;
    s16 v0;
    s16 v1;
    s32 d0;
    s32 cpy;
    s32 result;
    s32 frame_pad[2];

    a1 = a0v + zr;

    if (*(s16 *)(a1 + 0xD0) < 0x28) {
        v0 = *(s16 *)(a1 + 0xD0) + 8;
    } else {
        __asm__ __volatile__("" ::: "memory");
        v1 = *(s16 *)(a1 + 0xCE) + 2;
        d0 = *(s16 *)(a1 + 0xD0);
        cpy = d0 + zr;
        *(s16 *)(a1 + 0xCE) = v1;
        *(s16 *)(a1 + 0xCC) = v1;
        if (v1 <= d0) {
            goto skip;
        }
        v0 = cpy + 2;
    }
    *(s16 *)(a1 + 0xD0) = v0;
skip:
    (void)&frame_pad;
    result = *(s32 *)(a1 + 0xDC) - ((Unkstruct_80126948 *)a2)->unk38;
    if (result < 1) {
        result = 0;
    }
    return result;
}
```

Lever-free:
```c
s32 func_80182334(s32 a0v)
{
    s32 a1;
    u8 *a2 = D_80126948;
    s16 v0;
    s16 v1;
    s32 d0;
    s32 cpy;
    s32 result;
    s32 frame_pad[2];

    a1 = a0v;

    if (*(s16 *)(a1 + 0xD0) < 0x28) {
        v0 = *(s16 *)(a1 + 0xD0) + 8;
    } else {
        v1 = *(s16 *)(a1 + 0xCE) + 2;
        d0 = *(s16 *)(a1 + 0xD0);
        cpy = d0;
        *(s16 *)(a1 + 0xCE) = v1;
        *(s16 *)(a1 + 0xCC) = v1;
        if (v1 <= d0) {
            goto skip;
        }
        v0 = cpy + 2;
    }
    *(s16 *)(a1 + 0xD0) = v0;
skip:
    (void)&frame_pad;
    result = *(s32 *)(a1 + 0xDC) - ((Unkstruct_80126948 *)a2)->unk38;
    if (result < 1) {
        result = 0;
    }
    return result;
}
```

But the comment says `a1 = a0v + zr` is the entry `addu $a1,$a0,$zero` opaque copy. Without it, `a1 = a0v` might be coalesced (a1 and a0v same reg) — removing the copy. The target has `addu a1,a0,zero` (a real copy). Real C to keep a copy: use an HImode trick? a1 is a pointer (s32). The comment says the copy keeps a1 in $a0 and... Hmm.

Also `cpy = d0 + zr` keeps the load in $a0 and the addiu operand in $v1.

Let me first just drop the levers and see the score, then apply HImode tricks if needed.

Also the memory barrier: "the else-arm re-load of 0xD0 is a genuine second lh: cse's memory table reaches into the not-taken arm, so a plain re-read there is folded onto the entry load — the zero-byte "memory" clobber invalidates it without volatile's lhu+sll/sra cost." So the barrier forces a second load of 0xD0 (d0 = *(s16*)(a1+0xD0)). Without the barrier, cse folds d0 into the earlier load. Need real C to force a re-read. Options: make the first load not visible to cse, or use a different access. Hmm.

Let me first drop everything and see the score/diff.

Let me write nopin.c for item 2.

Note: `frame_pad` and `(void)&frame_pad` — is `(void)&frame_pad;` a "keepalive macro or asm"? It's not asm; it's a real C statement that forces the frame. The kind list is barrier,pin; frame_pad is neither. But is `(void)&frame_pad;` a "keepalive macro"? The brief says no "keepalive macro or asm". Hmm, `(void)&frame_pad` is a keepalive-ish construct (it keeps the frame alive). But it's not a macro; it's a real C expression. And the kinds are barrier,pin, not keepalive. The constraint says "Lever-free = none of the row kinds in <dir>/kinds remain". frame_pad isn't in the kinds. But "no new lever of any kind" and "levers of other kinds the def already had (pins under other causes) may stay, never added". frame_pad is a lever of another kind (frame padding) that the def already had — may stay. OK keep it.

Actually wait — is `(void)&frame_pad;` an "identity address spelling" launder? The brief says "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". Hmm, `(void)&frame_pad` is an identity address spelling used to force a frame. But it's not being used to fake a match — it's a frame-size lever. The constraint says levers of other kinds the def already had may stay. I'll keep it; it's not barrier/pin.

Let me write the lever-free body.

Actually, let me reconsider `a1 = a0v + zr`. To keep an opaque copy in real C, the HImode trick: e.g., `s16 tmp = a0v; a1 = tmp;`? No, that would truncate. Hmm.

Let me just try the plain drop first and see how many diffs.

Let me write nopin.c.
