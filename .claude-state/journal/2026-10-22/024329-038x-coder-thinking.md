---
ts: 2026-10-22T08:43:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_EzZl0F13lOy6UlNSbQzb
---
In the pinned version:
- Globals: 74 76 83 72 (4 regs).
- 74 conflicts: 72 74 83 2 29, preferences: 4 → r74 → a0 (4). r74 is the *val* copy? It prefers a0 and conflicts with r72(arg), r83, v0.
- 76 conflicts: 76 3 29 → r76 conflicts with v1! → r76 → v0 (2).
- 83 conflicts: 72 74 83 2 29 → r83 → v1 (3)?? Dispositions: 83 in 3.

Hmm, dispositions: 72 in 16 (s0=arg), 74 in 4 (a0), 76 in 2 (v0), 83 in 3 (v1), and 78,79,81,82 in 3, 84,85 in 2.

In the pinned version, q is a hard reg ($3) so it's not in the list. The globals are: arg(72), and 74, 76, 83 = the val copies and ptr?

Compare to the lever-free version: globals 73 74 76 83 72 = q1(73), q2(74)?, val1(76), val2(83), arg(72).

In the pinned: 74, 76, 83, 72 → one of the q copies is gone (the pinned q is hard $3, one pseudo? hmm 4 globals vs 5).

Whatever. Key: in the pinned version, r76 conflicts with 3 (v1) and r83 → v1.

Hmm, in the lever-free version: r76 conflicts {73,76,29} (no v1!) and r83 conflicts {72,74,83,2,29} → r83 → v1 (same as pinned). And r76 → v0.

Wait, in the lever-free version r76 → v0 too (disposition 76 in 2). Same as pinned! And r83 → v1 in both. So the difference is only the extra global 73 (q copy 1) which took a0 and pushed... hmm, but r74 → a0 in both.

In lever-free: 73 → a0, 74 → a0, 76 → v0, 83 → v1, 72 → s0.
In pinned: 74 → a0, 76 → v0, 83 → v1, 72 → s0.

So in the lever-free version there's an EXTRA global pseudo r73 (one of the q copies) that got a0. And the other q copy (r74) also got a0.

Hmm, so where do the q's live in the final asm? Both in a0. And the final asm shows the loads `lw a0,100(s0)` — so r73/r74 → a0 → the loads write to a0.

In the pinned version, the q loads write to v1 (hard reg 3).

Now: why did the lever-free q copies get a0? Because of "preferences: 4"! In the lever-free version, r73 has "preferences: 4" and r74 has "preferences: 4". In the pinned version only r74 has "preferences: 4" (r74 is a different pseudo than in the lever-free? numbering shifts).

Where does the preference for a0 come from? Copy preferences in GCC 2.7's global.c `dump_global_alloc` prints "preferences" from `reg_preferred` / copy preferences. The copy preference arises from a copy insn between two pseudos or a pseudo and a hard reg.

In the RTL at global-alloc time, look for copies. In the lever-free dump: insn 22: `(set (reg:SI 4 a0) (reg/v:SI 4 a0))` — a copy where the destination is hard a0 and the source is pseudo r? (reg/v:SI 4 a0 means "pseudo 4"). Hmm, in the dump, hard regs are shown as (reg:SI 4 a0) and pseudos as (reg/v:SI 4 a0) — the /v marks a pseudo! So `(set (reg:SI 4 a0) (reg/v:SI 4 a0))` = copy from PSEUDO 4 to hard reg a0.

So the copy is: pseudo4 → a0. Which pseudo is 4? That's a low-numbered pseudo (from the front end). Hmm, and the preference "4" for r73 means r73 prefers the reg 4?? No wait — "preferences: 4" means the pseudo prefers register number 4? Hmm, the alloc_table said "prefers a0" for r73/r74 and printed "preferences: 4". So "4" = hard reg 4 = a0. Hmm, but the copy is *from* pseudo 4 *to* a0.

Hmm, actually GCC's copy preference: for `(set (reg:SI D) (reg/v:SI S))` where S is a pseudo and D is a hard reg, the preference is "S prefers D's reg"? GCC's global.c:

