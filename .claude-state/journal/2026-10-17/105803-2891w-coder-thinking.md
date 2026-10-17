---
ts: 2026-10-17T16:58:03.686Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm trying to identify which pseudo-registers correspond to which variables, comparing reference counts and liveness between var_s2, var_s3, arg0, and arg2 to figure out the ordering constraints needed.

The jump from 8 refs/live 72 to priority 3333 means arg0 needs one more reference and var_s2 needs one more too. I'm considering whether the loop structure (goto loop vs a real structured loop) affects reference weighting, which could complicate things, so I'm looking for a simpler way to just add one extra use of arg0 somewhere in the existing code, and similarly add one more reference to var_s2.

I recall that in old GCC flow analysis, both uses and sets of a register get counted toward reg_n_refs, weighted by loop depth — so adding a second assignment to var_s2 would itself bump its ref count. I'm also wondering if some keepalive-style reference near the loop head was originally meant to compensate for a variable used earlier via inline asm, before the label.

Actually, stepping back, the real explanation is probably that loop.c's strength-reduction pass split a single induction variable into two: if the source had something like `for (p = base; p < end; p += 0x10C)` iterating over an array of 0x10C-byte structs, the compiler would naturally generate a second induced register for `p + 0xE` as a separate giv, which matches the var_s2/var_s3 split I'm seeing.

I notice 0x801202A0 + 0x6480 equals exactly 0x80126720, so both bounds likely originate from the same expression — the compiler probably constant-folded `&arr[0x6480/elemsize]` into the literal end address, making the entry test and loop test reference the same computed endpoint even though they appear as separate symbols.

So the goto-loop structure stays, but I still need an extra reference each to arg0 and var_s2 without inserting dead code. I'm considering swapping one of the var_s3 uses for var_s2 to satisfy that.

Maybe computing var_s2 as var_s3+0xE inside the loop each iteration instead of once before, but that changes the codegen pattern from the target's single addiu before the loop. I'm also checking if arg2's reference count can drop to push its priority below arg0's threshold.

That field load from arg2 needs a reload, so I can't trim that reference further. Looking at var_s3's usages now, there are nine references including the entry bound comparison which double-counts var_s3 since it appears on both sides of the inequality; rewriting that comparison against the raw constant might let CSE collapse it into a single register reference.

I'm also considering whether var_s2's reference count could be bumped by adding a genuine use right after its initialization, though swapping in an offset relative to var_s2 instead of var_s3 would shift the displacement and break the match. Since goto-based loops don't carry loop-depth notes the way structured loops do, converting the goto loop into an explicit while or for loop with a break might change how flow weights these references by loop depth.

If structured loop notes get added, that depth-2 weighting would roughly double in-loop reference counts and shift the relative priorities between arg0, arg2, var_s2, and var_s3 -- I'm trying to work out whether that tips the register allocation in the direction I need or just creates a new tie.

Testing a candidate loop structure where var_s2 is initialized from var_s3 plus a small offset before entering a do-while that checks a condition and returns early...

Still writing loop variant...
