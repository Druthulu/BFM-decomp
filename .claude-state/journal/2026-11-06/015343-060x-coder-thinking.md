---
ts: 2026-11-06T08:53:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MZUAqL0Y4VJ4ptWqEfMI
---
e2 is c1-like (store after t4 load) but with sp10[4]=t4 last: score 10, 46 insns. Hmm, c1 had sp10[3]=t3 then sp10[4]=t4 → same as e2? c1: t4 load; sp10[3]=t3; sp10[4]=t4. e2: t4 load; sp10[3]=t3; sp10[4]=t4 — identical! Yes, e2 == c1 except c1 wrote sp10[3]=t3 after sp10[4]? Let me recheck c1: 
```
t4 = ...;
sp10[3] = t3;
sp10[4] = t4;
```
Yes identical. So score 10 (my c1 was 10 too).

I've spent ~40 minutes on item 1. The brief: budget 20-30 min; past 30 min stop and record a wall. WALL needs ≥20 min and ≥30 scored tries. I have ~12 scored tries, not 30. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I can't record a WALL yet; I need ≥30 tries. I could run a batch of quick candidates (each ~1.5 s). Let me generate a systematic set of variants with a small generator script (scratch under shard) and score them all via sc.sh in one go (30+ candidates). That's the efficient path: e.g., permutations of statement order among {t0..t4 loads, stores, h updates} with the constraint that sp10 values are written before the call.

Actually, a smarter search: vary
- store positions of t3 (after each of the 5 loads/stores)
- reuse of a temp for the fifth load
- h placement
- t4 store position

Let me write a generator producing ~40 candidates, score them with sc.sh (one line each), pick the best. sc.sh prints one line per file, so 40 lines — over 40? It's ~40 lines, borderline; route through tools/run.sh to a log. Or redirect output to a file and Read it.

Let me write gen.py that emits variants under $D/gen/. The C body template with slots. Variants:
1. order of the 5 loads (permutations: keep t0,t1,t2 fixed, vary t3/t4 positions: 5 variants)
2. store order: permute the 5 stores (5! too many; use a few: t3 store at positions 0..4)
3. fifth load reuse t0/t1/t2/t3
4. h placement (before/after stores)
5. combined.

Let me be pragmatic: generate ~40 candidates combining (a) t3 store position among the store sequence (5), (b) t4 store position (5), (c) fifth-load reuse (4), (d) loads order (2). 5*5*4*2 = 200 too many; sample 40.

But each candidate must be semantically correct (sp10 all written before the call; temps not reused before their value is stored). I'll write a small generator that takes a list of statements and permutes specific adjacent ones.

Actually, let me think about which lever matters most. The two requirements:
A. a0-copy → a2, t3 → a3 (d3/d2 achieved with the t3 store late).
B. t4 → v1 (needs r84/off live past the fifth load, or t4 allocated after something taking v0).

For B, note in d3 the t4 was v0 and the store late. In the target, t4=v1. The off keepalive (score 7 variant) achieved B with t4=v1 because r84 lived past the load.

What if BOTH the t3 store is late AND off is live past the load? d3 + a later use of off. Hmm.

But wait: in d3, the store of t3 is at position 34 (after h[1]) and the diff shows insert/delete for the store; the rest matched except t4 v0/v1. If we could ALSO fix t4→v1 in d3 by moving the fifth load earlier or later... In d3 the fifth load is at 24 and the store at 26. t4=v0. To get v1, r84 must live past 24. What if the fifth load is moved to the very end (after h[2])? Then off's last use is later, but t4's own position changes (target wants it at 24).

Alternatively, make t4's priority lower than r84's... it already is (10000 vs 12000) but r84 dies before t4's birth.

Hmm, what if t4's birth is BEFORE r84's death? If the fifth load's *address* computation and load are split: the load is at 24 and r84 dies at the addu at 23. If sched1 places the addu after the load? No.

What if the fifth load uses a *different* address computation that keeps off live? E.g., if off's value is used directly in the load (off*4 recomputed)? The target computes v0 once.

New idea for B: make the h[] computation use the fifth value? No.

Honestly, maybe the intended real-C solution is a different, larger restructuring that I haven't found. Given time constraints (3 items, ~90 min total budget, I've used ~45), I should move to items 2 and 3 and come back if time permits.

But the WALL rule requires ≥30 scored tries per item for a WALL. For item 1 I have ~13. Let me run a quick 20-candidate batch to satisfy the "attempt" requirement, record the best lever-free score as WALL, and move on.

Actually wait. Maybe I'm overcomplicating: maybe a "PARTIAL:keepalive" is acceptable and simpler, but it requires keeping a keepalive — trivial and scores 0 (orig). But the task's spirit is to crack. The results format allows PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers). Since the orig body keeps keepalive and pins, and pins are allowed to stay, PARTIAL:keepalive = orig. That's a legitimate fallback per the INTERFACES. But it's the trivial answer and probably what the shard is designed to avoid... The instruction says result MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers) | WALL. So PARTIAL is for when win.c scores 0 but still keeps some levers of the listed kinds. For a keepalive-only item, PARTIAL:keepalive = orig body (still has the keepalive asm). Hmm, that seems too trivial; but it's literally "scores 0 keeping only those levers".

