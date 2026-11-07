---
ts: 2026-11-06T12:28:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_65CyOXjAEffN8B74aOLM
---
The do-while(0) technique is legitimate and noted with `// !FAKE: do-while` comment. The constraint says "`do{}while(0)` only with `// !FAKE: do-while`". Good.

Now: can a do-while(0) block split make the fall-through head ineligible? The block boundary emits a NOTE (BLOCK_BEG/END), not a barrier. reorg's fill_slots_from_thread stops at... `stop_search_p(trial, !thread_if_true)`. Let me read stop_search_p. Also, importantly, note that cse1's EBB split means the code layout gets a NOTE_INSN_BLOCK_BEG — hmm, that wouldn't affect reorg.

But maybe a do-while(0) creates NOTE_INSN_LOOP_BEG/END which mostly_true_jump scans! "If this is the test of a loop, it is very likely true. We scan backwards from the target label. If we find a NOTE_INSN_LOOP_BEG before the next real insn, we assume the branch is to the top of the loop" → returns 2.

Where's the target label? At the increment (2238 region). So if a NOTE_INSN_LOOP_BEG sits immediately before that label, prediction = 2.

Hmm, when gcc deletes a do-while(0) loop, does it delete the notes? In jump.c/loop.c, deleting a loop removes the LOOP_BEG/END notes usually. But C0535 shows an effect on cse1's EBB, so the block split is real (BLOCK_BEG note or CODE_LABEL?).

Actually, cse1's EBB splitting: cse1 splits at labels/branches; a block boundary... Hmm, in gcc 2.7.2 cse.c EBB: it processes insns and stops at a CODE_LABEL. A do-while(0) creates an extra CODE_LABEL? Possibly yes — the loop's head label, and when the loop is deleted, a label may remain (but unused labels get deleted).

Let's just experiment. Try wrapping the increment in do-while(0), then the if, and see the score. Cheap.

Candidates:
- c3: c2 + `do { i = i + 1; panel = panel + 0x20; } while (0);  // !FAKE: do-while`
- c4: c2 + wrap the if statement in do{}while(0)
- c5: c2 + wrap the call statement in do{}while(0)

Let me write them all and run sc.sh.
