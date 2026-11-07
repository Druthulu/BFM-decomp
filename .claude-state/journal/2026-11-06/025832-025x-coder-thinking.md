---
ts: 2026-11-06T09:58:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6FscpdYbVbGwOtia2jyg
---
b3 (keepalive only) has rv in v1 instead of v0, plus some order differences in delay slots. The target uses v0 for rv. The pin forced $2. Local-alloc chose v1. Why v1? Because v0 is used as scratch (comparison results) throughout, so rv conflicts. The pin forces it.

Could we influence local-alloc to pick v0 for rv without a pin? The target's v0 is the return register; in the real game the function returned s32, so rv was the return value → forced to v0. With void + keepalive, rv is a normal local; v1 is chosen. There's no way to make a void function's local go to v0 (it's a normal allocatable reg, chosen by priority/conflicts).

Hmm, unless we change the return type. Not allowed.

Wait — is it really not allowed? Let me re-read the exact constraint: "no signature or decl change outside the body (callers stay as they are)". Hmm "outside the body" could mean: no decl change outside the body. Signature is a separate item: "no signature ... change". So no.

But wait, maybe the target's void declaration in src is itself a project workaround. Let me check the original real game: the function likely is `s32 func_80182420(s32 a0, s32 a1)`. The TU declares `void` and callers cast. If the project's src has `void` and the fleet baseline object was built from that same src (with pin+keepalive), the target bytes are from the *real game*, not from src. The build/baseline object is the fleet run's baseline — hmm, "the same function in the fleet run's baseline object under build/". Is build/ built from the original game bytes (via splat) or from our src? It says "That target is the tree's own bytes — proven by the SHA1 check". Hmm, build/*.o might be from the original assembly. Let me check: build/src/ov_SC03_124/ov_SC03_124_jr_80181B44.o is a compiled object; the target function has 26 ins. Our src with levers also gives 26 ins and matches. So the baseline object is the original game's object (from splat/asmdiff) or built from a known-good source? Either way, the target is fixed.

So to score 0 lever-free, we'd need v0. If the function returns s32, it would. But changing the definition's return type: would the TU still compile? The callers' extern decls are `extern void func_80182420(s32, s32);` — a conflicting declaration would be an error. But wait, in the scorer, the TU is the src file; the body replaces the definition. The callers' extern void decls come after the definition. If the definition is `s32 func_80182420(...)`, then later `extern void func_80182420(s32,s32);` conflicts → compile error. Unless the scorer only compiles up to... no.

Hmm, but actually the body file we provide replaces the function definition. If we change it to s32, the TU has `s32 func_80182420(...)` then callers `extern void func_80182420(...)`. GCC 2.7.2 might warn (not error) on conflicting types? It's an error in C: "conflicting types for `func_80182420'". Likely error → COMPILE-ERROR. And also forbidden.

So the clone items are likely WALL expand-void-return. But the brief requires ≥30 scored tries for a WALL. Hmm, that's a lot of tries for a clearly impossible thing. But the rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need to do ≥30 tries. Maybe there are 30 variations of real-C moves. But first, let me check whether maybe PARTIAL:keepalive is achievable: keep the keepalive (kind kept) but drop the pin, and get score 0. b3 is keepalive-only at score 6. Can real-C moves make local-alloc pick v0? The target needs v0; with keepalive rv is live but allocated v1. Could we add real C moves to shift allocation? E.g., make v0 free at the end by reducing scratch usage, or give rv higher priority? local-alloc assigns based on qty and conflicts. The target's rv in v0 conflicts with nothing at the end.

Hmm, this is exactly the `lreg-qty-priority` wall: the target's pseudo got v0. In the real game it's the return value.

Let me look at the 3 clones and the 4th item. Item 4 func_8017D730 is bigger and might be crackable with real moves (it has a $2 pin and $3 pin + keepalives). Let me examine whether it's also void: `void func_8017D730(void)`. Yes void. Its v0 is used for computation (t*96>>12). Target keeps v0 as scratch. Without pin, v0 might be allocated differently. Let me test lever-free there.

For the clones, let me first try harder: maybe a real-C move makes rv land in v0 with keepalive kept (PARTIAL:keepalive). What determines rv's reg? local-alloc: rv's qty has refs at various points; v1 chosen because v0 has conflicting qty (the comparison results) across rv's live range? rv is live from first assignment to the end. v0 is used by every comparison (slt results) throughout — so v0 is busy until near the end. At the end, the last comparison `slti v0,a0,16` (target index 19) is dead by index 21. rv live range extends to end. local-alloc assigns v1 because v0 is taken during rv's live range (v0 dies at 19, rv born at 15). Actually rv born at index 15 (li v1,-1). v0 is used at 16-20. So conflict → v1.

