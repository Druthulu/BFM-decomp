---
ts: 2026-11-06T06:10:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CEfiXqbxRkwVbQmzfRkg
---
alloc_table needs cc1 dumps (.greg). I'd need to generate dumps for the TU via tools/cc1_dumps_tu.sh. That's the mechanism.

But maybe faster to reason with the tie: floor_log2(3)=1, 3*1/38 vs 5*2/126. Both 0.0789/0.0794. Let me compute precisely: pp 3/38 = 0.078947; zpush 10/126 = 0.079365. zpush slightly higher → wins. To flip, add 1 ref to pp: 4 refs → floor_log2(4)=2 → 4*2/38 = 0.2105 ≫. But an extra ref adds an instruction typically... unless free.

Alternatively lengthen zpush's live length slightly: if live were 128, 10/128=0.0781 < pp. Live length depends on insn positions between first and last ref. Hmm, if I can insert a couple of insns early (before zpush's def? no, that shifts both).

Hmm: live_length counts insns from first ref to last ref, likely including both endpoints. If I move zpush's *def* later (closer to the loop), pp's live length also shifts... pp's live ends at loop-1 use. If zpush def moves from position 22 to, say, 16 (earlier), live grows; if later, live shrinks → priority grows. Moving zpush def later reduces its live_length? No: live_length = last - first + 1 in insn counts. Moving the def later shortens it → higher priority. Opposite of what we want.

Move zpush's def *earlier*: pp def at 16; if zpush def moves before pp... but pp def is at 16 and zpush lh at 22. Actually zpush's def can't be earlier than after the call at 14.

Alternatively move pp's def later so its live_length shrinks? That raises pp priority but changes target order (pp set must be at 16 = before pf at 20).

Hmm, wait: maybe live_length isn't linear over insns but in "number of instructions live over" which counts basic blocks. Let me look at flow.c for live_length.

Actually let me just get the dumps — that's the reliable route and the brief points at tools/cc1_dumps_tu.sh + alloc_table.py. But dumps need to be under my item dir and deleted after.

But careful: cc1_dumps_tu.sh compiles the TU as-is (src). The dumps would be from the current src (with levers). Hmm, I want dumps for my candidate. There may be a --keep option on delever_search to keep scratch. Or I can compile the candidate TU myself... but tools/cc1_dumps_tu.sh operates on a TU path.

Alternative: `delever_search.py --try ... --keep` prints the candidate object path; dumps though need cc1 -dA output.

Hmm. Time budget matters. Let me think about likely free ref boosts:

Known moves from moves.md for adding refs:
- G18: "do-while(0) ref weight" (W03 line 25: "mny keepalive cracked by do-while ref weight").
- C0535 do{}while(0) splits cse1 EBB.
- worked example: `do { r = p + i; } while (0);` added +1 loop-weighted ref and folded into the store.

For pp: is there any expression using pp that folds? `*(pp)` is p itself. Hmm, what if I use `pp` in place of `&p` in the RotTransPers4 call (already), and also write the loop's else-branch pointers as `(s32)pp`? no.

What about changing loop 2 to pass `pp` but the target has addiu... mismatch.

Alternative idea: make pp a *pointer to a pointer* used differently, e.g. write `RotTransPers4(..., pp, pf)` where pp is `s32*`; already.

Alternative: Use pf's refs — no, pf already wins.

Alternative: reduce zpush refs by making it used only in loop 2? No.

Wait — maybe simpler: change zpush's *type/width*. If zpush were u16 or s16, the `lh` stays, same refs.

Alternative: get zpush a *lower* priority by giving it a second def (2 defs merge into one allocno, live length spans, nrefs +1 → 6 refs → floor_log2(6)=2 → 12/126=0.095, worse).

Hmm, what about splitting zpush into two pseudos that share a register? Like `zpush = ...; use in loop1; zpush2 = ...` no.

Let me reconsider: maybe the tie-break is what matters and mine is a tie broken by allocno number. If it's a tie, then *v1 - *v2: qsort ascending by (pri2-pri1), so higher pri first; equal pri → lower allocno first. pp's allocno number vs zpush's: allocnos are created per pseudo; pp's pseudo regno is likely lower (declared earlier / set earlier). Hmm.

But the observed order is pf > zpush > pp. Let's compute pf: refs = def + 1 (loop1 stack store) + 3 (loop2 a3) = 5; loop-weighted: def 1 + 2 + 3*2 = 9. floor_log2(9)=3 → 27/live. pf live from 20 to ~140 = 120 → 27/120 = 0.225. That's way above zpush 0.079. And pp 0.079. So pp vs zpush is a near tie; pp loses by a hair.

The cleanest: give pp one more reference. What about using pp instead of `&p` in loop 2 for *one* of the three calls? That'd be a move instead of addiu — mismatch at that site. Unless... hmm, target loop2 call 1 uses addiu a2,sp,40; call 2 addiu a2,sp,40; call 3 addiu a2,sp,40. All addiu. So no.

Different idea: make the loop-1 stack stores come from pp/pf in a different way? They're `sw s7,32(sp)` — expand stores the arg values. What if we declare pp/pf as `s32 *` but pass them through an intermediate? no.

New idea: change pp's live length by moving `pp = &p;` to just before the loop (after zpush). But target has addiu s7,sp,40 at 16, before lh s8 at 22. Order matters for codegen. So no.

Another idea: reduce zpush's live length by moving its load *later* — e.g., load zpush just before the loop, after pp/pf. Target already: pp(16), pf(20), zpush lh(22). Moving zpush later isn't possible (loop starts at 22). If we moved zpush's load inside loop 1 before the call... adds insns.

