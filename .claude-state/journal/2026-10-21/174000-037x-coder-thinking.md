---
ts: 2026-10-21T23:40:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_lv0Xh8ohrTJYmi1JMXJK
---
Hmm! This dump is NOT the real function. The insns show `(const_int 0)` for a0, and calls with `(const_int 16)` as the arg — the args are constants 0! That means the function's parameters were optimized away (const-propagated) — because in my padded TU, `func_801415C0` is never called and gcc's IPA/cse2 propagated... no wait, `(const_int 0)` for a0 in the call to func_800291B4 means d was known to be 0?!

Oh! I see: my padding functions `pad_fn_i` are static and unused → gcc removed them. But that's not the issue.

The real issue: the dump shows the function with all args as 0 — that's bizarre. Unless... this is a DIFFERENT function section? No, it says func_801415C0.

Hmm wait, `(const_int 0)` in `(set (reg:SI 4 a0) (const_int 0))` — movsi_internal2 with const 0. That means a0 = 0. And the call to func_800291B4 has arg `(const_int 16)`.

Hold on... this looks like the dump of a function where all the arguments were replaced by constants. That can't be from my source.

OH WAIT. I bet the issue is that gcc's dump file c1.i.greg contains MULTIPLE functions and the ";; Function func_801415C0" marker at line 1142 is a *later* function... no.

Hmm, let me reconsider: maybe `cc1 -quiet` with those dump flags prints the RTL at various stages. The .greg dump is printed after global allocation. But the insns show no pseudo registers at all — everything is hard reg. And the function's parameters are gone.

AH — I think I understand! The dump shows the function AFTER flow analysis found that the parameters are unused?? No, they're used.

Hmm, actually wait. Look: "(const_int 0)" appears for a0 = d (d = b+0x2F). And `(const_int 16)` for the arg to func_800291B4. These look like *constant-propagated* values. b = (s16)param_1 → param_1 = 0? 

This smells like the dump is from a DIFFERENT compilation unit — maybe c1.i is stale from another run? No, fresh dir.

OR: my padding functions are static and unused; but the real issue could be that the dump shows `func_801415C0` AFTER gcc's "const-prop" pass (cse2) where the function was cloned/specialized? gcc 2.7 doesn't do IPA const-prop.

Hmm hold on, maybe the dump is of the function *after* the `flow` analysis determined param_1 is unused because... no.

Let me look at the earlier part of the .greg file for other functions and at the .flow dump for func_801415C0 to see the pseudo registers.

Actually, maybe I should question: is `;; Function func_801415C0` at line 1142 the FIRST occurrence? The tool's section() looks for ";; Function func_801415C0\n" and takes text from there to the next ";; Function ". It found 0 pseudos because it looks for specific patterns.

But the real question: why are the args constant 0?

OH. I see it! Look at the insn numbers: `(insn 13 18 15 (set (reg:SI 4 a0) (const_int 0))`. In gcc dumps, the format is (insn INSN_NUMBER PREV INSN_NEXT ...). So insn 13's prev is 18 and next is 15?? That's odd (18 > 15). Actually gcc 2.7's format is (insn uid prev next ...). Hmm.

Wait — "(insn 13 18 15 (set (reg:SI 4 a0) (const_int 0)) 159 {movsi_internal2} (nil)". Hmm, and "(note 17 6 18 ...)" — so note 17 is prev 6 next 18. So the "prev" is a note number and "next" is an insn number. So insn 13: prev=18 (note), next=15 (insn). OK.

So this function's insns: 13 (a0=0), 15 (call 291B4 with const 16), 20 (a0=0), 22 (a1 = v0&0xff), 24 (call 291A0), 27 (a0=0), 29 (a1=0), 31 (call 291A0).

So indeed everything is constant 0/16. This is a function with no arguments — as if all parameters were replaced by constants 0.

AH HA. I bet the issue: `extern s32 func_800291B4(s32 arg);` and gcc knows nothing... but `func_800291B4` is declared extern; gcc assumes it may read memory... 

Hmm, but param_1 → b → d → passed to func_800291B4 as (const_int 16)?? That means d = 16, i.e. b = 16 - 0x2F = -25. And param_1 = -25? Where from?

Unless... gcc did "constant propagation" because func_801415C0 was called from somewhere with constant args? No, it's not called.

Hmm, wait: could the dump file be from a *previous* run in the same directory? The dir was rm -rf'd. 

OR: the padding `pad.inc` functions got inlined... no.

Hmm, what if cc1 dumped a DIFFERENT function but labeled it func_801415C0? The "Hard regs used: 2 4 5 31" — v0, a0, a1, ra. My function uses s0-s4 too. So this is definitely not my function's final allocation.

Let me look at the .flow dump for the function to see the pseudos. Actually, let me reconsider: maybe the dump shows the function AFTER "cse2" (which does PRE const folding) — no.

Let me look at the whole .greg file structure: how many ";; Function" sections.

Actually — hmm! Big realization: gcc's dump files c1.i.greg etc. are per-pass dumps of ALL functions. The order of functions in the file... The section I read at 1142 might be the tail. Let me grep for all ";; Function" lines in c1.i.greg.

Also possible: my function is `void func_801415C0(s32, s32)` and gcc 2.7 with -O2 might have applied "delete_null_pointer_checks"... no.

Let me just check the .flow dump for the function's pseudo registers, and grep the section list.

Actually hold on! I bet the problem is this: `-quiet` and the dump flags dump the FINAL RTL of each function at each pass. The .greg dump is "global register allocation" input. The function I'm looking at has "1 basic block" and no pseudos. 

But WAIT: what if this is the *padded* function's... no, name matches.

Hmm, let me look at the .i.greg from the start to see the function list.

Let me be efficient: grep ";; Function" in c1.i.greg.
