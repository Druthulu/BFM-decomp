---
ts: 2026-10-17T12:51:08.166Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm checking whether L_in is only reachable via the jump itself, which would make it a candidate for the skip_blocks pattern—a branch jumping over a block that nothing else branches into. The preceding bne instruction isn't a barrier, so this particular case doesn't qualify for the follow-jump optimization as cleanly as I'd hoped.

I'm checking whether making NUSES on L_in at least 2 prevents both the follow and skip paths in cse, but then wondering how a second use of L_in could survive into cse2 if thread_jumps or jump2 redirects one of the branches away first — maybe the bne t,5 is somehow the surviving second reference, though its actual target is elsewhere, so that doesn't quite work either.

I'm reconsidering the order of passes: thread_jumps only runs after cse1 (per toplev.c), while jump_optimize itself handles jump-to-jump chains and conditional jumps that skip over unconditional jumps, plus detecting jumps to a label followed by a conditional jump with the same condition — that mechanism might be the one responsible for retargeting here.

Actually, I suspect it's reorg's delay-slot filling logic instead: relax_delay_slots and fill_slots_from_thread thread a conditional jump through another conditional jump sharing the same (or reversed) condition, redirecting the branch target in the process.

So if cse1 doesn't fold the branch and thread_jumps redirects beq t,3 after that pass, I need to check whether cse2 would then see the label at L_in with zero uses and fold the fallthrough path from bne t,5 across it.

Actually thread_jumps itself likely catches this since it compares the two conditions' register values directly, meaning the beq t,3 at L_in gets threaded to 054 before reorg even runs — so the scenario requires L_in to retain multiple uses to survive that threading.

I'm thinking about a natural source pattern like `if (t == 3 || t == 5)` and whether reorg's jump threading, rather than thread_jumps itself, is what collapses the two jumps into L_in. I've spent about 20 minutes on this class now, so I should try a concrete example to test the hypothesis.
