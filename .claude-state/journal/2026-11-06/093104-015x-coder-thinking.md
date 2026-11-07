---
ts: 2026-11-06T16:31:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9buVGt8HevZ95OidtoRS
---
So the RM1 idiom: `tmp = (s16)t; u = tmp;` — the s16 temp copy escapes cse, so the copy `u = t` survives (as `move v1,v0`? Actually here `u = tmp` where tmp=(s16)t). Interesting: the copy is u←tmp, and t is used later (`if (t == 0)`, `t = u - 1`). So t is live across the copy → the copy can't be tied. And the HImode tmp escapes cse.

For our function: we want `ret` (v1) to be a copy of the call result (v0), and ret used at the test and the andi, with the call result... hmm, in RM1, t (the original) stays live across the copy and is used later. In our target, after the move v1,v0, v0 is dead (the andi writes v0 from v1). Hmm, but wait: is v0 really dead? `andi v0,v1,0x8000` overwrites v0. So v0's value (the call result) dies at the move. So a copy from v0 to v1 with the source dying at the move → local-alloc would tie. Unless the copy is HImode (tying for HImode?).

Actually! Here's the thing: local-alloc's tying only applies to certain insns; an HImode move might still be tieable. But cse merges copies. Hmm, but the RM1 trick's key is cse, not tying. Let's think: `u = (s32)(s16)t` where the source t is live → the copy is not tied because t doesn't die.

For our target, is there a way to keep the call result live past the move? What if `m` is derived from the call result (v0) rather than ret? Then andi would read v0. Not target.

Alternatively, maybe the copy's source is not the call result but... Let me reconsider the target: `move v1,v0` then `beqz v1` then `andi v0,v1,0x8000`. What if the source C is:

```c
s32 t = func(...);
s32 ret = (s16)t;   // HImode copy
if (ret == 0) ... else if ((m = ret & 0x8000) != 0)
```
Then: t = call result (v0). ret = (s16)t → a truncation. In MIPS, (s16)t then assigned to s32 ret requires sign extension: `sll v1,v0,16; sra v1,v1,16`. That's 2 insns. Unless ret is s16/u16 (no extension), giving just `move v1,v0` and the HImode pseudo.

But t is dead after (unless used). Tying: if t dies at the copy, local-alloc may tie. Hmm, but with HImode and SImode mismatch, tying isn't allowed (different modes) → the move stays! That could be the trick: `u16 ret = (u16)t;` where t is the SImode call result. The move v1←v0 stays because tying requires same mode... Actually does it? Tying happens in block_alloc's tie loop using regs with different modes? The comment says "two registers... tie two registers". Mode mismatch probably prevents.

Then `ret == 0` on u16 → beqz v1 (HImode, fine). Then `m = ret & 0x8000`: if m is s32, gcc needs to extend ret (u16) to SImode first → `andi v0,v1,0xFFFF` then andi 0x8000? Hmm, but if m is u16 too: `m = ret & 0x8000` HImode → `andi v0,v1,0x8000` and `m != 0` → bnez v0. That's exactly target!

Wait, but earlier I tried ret u16 with `ret = func(...)` directly (w1_r16) and got 104 ins (score 7). That's because `u16 ret = func(...)` may have generated an extra insn. Let me check the diff of w1_r16.

The difference in my new idea: a separate SImode t for the call, then `ret = (u16)t` HImode copy. Let's try:
```c
s32 t;
u16 ret;
u16 m;
t = func(...);
ret = (u16) t;   // HImode move
if (ret == 0) {} else if ((m = ret & 0x8000) != 0) {...}
```
Hmm, but cse: t is SImode, ret is HImode — different equivalence classes, so the copy stays. And ret = t's low half: the move v1,v0.

Wait, but the target's move is v1,v0 full 32-bit — a HImode move in a register is still a full move. Good.

But then the test `ret == 0` on u16: HImode comparison to 0 → beqz v1 if upper bits known zero. Hmm, gcc might emit `sll v1,v1,16; beqz` — actually for HImode, a value in a register has undefined upper bits in gcc's model? No — in gcc 2.7.2, HImode values in registers are stored in the low 16 bits with the upper bits *undefined*? Actually the MIPS ABI for gcc 2.7.2: QImode/HImode values are kept sign/zero-extended? The `movhi`/`extendhisi2` patterns exist. For a comparison `(ne (reg:HI) (const_int 0))`, gcc emits `sll; sra` or uses `bne` on the reg? Since the move from v0 gives an arbitrary upper half, a beqz would be wrong unless the upper bits are known. gcc's `movhi` pattern for MIPS may generate `sll`/`srl`? Hmm.

But the target `andi v0,v1,0x8000` zeroes upper bits, so m is fine. For ret's test, gcc knows ret came from a truncation (subreg) of t, so the upper bits are... unknown. So it'd emit an extension. That's why w1_r16 had 104 ins (one extra).

Hmm, but wait: in w1_r16 I wrote `u16 ret; ret = func(...)`. The call returns SImode; assigning to u16 ret means a truncation. gcc would then need to extend for the test. It got 104 (one extra). So close! Let me look at w1_r16's diff to see exactly what's extra.

Let me get the full diff for w1_r16.
