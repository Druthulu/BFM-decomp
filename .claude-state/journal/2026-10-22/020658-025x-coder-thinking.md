---
ts: 2026-10-22T08:06:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IDAo9zH3AZtMJVXCXESv
---
Not directly about cse copy propagation. Let me check regalloc.md for the cse copy-merge notes, which may explain when a copy survives.

Actually, let me stop theorizing and run experiments. Time budget: 20-30 min per item; I've spent ~10 min on 801880E0 (done) and starting 80182ED4.

Let me write a batch of candidates for 80182ED4 and score them.

Candidates:
c2: u as s16 (`u = t;` then `t = u - 1;`)
c3: u as u16
c4: u s32, but the else arm restructured so t outlives u:
```
} else {
    u = t;
    t = u - 1;
}
```
Hmm that's the same.

c5: use a second variable `v`:
```
} else {
    u = t;
    v = u - 1;
    t = v;
}
```
Hmm, extra copy.

c6: swap the roles: make the *loaded* value a separate var:
```
} else {
    u = t;
    t = u - 1;
}
```

Let me think about what specifically makes cse keep the copy. In gcc 2.7's cse.c, the relevant function is `make_regs_eqv`. I recall its code:

```c
static int
make_regs_eqv (reg, orig_reg, insn)
     int reg, orig_reg;
     rtx insn;
{
  int regno = reg;
  int orig_regno = orig_reg;
  rtx copy;
  HOST_WIDE_INT temp1;
  ...
  if (reg_equiv_content[regno] == 0 && reg_equiv_content[orig_regno] != 0)
    { ... }
  ...
  /* Don't attempt to equate the two registers if one of them is
     a hard register...  */
  ...
  /* If the equivalence is invalid ... */
  ...
  /* If we are setting a reg to a reg and the reg is a pseudo-reg, and the
     source is a pseudo-reg, ... */
  ...
  /* ... */
  reg_equiv_content[regno] = copy;   /* regno now holds the same value as orig_reg */
  ...
  /* If we are setting a reg to a reg, and the source reg is dead
     after this insn, we can delete the copy ... */
  ...
}
```

And crucially, in cse.c's main loop, there's this in `cse_basic_block`:
```c
	  /* If this insn is a copy (set of a reg to a reg) and the destination
	     is not a pseudo-reg, ... */
```
and there's the "reg_equiv_content" propagation which happens in `cse.c`'s `simplify_insn`? no.

Hmm, gcc's actual copy propagation of reg_equiv_content happens in the **`final`/`reload`** phase? No. It's in `cse.c`:

```c
/* Return true if we should consider the insn as a candidate for
   the equivalence table.  */
```
and
```c
      /* If we have a set of a reg to a reg, and the reg is not dead,
	 and the reg is a pseudo, we may substitute the value. */
```

Actually! I remember: gcc's cse.c contains:

```c
	  /* If this insn is a copy of a pseudo-reg, and the pseudo-reg is
	     not live, ... */
```
and
```c
      /* If REGNO is set to the value of ORIG_REG ... */
```

and importantly, the actual "make the copy real instead of propagating" decision is in `cse.c`:
```c
	      /* If we are setting a reg to a reg, and the reg is used more
		 than once, and the source is used once, we may prefer to
		 keep the copy and rewrite the source's uses. */
```
which matches the G02 wall note: "iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1".

So: the copy's SOURCE (t) gets rewritten to the DESTINATION (iVar1) when the destination outlives the source. In our case: u (dest) outlives t (src) → so t's uses get rewritten to u → the copy survives as `or v1,v0`!! And the addiu would read u's reg.

But empirically the copy did NOT survive (score 6). Hmm. Unless the rewriting of t's uses to u happened, and then the copy was deleted because...

Hmm, actually: if t's uses are rewritten to u, then after the copy, the value "t" is "u". The next insn `t = u - 1` defines t. And t's uses after that... `unk84 = t`. So the copy u=t survives, and `t = u - 1` → `addiu v0, v1, -1` with u in v1.

But the observed score-6 diff showed `addiu v0,v0,-1` — one register. So the copy did NOT survive. Hmm.

