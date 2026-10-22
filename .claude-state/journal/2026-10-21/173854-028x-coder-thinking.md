---
ts: 2026-10-21T23:38:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_9dCS0akEeSWm7zYuvmeF
---
Baseline confirmed: pinned body scores 0 (39 ins both). nopin scores 17.

Interesting: the class is "OTHER" not COUNT — because the difference is register mapping.

Now, how many includers? I need to know N to verify all. Let me check via the tool: `--plan`? or the ledger. Let me try `tools/delever_search.py --plan --only func_8014C308` to see copies count. Or check `dl.includers()` via some tool output.

Alternative: grep the repo for who includes src/shared/ov/func_8014C308.h.

Let me do: grep -rn "func_8014C308.h" src/ | wc -l and see files. That's the includer count (each includer = one TU file that #includes it).

Let me now think about the actual crack for item 3.

Target asm (39 ins) vs mine (41). Let me get the full target listing to reason. Let me dump the target function's instructions. I can get them from the diff output, but a full listing is better. Is there a tool to dump? `tools/cc1_dumps_tu.sh` and `tools/alloc_table.py`. Also the object: build/<md_MAIN_xxx>/... Let me find the baseline object for the TU.

Simplest: run --try with the nopin candidate and look at the whole diff (it prints the aligned diff, which shows most of both). Let me get the full output of nopin scoring (I have it above, 17 score). Let me reconstruct the target instruction list from that diff:

target:
```
0:  (?)
...
20  bnez v0,6ab8
21  li v1,9
22  beq a2,v1,6abc
23  li v0,1
24  li v1,17
25  beq a2,v1,6abc
26  li v1,41
27  beq a2,v1,6abc
28  li v1,10
29  beq a2,v1,6abc
...
34  j 6abc
35  ...
```
Hmm target[29] is `beq a2,v1,6abc` while mine[29] is `bne a2,v0,6aac` — because in the target, the last comparison `if (arg2 == v1) return v0;` is followed by fall-through to the final return expression. Mine has `bne` (jump if not equal) to the tail, target has `beq` to return. Different branch polarity due to code layout.

Also target[23] `li v0,1` placed after the first beq — meaning in the target, the assignment v0=1 is NOT hoisted to the top of the block; it's placed after the first comparison's branch. And in mine: `move v0,zero` at 21 (?), `li v0,9` at 22.

Hmm, mine[21] `move v0,zero`: where does that come from? In mine, "v0" is the const-chain temp (since I named the const temp v1 but gcc assigned it $2 = v0!). Right: in mine, gcc allocated the const-chain pseudo to $2 (v0) and the "1" value to $3 (v1). So mine[21] `move v0,zero` is... hmm, the const chain temp set to 9 would be `li v0,9` (mine[22]). The `move v0,zero` at 21 is a `return 0` → v0=0 in mine? Wait mine has `return 0` paths → li v0,0 → "move v0,zero"? But that's the const-chain temp's register... no: `return 0` sets the return register $2 = 0 → "move v0,zero" — yes! v0 is the return register $2. So in mine, $2 is used both as the return value register and as the const-chain temp. That means the const chain temp got allocated $2 (v0), so `return 0` (move v0,zero) and the const temp collide.

Hmm wait, that's weird: `return 0` writes to $2, and the const temp also in $2 — but they're in different blocks so they can share.

So mine: the "1" value is in $3, and const chain in $2. Target: "1" in $2, const chain in $3.

The fix: make the const-chain temp get $3 and the 1-value get $2.

Ideas:
(a) Make the "1" value not a variable but the literal 1 in each return: `return 1;` → then gcc emits `li v0,1` at each return site (5 sites) — target has only one `li v0,1`? Actually target has li v0,1 at 23 only, and returns v0 at the 5 arms. Hmm, if we write `return 1` in 5 places, gcc would produce 5 `li v0,1` → 5 sets → the flow might merge them (since v0 is the return reg, each block sets it). Target has one li v0,1 → so the source uses v0=1 once, as in the original. So keep v0=1 assignment but make gcc allocate it $2.

(b) Increase the "qty"/refs of the v0 pseudo so local-alloc prefers it for $2: local-alloc assigns $2 to the pseudo with the highest qty in the block? The const chain temp v1 has 4 sets + 4 uses = 8 refs; v0 has 1 set + 5 uses = 6 refs. So const temp wins $2. To flip: make v0 have more refs, or make v1 have fewer.

Idea: eliminate the v1 temp entirely by writing the constants directly:
```c
if (arg2 == 9) return v0;
if (arg2 == 0x11) return v0;
if (arg2 == 0x29) return v0;
if (arg2 == 0xA) return v0;
```
Then gcc generates `li v1,9; beq a2,v1` etc. — the constants need a register: gcc will use a pseudo for each, but since each is used once, gcc may allocate them all to $3? Hmm, in the target each `li v1,X` is a separate set of the SAME pseudo v1 (the original source's v1). If we inline the constants, gcc creates 4 different pseudos, each with one set and one use; local-alloc might give them $3 each (they're not live simultaneously)... but they'd be "different" pseudos, so the target bytes would differ? No — bytes would be the same: `li v1,9; beq a2,v1; li v1,17; beq a2,v1; ...` — identical bytes if each gets $3. Hmm! Because the register is the same $3 in each case. But the alloc could differ (e.g. $3,$4,$5,...). Since each pseudo is short-lived (set then used immediately), gcc's local-alloc might reuse the same register... not guaranteed.

But note the target has `li v0,1` at position 23 (after the first beq) — the source order v0=1 comes before v1=9, so the target's `li v0,1` is NOT at the start. Interesting: so in the target, the v0=1 set is delayed (sched1 moved it). gcc's scheduling moved the `li v0,1` after the first branch.

Let me look at the whole picture: I'd like the full target asm. Let me get it via the diff of a candidate that is wildly different (more diff output) or better, find the baseline object and objdump it.

Where's the baseline object? oracle.baseline_path(rec["obj"]). Let me find the object for the TU that includes this header. Let me grep for includers of the header.

Let me do: grep -rln "func_8014C308.h" src/ | head; and then find the corresponding build object.

Actually simpler: build/asm/md_MAIN_XXX/*.s? Let me check the structure of build/asm/md_MAIN_001.

Let me look.
