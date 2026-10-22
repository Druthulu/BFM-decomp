---
ts: 2026-10-22T04:48:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_4Hg5zNOZ2MkmjYhsGRKD
---
y1: r74 (the local result) now has pri 13333 (refs 4, live 6) and "prefers v0" ✓ and r73 (the call-result copy) has pri 10000 (refs 3, live 3), also "prefers v0". Both are global allocnos (order: 74 73 → r74 first!).

Yet the result still has r73 in v0 (the copy coalesced). Hmm, the order line "74 73" means r74 is allocated FIRST (higher pri 13333) → r74 should get v0! But the machine code shows the tests on v0 and the value computed into v0 (lbu v0, xori v0) — wait, in y1 (39 ins):
```
24 beqz v0
25 andi v0,v0,0x8000
26 beqz v0
27 nop
28 lbu v0,30(sp)
29 nop
30 xori v0,v0,0x15
31 j
32 sltiu v0,zero,v0
33 move v0,zero
```
The boolean is computed into v0 ✓ (r74 = v0 as expected!) and the call result (r73) is ALSO v0 (the test `beqz v0` on r73 and the andi in-place on r73's reg).

So r74 = v0 ✓ (as the allocation predicted) and r73 also = v0 — because r73's live range [65..74] doesn't overlap r74's live range [74..97] now! (In y1, the `result = 0` def comes after the AND.) So no conflict → both can be v0 → the copy is coalesced → no `move v1,v0`.

So now the lever-free code has the value in v0 ✓ (as in the target) but the call result ALSO in v0 (the target has it in v1 with a copy).

To get the copy, r73 must conflict with something in v0 during [65..74] — i.e. r74 must be live during [65..74]! But then r74's live range starts before the AND → its def is before the AND in RTL order → back to the nopin structure where r74 got v1.

Hmm! Unless r74 is live during [65..74] but STILL gets v0 and r73 gets v1. In the nopin case: r74 (live [72..97]) conflicted with v0 (r73's reg) → got v1. The conflict is symmetric: r73 and r74 overlap → they need different regs → one gets v0 (the one with the preference/priority).

In nopin: r74 (pri 11428) vs r73 (pri 7500, prefers v0) → r73 got v0 despite the lower priority! Because of the copy preference (r73 is copied from v0 → prefers v0).

In y1: no overlap → both v0 → the copy coalesced.

So we need: r73 and r74 to OVERLAP (so r73 is forced out of v0), and r74 to WIN v0 over r73.

In nopin, r73 won v0 due to its copy preference. To make r74 win, r74 needs a preference for v0 as well AND a higher priority (13333 > 10000 in y1's numbers; in the overlapping case r74's pri would be 4 refs/live 7 → 11428 > r73's 7500 → priority favors r74!).

Wait: in nopin, r73's pri was 7500 (refs 3, live 4) and r74's 11428 (refs 4, live 7) — r74 had the HIGHER priority but still lost v0 to r73. So the copy preference beats priority in gcc's global allocation.

Hmm. So how does the target's pinned version resolve? There, r73 conflicts with the hard reg v0 (the pinned pseudo) → r73 can't have v0 at all → r74 (no conflict with v0 then) gets v0 ✓.

So, lever-free, to deny v0 to r73, we need a hard-reg pseudo holding v0 — i.e., a `register` variable — that's the lever itself.

OR: r73 must lose its copy preference for v0. The copy preference comes from the copy `(set r73 v0)` — the source is the call's hard-reg output. What if the call's output were a PSEUDO instead of the hard reg v0? Then `(set r73 rXX)` and r73's preference would be for rXX's reg, not v0.

When does gcc 2.7.2 put the call's result in a pseudo? Looking at the RTL: `(call_insn 63 ... (set (reg:SI 2 v0) (call ...)))` — the output is the hard reg v0. In gcc, `expand_call` uses the call's return reg directly. But there's a case: if the call's return value is used in a context requiring a specific register... no.

Hmm, however! There's another possibility: what if the call's result is used by a subsequent CALL as an argument? Then the value must be in a0 → the copy would be `move a0,v0` — not our case.

What if the call result is stored to memory? Then `sw` — extra insn.

Hmm, what if the call result is compared using a 64-bit op? no.

OK, so: the copy `move v1,v0` in the target comes from the pinned pseudo reserving v0. Lever-free, the only way to reserve v0 for the whole function is... hmm.

Hmm! What about the RETURN VALUE's pseudo? The RESULT_DECL is a pseudo that gcc gives a hard preference for v0 (the return reg). In our RTL there's no RESULT_DECL pseudo (the copy to v0 is direct).

Hmm, what if we make the function return the value in a way that creates a RESULT_DECL pseudo live across the call? No.

Let me reconsider: is there any C construct that makes gcc reserve a hard register for the whole function lever-free? YES: a variable that is live across a CALL goes to a callee-saved register... but that's s0-s7, not v0.

Hmm, what about the "sp-stack-switch" wall tag: "hand-placed $sp write, no C spelling".

OK. Let me consider the possibility that the intended lever-free spelling for this item is something else entirely: maybe the ORIGINAL source didn't have a separate `ret` variable — maybe the call result was used directly in the tests, and the `move v1,v0` came from the compiler's handling of the two tests:

```
if (func_80133784(1, buf1, (int)buf2) != 0) {
    if ((func_80133784(...) & 0x8000) != 0)  /* calling twice! */
```
No, that would be two calls.

What if the call result was stored in a variable that is ALSO used after the branch, e.g.:

```
ret = func_80133784(...);
if (ret != 0) {
    ...
}
if (ret & 0x8000) ...   /* a second use later */
```
Hmm, that changes the semantics.

Hmm, what about this: the ORIGINAL might have had the call result assigned to a variable of type `char`/`short` where the truncation copy is `move v1,v0` — and gcc 2.7.2 keeps the 16-bit value in the register without masking (since HImode uses only the low half). Then:
- `beqz v1` — the test of a 16-bit value: gcc would compare the HImode value with 0 → `beqz v1` requires the upper 16 bits to be zero... gcc 2.7.2 for a HImode comparison with 0 emits `beqz` on the register ONLY if the value is known to be zero-extended. If the value came from a truncation (the upper bits garbage), gcc would emit `sll/sra` or mask.

Hmm, BUT: the ROM's `andi v1,v1,0x8000` — if `ret` were u16, the mask test `ret & 0x8000` on a HImode value → `andi v1,v1,0x8000` ✓ (a 16-bit ANDI, no mask needed since the AND is in HImode). And the test `ret != 0` → for a u16 value: `beqz v1` needs the upper bits zero → gcc would need `andi v1,v1,0xffff` before. Hmm, unless gcc's `sne`/`sltu` on HImode uses the full register...

Actually, in gcc 2.7.2, a comparison of a HImode value with 0 is done as `(set (reg) (eq (reg:HI) (const_int 0)))` → the RTL is HImode → the machine description's `sne` pattern for HImode... The mips `sne` pattern is for SI mode. For HImode, gcc would zero-extend → `andi v1,v1,0xffff` then `beqz`. Extra insn.

Hmm, but what if `ret` is `unsigned short` and the test is `ret != 0` — semantically the same as the 32-bit test? No! For u16, ret != 0 means the low 16 bits are nonzero; for int, ret != 0 means the whole value. Different semantics (e.g. ret = 0x10000 → int: nonzero; u16: zero). The ROM's behavior: `beqz v1` on the full 32-bit value → the int semantics. So `ret` must be 32-bit (or the code must be semantically different but produce the same instructions... the compiler would produce different code for u16).

So the copy `move v1,v0` is a plain 32-bit copy of the call result. And the only lever-free way I can see to get it is if the call result's copy destination (r73) is forced to a non-v0 register.

Hmm hold on, what about the RELOAD phase's behavior: the copy `(set r73 v0)` is a "reload" of r73 from v0. The reload phase decides whether to keep v0 or use another reg based on the "prefer" analysis: r73 prefers v0 (the copy's source reg). If r73's live range had a conflict with v0...

What if r73's live range overlapped ANOTHER pseudo that has a HARD preference for v0? E.g. the AND temp r80 (pri 10000, hard v0 — the table shows r80 with hard v0!). Look at the y1 table: r80 (hard v0), r82 (hard v0), r84 (hard v0) — these are the temps with hard v0. Hmm, "hard v0" for r80/r82/r84 in the lever-free dump: those are LOCAL allocnos assigned v0 by local allocation (they're the AND/load/xor temps, allocated to v0 because... hmm).

And in the pinned dump: r80 (hard v1!), r83 (hard v0), r85 (hard v0).

So in the pinned version, r80 (which is the call-result copy — numbering differs) is in v1 and the temps r83/r85 in v0.

So in the pinned version: the call-result copy is a LOCAL allocno (r80, hard v1) while in the lever-free version r73 (the call-result copy) is GLOBAL (in the .greg order line "74 73").

Interesting! In the lever-free version, r73 is global because it conflicts with a hard reg (v0 — the call's output or the temps). In the pinned version, r80 is LOCAL (assigned v1 by local allocation).

Hmm, so in the pinned version, the call-result copy r80 was allocated v1 by LOCAL allocation. Why v1 and not v0? Because v0 was reserved by the pinned pseudo ✓ (local allocation gives each hard reg to one pseudo; the pinned pseudo took v0).

And in the lever-free version, r73 is GLOBAL — meaning at the local-allocation stage it conflicted with a hard reg. Hmm, but r80/r82/r84 (the temps) got v0 locally, and r73 (the call result copy) is global — it conflicts with v0 because v0 is used by the temps? Hmm.

Wait, in the lever-free dump r73's note says "TIE (lower allocno wins, global.c:607) conflicts sp prefers v0" — so r73 is global, prefers v0.

In the pinned dump, r73 is global too ("conflicts v0,sp, prefers v1") but that's the RESULT_DECL in the pinned version? The numbering differs between the two dumps (the pinned version has fewer pseudos). Ugh.

Let me directly compare the RTL of the pinned version: which pseudo holds the call-result copy there, and is it local or global?

Let me grep the pinned dump's RTL around the third call.

Time: 23:25. I'll do this one check, then write up.
