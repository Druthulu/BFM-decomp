---
ts: 2026-10-22T20:20:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DejyPrv75KVFVKjbCmNY
---
Interesting! In the score-0 body (og2), r80 (4 refs, live 8, dies in 2 places) does NOT get s1; instead it's allocated in global (order 78 79 80 72) and presumably spilled/rematerialized. In c_struct (cs2), r80 got s1 (local-alloc assigned it!).

Wait, cs2 shows r80 hard s1 with "crosses 2 calls" — in .lreg? The .lreg dump shows the state after local-alloc, which shows hard regs for pseudos that local-alloc assigned. But r80 crosses calls, so local-alloc can't give it s1 (callee-saved across calls requires global). Hmm, the table's "hard" column may come from the .greg order line mapping.

Key difference: in c_struct, there are only 20 pseudos and .greg order is "72" (one allocno), while score-0 has 22 pseudos and .greg order "78 79 80 72" (four allocnos). The score-0 body has MORE global allocnos, and r80 (the m address) is one of them, and it apparently got no reg → remat.

In c_struct, r80 is not a global allocno — because local-alloc gave it s1?? A pseudo that crosses calls can't be local-alloc'd to a callee-saved reg... unless the "crosses 2 calls" note is wrong, or local-alloc assigned it a call-clobbered reg and it was saved... no.

Hold on: maybe the hard column for r80=s1 in cs2 is wrong (the tool takes it from the order line?). Coverage says ".greg order: 72" and r80 shows s1. Where did s1 come from? Possibly the .lreg dump's "Register 80 in 17." line — local-alloc did assign it. Local-alloc can assign a callee-saved hard reg to a pseudo that crosses calls? No — local-alloc only assigns regs to pseudos that die within the block; if it crosses a call it's not eligible for caller-saved... Actually local-alloc assigns regs from `regs_live_at` etc. It can assign a callee-saved reg if the pseudo lives only in the block, but crossing a call means it must be saved — local-alloc avoids callee-saved for call-crossing pseudos unless the pseudo is dead... Hmm, "crosses 2 calls" with live 8: if a pseudo crosses a call, local-alloc can still give it a callee-saved reg? No: local-alloc assigns only registers not live across calls? Let me not guess.

The important actionable difference: in c_struct the m-address pseudo (r80) got a hard reg (s1) at local-alloc, so global never saw it; in score-0 it became a global allocno and lost (spilled → remat).

Why would local-alloc give a call-crossing pseudo s1? Because in c_struct the calls are only 2 crossing (X and Z? no, 3)... "crosses 2 calls" — maybe the pseudo's live range spans 2 calls (between X and Y? no).

Hmm, let me look at the .lreg and .greg dumps directly for the r80 line. Grep in the dump files. The dumps are large (47677-line TU). Use grep with context, narrowed.

Actually, time. Let me think about what C change would make the m-address pseudo become a global allocno that loses (like score-0), i.e., increase the number of global allocnos / make local-alloc reject r80.

In score-0, the movstr is gone? Let's check: score-0's C is scalar assignments; the output still has 3-load groups. Let me diff the two functions' .cse/.lreg dumps around the relevant insns. Better: look at the .greg section for func_8012B4B8 in both and compare allocnos.

Let me grep the .greg dump section for the function. Use awk to extract from "<func_8012B4B8>" to the next function... The dump format: `;; Function func_8012B4B8`. Let me grep line numbers.
