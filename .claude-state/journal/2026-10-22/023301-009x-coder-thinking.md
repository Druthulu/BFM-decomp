---
ts: 2026-10-22T08:33:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_WzK5UWLNR43bFxaOpnCn
---
So target has `q` in v1 ($3), lever-free gives a0 ($4). Interesting: `lw a0,100(s0)` in mine loads into a0 — so gcc even used a0 for the load (probably because of the "sh v0,2(a0)" and the arg a0 dying).

Wait, actually in mine, `q` got a0 because arg `arg` is in a0 and dies after `ptr = arg->unk64`; then `q` load `((Unkstruct*)arg)->unk64` reuses a0.

Target uses v1 for q and the constant 0x9000 also v1.

How to make gcc allocate v1 ($3) for q without pinning? Options:
- Use v1 by making q's live range across blocks and have enough register pressure so that a0 isn't preferred.
- Note in target: `lw v1,100(s0)` — the base is s0 not a0! So in the target, `arg` was copied to s0 (callee-saved) because it's live across the switch call? Let's see the full target asm.

Let me get the target asm. Where's it? Maybe in build/. Let me look at the explain output more: mine vs target only differ in those 4 lines, so the prologue is the same (both have s0). Good.

So mine: q in a0, target: q in v1. Since the base s0 is used in both, the difference is just the destination register of q's 4 uses.

Ideas to push q into $3:
1. Make q used more so it gets a higher priority register? But local-alloc gives $3 to the constant 0x9000. Hmm, in the target, the constant 0x9000 is also in v1. That's fine since constant dies.

Actually the note says: local-alloc runs first and gives $3 to the block-local constant 0x9000, then global-alloc may not reuse $3 for the global q (conflict set is block-granular), so q falls to $4.

If the constant 0x9000 were not in $3 in my version... it is in both.

Hmm. What if the comparison `func_8012BD14(ptr) > 0x9000` is restructured so that the constant 0x9000 is not materialized in $3? E.g. `> 0x9000` vs `>= 0x9001`? That changes the instruction (li 0x9001) but that changes code. Target uses li v1,0x9000? Wait, the constant and q both sit in $3 — but "the constant and q do not overlap in life". Let me look at the actual target asm to know exactly.

Let me find the target asm file. Search for a directory with asm for these functions.

Actually, the explain tool prints the diff; I could ask for the full asm via some tool. Let's check what files exist: build/? Let me look at the project structure quickly.
