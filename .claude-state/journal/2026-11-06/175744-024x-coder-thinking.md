---
ts: 2026-11-07T00:57:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_K8FcIU325egTlh5Et7vi
---
This is the set-side (reg_n_refs += loop_depth for a set). And on the use side similarly. Let me not dig further.

Key insight: priority = floor_log2(refs)*refs/live*10000*size. p is dominant. The wall stands unless we can restructure the pointer into pseudos whose individual priorities are low. That's a deep restructuring that would change the instruction stream.

Given the prior 28 tries + this analysis, item 1 is a WALL. But the brief requires ≥20 min and ≥30 scored tries on the item for a WALL. So I'll generate ~30 lever-free variants, score them, take the best, and record the WALL with tag (from walls.txt or new). Let me check walls.txt tags.

But wait — before concluding, consider: the target's register assignment might be reachable via the *param copy order*? No, global alloc priority is the determinant.

Actually hold on. Let me reconsider. There might be a subtlety: p's allocno might not be the param pseudo. Let's see what actually happens in plain C: mine has `move s0,a0` (p=s0), `move s1,a2` (b_=s1), `move s3,a3` (c_=s3), `move s2,a1` (a_=s2). So a_=s2 matches target! And b_,c_,p are cycled.

Target: b_=s0, c_=s1, p=s3.

So we need b_ to take s0 instead of p. b_ priority 3333 vs p 11379.

Wait, what are b_'s refs? b_ is used: `(b + 0xf)` before the loop, `b & 0xffff` in the loop, `b += 8` in the loop. 3 refs, live 9. In the target, b is a hard-reg pinned var, so b_ (param) has just the copy `move s0,a2` — one ref, live 1! In the target, b_'s param pseudo is dead after the copy.

Right! In the target (pinned body), the param b_ has 1 ref (the copy to hard $16). So b_ never competes. The hard reg b=s0 is taken because of the pin.

Lever-free, b_ carries the b uses (3 refs) and must take s0 — but p outranks it.

So the lever-free body fundamentally can't reproduce the pinned allocation unless we make the *source* variables behave like the pinned ones: i.e., have a separate variable that takes s0 and is used 3 times, while the param copy dies.

What if we introduce local variables for b, c, a that copy the params at entry, and use those? That's what `b = b_` does in the original. But without pins, `b` and `b_` are the same pseudo after copy propagation/cse (they'd be coalesced by reg_may_share or copy propagation). Unless we prevent the merge...

Hmm, actually the original pinned source has `new_var = a_; b = b_; c = c_; a = new_var;` — the pins force hard regs so the copies survive. Lever-free, those copies are copy-propagated away.

What if we make the local variables have a *different mode/type* so the copy can't be propagated? E.g. `s16 b2 = b_;`? That would truncate — changes codegen (b & 0xffff already...). Hmm, b is u32 and used with `& 0xffff` and `+0xf`, so a u16 truncation would change the value (b can be > 0xffff: b starts as arg and += 8). Actually p[2] = cs | ((b + 0xf) & 0xffff) — only low 16 bits. q[2] = (cs | (b & 0xffff)) | flag — only low 16 bits. So b's high bits are never used! b could be u16. Then `b += 8` on u16... target's addiu s0,s0,8 (no mask). If b is u16, the += would need masking (andi) unless gcc knows... risky.

Hmm, but the prior attempt tried "s16/u8 widths" maybe.

OK. Let me look at the walls.txt for a tag and just run the 30 tries. Time check: started item 1 at ~17:57. It's now maybe 18:05.

Actually — hold on. Let me reconsider whether MATCH even needs the register assignment to be identical. Yes, byte-identical instructions.

The score is 43 (masked diff count). To get 0, everything must match.

Let me think about the *third* possibility: make p's allocno smaller in refs by using `q` for the first stores AND having p die early, then the loop pointer q is a different pseudo. In the target, the loop pointer is a0 (q) and p=s3. p's refs in the target: let's count from the target instructions using s3:
1. move s3,a0 (write)
2. addiu v1,s3,-20 (p-5)
3. sw v1,0(s3)
4. sw v1,8(s3)
5. sw a1,4(s3)
6. sw v1,12(s3)
7. addiu s3,s3,20 (p+=5)
8. move a0,s3 (q=p)
9. move s3,a0 (p=q) at loop exit
10. move v0,s3 (r=p)
11. lhu v1,-32(v0), lhu a0,-12(v0), sh ... use v0 not s3.

