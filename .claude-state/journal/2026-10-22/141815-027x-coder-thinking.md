---
ts: 2026-10-22T20:18:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3KU9OCk0GCZm1wmqzOlz
---
Hmm, `grep -c launder` = 1 and line 26 has `*(Mat32 *)(obj+0x34) = *(Mat32 *)m;` — that's the orig.c body (has launder). Wait, but that's the last --keep run (orig.c). Right.

Let me write my own dump script under the item dir: takes the scratch dir, cpps with -I<scratch> first, and runs cc1 with dumps into DUMP_ROOT.

Actually simpler: I can reuse the scratch dir produced by --keep, and run cpp manually:
```
mipsel-linux-gnu-cpp -lang-c -Iinclude -I<scratch> -Isrc/shared -undef ... <scratch>/ov_MAIN_012.c
```
Wait, the include line is `#include "../shared/ov/func_80128158.h"` relative to the includer's directory (src/main/...?). The script uses -I$(dirname tc) plus -Isrc/shared and -Isrc. Since the scratch .c is at scratch/ov_MAIN_012.c, `../shared/...` from there = .run/P36/engine/score/shared — wrong. So the includes resolve via -Isrc? `-Isrc` makes "../shared/..." resolve to src/../shared = shared/ at repo root — no. Hmm, how does the recipe compile normally? The pipeline replaces the src path with scratch_src in the recipe's compile command; the recipe probably has -I<the includer's dir> and -Iinclude etc. The extra was `-I{shadow} -I{dirname(rec['src'])} -I{src_dir}` where src_dir = dirname(tu) for a header = src/shared/ov. So `../shared/ov/...` from src/shared/ov = src/shared/... no wait, the include is `"../shared/ov/func_80128158.h"` relative to the includer's real directory (src/main/ov? whatever), so -I{dirname(rec['src'])} resolves it. And the shadow is found via -I{shadow} where shadow=scratch/inc, and inc/../shared/ov exists → scratch/shared/ov. But the include is "../shared/ov/func_8012B4B8.h" — with -I{dirname rec src} that resolves to src/shared/ov/func_8012B4B8.h (the REAL one) before the shadow? Include order: -Iinclude -I{shadow} -I{dirname} -I{src_dir}... The extra is appended after -Iinclude. So shadow comes before the includer dir. Then `../shared/ov/x.h` relative to -I<shadow> = scratch/inc/../shared/ov = scratch/shared/ov. Good.

For my dump script, replicate: 
```
mipsel-linux-gnu-cpp -lang-c -Iinclude -I$S/inc -I<includer dir> -Isrc/shared -undef ... -Isrc ...
```
What is the includer dir? From the recipe. I can find it: the recipe src. Let me get it via incl.py (gives recipes) or from the scratch .c path name ov_MAIN_012.c — the recipe's src is likely src/main/ov/ov_MAIN_012.c? Let me run incl.py.

Actually easier: the score pipeline's exact compile command is in the recipe. Let me just get rec['src'] with a tiny scratch script... or use incl.py which prints rec srcs.

Alternatively — do I really need dumps? The comparison tells me: c_struct merged the call-address pseudo with the movstr dest pseudo (4 refs, pri higher), score-0 keeps them separate (3 refs, spilled). The empirical fix: find a C spelling where the copy is a block move but the call-address pseudo is separate.

Let me just test candidates empirically; scoring is ~2-3 s each. I'll write a batch of candidates.

Candidate ideas (base c_struct, changing only the copy/call spelling):

A. copy via pointer, calls via array:
```
Mat32 *d = (Mat32 *)m; *d = D_800AE620;
RotMatrixX(..., (void *)m);
```
(c_d3) = 19.

B. calls via a pointer variable set after the copy:
```
*(Mat32 *)m = D_800AE620;
mp = m;   // int *mp
RotMatrixX(..., (void *)mp);
```
cse may merge mp with &m but the pseudo birth is after copy; still one pseudo live across calls with 3 refs → could be spilled like target! Worth trying.

