---
ts: 2026-11-06T21:02:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_D8pAzKjTSzcH7pcTMatT
---
C0414's dead-reset CSE-breaker: `p = expr; f(..., p); p = 0;`. Dead reset after use invalidates cse equivalence; flow deletes it. But here the issue is combine folding a copy into the defining insn, not cse equivalence. Hmm.

Actually maybe the mechanism is different. Let me get the cc1 dump to see which pass folds. Let me use delever_search --explain? `--explain TU FN` reads one body's residual (no writes) but with the current tree body, not a candidate. There's `--try ... --keep` to keep scratch and print the candidate object path. Hmm.

Maybe tools/cc1_dumps_tu.sh can dump. Let me check how to generate cc1 dumps for a body. Actually simpler: use the --keep flag to get the candidate object and maybe assembly. Let me check what scratch --keep leaves.

Let me try: `--try TU FN file --body --keep` and see.

Actually, let me first try the do-while move and a few variants quickly, since scoring is cheap.

Item 1 variants:
A. Keep pin, no asm, wrap `ang = a;` in do{}while(0):
```
do { ang = a; } while (0);  // !FAKE: do-while
```
This splits EBB; combine operates within basic blocks; the do-while may create a NOTE_INSN_BLOCK boundary but not necessarily a basic block boundary (no jumps). cse1 EBB split is about the extended basic block; combine works on basic blocks. Hmm.

B. Dead-reset: after `ang = a;` add `a = 0;`? But a is a hard-reg pinned variable; assigning a=0 emits a set of $4 = 0, then dead → flow deletes. But it might interfere. Actually this would create another set of $4 after the copy, making $4 live? No. Let's test.

Actually the cleanest: make the andi's destination $4 used twice by assigning `ang = a` and also using `a` in the d comparison? Not in target.

Let me think about the actual fold. Which pass turns `$4 = and(v0,0xfff); ang = $4` into `ang = and(v0,0xfff)`? That's copy propagation (or local-alloc coalescing where ang and the andi's dest pseudo are merged). If `a` is a hard reg $4, the andi dest is $4 (hard). `ang` is a pseudo. The copy `ang = $4` can be eliminated by *replacing ang with $4* only if $4 is live throughout — it isn't (calls). So the copy must stay; but the diff showed andi s0, meaning the andi's destination was changed to s0 and the copy deleted. That is what local-alloc does: it can allocate the andi's result pseudo to the same reg as ang, but the andi dest is hard $4, not a pseudo...

Unless: `register asm("$4")` in GCC 2.7.2 does NOT make the variable a hard register in the RTL; it only sets a "preferred register" / it's a pseudo with a hard-reg constraint applied at local-alloc? Let me recall GCC 2.7.2 behavior: `register int x asm("$4")` — "In the MIPS port, this is used..." Actually GCC docs: "You can specify a register for a variable using `register ... asm("regname")`... The variable is placed in that register." It creates a pseudo with DECL_RTL = (reg:SI 4) hard register. Hmm.

But local-alloc can then handle it: a hard reg used as a variable is a "user variable" and local-alloc tries to keep it in the hard reg, but if it can't (live range conflicts), it may copy to a pseudo. Actually local-alloc doesn't reassign hard regs.

Given the diff, the andi dest became s0, meaning the andi was emitted with a pseudo destination, not $4. So maybe `a` is a pseudo whose allocation is forced to $4 by local-alloc only when possible; and the copy-prop merged ang and a into one pseudo before allocation, and that pseudo got s0 (because $4 conflict? no...). Hmm.

Let me just get the RTL. I'll use --keep and inspect. Let me look at what delever_search does. Maybe it has --explain that shows pass-level residual. Let me try `--explain` with a candidate? No, --explain takes TU FN only.

Better: check tools/cc1_dumps_tu.sh usage.