So p (s3) has ~10 refs in the target's instruction stream. And it still got s3 because pins took s0,s1,s2.

So lever-free, with p refs ~10-11 and live ~29, priority 11379 — the highest among the s-register candidates (b_ 3333, a_ 1944, c_ 1666). Global alloc assigns p s0 first.

To beat this, the ONLY lever-free route is to make three other pseudos outrank p, or make p's priority lower. p's priority is structurally high.

Could we make p not a global allocno at all — i.e., local-alloc'd? If p's uses were confined to a single basic block, local-alloc could assign it a caller-saved reg (like a0). The target has p in s3 across the call... the call is at the top. Hmm.

What if the pointer variable p is split into block-local pieces? E.g., the first block stores through a temp that's local-alloc'd to a0/a1, and the loop uses q... but the target uses s3 for the stores.

So MATCH seems impossible → WALL. Prior evidence agrees (28 tries, best 37 with a signature change, 43 void).

Now: is the wall tag "callee-saved-order" or "global-pri-bank-order"? The walls.txt has tags. Let me read walls.txt (49 lines).

Then I'll do the 30 tries efficiently.

Let me now plan the 30 candidate bodies for item 1. I'll write a generator script in Python (scratch) that emits variants from a template, then run sc.sh over them. The generator can produce combinations:

Dimensions:
1. nn copy: yes/no (`nn = (a<<16)>>28; n = nn;` vs `n = ...`).
2. r copy: `r = p;` / `r = q; p = q;` / `u16 *r = (u16*)p;` / no r.
3. first-store pointer: p vs a temp.
4. cs temp vs inline c<<16.
5. flag init at decl vs later.
6. col init at decl vs in loop.
7. cl computed with (s16)v cast vs plain.
8. loop: for / do-while / while.
9. i type s16 vs u32 vs int.
10. declaration order permutations.
11. `&&`/`||` fold: `if (nn || i == 3 || i == 1)`.
12. statement order: swaps of the 4 pre-loop stores.

I can generate ~30-40 combos. But note: each candidate changes the code shape; the best score will likely stay ~43.

Also, importantly, the launder removal: the original has `cl = ((v << 6) | 0x4016) << 16;` after the asm launder. The prior note says "(s16)v cast for 2nd (v<<6|0x4016)<<16 (kills launder 1: cse can't fold, combine drops it)". Hmm, r4.c has `cl = ((((s16) v) << 6) | 0x4016) << 16;`.

Let me check the second launder: `r` — the target has `move v0,s3` (r=p). The prior note says "return type u32* + return r (kills launder 2)". But without a signature change, can we keep r? The target's `move v0,s3` comes from `r = p` where r is used as the base for two loads/stores. If cse folds r into p, no move. In the pinned body, the launder asm prevents the fold. Lever-free, cse folds (r and p are equal).

C0414 dead-reset idea: after `r = p;`, insert `p = 0;`? Then p's later uses... p isn't used after r=p (the tail uses r). So `p = 0` is a dead store to a pseudo — flow's dead-code elimination would remove it (or not? gcc 2.7.2's flow does dead store elimination for pseudos? `delete_dead_store`? There's "dead code elimination" in flow.c). If it survives, p's value changes so r != p for later uses — no, r was already copied; the fold happens at the point of `r = p`: cse records reg_eqv(r,p), then uses of r are rewritten to p. If p is later set to 0, cse's equivalence must be invalidated at the set (cse invalidates the class on a set). But the *use* of r happens after p=0, so at that point r's class... cse's canon_reg(r) would map r to the class representative; if p was re-set, the class is broken and r becomes its own value — but then r's value must be *saved* somewhere, i.e., the copy `move r,p` must exist! That's exactly the C0414 dead-reset trick: `r = p; p = 0; ...use r...` forces the copy to materialize.

But wait: p=0 would clobber p — p isn't used later, so it's fine semantically. And the compiler must keep the copy because r's value differs from p's now.