```
  /* Record the preferences for the copy: if S is allocated reg R, then D should be in R too */
```
In GCC's `record_preferences` / `make_reg_preferred`... The relevant code in global.c:
```
	  /* Record the copy preferences: 
	     (set (reg P) (reg Q)) where Q is a pseudo: P and Q should be in the same reg. */
```
and for a hard reg destination, `reg_preferred` marks that the pseudo should get that hard reg.

So: the copy (set (reg:SI 4 a0) (reg/v:SI 4 a0)) at insn 22 — the source pseudo 4 (a low pseudo) — hmm, that means pseudo #4 (not r73).

Hmm wait, maybe I'm misreading. Let me look at the actual insn text again:

```
(insn 22 26 24 (set (reg:SI 4 a0)
        (reg/v:SI 4 a0)) 159 {movsi_internal2} (insn_list 4 (nil))
    (expr_list:REG_DEAD (reg/v:SI 4 a0)
        (nil)))
```
The destination `(reg:SI 4 a0)` = hard reg a0, source `(reg/v:SI 4 a0)` = pseudo 4. Hmm, but at this stage (before global alloc) the pseudo numbers are the ORIGINAL pseudo numbers (not the "regno" allocno numbers). So pseudo 4 is a front-end pseudo.

Hmm OK. And the copy at insn 22 is the call argument copy: pseudo4 = ptr, copied into a0 for the call. So the preference "prefer a0" belongs to pseudo 4 = ptr, not to r73.

But the .greg dump says "73 preferences: 4" — hmm, maybe the format is "N preferences: <reg list>"? "73 preferences: 4" = pseudo 73 has one preference: reg 4.

Hmm, so r73 (q copy 1) prefers reg 4 (a0). Which copy involves r73 and a0?

Looking at the RTL: the q load in case 2: insn 43: `(set (reg/v:SI 4 a0) ...)`. Hmm, that's the dump AFTER allocation (regs assigned). So at dump time, r73 is a0.

I need the RTL *before* allocation to see the copies. The .rtl dump (c1.i.rtl) is the RTL after flow analysis, before allocation. Let me look at the .rtl section for this function to see the copies involving the q pseudos.

Actually — maybe simpler: think about what makes the q copies prefer a0.

In the source, `q = ((Unkstruct_801815AC_2 *)arg)->unk64;` — a load. Then in the join: `((Unkstruct_801815AC_3 *)q)->unk2 = val;` — the address is q+0 (no offset) → the store is `(set (mem:HI (plus (reg q) 2)) val)`. Hmm, offset 2 → the address is q+2, and GCC computes it as a "plus" of the pseudo q with a constant. If q is a pseudo, the address is (plus:SI (reg q) (const_int 2)) and MIPS would need the address in a register → it computes q+2 in a temp reg → copy! But the target shows `sh v0,2(v1)` — so the address is q+2 with q in a register: MIPS supports the offset in the store instruction.

So at the RTL level, the store's address is (plus:SI (reg q) 2) → mips can fold it. But the "mem" might be (plus (reg q) (const_int 2)) which is address+offset → the mips output pattern does that without a copy.

Hmm, so where does the copy to a0 come from?

Let's think about the *load* of q: `q = arg->unk64` → (set (reg q) (mem (plus (reg arg) 100))). No copy.

Hmm, what about the *join* block: the store `((Unkstruct_801815AC_3 *)q)->unk2 = val;` — the pseudo q is used in an address. And the second store `->unk34 = 0`.

Hmm, and "r73 preferences: 4" — maybe the preference comes from the *reload* of q? Since q is a pseudo assigned a reg, and the store's address needs a register... 

Actually here's a thought: in GCC 2.7, `global.c` computes copy preferences from the insns where a pseudo is copied to a hard reg. The relevant copy might be this: in the join block, the value `val` (r76 or r83) is copied to a hard reg for the store? No, the store is to memory.

Let me look at the .rtl dump to see the RTL before allocation. That will show the copies.

Let me find the function section in c1.i.rtl.
