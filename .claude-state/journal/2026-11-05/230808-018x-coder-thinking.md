---
ts: 2026-11-06T06:08:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k0PjycHdquhdGcie0Lae
---
Score 8, mine 161 vs target 162. Missing 1 insn: the two moves (move s1,v0 / move a0,s1) — that's the launder. And a reg: s7 vs s8 (pp/pf pinned to $23/$22 = s7/s8? $23=s7, $22=s6... wait MIPS regs: $16=s0..$23=s7, $30=fp, $31=ra). Hmm $23=s7, $22=s6. But diff says move a1,s7 vs move a1,s8. Hmm, s8 = $30 = fp. So target has a1 from fp ($30)? and mine s7. Wait, target: move a1,s8 where s8=fp.

Hmm, actually MIPS gcc names $30 as s8/fp. So the target uses fp for something (zpush?), and pinned $23/$22 → s7/s6 for pp/pf. But then who is in fp? zpush — comment said "Pinning the two pointers frees $fp for `zpush`". So target: pp=$23(s7), pf=$22(s6), zpush=$30(fp). Mine: pp and pf take... apparently s7 and something, zpush takes s6 or so.

Let me get a full diff. Let me run dt.sh with a bigger tail (say 60) and read.

Actually the output of dt.sh tail-8 showed lines 54-55 (the missing move), 75, 77, 144. So diffs: missing move pair at 54/55, and register differences a1,s7 vs a1,s8 at 75 and 144 (zpush arg).

Score 8 probably = 1 deletion (2 insns shift) + 2 register mismatches weighted... Anyway.

Two problems:
1. otz launder: need `move s1,v0; move a0,s1`. Target keeps otz in $17 (s1) from call result then copies to a0 for the next call arg. Plain C: `otz = RotTransPers4(...); otz = func_801823D4(otz, -0x1A);` → combine folds into move a0,v0. Need a real 2nd set that forces the copy but costs no insn. Options:
   - `do { } while (0);` between? That splits EBB but doesn't create a 2nd set. From G14 line 187: "the launder tied-output on sc -> empty do { } while (0) (plain C keeps the CFG shape the asm forced)". Let me try that first.
   - C0414 dead-reset: `otz = 0;`? no, changes value.
   - `otz = otz;` — cse/combine may keep as a copy? A self-assignment in RTL is (set reg reg) which is a no-op insn likely deleted by cse.
   - Real 2nd set: `otz = (s16)otz` adds sll/sra.
   - `otz = otz | 0;`? identity, combine folds.
   - `otz = otz & -1`? folds.
   - What about `otz = RotTransPers4(...) ; if (otz) {}` no.
   
   Look at the target: `move s1,v0` then `move a0,s1`. That means otz lives in s1 across... Actually otz assigned from call result v0 → move s1,v0 (assign to pseudo in s1), then move a0,s1 for the next call's arg. That's just normal codegen when otz pseudo is in a callee-saved reg (s1) and the call arg needs a0. Combine folds the copy only if the pseudo is in v0? Hmm no: the pseudo otz gets s1 because it's live across the func_801823D4 call? No wait — otz = RotTransPers4(...); otz = func_801823D4(otz, -0x1A); so otz value dies at the arg copy. Then the result of func_801823D4 is the new otz used for the AddPrim index.

   Target insns: move s1,v0 (otz = result), then move a0,s1 (pass to func_801823D4). So otz is in s1 and the arg copy to a0 is a separate move. In plain C, combine turns `otz=call(); a0=otz` into `a0=v0` because the pseudo's reg is v0... Actually if local-alloc gave otz v0, then the copy is redundant and deleted. With the asm re-tie, otz gets a real set so it can't be coalesced.

   So we need otz's first set to be a distinct pseudo that combine can't merge. The do-while(0) split: `otz = RotTransPers4(...); do { } while (0); otz = func_801823D4(otz, -0x1A);` — the EBB split might stop cse/combine from merging across? Actually combine works within a basic block; do{}while(0) creates a new basic block? An empty loop... gcc may optimize `do{}while(0)` into nothing but at -O it typically leaves NOTE_INSN_LOOP_BEG/END or a code_label. The cookbook C0535 says do{}while(0) splits cse1 EBB — so it does create a block boundary. That might stop the merge.

   Let's try that.

2. The zpush register: target zpush in fp ($30), pp/pf in s7/s6 ($23/$22). Mine: pp/pf got s7 and ...? diff says mine `move a1,s7` vs target `move a1,s8`. If zpush is the a1 arg, mine zpush=s7, target zpush=fp. And pp/pf took s6/s? Hmm mine's a1 comes from s7 → zpush in s7; target s8(fp). So in mine, pp/pf took s6 and maybe s5, and zpush took s7.

   Need to boost pp/pf priority so they get $23/$22 and zpush gets $30. In target, the pinned pp=$23 and pf=$22. Lever-free: allocate priority by nrefs. Comment: "allocno_compare ranks zpush (3 refs, loop-weighted) above them". So we need pp/pf to have more refs than zpush. pp is used once per loop iteration (passed as arg) = loop-weighted. pf likewise. zpush used once per iteration in both loops.

   Add refs to pp/pf via real C: e.g. `pp = &p; pf = &flag;` plus extra uses. Or wrap in do-while to increase loop weight? Actually refs count.

   Alternative: make zpush cheaper: compute it differently, e.g. use `((Unkstruct*)arg0)->unk6` directly at each call (2 uses, not loop-weighted?) — it's inside loops, so still loop-weighted. Hmm.

   Alternative: give pp/pf more refs by using them in more places. e.g. `RotTransPers4(..., pp, pf)` and later `RotTransPers(..., pp, pf)` in loop 2 instead of `&p, &flag`? Wait loop 2 currently passes &p, &flag directly. If we pass pp, pf there too, then pp/pf get +3 refs (3 calls) and &p/&flag address is not re-derived... but that changes codegen: target in loop 2 probably uses `addiu a2,sp,40` style? Let me look at the actual target disassembly to know.

Let me dump the target. Is there a helper? `tools/cc1_dumps_tu.sh`, or maybe the diff output shows target lines. dt.sh prints diff tail only. Let me check if there's a disassembly tool. Maybe `tools/match_one.py` or objdump. Let me check what delever_search --explain gives, or look for a tgt file in the worked example (there's `tgt` and `start` and `end` files). In the example dir, `tgt` file probably holds target asm. Let me look.
