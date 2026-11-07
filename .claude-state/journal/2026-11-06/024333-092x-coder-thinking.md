---
ts: 2026-11-06T09:43:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GTvsuJhMneJyYbRPivsW
---
The label didn't split (jump.c merged/removed the label since it's not a target? or the goto was removed and the label deleted). Score 2.

Hmm. Let me try a label that's targeted by a conditional that's always false but opaque... `if (uVar2 & 0x100) goto L1;` — uVar2 < 7 at that point, so the compiler might not know; the branch would be emitted → extra insns. No.

Let me try `switch` or a `while`? Extra code.

OK, another idea: make the store's address computation depend on the copy. What if the store is written as `*(u16 *)((s32)(s0) + 0x188) = 0;` — no.

What if the store uses a pointer variable that is *also* used by the RMW, defined between the store and the RMW? Hmm.

Let me look at the target's store base: s0 (reg 74 → $16). The copy a0=s0 at 38. So the store used s0 and the RMW used a0.

What if the original C's RMW was written as a *function call*? No.

What if the original C's store was `*(u16 *)(s0 + 0x188) = 0;` and the RMW `*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB;` — the current source. The difference is the compiler's scheduling; the original compiler is the same. So the original C must differ somewhere. Since the function is 57 insns and only this one position differs, maybe the original C had the store written *differently* such that sched1 scheduled it first: e.g., if the store's insn had a higher priority. Priority comes from dependents: an insn's priority = 1 + max over insns that depend on it (LOG_LINKS). If the store had a dependent (an insn reading the 0x188 memory or s0), its priority would rise above the copy's.

What real C makes the store a dependency of a later insn? If a later insn *reads* 0x188. Is there any later read of 0x188 in the target? No. But what about s0: the store uses s0; an insn that *sets* s0 after? No.

What if the store's value (0) came from a variable computed later? No.

What if the RMW's load were from 0x188 instead of 0x44? No (target: lw 68).

Hmm what about the *load* at 39 using a0: the load depends on the copy; the copy depends on... if the copy's source were a value *set by the store*? The copy is a0=s0. If s0 were re-set after the store... no.

What if the source wrote `s0 = s0;` after the store? identity — forbidden and probably folded.

OK. Another thought: maybe the original C's call was `func_801553C0(s0)` but the *RMW* was before the store in source, and the scheduler in the original build moved the store up because of the *load-store ordering* with the RMW's load... In our t3 test, the result was 2. But maybe with the compound assignment and the load first, the scheduler could produce the target. Let me look at t3's actual insn order vs target: same diff (store at 40). So no.

I think it's a WALL. Let me fill the remaining time with a few more tries and then write up.

Actually, wait — one more idea: what if the RMW is written as `*(u32 *)(s0 + 0x44) = (*(u32 *)(s0 + 0x44) & 0xFFFFFFFB);` and the call takes `s0`, but we insert a *real* use of s0 between the store and the RMW that the compiler cannot rewrite: a use in a *call argument*! E.g., the target's call func_801553C0(s0) is after the RMW. What if there were a second call? No.

What about a use of s0 in a *comparison* that the compiler keeps, e.g. `if (s0) {}`? The target has no branch. 

What if the RMW's address expression uses a *different* variable that the compiler must keep: e.g., `u32 *p = (u32 *)(s0 + 0x44); *p &= ~4;` — p is a pseudo = s0+0x44? No, p = s0+0x44 would be computed with addiu into a register; but the compiler folded it (target lw 68(a0)). Fine.

Hmm, what if we use `s0` as an index: `((u32 *)s0)[0x11] = ((u32 *)s0)[0x11] & 0xFFFFFFFB;` — same.

Let me try a batch of ~6 more and then write up. Time 02:43; need until 02:53. I'll do a couple more batches.

Actually, let me reconsider the problem from the target's side: maybe the target's `move a0,s0` at 38 is NOT an arg copy but the *result* of local-alloc coalescing the RMW's base into a0 because the RMW was written with a *separate variable* in the original C:

```
u32 *p = (u32 *)(s0 + 0x44);   // p = s0 + 0x44
*p = *p & 0xFFFFFFFB;
func_801553C0(s0);
```
Here p is computed as s0+0x44 — the compiler could use s0+68 directly (no addiu) — target shows lw 68(a0), so the base is a0 with offset 68. The copy a0=s0 might be the call arg copy.

What if the original C called `func_801553C0((s32)p - 0x44)`? u8 did that = 2.

OK. Let me also try: the RMW as a *post-decrement style*? no.

Let me look at the actual original decompiled C for this function elsewhere in the repo (maybe there's an old non-dedup copy under src/ov_*/ with the same function as a standalone, or in docs/retired — I mustn't read docs/retired). The header is the only source. But maybe there's a `.s` or a comment. Let me grep the repo for func_8016432C references (allowed: grep src/).
