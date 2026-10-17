---
ts: 2026-10-17T12:39:54.307Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm thinking a call already acts like a near-barrier since it flushes memory and sets reg_last_sets for call-used registers, so if loop notes attach to the CALL_INSN, everything before it (argument setup, stores, loads) becomes a dependency, and since calls set reg_pending_sets_all, everything after it depends on the call too.

So moving anything across a call insn is already essentially blocked, meaning notes attached to a CALL_INSN would be mostly harmless. The real question is whether notes could end up between the argument-setup moves and the call itself, which seems impossible given how expand_call emits instructions, or attached to the first real instruction after the call in the next block.

I'm testing whether a0/a1 argument setup could legitimately precede a barrier-inducing store, which seems inconsistent with source order unless the loop body's final statement is the call itself — but that runs into the same block-boundary problem. I wonder if the LOOP_END note could instead land at the very end of the function.

But the barrier would then attach after the note, right before "la", forcing the prologue's sw ra to stay before la — which contradicts the target ordering of la before sw ra. So I'm checking whether reordering the first loop insn avoids that conflict, trying putting the store as the leading instruction instead of the base-address load.

Actually I should stop guessing and go look directly at how cse determines the end of the EBB at LOOP_BEG.