Unless the cse rule is the opposite: the destination is rewritten to the source when the source outlives. In our case, t (src) — does t outlive u? t is defined by the copy's source... hmm, t's live range: the `lh` defines t; t is used by the copy (u = t) and by `beqz/bnez v0`; then t is redefined. u is used by `t = u - 1`. So both die around the same time.

The G02 wall case had "iVar1 outlives t" → iVar1 canonical. Here maybe t and u have equal lives and the tie-break goes to the source (t) → t canonical, u rewritten to t → copy removed → `addiu v0,v0,-1`.

To flip the tie-break: make u strictly outlive t. E.g., use u AFTER the addiu:

```
} else {
    u = t;
    t = u - 1;
    /* use u later */
}
```
But there's nothing after. Unless we restructure the store:

```
} else {
    u = t;
    t = u - 1;
    unk84 = t;
}
```
and the t==0 path also stores unk84 = 0x1E separately. Then the target's common store at 8138 would be split into two stores → different asm (target has one `sh v0,132(s0)` at 8138 reached from both paths: 8130 `li v0,30` falls through to 8138, and 8134 `addiu v0,v1,-1` falls to 8138). So a single shared store is needed.

Hmm, but we could keep the shared store AND use u after it:
```
} else {
    u = t;
    t = u - 1;
}
unk84 = t;
/* now u is dead */
```
u dies before the store.

What if we use u in the store?
```
unk84 = t;
```
→ what if `t` is redefined as `u - 1` and we keep u alive by... hmm.

Alternative: make `u` live longer by declaring it and using it in a harmless way after. E.g.:

```
} else {
    u = t;
    t = u - 1;
}
((Unkstruct_80182ED4 *)arg0)->unk84 = t;
```
u dead.

What if we swap the copy direction: `t = u` where u is the loaded value:
```
u = unk84;     /* u = the field */
if (u == 0) { ...; t = 0x1E; }
else { t = u - 1; }   /* hmm, then no copy at all */
```
Wait! That's interesting. What if the copy in the target corresponds to:
```
u = unk84;         /* the load → u in v0 */
if (u == 0) { ... }
else { t = u;  t = t - 1; }
```
Hmm, the target's `move v1,v0` copies v0 (the loaded value) into v1. So v0 = loaded value, v1 = copy.

Alternatively the target could be read as: v1 = the loaded value's copy, and the addiu reads v1.

What if in C:
```
s32 t, u;
t = unk84;         /* t in v0 */
if (t == 0) { ...; t = 0x1E; }
else { u = t; t = u - 1; }
```
Hmm same.

What if:
```
s32 t, u;
u = unk84;        /* u in v0 */
if (u == 0) { ...; t = 0x1E; }
else { t = u; t = t - 1; }   /* t = u - 1 */
unk84 = t;
```
Here `t = u` is a copy where the SOURCE u outlives t? u is used by the copy and dies there; t is redefined. Hmm, t (dest) outlives u (src) → dest canonical → t's uses rewritten to u → `addiu v0,v0,-1`? Hmm.

Hmm, wait: if dest is canonical, then t's value after the copy = u's value. `t = t - 1` → `t = u - 1`. The copy `t = u` remains as a real copy (since t is redefined right after, and the copy is the only way to have t≠u). So we'd get `or v0,v0`?? no: `move v0, v0`? The copy `t = u` where both are the same value → gcc would coalesce it away since it's a copy to the same reg? No, t and u are different pseudos; the copy `t = u` creates a new value. But `t = t - 1` immediately after → the copy is dead (t's new value doesn't use t's old value) → the copy gets deleted! Because `t = u; t = t - 1;` → the first assignment is dead. gcc would delete it (dead store / no uses). Then `t = u - 1` → `addiu v0,v0,-1` with u in v0.

Argh.

OK so the copy must be USED: `t = u - 1` uses u. And u must be a separate value from t at that point.

The only way: u's live range must extend beyond t's death so cse picks u as canonical.

In the target: u (v1) is used by the addiu; t (v0) is dead after the copy (redefined). So u outlives t. So per the G02 rule ("iVar1 outlives t -> canonical"), u should be canonical → the copy survives! But empirically it didn't.

Hmm, so maybe the rule is about *references* not lives. Let me look at the actual gcc 2.7.2 cse.c source. Maybe it's vendored in the repo (a toolchain dir). Let me search the filesystem for cse.c.

Let me check for a gcc source tree.
