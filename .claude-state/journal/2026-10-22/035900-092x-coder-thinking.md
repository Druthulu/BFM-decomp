---
ts: 2026-10-22T09:59:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_yJTS4BgUvWFSY67WXZWI
---
So v9 = the address used twice (once via p and once directly via `*(u16 *)&D_800B99DC`). The count matches (115) but the materialization is into s0 instead of v0+copy.

So the "2 uses" didn't produce the copy either.

Let me think about the target's structure once more:
```
313c: lui s3; addiu s3        (q)
3144: lui v0; addiu v0        (&D_800B99DC)
314c: move s0,v0              (p = v0)
3150: lui s2; addiu s2        (r)
3158: lhu v0,0(s0)
```

Compare with q → s3 and r → s2: materialized DIRECTLY into the callee-saved regs. So for q and r, gcc materialized the constant into s3/s2 directly. For p, it materialized into v0 and copied to s0.

What's different about p? p is DEREFERENCED (used as a base for loads/stores). Hmm! Maybe that's it: for a pointer that is dereferenced, gcc must have the address in a reg; but that's the same for the load base.

Hmm, what else... p is used across calls (in the loop) → callee-saved. q and r are also used across calls? q is used in the loop (`*q = ...`) — hmm, q is written in the loop but read? `*q = *p & 0xFFF;` — q is only written → maybe q doesn't need to be callee-saved... but it IS in s3. Hmm, so q is also callee-saved (s3) — because it's live across the call in the loop.

So why does p get the extra copy?

In gcc, when a value is a constant and it's assigned to a pseudo that is allocated a callee-saved reg, the materialization goes directly into the callee-saved reg (lui s3/addiu s3). To get "lui v0; move s0,v0", the value must be in a caller-saved reg first.

Hmm, here's a thought: the value &D_800B99DC is used as a base for a load: "lhu v0,0(s0)" — the load's base is s0 ✓ (the copy target).

What if the original source had the pointer p *initialized from another pointer* — e.g. from a table?

Alternatively — what if the original source had TWO statements:
```c
    p = &D_800B99DC;    /* some other use of p... */
```
Hmm.

Let me think about the "zero-byte re-tie fence (cookbook §34)" mentioned in the orig.c comment: that's the mechanism the project used to keep the two pseudos apart — a trick where a zero-byte read re-ties them? Hmm, the comment says the fence keeps the two pseudos apart so the short-lived one lands in v0 and the call-crossing one in s0 = the extra move. But the current orig.c doesn't have the fence (only the asm) — the comment is stale (from an earlier version).

Hmm! Maybe the fence is a lever-free way! Let me look at cookbook §34 to see what the "zero-byte re-tie fence" is. If it's a C-level trick (like a zero-length memcpy or a dummy read), it might be a legitimate "real C move" — but it might also count as a barrier/launder (a dummy read to prevent an optimization is a "barrier"-ish lever!). The brief says: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind." A zero-byte read used as an optimization fence is a launder/barrier by nature — it's an identity statement. The brief explicitly says "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack".

So the fence trick is a launder → not allowed. OK.

So: we need the copy "move s0,v0" to arise naturally.

Think about it as: the value &D_800B99DC is computed into v0 (a caller-saved pseudo) and then copied to s0. For gcc to do this, the *source* of the copy must be a pseudo that is NOT the same as p. That happens when the source expression is a variable (reg_equiv) rather than a constant.

In gcc 2.7, `p = pb` where pb is a local with a constant init: the front end creates pb as a VAR_DECL with DECL_INITIAL = &D_800B99DC. Expand creates a pseudo for pb and a set insn `(set (reg pb) (symbol_ref))`. Then `p = pb` → `(set (reg p) (reg pb))`.

Then cse: the set `(set (reg pb) (symbol_ref))` records a reg_equiv: pb ≡ symbol_ref. cse's "forward scan" (in cse_main's second phase) replaces uses of pb with the symbol_ref → the copy becomes `(set (reg p) (symbol_ref))` → then local-alloc materializes the symbol into p (s0) directly ✓ (our version).

To prevent this, the set must not be recorded as a reg_equiv. In cse.c, the recording happens in `record_eq_reg`/`update_eq_reg_notes` for a SET of a REG to a constant. But there's a condition! Let me look at cse.c's handling: in cse_main, for an insn `(set (reg r) (const))`:

```c
	  /* Record the constant value in the reg_equiv table ... */
```
and there's a well-known condition: "if the reg is used more than once, don't record the equivalence" or "if the set is the only one and the reg has one use".

Let me look at cse.c for the reg_equiv recording of constants. Search for "is_const" and "elt->is_const = 1".
