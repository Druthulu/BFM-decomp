---
ts: 2026-11-06T07:45:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mvveRCVO0BbEtSf4HNY0
---
v5/v7 got the `w3c = *(u32*)twicep` load into a0 (the REG-mixed s5→a0 issue is gone!), but now the L.o1 pointer (`addiu a0,sp,16` vs v1) is off: mine uses v1, target a0, and it's scheduled one insn later (delete at 59, insert at 61). So the split made the loaded value get a0 (good) but the pointer var `w3d`/`dst` got v1 instead of a0.

Target: `sw a0,60(sp); addiu a0,sp,16` — the pointer uses a0 (reusing the just-stored loaded value's register). In mine v5: the loaded value w3c is in a0 (stored at 60), then the pointer w3d is in v1 (`addiu v1,sp,16`). So I need the pointer variable to reuse a0.

In v5, w3c dies at `L.w3C = w3c` (insn 59) and w3d is born at 60. If w3d were assigned a0 (reusing the dead w3c), we'd match. Why did it get v1? Because w3c (a0) and w3d are separate global pseudos; global-alloc might not coalesce them. The ORIGINAL source reuses `w3c` for both (`w3c = (u32)L.o1;`), which is exactly the reuse. But with the single w3c variable, the allocator gave w3c s5 (v1 in v5? no).

Wait: v5 splits into w3c (loaded value) and w3d (pointer). The loaded value gets a0. The pointer gets v1. In the original single-variable version, w3c gets s5 (one variable, range 40..72, too long, conflicts with s5 and gets s5 because... hmm).

Target has the SAME register (a0) for both phases — that's natural for a single variable reused. So the single-variable source should produce a0 for both. But mine gave s5. The difference is the load's dest.

Hmm, v5 shows the loaded value CAN get a0 when it's a separate variable. Then the pointer part needs a0 too. What if I keep the single variable but split the *live ranges* differently: e.g., use w3c for the loaded value, then `w3c = (u32)L.o1;` (reuse). That's the base, which gives s5 for the whole thing. The allocator sees one global pseudo with a long range; it conflicts with s5 (twicep) and takes... s5 anyway? Wait, in w1, w3c GOT s5 (reusing twicep's reg). In v5, the loaded value (shorter range) got a0. So the difference is live length/priority.

So the target's w3c pseudo must have a shorter live range or higher priority to get a0. The target's actual allocation: the loaded value in a0 from 40 to 59, and the pointer in a0 from 60 to 72 — the SAME register, but are they the same pseudo? In the target's original C, probably yes (single variable reused). But the allocation algorithm could give a single pseudo a0 if its range doesn't conflict with s5's range... 

Wait, in w1 the single pseudo got s5, meaning s5 was FREE across its range (twicep died at 40) and a0..a3/v0/v1 were occupied. In target, a0 is free and s5 is taken (twicep live). 

So the ONLY difference is twicep's liveness. To get the single pseudo into a0, twicep must be live across its range.

Back to that. In the target's natural C, twicep must be live across w3c's range (40..72). Is there any evidence of s5 being live there? s5 is saved/restored (callee-saved) but no use after 40. A pseudo can be live without uses (just kept in a register). In the natural C, maybe twicep is live because of a use that is optimized to nothing AFTER allocation? No.

OR: the natural C has a DIFFERENT value in s5 that's live there, and the target's `lw a0,0(s5)` at 40 reads twicep from s5 — so s5 is twicep. If twicep were dead after 40, the allocator could still keep it in s5 and consider it live if there's a REG_DEAD missing. 

Hmm, let me look at the actual conflict mechanism in global.c. r77 (twicep) and r79 (w3c). In w1, r77 dies at 44 (live length 44); r79's range 26. The .greg order has only 79 (r77 is allocated by local-alloc? No, r77 crosses calls → global). The .greg order line "79" means only 79 was allocated globally in that dump? alloc_table said ".greg order: 79". But r77 is also global. Maybe the .greg order line lists only the allocnos in the order for a specific class. Hmm.

Let me look at the .greg dump around r79 and r77 to see conflicts. Let me grep.
