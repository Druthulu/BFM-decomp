---
ts: 2026-11-06T23:53:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cswafkrGdzlvFeKVwGOl
---
I need a .c TU file. For resident.c, I can pass src/resident/resident.c directly (it's a .c file). But it must be the *candidate* body to see the dumps of the lever-free version. Hmm, I'd need to splice my win.c into the TU. That's what --try does internally.

Alternatively, dump the ORIGINAL TU (with the pin/launder) to see the allocno table — that shows the pinned version, not the lever-free one. I need the lever-free one.

Hmm, maybe simpler: use --try --keep to get the candidate object and then... but I need the .greg dump.

Wait — maybe I can use `tools/cc1_dumps_tu.sh` with a spliced TU. I can create a spliced copy of resident.c with my win.c body under my item dir. That's a big file (resident.c could be large). Let me check its size.

Actually — is this item worth that effort? The budget is 20-30 min per item. I've spent ~10 min on item 1. Let me be pragmatic.

The reg swap: base s4, mode s3. This is a "global-pri-bank-order" style wall (see walls.txt: `global-pri-bank-order`). Several WALLs in moves.md for that tag. Hmm.

But maybe there's a simpler C lever: make `mode` have more refs or shorter live range. For example, declare mode later / set it later. Currently `mode = -1` is at line 970 before the if. What if mode is initialized at declaration? Same.

What if `mode` is used in an extra place? Not allowed (changes bytes).

Alternatively, make `base` live longer or have fewer refs — e.g., use a different expression for one base access. Hmm.

Hmm wait. Actually, maybe the allocation isn't global at all for mode/base. Let me reconsider: maybe local-alloc handles them because... no.

Let me test the hypothesis with a cheap experiment: change the ORDER of variable declarations? No effect on allocation.

Let me look at this from the "what did the original source look like" angle. The pinned version has base in s4 and mode in s3. Since s3 is reserved, base takes s4 — meaning base was allocated AFTER other allocnos took s0,s1,s2. So in the pinned version, the allocation order was: cnt→s0, file→s1, val→s2, [s3 reserved], base→s4. And mode is pinned so not in the order.

Lever-free: base→s3 means base is allocated after cnt,file,val (s0,s1,s2 taken) and then base gets s3, mode gets s4. So base is allocated BEFORE mode in both cases; the only difference is that s3 is free.

So mode is allocated AFTER base in both. That means mode's priority < base's priority. For mode to get s3 lever-free, mode must be allocated BEFORE base. So I need mode's priority > base's priority.

pri(mode) = floor_log2(refs_mode)*refs_mode/live_mode
pri(base) = floor_log2(refs_base)*refs_base/live_base

base: refs = number of REG references in the allocno (global.c counts n_refs as the number of references to the register in the function). base is used ~10 times → let's say 11. live_length ~ 110.
mode: refs ~5, live ~90.

To flip, I could increase mode's refs by 1 or 2, or shorten its live length.

Hmm, but changing refs changes the code (an extra use = extra insn). Unless the extra ref is a *use in a place that already has one* — e.g. replacing `mode >= 0` with `mode > -1`? Same refs.

What about `mode = -1` → does that count as a ref? A def counts.

Alternative: reduce base's priority by increasing its live length: start base's live range earlier (move `base = D_800AF630;` earlier in the function). Hmm, that doesn't change the emitted bytes if the assignment is already first. Actually `base = D_800AF630;` is at line 964, before file/val computations. In the target, base's lui/addiu is at 10d8, AFTER the file/val loads. So sched1 sunk it. The live range in RTL is from the set to the last use. Moving the C statement earlier doesn't change the RTL position much.

Hmm, what about making base die earlier? No, it's used to the end.

What about giving mode fewer live insns? mode is set at 10ec and last used at 1278. That's fixed.

Alternatively: increase base's live_length by... it's fixed.

Hmm, what if we split `base` into two variables? No, changes code.

What if we add a *dead* use of mode early? That changes refs and maybe code (deleted later, zero bytes). E.g. `mode = mode;` — a dead self-copy, flow deletes it. But the cse/flow counts... allocno_n_refs is computed in global.c from the RTL after... hmm, n_refs comes from `reg_n_refs` computed by flow. A dead copy might be deleted before global-alloc (flow runs before global-alloc). So it wouldn't count.

What about a real use that's optimized away? Hmm.

OK, alternative: maybe I'm wrong that mode and base are global allocnos; maybe they're in the same basic block(s). Let me just get the dump. It's the reliable path. Let me create a spliced TU.

Actually, easier: `--try --keep` keeps the scratch and prints the candidate object path. Maybe the scratch dir also has the .i or dumps. Let me check delever_search's Scorer for what it keeps.

Actually, let me try the most promising C-level experiments first (cheap), then dump if needed.

Experiment ideas for the reg order:
- Move `mode = -1;` to before the `st = func_8002F648();` call (changes live range? it would extend mode's live range, making it WORSE).
- Move `mode = -1` after the if? Can't, it's the default.
- Declare mode inside the function but initialize at declaration: `s32 mode = -1;` then remove `mode = -1;` — the set moves earlier (at declaration point). That EXTENDS live range → worse.
- Make mode's last use earlier? It's used at 1278 (`if (mode == 0 ...)`).

Hmm. To make mode's priority higher, shorten its live length: move `mode = -1;` LATER, closer to the first use. Currently at line 970 (before the if). First use is `mode >= 0` at line 1000. If mode is set at 970 and first used at 1000, live = 30 insns before use. Moving `mode = -1;` down to just before the if (line 1000) shortens live by ~5 insns (the cnt call etc.).

Actually in the target, `li s3,-1` is at 10ec, which is BEFORE `cnt = func_80029504()` (1100) and before the if (1208). Wait, the target's `li s3,-1` at 10ec is in the delay slot of `beq v0,v1` at 10e8. And `move s3,zero` at 10f4 in the delay slot of beqz. So mode=-1 is set right at the if (st comparison), i.e., sched1 hoisted it. Hmm, in the C, `mode = -1;` is before the if, and `cnt = func_80029504()` comes after the if. So in the RTL order, mode=-1 is right before the if. OK.

So mode's live range: from the set (right before the if) to the last use at 1278. That's from ~insn 34 to 139 → 105 insns.

base's live: set at 10d8 (insn 29) to last use 12ac (insn 139?) → similar.

Both long.

refs: base ~11, mode ~5.
pri_base = floor_log2(11)*11/110 = 3*11/110 = 0.3
pri_mode = floor_log2(5)*5/105 = 2*5/105 = 0.095

To flip we'd need pri_mode > pri_base: e.g. refs_mode = 16 → floor_log2(16)=4, 4*16/105=0.61. That's a big change.

Hmm, that seems impossible without changing code.

So maybe my model is wrong. Maybe base and mode are NOT global allocnos; maybe local-alloc assigned them. local-alloc assigns in BIRTH order for blocks with 3 quantities, etc.

Wait — actually! Maybe base is NOT a single pseudo. Look at the target: `lui s4; addiu s4` for D_800AF630, and then all the `lui at,0x1; addu at,s4,at; lh v1,-23592(at)` — base is used as a base register with constant offsets. So base is one pseudo in s4.

And mode in s3.

Hmm, what if these are assigned by local-alloc? local-alloc assigns a pseudo only if its live range doesn't cross a basic block boundary. base is live across many blocks (the if arms), so no.

Unless... hmm.

Wait, maybe the answer is that global-alloc allocated them but the *order* is different from my priority model because `allocno_n_refs` counts differently (e.g., base's refs might be lower, or the live_length computation differs).

Let me just get the dump. I'll splice the lever-free body into a copy of resident.c and run cc1_dumps_tu.sh. But resident.c is big. Let me check its size first.

Actually, `tools/cc1_dumps_tu.sh` accepts a .c FILE directly. So I can make a copy of resident.c with my body spliced. Let me check the size of resident.c.