Hmm what about giving pp an extra ref via the *second* loop where &p is used: what if we write the third call's arg as `&p` but for one call we use `pp`... no.

OK alternative: maybe lower zpush priority by making it a *local-alloc* pseudo instead of global: if zpush's live range is confined to one basic block, it won't be a global allocno. But it spans loops.

Alternative: use two separate variables zpush1 and zpush2, each loaded... no extra insn.

Wait! What if zpush is passed as `(s32)zpush` vs the call? no.

Hmm, let me reconsider the free-ref trick: a use that folds into an existing addressing mode. In loop 1, the else-arm computes `v0p = arg0 + 0x84` etc. Not pp.

What about `pa` and `pb`? no.

What about a use of pp in the `if (i != 11)` test? no.

Another angle: the *copy preference*. pp = &p is a copy from the address pseudo &p; pp's copy preference is toward the &p address pseudo's register, which is none (it's a constant address). Hmm.

Actually, maybe I should look at this from the "what did the pin do" angle: the pin put pp in $23 and pf in $22. Comment says "Pinning the two pointers frees $fp for zpush". So without pins, $fp went to pp (mine). The pin forced pp to s7, which left fp to zpush, and pf took s6.

Lever-free we need pp to naturally land s7 — i.e. pp allocated before zpush. 

What if we swap the declaration/assignment order of pp and pf? The allocno order could change. pf currently beats pp; if pp is set first... they're already pp first.

What if we add a *third* address variable to change the bank? no.

Let me try the simplest experiments in batch:
a) `pp = &p;` and use `pp` in loop 2 first call: `RotTransPers((s32)&pa[i], (s32)&t->xy0, pp, pf);` — this gives pp +3 refs but changes addiu→move at those sites. Actually maybe not: if pp is in a reg, a2 = move a2,s7; target wants addiu a2,sp,40. Mismatch. Skip.

b) Add a dead use: `do { s32 *tmp = pp; } while (0);`? That's a copy → cse kills. 

c) A dead reset (C0414): `pp = &p; ...; pp = 0;` at the end? Dead reset is deleted by delete_dead_from_cse, but does it add refs? The refs are counted after flow's dead-code deletion? The C0414 note: "dead-reset cse-breaker; cracked 3 launders in G16x" — it breaks cse equivalence, but refs counted at flow time would include it if not deleted before global-alloc. flow deletes dead code before global alloc, so refs likely unchanged. Not reliable.

d) `zpush` via a u16 temp: `u16 zp = ...; zpush = zp;`? extra insn.

e) Change zpush's declaration type to `s16 zpush` — the `lh` then produces HImode, and `move a1,s8` same. Ref count same. But the *copy* at zpush = ((Unk*)arg0)->unk6 — with s16, same lh.

Hmm wait, maybe there's another difference: maybe in mine, zpush's priority is inflated because its `lh` result is used in two loops and gcc counts... no.

f) What about making pp/pf *parameters* of the loops? no.

g) What about declaring pp and pf `volatile`? No, that adds loads.

h) What about giving pp an extra ref in a *cold* block that's cheap: e.g. in the else arm add `v0p = (s32)pp;`? That would emit a move in the else arm — mismatch (else arm is at 2fe0: addiu a0,s3,132...). Skip.

Let me instead consider: maybe I can *raise* pp's priority by shortening its live length without changing instruction order — live length is computed from reg_n_live... but what if pp's def is moved *after* the func_8012E32C() call? Already is.

Hmm — actually! What about the *order of the two assignments* `pp = &p; pf = &flag;` vs `pf = &flag; pp = &p;`. Target: addiu s7 (pp) then addiu s6 (pf). If I swap source order, the target order would break (s6 first). No.

What about `i = 0;` placement? no.

New idea: make zpush's *use* in loop 1 happen through a different pseudo: e.g. `func_8012E28C(otz, zpush)` in loop1 and `func_8012E28C(otz, zpush)` in loop2 — could we compute `zpush` once but copy into a local `zp1` for loop 1? That adds a move.

OK, let me try the empirical route with a small sweep. Candidates:
1. do-while(0) around the `zpush = ...` or around pp assignments (ref weight changes?).
2. `pp` set with `pp = &p + 0;`? folds.
3. Give pp a use via the RotTransPers4 stack arg written explicitly? no.
4. Try making the loop-1 call args `pp, pf` written as `(s32 *)&p, (s32 *)&flag`? no.

Actually, wait. Let me reconsider: maybe the free-ref trick works with the *store* of pp to the stack: the arg `pp` is stored to 32(sp) at 3010. If we wrote `pp` differently... no.

Alternative plan: reduce zpush's nrefs by loading it once per loop but the target only has ONE lh. So zpush's 3 refs are fixed.

Hmm, unless we can make zpush's live length *longer* in a free way: e.g. make zpush's first reference earlier? Its def is the first ref. Moving the `lh` earlier — it's already at 22 right before the loop; the call at 14 is before.

What about making zpush's last use later? Loop 2's `func_8012E28C(otz, zpush)` is the last use. Nothing after.

OK so priority is fixed... unless we change pp. Let me compute more carefully whether the tie-break matters. If pp and zpush have exactly equal priority, qsort order decides. My body gives zpush > pp, target wants pp > zpush. So they're not equal — zpush strictly higher.

Let me get the real numbers with cc1 dumps. How? `tools/cc1_dumps_tu.sh` — let me check its interface.