Let's check: does that produce the target's `move v0,s3`? Target: `move s3,a0; move v0,s3; lhu v1,-32(v0); ...`. So p=q (move s3,a0), then r=p (move v0,s3), then p=0 would be `move s3,zero` — an EXTRA instruction not in the target! Unless gcc's dead-store elimination removes `p = 0` since p is dead afterwards. Then would cse still keep the copy? The dead-store pass runs after cse? Order in gcc 2.7.2: cse runs, then flow (dead code elim), then... The copy decision happens in cse. If `p = 0` is present in the RTL at cse time, cse breaks the class; the copy is emitted. Later, flow's dead-store elimination could remove `p = 0` (p is dead after). Then we'd have the copy but not the dead store — exactly the target!

That's a promising real-C move (C0414 style). Let me try: 
```
p = q;
r = p;
p = 0;
*((u16*)(r-8)) += 6;
*((u16*)(r-3)) += 6;
```
But `p = 0;` after r=p: p is dead, so flow deletes it (dead store to a pseudo with no later use → `delete_dead_store`?). In gcc 2.7.2 flow.c, dead store elimination is in `flow_analysis`/`delete_dead_stores`? There's `-dce`? Hmm, gcc 2.7.2's flow does `if (reg_n_sets... )`. There is dead code elimination in `flow.c` (`delete_dead_insns`?). Actually gcc 2.7.2 has `dce.c`? No. The `flow.c` has "dead code elimination" via `mark_used_regs`? Let me check: gcc 2.7.2 flow.c does dead store elimination for local vars? There's `-fcse-follow-jumps`, `-fdce`? Hmm.

In gcc 2.7.2, `flow.c` has `life_analysis` with `PROP_DEATH_NOTES` and dead code elimination is done by `delete_dead_insns`? Let me grep.

Actually, gcc 2.7.2 does dead-store elimination in `flow.c`: "Delete no-op move instructions... Also delete insns that are dead stores"? Let me grep for "dead".

Let me be quick: grep flow.c for "dead store" / "delete_insn".

Also `p = 0` where p is a pointer param: setting a param to 0 is a real store to a pseudo; if the pseudo is dead, sched/dead-code might remove it. Actually gcc 2.7.2's `flow.c` has `delete_dead_insns`? Hmm.

Alternatively use the C0414 pattern literally: `_v = v; v = 0;` from moves.md line 387: "C0414 dead resets (_m = 0 after each func_8012F14C call; m = 0; _v = 0 after RotTransSV)". So dead resets work.

OK let me just try it. That's the most promising lever for the second launder.

Now for the first launder (v): the asm `__asm__("" : "=r"(v) : "0"(v))` forces v into a register and prevents cse from folding the two `(v<<6|0x4016)` expressions. Target: 
```
sll v1,v0,0x6; ori v1,v1,0x4016; sll v1,v1,0x10; ori v1,v1,0x3850; sw v1,12(s3)
...
sll v0,v0,0x6; ori v0,v0,0x4016; sll t2,v0,0x10
```
So the first expression `((v<<6)|0x4016)<<16 | 0x3850` uses v0 and v1; the second `((v<<6)|0x4016)<<16` (cl) uses v0 and t2. Note the first is computed first (v1) then the second (v0). Interesting: the first expression's v is v0, and the second also v0 — same register, so v stays in v0.

Hmm, actually in the target: `sll v1,v0,0x6` uses v0 = v. Then `sll v0,v0,0x6` for cl. So v is v0 and both expressions read it.

Plain C: cse would fold `(v<<6)|0x4016` across the two statements → compute once. That's why the launder exists: to force two computations. In the target there ARE two computations (two sll/ori pairs). So a lever-free body must force the duplication: the (s16)v cast idea: `cl = (((s16)v) << 6 | 0x4016) << 16;` — a different expression (sign-extended), so cse can't fold it with the u32 version. But then the generated code would have extra sign-extension insns? The prior note says "(s16)v cast for 2nd (v<<6|0x4016)<<16 (kills launder 1: cse can't fold, combine drops it)" — meaning it produced the right code (the (s16)v is value-preserving since v is 0..0xb4). In r4.c that's what's used: `cl = ((((s16) v) << 6) | 0x4016) << 16;`.

OK so the first launder is handled by the (s16) cast. Good.