Given the shard is "singleton crack shard G25" and all three items are keepalive, the goal is to crack them. A PARTIAL is a legitimate non-crack outcome.

Let me do a quick batch of ~20 more candidates for item 1, then decide. Actually, let me think ONE more time about the mechanism, because there may be a clean trick.

The target needs:
- r72 (a0 copy, 5 refs, live 27) allocated BEFORE t3 (2 refs, live 5, pri 4000). r72 pri 3703.
- t4 → v1: needs v0 occupied across t4's birth, i.e., r84 live past the fifth load.

What if BOTH are achieved by extending the *address temp* r84's liveness? In the off-keepalive variant (w3, score 7), t4=v1 (B fixed) and t3=a2 (A not fixed). The asm used r84 (off*4), extending its live range, which also *changed the allocation order*: r84's live length grew, and importantly, keeping r84 (v0) live across t3's range doesn't affect t3.

For A: t3 must not take a2. What if v0/v1/a0/a1/a2 are all occupied during t3's range? a0/a1 are taken by t1/t2; v0 by r84; v1 by t0 (live 24..42) — t3's range is 39..51, and t0 is live until 42 (overlapping!). So v1 is occupied during part of t3's range (39..42). If t3's range overlapped v1 fully, it couldn't use v1 anyway; but v1 is not free due to t0. So t3 takes a2. To make t3 take a3, a2 must be occupied during t3's range by a local pseudo. Which pseudo could take a2? The HI pseudos (r90-r98) take v0/v1. Hmm.

What if the a0-copy were allocated by local-alloc BEFORE t3 and took a2? r72 pri 3703 < t3 4000. If r72's live length were 24 or less → 4166. r72 live 27. What if we shorten r72's live range by 3 insns? The live length counts insns from insn 4 to the last use (the call). Can't.

What if r72's refs increase to 6? pri 4444 > 4000 → r72 allocated before t3 → a2. Then t3 → a3. AND t4? t4's v0/v1 is independent.

A 6th use of the a0 copy: the a0 copy is used at 3 lhu's + call. What if the source uses the pointer a 4th time in an existing instruction? For example, `func_8012C51C(sp10, (s32)a0)` — what if sp10's address were computed via a0? No.

What about the three lhu's: they use `((Unkstruct*)a0)->unk6/unkA/unkE`. Could we write one of them as `*(u16*)((char*)a0 + 6)`? Same one use.

What if the h[] computations use `h` and `a0` where h is derived from a0? no.

What if the call's first argument is `(s32*)sp10` and the second `(s32)a0`, and we write `func_8012C51C((s32*)sp10, (s32)((char*)a0 + 0))`? Same.

Hmm, what about `CAST_ALIAS(u16, (s32)a0, 0xA)`: maybe it expands to `*(u16*)((s32)a0 + 0xA)` — one use.

What if the a0 pointer is used in the h[0] store address too? The stores are to sp10.

OK, what about making r72 a *global* pseudo (allocated by global-alloc, which runs after local-alloc)? No, global runs after local, so t3 would take a2 anyway.

Hmm, what if the a0-copy is allocated by local-alloc but with a *copy preference*... suggestions aren't used.

Let me try the "6th use" idea via a real C construct: `h[0] = h[0] + ((Unkstruct_800B5CB8 *)a0)->unk6;` could be written as
```
    s32 p = (s32)a0;  // copy
    h[0] = h[0] + *(u16*)(p + 6);
    h[1] = h[1] + *(u16*)(p + 0xA);
    h[2] = h[2] + *(u16*)(p + 0xE);
    func_8012C51C(sp10, p);
```
That's the same 4 uses.

What if we add a use that combines with the call: `func_8012C51C(sp10, (s32)a0 & ~0)`? An identity — launder, disallowed and folded anyway.

What about `func_8012C51C(sp10, (s32)a0 + (s32)sp10 - (s32)sp10)`? No.

OK. I'll do the batch and move on. Let me generate ~20 structured variants programmatically and score them.

Actually, a better use of the remaining item-1 time: try the 5-store permutations with the t3 store at each position, and the fifth load position variants. Let me generate with a script and score all.

Template:
```
void func_8017F6B0(void *a0, s32 a1) {
    s32 t0, t1, t2, t3, t4;
    s32 sp10[5];
    u16 *h;
    s32 off;

    off = a1 * 20;
    <LOAD0..LOAD4>
    <STORE0..STORE4>
    h = (u16 *)sp10;
    h[0] = ...
    ...
}
```
where LOADi = `t{i} = *(s32 *)((char *)&D_<sym> + off);` and STOREi = `sp10[i] = t{i};`.

Permutations: I'll generate all 5! = 120 load orders? too many. Use random 30 permutations with stores in fixed order, plus 10 with stores permuted. Score 40 candidates ≈ 60 s. Let me do it.

But careful: the results must be meaningful; a random search over statement order is exactly what the "real C moves" allow (statement order). 40 scored tries satisfies the WALL threshold (≥30).

Let me write gen.py.
