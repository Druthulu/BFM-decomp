---
ts: 2026-11-06T10:37:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eNSm2jLLZ64NeNZQXO3Q
---
Interesting: nobar (pins kept) → all constants go to v1 in mine, target v0. So the barrier's removal changed local-alloc priorities? Or rather, the barrier made... wait, no. With barrier kept and pins kept, orig = 0. Without barrier, constants use v1 instead of v0.

Why? The memory barrier (`__asm__ __volatile__("" ::: "memory")`) probably forces... hmm, it shouldn't affect allocation of constants. But it changes basic block structure! An asm volatile is a scheduling barrier; it may split basic blocks or change REG_N_REFS? Actually no. Hmm.

Wait, maybe the barrier is at the point after `unk5C = 0x8000` and before `t = unkC4`. It splits the block. Without it, the block is bigger; local-alloc's qty allocation order changes (block-local alloc processes in insn order; with more insns in one block, the pseudo for v0 (pinned t) ...). But t is pinned to $2, so v0 is taken. Hmm, but these constants are before the t load.

Actually, `li v1,1` vs `li v0,1`: the constant 1 used for two stores. In target it's v0. With barrier removed it's v1. The difference: the block got bigger, and local-alloc assigns regs per block in order of qty priority (number of refs * length). Adding the barrier creates a new basic block boundary, so the constants and the t load are in different blocks and get allocated independently. Without the barrier, the whole tail is one block, and t (which is pinned to $2 → v0 taken) conflicts... no, t comes after.

Hmm, actually local-alloc runs over each basic block: it allocates qty's in priority order, considering regs already allocated (global regs). The t pseudo pinned to $2 is a global? Pinned hard regs are global alloc? The pin makes t hard reg $2, i.e., a "global" hard register, which reserves v0 for the whole function? If t is a local register variable, it's a hard reg used in the function; global alloc may consider $2 used... Actually with `register s32 t __asm__("$2")`, t is a local-alloc pseudo assigned to hard reg v0 (a local register var → allocno?). Hmm.

The observed: with barrier, constants get v0 and t gets v0 too?? Both can't. Let me look at orig's actual output around that region.

Let me dump the target object's insns for this function. Easier: use dt.sh with orig (score 0) won't show diff. I can use `delever_search --try ... --keep` and objdump. Or there's hdump.sh. Simpler: use tools/cc1_dumps_tu.sh? Hmm.

Alternatively, score orig with a modified target? No.

Let me just reason from the target instructions (we know target from the diff context). In the target (from the earlier full diff of nopin):
```
28 lw v0,196(s0)      <- t load
29 lui v1,0
30 addiu v1,v1,0
31 sw v1,88(s0)
32 ori v0,v0,0x2
33 sw v0,196(s0)
34 li v1,16384
...
```
Wait earlier the full nopin diff showed target[28:34]: lw v0,196; lui v1; addiu v1; sw v1,88; ori v0,2; sw v0,196. And target[35] li v1,16384.

Hmm so in target, t is v0 and the address constant v1, and 16384 is v1. In nobar (pins kept: t pinned $2 = v0), the constants BEFORE the load got v1 (because v0 is reserved for t by the pin? no—the pin only covers t's live range). Wait, nobar's diff shows mine has `li v1,1` etc at 20-28 where target has `li v0,1`. So with t pinned to v0, local-alloc can't use v0 for the constants in the same block?? But target uses v0 for those constants AND for t later. In target, these constants and the t load are in different basic blocks — because of the barrier! The barrier splits the block, so the constants (block A) can use v0, and t (block B) can use v0 too.

So the barrier is load-bearing for allocation: it splits the EBB so that v0 is free for the constants in the earlier block. Without it, t's pin to v0 reserves v0 across the merged block, so the constants go to v1.

That's the mechanism. So we need a lever-free way to split the block or to not pin t but still get t into v0.

Since we must remove the pin anyway, t is not pinned. Then in win0, the constants: mine had `li v1,1`? Let me check win0's diff. In the nopin score (pins removed, barrier kept) the constants region wasn't in the diff, so they were correct (v0). So with the barrier kept and pins removed, constants are fine; t gets v1 and address v0 (6 insns swapped).

In win0 (both removed) we saw 66 ins due to extra s0/s1 copy, plus likely the swap.

Hmm wait: nopin (barrier kept, pins removed) = 66 ins. That extra copy is not from the barrier. Let me re-read the nopin diff: yes 66 ins with s1/s0 two-copy.

So the two problems are independent:
(A) removing the s0 pin → two copies / extra callee-saved.
(B) removing the t pin → t in v1 instead of v0 (with barrier kept), and removing the barrier → constants in v1.

Let me tackle (A) first. Why two copies? Let me test a variant: `void *s0 = a0;` at declaration. And a variant with the local renamed and the parameter used directly for the first store.

Actually maybe the extra copy arises because `s0` is a local that is live across the `func_8012C1B8` call and also across `func_8012CAE4`; global alloc... no, a single pseudo. Two moves in prologue means two pseudos: s1=a0 (pseudo P1 = the local s0) and s0=s1 (P2 = ?). Hmm, which uses s0 vs s1?
- index 8: `sw v0,32(s1)` — so the store unk20 uses s1 (P1).
- index 10-11: `move a0,s1; j ...` — the call func_8012CAE4(s0) uses s1.
- later: `lw v1,196(s0)`, `sw v1,88(s0)` etc use s0 (P2).

So uses after the barrier-ish point use P2, uses before use P1! That suggests the compiler made a copy of the local at some point: `s0 = s0;`? No...

OH. I bet it's the type cast: `((Unkstruct_800B5CB8 *)s0)->unk20 = v0;` and `*(s32 *)((s32)s0 + 0x20)` and `(s32)s0`. Hmm no.

Wait — could it be that `s0` is assigned twice? In nopin.c the declaration is `void *s0;` and `s0 = a0;`. One assignment.

Unless... gcc's "register variable" removal changed the C semantics: `register void *s0 __asm__("$16")` was NOT an assignment target? No, it is.

Hmm, let me look at the actual nopin.c file to make sure the sed didn't mangle.
