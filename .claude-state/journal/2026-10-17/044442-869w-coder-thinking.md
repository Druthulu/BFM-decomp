---
ts: 2026-10-17T10:44:42.825Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm working out which variable, k or m, becomes the canonical "head" based on whose last use extends further—if m is used later, past the inner loop, it would take over as head and CSE might canonicalize k's uses within the extended basic block to m instead.

I realize cse operates per extended basic block, and since labels with multiple predecessors end a block, the loop body is a separate block from the preheader—so uses of k inside the loop body won't get rewritten to m unless -fcse-follow-jumps is in play. But within the preheader itself, any use derived from m would canonicalize to the head register. I'm also considering whether k's assignment itself (e.g. a load or sign-extension) gets CSE'd to be equivalent to m's value, which would make k inherit m's equivalence class without an explicit copy.

Trying another angle: what if the multiply by 4 happens before the branch, in a totally different block from the loop—then block boundaries make this irrelevant. For the `k = m` copy itself, cse decides which register becomes canonical based on which one's last use (by cuid) comes later; since m's last use is actually that very multiply instruction, which occurs before k's last use inside the loop, k ends up as the head unless m has some later use outside the loop I'm missing—like if the outer loop's increment also referenced m.

Maybe loop.c isn't doing invariant code motion here but strength reduction instead, since k stays invariant inside the inner loop while the address computation still happens inside the target code. That suggests k is its own source variable, or possibly a result of type narrowing—like m being a u16 that gets compared against a sign-extended i, which would explain the separate load and extension steps.

I'm considering whether the lhu load into a HImode pseudo gets treated as already zero-extended by combine, since MIPS's LOAD_EXTEND_OP for HImode might be defined as ZERO_EXTEND, which would let combine track the nonzero bits from the load itself rather than inserting an explicit andi mask.

That's unless t3v is computed before k, or m stays HImode so the extension differs. I'm trying to work out how to tip the reference-count ratio so j gets priority over k—j needs about 14 refs versus k's 13, so maybe adding an extra inner-loop use of j that combine folds away after flow analysis would do it.

I'm wondering if the exit test could read j directly instead of a temp variable, giving three more references that way.

I'm leaning toward s16 j given the branch instruction used. Since all prior analysis pointed to keepalive being necessary, I'm trying another angle: whether loop depth weighting changes if the outer construct isn't counted as a true loop, which would shift the ref-weighted scores for j versus k and potentially flip the comparison.

I'm also considering whether wrapping the inner loop in an extra do-while(0) nesting adds another loop_depth level, which could again alter how j's and k's weighted reference counts compare against each other.

Wondering if the two loads could be hoisted, but the signedness differs between arms so that won't collapse. I also consider whether k2's multiply could derive from something other than k, but tracing through the cse blocks shows m would need to stay live into the loop either way, which seems worse. Stepping back, I think I need to reconsider what the target computation actually is.

The copy of k into a3 happens at the preheader, which fits. So the original source likely had j with more references than k since j appears in more conditional branches within the loop. I'm trying to reconstruct the original programmer's loop structure, picturing something like a check against D_80115140 indexed by k, feeding into related byte and halfword arrays at index k with different strides — that pattern would explain why k's live range needs to start before the loop.

Let me reconsider whether k is actually some player or item index derived from b[0], and whether the second branch computes a different index entirely rather than reusing k directly, which would change how many references k truly has in the source.

Maybe register allocation reused a3 for a different pseudo in arm B that's actually a copy of k, rather than k itself being reused three times—so it's not necessarily the same variable semantically. I keep going back and forth, so let me instead try writing natural source code where k is declared at the top of the `if (i == c3)` block, assigned from b[0], and m gets eliminated entirely to see if that produces matching codegen.

k outlives m and becomes the class head (cse.c:853-858), so any `m` in the preheader gets replaced with k. I'll run more structural probes next: merging m into k, giving m a later use, testing `do`/`while` loop forms, and narrowing k.
