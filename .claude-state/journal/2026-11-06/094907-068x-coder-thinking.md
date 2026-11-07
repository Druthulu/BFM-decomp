---
ts: 2026-11-06T16:49:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n2o38CLQgUJZJrI0kXe2
---
o01 still has the same rotation (v0→$v1, v1→$v0) — the split didn't help the global allocation; global-alloc still gives v1 $2.

The difference between target and mine is exactly a $v0/$v1 swap for the two source locals. The shift temp isn't a separate pseudo in o01? Let me see the first block. The diff starts at mine[23]. Let me look at the head.

Actually, the issue is global-alloc priority: v1 (short-lived) beats v0.

Idea: make v1 and v0 ONE variable? They hold different values simultaneously (v0 = loaded u16, v1 = field sum). Can't.

Idea: reduce v1's priority by making it live longer globally. v1 is currently used in block1, both branches, and JOIN. If we *reuse* v1 for something else later (extending its live range), its priority drops. But that changes code/registers.

Idea: increase v0's priority by adding refs (zero-byte references). C0385: "RAISE A BIV's global_alloc PRIORITY WITH A ZERO-BYTE REFERENCE INSTEAD OF PINNING IT". A zero-byte reference! E.g., a use that produces no instruction. For a variable, what use is zero-byte? A use in a context that folds... but it must survive to global-alloc (which runs after jump1/flow/cse/combine).

Hmm, "zero-byte reference" in C0385 — how was it done? Probably a reference in a `do{}while(0)` or a dead-ish context that still counts as a ref in the RTL but emits nothing? If it emits an insn, not zero bytes. Maybe an address computation that folds?

Actually, refs for global-alloc are counted from the RTL (reg_n_refs). A reference that survives but emits no instruction... hard.

Wait, maybe simpler: the target's assignment could be reached by making v0's live range shorter *globally*. v0 is live from its first use to its last use across the function. If we split v0 into several variables (per region), each has a shorter live range and higher priority. Then the *first* v0 (in block 1) might outrank v1.

o01 split only the index; let me try splitting v0 into per-region variables: v0a (block1), v0b (branches), v0c (JOIN), v0d (K). But the target uses $2 for all of them — if their live ranges are disjoint, they can all share $2. And each gets high priority. But adding 3 variables changes the decl list; if the live ranges are disjoint, no extra registers.

Hmm, but the branches: v0 is set in the if-branch and the else-branch; those are different blocks, so splitting per branch is natural.

This could work but it's a big rewrite. Let me first try a smaller change: split v0 in the first block only (o01) — didn't help. So the global priority of v0 vs v1 didn't change. Hmm, because v0 is still live from block1 through the whole function (v0 used in JOIN and K). So splitting the first-block use didn't shorten v0's global range.

Wait, o01 introduced v0i for the index; v0 is still born at the lhu in block1 and lives to the end. So no change.

Let me split v0 so that the block1 instance dies at the test: use a separate variable for the *branches* onward. E.g., v0 (block1) dies at the test; v0b (branches) born in the if-branch. Then v0's global live range = block1 only (short!) → high priority → likely beats v1.

But wait, v0 is assigned in each branch and used in JOIN. If we rename all post-test uses to v0b, then v0 (block1) dies at the test. v0b is born in the branches. Their live ranges are disjoint (block1 ends at the branch). So both can get $2.

Let me do this: rename every `v0` after the first `if ((s32)(v0 << 16) < 0)` block to `v0b`, and declare `s32 v0b;`. Careful with the JOIN/K regions.

Actually the source structure:
```
v0 = unk70; v0 *= 2; at = D4 + v0; v0 = *(u16*)at;
v1 = ...; v1 += v0; store;
if ((s32)(v0<<16) < 0) {          // v0 used here (test)
    v0 = unk70; ... v0 = *(s16*)at; a0r = v0; v0 = v0-0x30;
    if (v0 >= v1) { store a0r; }
} else {
    v1 = (s16)v1;
    v0 = unk70; ... v0 = *(s16*)at; a0r = v0; v0 = v0+0x30;
    v1 = v1 < v0;
    if (v1 != 0) goto JOIN;
    store a0r;
}
JOIN:
if (!func_8012BEE8(s0)) goto K;
v0 = unk70; ... v0 = *(u16*)at; s0->unk1C = v0; func_8012C588(...);
K:
v0 = unk70; if (v0 == 0) func_8017F348(s0);
```

If I rename the v0 in the branches/JOIN/K to v0b, then v0 is used only in block1. Let me try.

Also, alternatively rename only the branch uses.

Let me generate this carefully with a Python script that operates on the tail portion.

I'll split at the line `    if ((s32)(v0 << 16) < 0) {` — everything after that (v0 occurrences) becomes v0b.

Let me write it.
