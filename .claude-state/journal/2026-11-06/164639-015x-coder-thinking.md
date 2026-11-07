---
ts: 2026-11-06T23:46:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Kbnh4PzZqAnNWmNxjOW6
---
So the lever-free body: `mode` gets $s4 (mine), target wants $s3. Wait, register pairs mine -> target: s3->s4 x10, s4->s3 x4. So in target, the roles are swapped: what is in mine's s3 should be s4, and mine's s4 should be s3.

In the original with pin, mode is $19 = s3. So target has mode in s3 (i.e. the `mode` variable). In my lever-free version mode is in s4? Let's see: `li s4,-1` is `mode = -1` in mine, target `li s3,-1`. So yes, mode → s4 in mine, target s3.

The other one: `lui s3,0x0; addiu s3,s3,0` = base = D_800AF630? Hmm base is u8* D_800AF630. In target it's s4. So base → s4 in target, s3 in mine. They swap.

Wait — actually the register pairs say s3->s4 x10 (10 occurrences of mine s3 = target s4) and s4->s3 x4. So base (heavily used, 10 refs) is s3 mine → s4 target. mode (4 refs) is s4 mine → s3 target.

So global/local alloc prefers base in s3 (more refs), but target wants base in s4 and mode in s3. Interesting. The pin made mode take s3, which pushed base to s4.

Also there's an extra `lui a3; addiu a3` vs `lui v0; addiu v0; move a3,v0` — one extra insn in target (161 vs 160). That's the `D_800C7C64 = &D_800A2E20;` where target loads the address into v0 then moves to a3, whereas mine directly into a3. Hmm, or it's the `q = &D_800C7C60` part.