Now the C0414 dead-reset for r. Let me build candidate w1 = r4.c + nn copy + r dead-reset.

Let me write a batch generator. Actually simpler: write candidates individually but compactly, using a template script.

I'll write a Python generator under the item dir that writes wNN.c files. But note: "Scratch files only under the shard dir" — yes, item dir is under .run/P40/T11/P1x/.

Hmm, but the trap: cleanup globs match win.c. I'll use explicit rm lists or leave files (shard < 200 MB).

Let me write the generator.

Template (lever-free base):

```c
void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_)
{
  u32 v;
  u32 flag;
  u32 n;
  u32 cl;
  u32 t;
  u32 *q;
  u32 *r;
  u32 col;
  s16 i;
  ...
}
```

Variants to generate (say 24), each with a name:
- v0: base (r4 copy)
- v1: nn copy (nn var + n=nn)
- v2: r dead-reset (p=q; r=p; p=0;)
- v3: v1+v2
- v4: v2 with `p = 0; r = p;`? no, order.
- v5: r = p then p = 0 with p's decl...
- v6: `u32 *r = p; p = 0;`
- v7: r as u16* with dead-reset.
- v8: nn copy + r dead-reset + col init at decl.
- v9: do-while loop shape.
- v10: while loop.
- v11: i as u32.
- v12: i as int.
- v13: `if (nn != 0 || i == 3 || i == 1)` (fold ||).
- v14: if with nested form.
- v15: stores reordered (p[1],p[3] first).
- v16: cs inline.
- v17: flag init at decl (flag = 0x1000000 at decl).
- v18: col init at decl and no col=0 in loop.
- v19: t computed via n directly.
- v20: q = p + 5 (instead of p += 5; q = p).
- v21: p += 5 then q = p (base) but tail uses q directly (no p=q).
- v22: r = q; p = q; (r before p)
- v23: nn copy + tail r = q; p = q.
- v24: v = (u32)func_80029504(); v = -((v-10) < 0x4b0) & 0xb4 (fold).

Each is lever-free (no asm, no register).

Also I should double check: does the target's `move a2,v0` (nn copy) require `n = nn;`? Yes.

And `move v0,s3` requires the r copy.

Both together would make mine 101 ins (matching target count).

Let me generate and score. I'll write the generator script now.

Actually, maybe simpler and less error-prone: write a single Python script with a list of (name, body) strings. That's a lot of text but fine. Let me instead write a template function with flags, generating bodies programmatically — more compact.

Let me write the script.

Template structure with flags:
- nn_copy: "  nn = (a << 16) >> 28;\n  n = nn;\n" vs "  n = (a << 16) >> 28;\n"
- r_mode: "plain" (r = p; use r), "deadreset" (p = q; r = p; p = 0;), "none" (use q directly), "qfirst" (r = q; p = q;)
- tail: use r or q.

Let me define the pre-loop block as in r4:
```
  v = -((u32) (func_80029504() - 10) < 0x4b0) & 0xb4;
  c <<= 16;
  p[0] = (((u32) (p - 5)) & 0xffffff) | 0x3000000;
  p[2] = c | ((b + 0xf) & 0xffff);
  p[1] = 0x74808080;
  p[3] = (((v << 6) | 0x4016) << 16) | 0x3850;
  p += 5;
  q = p;
  cl = ((((s16) v) << 6) | 0x4016) << 16;
  flag = 0x1000000;
  for (i = 0; i < 4; i++)
  {
    ...
  }
  p = q;
  r = p;
  *((u16 *) (r - 8)) += 6;
  *((u16 *) (r - 3)) += 6;
```
with the loop body from r4.

Wait: `c <<= 16` vs `cs = c << 16`. r4 uses `c <<= 16;` and then `p[2] = c | ...`, `q[2] = (c | ...)`. In the target, c (s1) is `sll s1,s1,0x10` before the stores, and `or v1,s1,v1` in the loop. So c is shifted in place. Good.

Let me write the generator with these variants and score all in one sc.sh run (each ~1.5 s; 25 candidates ~40 s).

Actually sc.sh prints one line per candidate with score. Good. But it doesn't show the diff. I'll then take the best few and dt.sh them.

Let me write the script.
