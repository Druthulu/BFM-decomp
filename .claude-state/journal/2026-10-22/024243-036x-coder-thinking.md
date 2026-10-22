---
ts: 2026-10-22T08:42:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_JMlV1HXKzkLbelC3dnMT
---
Note: at the global-alloc stage, the constant 0x9000 is in v1 already (insn 28: `(set (reg:SI 3 v1) (const_int 36864))` and insn 30 slt). So the constant pseudo was ALREADY assigned v1 before global allocation? These dumps (.greg) are printed by global.c at the start of global allocation — and they show the RTL after the "reload" pass? The regs v0/v1/a0 shown are hard regs used in the RTL at that stage. Hmm, in the .greg dump, some pseudos have been assigned hard regs already (those are local pseudos assigned by... hmm, no; the dump shows "Register dispositions" listing 72 in 16, 73 in 4, ... — this is after global allocation? The tool said the .greg dump is the INPUT to global allocation, but the dispositions show assignments.

Hmm, in GCC 2.7 global.c, `global_alloc()` prints the ";; N regs to allocate" and the dispositions at the end (after allocation). Actually the dump function `dump_global_alloc` prints both the conflicts and the final dispositions. So this .greg dump is printed AFTER global allocation. Good: 73 in 4, 74 in 4, 76 in 2, 83 in 3, 72 in 16.

So after global allocation: r73→a0, r74→a0, r76→v0, r83→v1, r72→s0.

Wait, but the final asm has val in v0 and the constant in v1 and q in a0. And r83 → v1. Hmm, r83 is one of the val copies? Earlier the alloc_table said r76 pri 6000 refs 3 live 5 conflicts sp; r83 pri 6000 refs 3 live 5 conflicts v0,sp.

Hmm, if r83 → v1 then the *constant* 0x9000 would be in v1 — but the constant is a local pseudo (in the arm block), assigned by local_alloc later. Hmm, but r83 is in the "regs to allocate" list = a global. So r83 is a global that got v1.

But wait, at the time of the .greg dump, the RTL already has v1 for the constant (insn 28/30) — those are hard regs in the RTL, meaning the constant had already been assigned a hard reg (v1) BEFORE global allocation! How? Because these are the *reload* results? Hmm, in the RTL at global-alloc time, the constant 36864 is in v1 (hard reg). Hmm, that means the constant was already allocated a hard reg.

Ah, I see: in GCC 2.7, `global_alloc` is called AFTER `local_alloc`?? No... Actually the RTL dump shows v1 for the constant because... hmm, in GCC's "expand" phase, constants are often put in a hard reg directly? No.

Hmm, wait. Maybe the .greg dump is printed at the *end* of global_alloc, after allocation, but the RTL dump printed is the *current* RTL at that time (after the allocation was applied). The constant 36864 in v1: that could be the result of local_alloc which ran before? In GCC 2.7 alloc.c: `allocate()` does:

```
  /* Now allocate the hard registers. */
  ...
  global_alloc ();   /* hmm */
```

Let me check GCC 2.7.2 source order... I recall in alloc.c:

```
  /* Perform a pseudo register allocation... */
  ...
  if (obey_regdecls) ...
  /* Allocate the globals and locals */
  ...
```
Honestly the empirical evidence: at global-alloc time, the constant pseudo already had a hard reg (v1) and the pseudos r73/r74 (q copies) were still pseudos. And the final result: r73, r74 → a0.

Why a0? The "preferences: 4" — GCC's global_alloc honors copy preferences: r73 prefers reg 4. Where does that come from? Look at the RTL: insn 43: `(set (reg/v:SI 4 a0) ...)` — hmm this is in a later block. Let me look at insn 43 and 74 (the q loads) — the dump shows them with hard reg 4 already! So at global-alloc time, the q loads' destinations were already hard regs?? That can't be.

Hold on: `insn 43 40 46 (set (reg/v:SI 4 a0) ...)`. Hmm — these dumps might be printed after local_alloc too (the .greg dump is printed in `dump_global_alloc` from global.c; but the RTL dumps with hard regs...).

Hmm, actually! The order in GCC 2.7's alloc.c `allocate()`:

```
  /* Now allocate the hard regs... */
  global_alloc ();  /* hmm, no */
```

Let me actually check: in GCC 2.7.2 alloc.c:

```
static void
allocate (...)
{
  ...
  /* Now allocate the register for each pseudo... */
  ...
  /* Free up the pseudo regs... */
  ...
  /* Perform global register allocation... */
  global_alloc ();
  ...
  /* Now allocate the local registers... */
  local_alloc ();
```
But the dump we see shows hard regs for the constant and the q loads, and the "Register dispositions" showing 73 in 4, 74 in 4 — that's the FINAL allocation, so the dump must be printed at the end of global_alloc AND the RTL shown is post-global-alloc (the dump happens after allocation, showing the RTL with the new hard regs).

Hmm, but then the constant in v1 at insn 28 — was it v1 before global alloc? If local_alloc ran first, the constant would already be v1 (as a local pseudo assigned by local_alloc). And r73/r74 got a0 from global_alloc. And the q loads at insn 43/74 show a0 — consistent with r73/r74 → a0.

So the order is: LOCAL_ALLOC FIRST, then GLOBAL_ALLOC! That matches the note's claim: "local-alloc runs first and gives $3 to the block-local constant 0x9000, and global-alloc then may not reuse $3 for the global q (its conflict set is block-granular)".

Wait, but is that GCC 2.7's order? Actually yes! In GCC 2.7's alloc.c:

```
  /* Now allocate the hard registers... */
  ...
  /* Do local allocation first, then global */
```
Hmm, I recall the opposite in newer GCC (global first). But the note (written by a previous agent who read the dumps) says local first, and the evidence (constant already in v1 at global-alloc time) confirms local-alloc ran first.

So: local_alloc assigned $3 (v1) to the block-local constant 0x9000 (in both arm blocks) — and possibly also $3 to st (r79/r82 → v1, in blocks 2 and 5).

Then global_alloc runs with the globals r73, r74, r76, r83, r72 and their conflict sets:
- 73 conflicts: 73 76 29 → conflicts with itself, r76, sp. So r73 does NOT conflict with v1($3) or v0($2) or a0($4)!
- 74 conflicts: 72 74 83 2 29 → conflicts with r72, itself, r83, v0, sp. So r74 conflicts with v0 but not v1 or a0.
- 76 conflicts: 73 76 29
- 83 conflicts: 72 74 83 2 29
- 72 conflicts: 72 74 83 2 3 4 29 → conflicts with v0, v1, a0!

So r72 (arg in s0) conflicts with v0,v1,a0 — because arg is live across the whole function and v0/v1/a0 are used in blocks where arg is live.

Now, global_alloc picks regs for r73, r74, r76, r83 in that order (the "regs to allocate" order = priority order).

r73: preferences 4 (a0). conflicts {73,76,29}. Available: a0 not taken yet → r73 → a0 (preference honored).
r74: preferences 4 (a0). conflicts {72,74,83,2,29}. a0 is taken by r73 — but r74 doesn't conflict with r73! (r74's conflict list doesn't include 73). So r74 → a0 as well.
r76: conflicts {73,76,29} → conflicts with r73 (which took a0) → so a0 is out. Available: v0, v1, ... r76 → v0? It got v0 (in 2). But v1 was taken by the local constant (block-granular) — r76's conflicts don't include v1 (3) but v1 is used by a local pseudo in the blocks where r76 is live → block-granular conflict → v1 unavailable for r76. So r76 → v0.
r83: conflicts {72,74,83,2,29} → conflicts with v0 (2) → out; v1? not in the conflict list, but v1 is taken by the local constant in the block where r83 is live → out. So r83 → v1? But the disposition says 83 in 3 = v1! Yes: r83 → v1.

Hmm wait, but then r83 (a global) is in v1, and the final asm shows the constant 0x9000 in v1 and val in v0. Hmm, r83 → v1 means r83's value lives in v1. Which pseudo is r83? conflicts {72,74,83,2,29}: conflicts with r72 (arg) and r74, and v0. Since r74 is one of the q copies and r76 the other val copy...

Let's map: r73 and r74 = the two q copies (both prefer a0). r76 and r83 = the two val copies. r72 = arg.

But r83 → v1 in the final allocation. Then in the final asm, val (the value 3/4) is in v0 (r76 → v0) and the other val copy in v1 (r83 → v1)? But the asm shows `li v0,3` and `li v0,4` — both in v0! Hmm.

Hmm, so r83 → v1 must be something else. Maybe r83 is the *call result* pseudo? The call result v0 is a pseudo r79/r82 → v1?? The alloc table said r79: v1, refs 2, live 2, block 2; r82: v1, refs 2, live 2, block 5. Those are local pseudos in blocks 2 and 5 assigned v1. Hmm, the call result should be v0.

I think I'm overanalyzing. Let me get the .lreg dump which shows the final register for each pseudo, and the .greg's dispositions. The alloc_table already gives the final: r79 v1, r82 v1, r78 v1, r81 v1, r84 v0, r85 v0, r73 -, r74 -, r76 -, r83 -, r72 -.

Hmm, the .lreg table shows the final assignment for locals only.

OK, let me get the definitive answer differently: compare with the PINNED version's dump. The pinned version has q in $3. Let me dump the pinned src TU and read the .greg section: then I'll see which pseudo is in $3 and what the preferences/conflicts look like. Then I can figure out what C-level change would produce the same allocation.

That's the right move: the target's allocation is known-good; find the C-level lever that reproduces it.

Let me create the pinned TU copy: take src/ov_SC05_018/ov_SC05_018_jr_8017D604.c as-is (it has the pin) and dump it.

Note: cc1_dumps_tu.sh takes a .c file. Let me copy the src file to my item dir as tu_pinned.c and dump.

Wait — but is the src file's pinned version the same as build/'s? The build's asm matched the pin, so yes.

Let me dump.