C. calls via `(void *)&m[0]` (identity, but test the score; even if 0, it's an identity spelling → not a crack, so skip if it's the only thing. Actually the rule says identity-statement launders don't count as a crack; if the win comes from `&m[0]` vs `m` that's an identity address spelling → not acceptable. So skip.

D. Copy in two 16-byte chunks with different dest expressions (m and m+4) — changes the address pseudos: two dest pseudos (m, m+4), each dies; call pseudo separate. But changes load grouping (target 3,3,2). Probably worse.

E. Copy the struct via a temporary and a store: `Mat32 t = D_800AE620; *(Mat32 *)m = t;` — two block moves, worse.

F. Make the copy use the source pointer `src` pinned but copy via struct: `*(Mat32 *)m = *(Mat32 *)src;` with src pinned $5 and NO launder. The pin alone may keep the source address in $5 (like a1). Hmm, but $5 = a1; the target has the source in a1 anyway. Actually with the pin, the source pseudo is hard $5, so cse can't fold it into loads. That could give the block move with a1 as base. And the dest issue remains (movstr dest + calls merge). Unless the pin changes the alloc: src is pinned hard, so it's not an allocno. Hmm.

G. Use a *pointer* for the m address in the calls, declared as `int *mp` and initialized *inside* the if after the copy — test B.

H. Copy with `m[0]=...` scalar but with the source held via a *local struct* object: `Mat32 src = D_800AE620;` then `*(Mat32*)m = src;`? Two moves.

I. What about making the m array accessed via a struct field of a local struct with another member before it, so the call address is &s.m — same.

J. The target's address is sp+16; the m array is the first stack object. What if m is declared as a pointer to a local? no.

K. Force the call-arg address pseudo to be born later by ordering the code: do the copy, then the loads for the last store... no.

Let me think about how the score-0 body works, RTL-wise. In score-0, the C is scalar copies from `src` (pinned $5) into m[0..7]. The block move in the target output — is it really a movstr from expand, or is it sched1 grouping the scalar load/stores? The output has exactly 3 loads then 3 stores repeated, which sched1 could do from interleaved scalar copies (t0=src[0]; t1=src[1]; t2=src[2]; m[0]=t0;...). Yes! The source C already groups 3 loads then 3 stores. So the target output could simply be the scalar assignments scheduled by sched1, NOT a block move. That means the target's C may well be the scalar form (as in src), with the source base in a register (the pin/launder) and the dest as direct sp stores (because m[i] with constant index → sp offset).

So the real target source is probably the scalar form with some lever-free way to keep the source base in one register. In score-0 the pin $5 forces `src` into a1 and the launder stops cse folding.

Without the pin but with the launder removed: cse folds the address into each load (lui per load). Without the launder but with the pin: `src` is a hard reg; cse can still substitute the *value* (constant address) into the loads? n1 (pin kept, launder removed) = 20, showing cse folds. Right: cse replaces uses of src with the constant, ignoring the pin? Apparently.

So how does the target keep the source base? Because in the target, the source address is a *symbol_ref* used as a memory address: `D_800AE620.w0` etc. — i.e., the C reads the global directly by name:
```
m[0] = D_800AE620.w0; m[1] = D_800AE620.w4; ...
```
Then gcc loads with `lui a1; lw v0,0(a1); lw v1,4(a1)...` — cse merges the symbol address into one base register because the address is a symbol_ref constant and cse's constant folding for memory addresses chooses a base reg! Yes: `lui/addiu a1` then offsets. That's the classic pattern: direct global member reads produce one address register, not lui per load, when cse merges the address expression... Actually cse folds the address into each load normally? The target's output has ONE lui/addiu a1 and loads with offsets 0,4,8,... — that's gcc's cse creating a base register for the symbol (it does this when the address is used multiple times: cse replaces the address with a pseudo... `cse_insn` has code to create a base reg from a constant address when it appears multiple times, with REG_EQUAL note).

So: write the copy as direct member reads from the global:
```
t0 = D_800AE620.w0; t1 = D_800AE620.w4; ...
```
Hmm, but that's 8 named fields; Mat32 has w0,w4,w8,wC,h10,hpad,t0,t1,t2 — that's 4*4+2+2+3*4 = 32 bytes: w0,w4,w8,wC (16), h10,hpad (4), t0,t1,t2 (12). So 8 words: w0,w4,w8,wC,h10hpad(two shorts),t0,t1,t2. Copying 8 ints: `m[0]=D_800AE620.w0; ... m[4]=D_800AE620.h10...`. Awkward for the shorts.

Better: cast: `int *s = (int *)&D_800AE620;` then `m[0]=s[0]...` — that's what src does, and cse folds. But direct global member reads via a struct pointer:
```
Mat32 *s = &D_800AE620;
m[0] = s->w0; ...
```
Same folding likely.

Hmm, what makes cse keep the base register? The block-move/struct-copy route did keep it in a1 (c_struct's output has one lui a1). So `*(Mat32 *)m = D_800AE620;` gives the right *source* behavior. The dest is the only issue.

So focus on the dest. Let me try the mp variant (B) and a few others. Also consider: maybe use `*(Mat32 *)&m[0] = D_800AE620;` for the copy and `(void *)m` for calls: the dest expression `&m[0]` vs `m` are the same address → cse merges (identity spelling, not a crack anyway).

What about doing the copy to m through a struct pointer parameter-like local:
```
Mat32 *d;
d = (Mat32 *)m;
*d = D_800AE620;
d = (Mat32 *)m;      // real 2nd set? same value, cse kills it
```
No.

Think about the actual RTL: movstr expansion (expand_block_move) emits a `movstr` pattern or a sequence with `(mem:BLK (reg))`? For gcc 2.7 mips, `movstrsi` may not exist; expand_block_move emits a loop or unrolled loads/stores using an address register for both src and dest. The dest address register is a pseudo (m's address). Then the calls also need m's address. cse merges them → one pseudo live across calls → allocated s1 (4 refs, pri ~10909? no).

Hmm wait, actually the c_struct alloc table (cs) shows r78,r79,r80 with 6 refs each and "dies in 3 places" — those are weird. Those are likely the movstr's src/dest address pseudos? And r72 = self (9 refs, live 48, crosses 3 calls, pri 5625). But global-alloc order is 78,79,80,72. So r78/r79/r80 get allocated first and r72 last. Three callee-saved regs (s0,s1,s2) go to... In the final code s0=obj, s1=addr, s2=self. Hmm.

Wait, but obj is r77 (a0, pri 11739, refs 9 live 23, blk 1)? That's local-alloc'd. Hmm, the table mixes.

This is getting deep. Empirical search is faster. Let me write ~12 candidates varying the copy and call spellings, score them all in one sc.sh run.

Candidates:
1. mp_after: `int *mp;` + `*(Mat32 *)m = D_800AE620; mp = m;` calls `(void *)mp`.
2. mp_before: `mp = m; *(Mat32*)m = D_800AE620;` calls mp.
3. copy_ptr_call_m (c_d3, 19) skip.
4. two-step: `int *mp; *(Mat32 *)m = D_800AE620; mp = m; mp[0] = mp[0];` no.
5. void* variant of 1.
6. `Mat32 m;` + `m = D_800AE620;` + `int *mp = (int*)&m;` after, calls mp.
7. copy via `*(Mat32 *)&m[0]` + calls `(void *)&m[0]`? identity but the copy dest spelling differs from calls only if calls use `m`. Test `*(Mat32 *)&m[0] = D_800AE620;` with calls `(void *)m` — this IS an identity address spelling (m vs &m[0]) → not acceptable as a crack, but let me see if it even scores 0; if it does, it's tempting but disallowed.
8. Use a separate `Mat32 tmp;` for the copy then copy tmp→m? no.
9. Declare m as `int m[8]` but pass `(void *)(m + 0)` to calls while copy uses `m` — identity.
10. Copy using `memcpy(m, &D_800AE620, 32)`? That's a call — changes everything.
11. Copy with `*(Mat32 *)m = D_800AE620;` then calls with a *different pointer variable assigned from m in a different block*: e.g. inside `if (obj != 0) { ... }` — one block. Add an inner block: `{ int *mp = m; RotMatrixX(..., mp); ... }` — a scope shouldn't matter to cse but the declaration might create a new pseudo born at the block start.
12. Put the calls' argument as `m` but with m declared `Mat32 m;` and the copy `*(Mat32 *)&m = D_800AE620;` — identity.

Also consider changing the *order*: target's calls come after the copy. What if the address pseudo's live range is shortened by making the last call's argument computed fresh: e.g. use `(void *)(m + 0)`? no.

Hmm, wait. Let me reconsider the target's own structure: `addiu a1,sp,16` in each call delay slot. If a single pseudo were live across the 3 calls and spilled, reload would insert a load at each use → addiu per use. That's exactly it: the pseudo is live across calls but got NO hard reg (spilled), and reload rematerializes the address constant. So the target's call-arg pseudo is spilled. Why spilled? Because global-alloc gave s0/s1 to obj and self and had no more callee-saved needs... but it could give s2. GCC allocates as many as needed; spilling only when... global-alloc allocates callee-saved regs to allocnos by priority until all are assigned; if the addr pseudo's priority is lower than self's and obj's, it gets no reg? No — global-alloc assigns *all* allocnos that conflict with hard regs to some reg, spilling only if no free reg among those it can use. With s0..s7 available, there's no shortage. So why spill?

Ah — unless the pseudo is "not worth allocating": gcc's global-alloc has `allocno_compare` and assigns in order; a pseudo that crosses calls and has low priority still gets a callee-saved reg if available. It wouldn't spill with 8 available. Unless... the address pseudo is not an allocno at all: it's a constant that reload materializes because the *insn* uses a `(mem (plus (reg fp) (const)))` and the address pseudo was already eliminated. 

Actually maybe in the target the address is not a pseudo: `addiu a1,sp,16` could come from `la`-like reload of a `(high/sum)`? No.

Alternatively, in the target the call argument is a *constant expression* `(void *)m` where m's address is a SYMBOLIC constant (virtual_stack_vars + 16) that cse folded directly into the call insn, and reload materializes it per use because it's cheaper than a register (a "rematerializable" address). In c_struct, the same constant got a pseudo (from the movstr dest) that cse reused.

OK here's a cleaner hypothesis: if the call-arg address expression is a *constant* in the RTL (not a pseudo), then each use rematerializes. cse creates a pseudo only if it decides the constant is worth a register (many uses). The difference between 3 uses (remat) and 4+ uses (register) is plausible: cse's `cse_insn` for address constants does `if (n_uses >= threshold) create base reg`. Hmm.

So: reduce the number of uses of the m address to 3, and keep the copy from creating a 4th. In c_struct, the copy creates a dest address use → 4 total → register. In score-0 (scalar), the copy stores use direct sp offsets (no address reg), so 3 uses → remat.

Therefore: make the copy's dest stores sp-relative without an address pseudo. That happens with scalar `m[i] = ...` assignments (constant indices). So use the scalar copy form but fix the SOURCE base register problem.

The source base in the scalar form without launder gets folded (lui per load). Why? Because `src[i]` where src = &global: cse substitutes the constant address into each load, giving 8 loads each with their own lui... but wait, the target has one lui + offsets. In n1 (pin kept, no launder), the output was `lui v0,0x0; lw v0,12(v0)` etc. — one lui per load. So cse did NOT create a base register. But c_struct's movstr source DID use a1 with offsets.

Why? In c_struct, the movstr expansion creates ONE address pseudo for the source (block move needs a base). cse then keeps it (the loads use offsets from it). So the movstr route gives the right source.

So: source needs the movstr; dest needs scalar stores. Can we have a block move whose dest is sp-relative direct? In the c_struct output, the dest stores ARE sp-relative (`sw v0,16(sp)`), no dest address register! Look: `afa20010 sw v0,16(sp)` — yes direct sp. So the movstr dest didn't create a live address pseudo for the stores. But `addiu s1,sp,16` exists before the copy... that's the call-arg pseudo, created early (hoisted by sched1 into the beqz delay slot), allocated s1.

So the call-arg pseudo (3 uses) got s1 in c_struct, but was rematerialized in score-0. Both have 3 uses? In c_struct maybe 4 (including the final `*(Mat32 *)(obj+0x34) = *(Mat32 *)m;` source address!). Wait, the final store reads from m: `lw v0,16(sp)` — direct sp-relative in both. And in score-0 the same. Hmm.

So why does the 3-use address pseudo get s1 in c_struct but not in score-0? The RTL must differ. Let me actually dump both correctly. I'll write a dump script for header TUs.

Let me get the includer recipe src. Use incl.py.
