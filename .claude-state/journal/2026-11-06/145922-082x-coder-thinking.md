---
ts: 2026-11-06T21:59:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FKzWsVfoFS9aYX5H2nMr
---
Best is 24 (u06 = dst s16, tmp u16; u13 = dst u16, tmp u16). Still 24.

The main residual is the lh/lw (8 sites = 16 mismatches?) plus tmp.

Hmm. Let me think about fixing the lh→lw. If dst is a 16-bit variable, the compiler narrows the load. Can we force the full word load while keeping the 16-bit qty? 

What if the *source* declares dst as `s32` but we introduce an intermediate 16-bit variable only at the load? e.g.:
```
{ s16 d16 = *(s32 *)(arg0 + 0xD0); dst = d16; }
```
No, dst is s32 then, and the truncation+extension adds insns.

Alternatively, declare dst as `s32` and use `(s16)` in the *address* computations to make the qty HImode? The addresses are `dst + 6` etc.; casting to s16 in each use would create a new s16 pseudo per use — not one kept pointer.

Hmm.

Let me look at what exactly the target's dst qty is. In the target, dst is SImode in v1. Our s32 lever-free gives a2. The s16 gives v1 but with lh.

The allocation difference for SImode: qty priorities. Maybe a different lever (not type) can move dst to v1: e.g., the order of the dst block statements, or the number of temporaries.

Let me examine the target's dst block vs ours (s32) more: ours has dst=a2 and temps v1,a0; target dst=v1, temps a0,a1. The temps are the same instructions. So the qty set is identical; only the allocation order differs.

What determines it? The pin. Without it, local-alloc gives dst a2 because dst's qty has lower priority (long life) and the temps take v1/a0? Wait, temps are short-lived (higher priority) so they take the low regs first: v0 ($2) for the loaded value, v1 ($3) for the first temp, a0 ($4) for the next. Then dst (long-lived) gets a1/a2.

In the target, dst=v1 ($3) and temps a0/a1 — meaning dst was allocated BEFORE the temps (higher priority or a suggestion). Since dst is long-lived, its priority is low. Unless... dst has a *copy suggestion* to $3 in the target (from the pin). Or the target's dst qty is short-lived because it's re-loaded? No, kept.

So again, the target's dst in $3 is almost certainly from a hard-reg preference/pin in the original source. Lever-free, local-alloc will not give a long-lived pointer $3 when short-lived temps compete.

BUT the s16 variants changed the priorities enough to give dst $3 (because the HImode qty has a different size/mode affecting ties). That's a promising direction: make the SImode qty behave like the HImode one *without* changing the load width.

What made the s16 dst qty win? Let me dump the RTL for t09's dst block and compute. Actually, maybe the key: with dst s16, the load `lh` result is HImode, and the address computations use SUBREG (s16→s32), creating different pseudo lifetimes (each use may create a new SI pseudo from the subreg!). That changes the qty set substantially.

Hmm.

Alternative idea: keep dst s32 but add a real C move that creates a copy tie to $3. For instance, the target's dst might be the *return value* of something? No.

Let me look at the score-24 diff (u06) to see if the tmp part can be fixed. If I can get the tmp part right, maybe the dst lh is the only issue left (16 mismatches).

Actually, what if we accept dst as s16 (lh) but change the *source* so the compiler emits `lw` by making the high bits observable? For example, use `dst` in an expression that requires all 32 bits, like `*(u16 *)(dst + 0xFC)` where dst+0xFC might overflow 16 bits? The compiler knows the address. If we add a use like `if ((u32)dst & 0xFFFF0000) ...` — adds code.

Alternatively, the target's `lw` might actually be `lh` in disguise? No.

Hmm, what about declaring dst as `s32` but making the *pointer arithmetic* use `(s16)`? no.

Let me look at this from a different angle: maybe the original source didn't use a `dst` variable for the pointer but rather `((Unkstruct *)arg0)->unkD0` directly, and GCC's CSE kept it in v1. Let me test: replace `dst` uses with a direct field expression. But the target keeps dst in one register across 8 statements — CSE would do that if the memory isn't modified (stores to dst+6 don't alias arg0+0xD0? They might alias! If pkt could alias arg0, CSE can't keep it). Actually dst = arg0->unkD0, and stores to dst+6 could alias arg0+0xD0, so CSE wouldn't keep it. The target keeps it, so it was a local variable.

Let me test the direct-expression variant anyway (it would reload each time → mismatch).

OK, time check: I've spent ~1h40m total. Items 2 and 4 need resolution. The best lever-free is 24 (vs 135). That's a big improvement but not a crack. Per the rules, WALL requires ≥30 tries — I have 35 + 21 + 1 = 57 scored tries. Good.

But wait — maybe I should keep pushing a bit since 24 is close-ish and the same move helps both twins. The remaining issues: 8 lh/lw + tmp bank.

Let me inspect u06's diff fully to quantify.