Actually in target with the launder, q is a new pseudo reg, so `q = &D_800C7C60` gets a fresh reg (v0?) then `p = q` moves it to a3 (p's reg). Without the launder, `q` and `&D_800C7C60` are the same pseudo, so it goes straight to a3.

So target needs: (a) an extra copy for q->p, and (b) mode in s3 with base in s4.

How to get the extra move without asm? The launder is on q. A real C approach: make q a separate variable that gets a 2nd set... Actually the pattern from moves: "launder->real 2nd set" — e.g. C0414 dead-reset.

Here: `s32 *q = &D_800C7C60; p = q; *p = val; D_800C7C64 = &D_800A2E20;`

Target assembly: `lui v0; addiu v0` (address of D_800C7C60 in v0), `move a3,v0` (p = q), then store `sw val,0(a3)`.

Why would cse/combine fold without launder? `p = q` — both are pseudos; combine copy propagation merges p and q. With the launder, q gets a new reg (an asm output), so p=q becomes a real copy.

A lever-free way: make p be assigned twice? Hmm. Or make q have a real second set so cse can't fold. E.g.:
```
s32 *q;
q = &D_800C7C60;
p = q;
```
Same thing. Need something to prevent copy propagation of p=q.

Ideas from catalog: "statement order, init at decl, pointer reuse, && folds". Copy propagation in combine (combine.c) merges reg copies. C0414 dead-reset: set q=0 after use? That would kill it.

Hmm, actually the standard trick used in these shards: split into a real 2nd set. For the launder `__asm__("" : "=r"(q) : "0"(q))`, the effect is q is redefined (new pseudo) from the old value. Equivalent lever-free: `q = (s32*)q;` — but that's an identity cast which combine may fold... and the brief says identity-statement launders do NOT count as a crack.

Alternative: give q a real second assignment that is value-preserving but not an identity the compiler recognizes... e.g. `q = &D_800C7C60; p = q;` vs using different types.

Wait. Let's think about what target actually needs. Target:
```
lui v0,0x0
addiu v0,v0,0      ; v0 = &D_800C7C60
move a3,v0         ; p = q  (a3 = p)
sw ...
```
Actually maybe not. Let's look at the real target disassembly. Let me get the dumps. Hmm.

Actually let's reconsider: mine[107:109] has lui a3/addiu a3 (direct address in a3), target has lui v0/addiu v0/move a3,v0. So target computes the address into v0 then copies to a3. Why v0? Because q (the fresh asm-output pseudo) got v0, then p (used for *p = val and passed as 4th arg to CdReadRequest) got a3.

So the target's `q` is a distinct pseudo with its own reg (v0) that dies at `p = q`, and p takes a3.

How to get a distinct pseudo in C without asm? The launder's semantics: q_new = q_old where q_new is a fresh register (unknown value to the compiler? No — "=r" output with "0" input means the output is tied to input reg, value preserved, but compiler treats it as a new value).

Real C equivalents that produce a copy:
- Make q's value come from a computation the compiler can't fold: e.g. `q = &D_800C7C60; p = q;` — combine folds.
- Use a u32 intermediate: `u32 a = (u32)&D_800C7C60; q = (s32*)a; p = q;` — probably still folded.
- Two-step: `q = &D_800C7C60; p = &D_800C7C60;` no.

Hmm, what about the type? What if `p` is not `s32*` but assigned from q where q has different type... The copy is a same-mode copy.

Another approach: the launder might not be needed if we change something else so that q naturally has a second set. C0414: dead-reset. For example:
```
s32 *q;
q = &D_800C7C60;
p = q;
*q = val;
q = 0;          // dead reset
```
But q = 0 after its last use is dead code; flow/cse might remove. Actually C0414 "dead-reset cse-breaker" says a dead reset breaks cse classes. But here we need the copy p=q to survive; a dead reset of q after the copy wouldn't affect the earlier copy... hmm, it might: cse makes p and q equivalent; a subsequent set of q to 0 un-equivalents them but the earlier copy is already merged in combine.

Actually combine is what folds `move a3,v0` when p and q are equivalent registers. combine (combine.c) does reg copy propagation: if a pseudo is set by a copy and used once... Let's think about pass order: cse1 → ... → combine → ... Actually in gcc 2.7.2: cse (cse1), then loop, then cse2, then flow, then combine, then sched. The copy p=q is a `set (reg p) (reg q)`. Combine's `try_combine` on the adjacent store `set (mem a3) (reg val)`: the store uses p; combine propagates p=q into the store and deletes the copy, if p has only one use. Since p is used by the store and by CdReadRequest arg (2 uses), combine might not delete it. Hmm but the address register here: actually `*p = val` where p is the address. The move a3,v0 is `p = q`; then `sw val,0(a3)`.

Hmm wait, maybe the copy is being folded by cse1 already (make_regs_eqv) so the pseudo is the same, and there is no copy at all in mine. In target, the launder creates a real copy that survives.

What C construct creates a real copy that survives? Options:
1. Different pseudo lifetimes / a loop.
2. Volatile? No, that's a barrier kind (levers). Actually `volatile` is a barrier/launder-ish? The brief's kinds list: pin (register-asm), launder, barrier, keepalive macro or asm. So no volatile.
3. Make q assigned from a function? No.
4. Do the copy through a struct field or array? e.g. `s32 *tmp[1]; tmp[0] = &D_800C7C60; p = tmp[0];` — that's a memory round-trip, would add lw/sw (too many insns).
5. Make q's value come from a conditional: `q = cond ? &D_800C7C60 : &D_800C7C60;` — combine may simplify.

Alternative: accept that q is the same pseudo but arrange the address in v0 and p in a3 differently... Actually maybe we can change the code so p is a different register (a3) and address computed in v0 naturally: what if we don't use q at all:
```
p = &D_800C7C60;
*p = val;
```
Then only one insn pair. Mine currently is exactly that effectively (160 ins). Target has the extra move. So target genuinely needs 2 regs for that address.

Hmm, but maybe target's extra insn comes from somewhere else. Let me actually look at the target disassembly around there to be sure. Let me use the dumps. There's a tool for objdump. Let me check tools/cc1_dumps_tu.sh or use dt.sh's "diff" mode? Actually the scorer's output already gives the target insns.

So yes: target at insn 107-109: `lui v0; addiu v0; move a3,v0`. Mine: `lui a3; addiu a3`. So target = 1 extra insn.

The natural C: two variables, the first loaded with the address and then copied.

OK so I need a C construct where the copy survives cse/combine. Ideas:
- Make the source a value of a different mode? e.g. q as u32 (pointer arithmetic), p as s32*. If q is u32 and p is s32*, the copy is still SImode.
- Use `(s32*)((u32)&D_800C7C60)` — same.

What if q is assigned twice, once before the if and once inside? Hmm.

What about making the copy via a function argument? `func_800D00E4`? no.

Let me look at how other shards cracked launder where the launder was a simple out-only one. From moves: "out-only launder -> real 2nd set `pv = pv & 0xFF000000;` split from the store". That's for a different pattern (mask laundering). For a copy launder like here... "launder->pv=*p; pv&=mask split". Hmm.

Another move: func_8018C2D8 "reuse m for next ptr (m = s1+0xD0; dv = m) and m1 for col: reassignment kills the cse sym class".

Hmm. What about the "dead-reset" C0414 idea applied to the address temp: 
```
s32 *q = &D_800C7C60;
p = q;
q = 0;
```
The `q = 0` after: does it prevent cse1 from making p equivalent to q? cse1 (cse.c) computes equivalence classes; a set of q to a constant invalidates q's equivalence for later uses, but the earlier `p = q` already recorded p ≡ q... Then combine merges the copy into uses of p. Hmm, actually combine merges only when the copy's destination has one use and it's a reg-reg or reg-mem. `p = q` then `*p = val`: the store's address is a reg. try_combine can combine `set p q` + `set (mem p) val` into `set (mem q) val` only if p is not used elsewhere (it is: passed to CdReadRequest). Actually wait — is it? `CdReadRequest(&cdFileLocTable[file], D_80072C74, mode, p)`. Yes p is used there. So combine shouldn't fold it, since p is live and used twice. Hmm, then why did mine fold?

Unless in mine cse1 made them the same register (make_regs_eqv), so there's literally no copy insn. Then combine sees a single pseudo. The launder's asm output forces a *new* register, so cse can't merge.

So I need something that stops cse1 from equating p with the address pseudo. cse1: `p = q` where q is `&D_800C7C60` — actually in C, `s32 *q = &D_800C7C60; p = q;` The compiler (cc1) likely emits directly `p = &D_800C7C60` via copy propagation in the frontend or in cse. Hmm.

Wait — maybe the launder's real function is at the RTL level: q is set twice (once from the address, once from asm) so cse sees a multi-set pseudo and doesn't propagate. That's the "real 2nd set" mechanism.

So a real 2nd set of q that's value-preserving and not an identity-statement launder. Hmm, the brief says identity-statement launders do NOT count as a crack. But a "real 2nd set" like `q = (s32 *)((u32)q & 0xFFFFFFFF)`? identity.

What about the C0414 dead-reset: `q = 0;` after use is a real 2nd set (different value), not identity. That is the C0414 technique that cracked 3 launders in G16x. Let's try:
```
s32 *q;
q = &D_800C7C60;
p = q;
*p = val;
q = 0;   /* dead reset */
D_800C7C64 = &D_800A2E20;
```
But does the dead reset prevent cse1 from making p≡q? In cse1, q has 2 sets; cse still processes `p = q` and records the equivalence, then when q is re-set, it invalidates. But p is still equivalent to the *old* q value. Hmm, cse's make_regs_eqv works on registers, not values: p and q become the same register for the rest of the block until q is set. When q is set to 0, cse breaks the equivalence. Then combine: the copy p=q... if p and q are different pseudos, combine sees `set (reg p) (reg q)`. Then the store `set (mem p)`. Combine can propagate.

Hmm, the C0414 mechanism: "dead-reset cse-breaker" — a dead reset breaks cse's class so a second derivation isn't folded. Different use case.

Let me look at the actual pass behavior. Maybe easier: try a bunch of candidate bodies with sc.sh and see scores.

Actually, first let me reconsider the register allocation issue: mode should be s3 and base s4. Even if I fix the copy, the reg assignment may differ. But the pin removal means mode is just a local. In the target, mode got s3 (callee-saved, more refs?) and base s4. In mine, base got s3 (10 refs) and mode s4 (4 refs). local-alloc/global-alloc assigns by ref count and live length. To make mode win s3, mode must have higher priority... but mode has fewer refs. Hmm.

Wait: in mine, base s3 (10 refs), mode s4 (4). In target, base s4 (10 refs), mode s3 (4). So the *ordering* of allocation flipped: target allocated mode first (got s3), then base (s4). That's global-alloc's allocation order: it sorts by "allocno priority" = refs/live-length. In mine base is allocated first because it has more refs? Actually the order: global.c sorts allocnos by floor_log2(refs)*refs/live_length or similar.

Hmm, but this could be affected by the extra insn/copy: the copy in the block adds a use of... no.

Wait, maybe the difference: with the pin, mode was fixed to s3, so base got s4. Without pin, base gets s3. So we need to change priorities so mode gets s3. That's hard: base has more refs.

But hold on — maybe base and mode are both *local* (block-local) and local-alloc assigns in order of first use / qty. Hmm, base is used across the whole function (assigned at top, used in many ifs), mode is also used across. Both cross blocks? base is set once at top and used in every if-block; mode set in one block and used in the if and at the end (CdReadRequest arg and `if (mode == 0 ...)`). Both global.

Hmm, the register pair counts: s3->s4 x10 means base has 10 refs to s3 in mine. mode s4 x4.

global.c's `allocno_compare` sorts by floor_log2(refs * something / live_length). Let me recall gcc 2.7.2 global.c:

```c
static int
allocno_compare (v1, v2)
{
  ...
  /* Prefer the one with the highest floor_log2 (refs * something) ... */
  ...
}
```
Actually in global.c: `allocno_compare` compares `floor_log2 (allocno[p1].refs) * allocno[p1].refs / (allocno[p1].live_length + 1)` ... Let me check the actual source: tools/reference/gcc-2.7.2/global.c.

Actually let me focus: what would make mode outrank base? In the target, mode got s3. Maybe it's not global-alloc but local-alloc ordering: if both are local to the same block... no.

Hmm wait, maybe the real difference: with the pin present, `mode` was a *hard register* variable, so it wasn't in the allocator at all; base took s4 because... s3 was reserved. Without the pin, mode takes s4? Why s4 and not s3? Order: base first → s3, mode next → s4. In target (pin), base first → s4 (since s3 reserved by the pin), mode = s3 fixed.

So in target, base is allocated to s4 because s3 is taken. Lever-free, base takes s3. To get base→s4 and mode→s3 lever-free, we need mode allocated *before* base. Since the allocator sorts by priority, we need mode's priority > base's.

Global allocno priority in gcc 2.7.2: let me check the source.

Actually, let me read global.c allocno_compare.