To make rv get v0, rv's live range must start after the last v0 use, or v0 must be free. In the target, rv IS v0 and the comparison results also use v0 — they overlap! Target: index 15 `li v0,-1`, then index 16 `slti v0,a0,16` — v0 reused after the -1 branch? Wait the target's `li v0,-1` is in the delay slot of `j 93c` (the return path). So on that path, v0=-1 and return. The other paths continue and use v0 as scratch, then set v0=rv at the end. So the target has v0 as the return value, and the comparisons use v0 because it's free on those paths. The register allocator sees rv (return value) live at the end and gives it v0; the comparison pseudos also get v0 because they're dead before rv's definition. That's fine because the values are in the same register at different times — but local-alloc operates per basic block with conflicts; rv is live across the whole function from its first definition (index 15 in one block) — no, rv is defined in multiple blocks; each definition's live range starts there. The last definition `li v0,31` at index 22 (target). The comparison at 19-20 uses v0 and dies before 22. So v0 is free at the end. In b3, rv got v1 — why not v0? Because in block 15 (`li v1,-1` path), rv is live to the end and v0 is used... Let me see b3's actual asm to understand. But maybe a real-C move can change it.

Let me dump b3's compiled asm? The scorer doesn't keep it. I can use cc1 dumps? Simpler: the diff above shows b3 mine has `li v1,-1`, and in the d<16 path `sll v1,a0,0x1`. So rv=v1 throughout. v0 used for comparisons. So local-alloc picked v1 for rv because v0 is live simultaneously somewhere. Since rv is live from `li v1,-1` to end (block 15), and v0 is used in the same block? In the branch `if (a0>=x) { rv=-1; goto done; }`, after rv=-1 we goto done, so v0 isn't used after in that path. But local-alloc's conflict is per-block and considers all insns in the block: block 15 might include the comparison `slt v0,a0,v1` before `li v1,-1`? The block starts at label 900 (slt v0,a0,v1; beqz; then slt v0,v1,a1; bnez; subu a0...). Hmm, actually rv=-1 is in the `if (a0>=x)` block which is after `beqz v0,914`. In that block, v0 was just used for the slt. rv's live range starts at li v1,-1 and goes to end; within that block v0 is dead after the branch. So why conflict? Maybe local-alloc sees qty v0 live across the block boundary (the slt result v0 is used by beqz in the same insn). Hmm.

Actually, local-alloc assigns registers to each pseudo. The pseudo for `slt v0,a0,v1` has its own qty; it's live only between the slt and beqz. rv's qty is live from li to end. They don't overlap if li comes after beqz. But in the target, rv = v0 and the slt also = v0, so it's fine.

Wait, in b3, maybe rv got v1 because v1 was the register already used for x? No, x is in v1 in target (lw v1). In b3, the `lw` might be v1 too. Let me get b3's full asm. Let me use tools/cc1_dumps? Simpler: temporarily create a small test? Hmm.

Actually, maybe I should look at the target's difference: in b3, `li v1,-1` — rv=v1. But x is also v1 (lw v1). So rv conflicts with x? x is dead after the first if. Hmm.

Let me get the actual asm of b3 via the delever tool with --keep? The brief mentions `--keep` scratch removed after use. Let me check delever_search --help for a way to dump.

Alternatively, use tools/cc1_dumps_tu.sh with a modified TU. That's heavier. Let me first try simple real-C variations on b3 (keepalive only) to nudge allocation.

But actually, the goal per item is a lever-free MATCH, or PARTIAL keeping only some kinds, or WALL. PARTIAL:keepalive means win.c keeps the keepalive but drops the pin and scores 0. That requires rv in v0 with keepalive. The keepalive asm `__asm__("" :: "r"(rv))` forces rv into a register and live; which register? Whatever local-alloc chooses. To get v0, we need allocation changes.

Hmm, but wait: maybe drop the keepalive and keep the pin (PARTIAL:pin) — b2 scored 15 (stores deleted). So pin alone doesn't work; keepalive is needed to keep the stores. So PARTIAL must be :keepalive if achievable.

Let me think about how to get rv→v0 with keepalive. Ideas:
1. Reorder declarations / add a local so that v0 is free.
2. Use `s32 rv` and the keepalive at the end; give rv more refs/priority to win v0? local-alloc doesn't work by priority; it's per-block allocation with preferences.
3. Make the comparisons use a different register (e.g., compute them with a different temp) so v0 is free. But the target's comparisons DO use v0. If our comparisons use a different reg, mismatch.

Actually, let's look at b3's diff again: only 6 differing insns, all register/order. Mine[15] li v1,-1 vs target li v0,-1. Mine[17-19] etc. The issue is purely rv=v1 vs v0 and delay-slot fills. What if we split the `d` computation so that v0 is used less? Hmm.

Let me get the full b3 asm to reason. I'll compile the TU with the body and objdump. How does delever_search --try work? It creates a scratch object. Maybe it leaves it. Let me look at the --try implementation to see if I can dump. Let me grep cmd_try.
