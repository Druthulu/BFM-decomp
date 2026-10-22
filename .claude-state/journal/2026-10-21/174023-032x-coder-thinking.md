---
ts: 2026-10-21T23:40:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_JaTe1laILSrWJoGyNM7A
---
"gcc 2.7.2 source" — so it's GCC 2.7.2 (old!). That changes the register allocation model: GCC 2.7.2 uses local-alloc (not IRA). The pass order in gcc 2.7.x: expand → ... → cse → ... → sched (sched1) → ... → local-alloc → reload → final.

Actually in gcc 2.7: `sched` (sched1) comes before `local-alloc`? The order in gcc-2.7/flow.c: expand, jump, loop, cse, cse2, gcse, ..., sched1 (in `sched` pass), ..., local_alloc, ..., reload.

Hmm, in gcc 2.7 flow.c order (roughly): expand, jump, loop, cse, cse2, gcse, loop, cse_basic_blocks, ..., sched, ..., local_alloc, ..., reload, ...

Hmm, actually I recall `local_alloc` is fairly late: after `sched`? Let me check the GCC 2.7 pipeline in flow.c:
expand, jump, loop, cse, cse2, cse_basic_blocks, cse_class, loop, ..., sched? Actually `sched` (the pre-RA scheduler) is called in `sched` pass which comes after `cse` family and before `local_alloc`? I believe in gcc 2.x: `sched` (sched1) → `combine` → `regmove` → `local_alloc` → `reload` → `reload_cse` → `sched2`.

Yes: `sched1` is before `combine`, and `local_alloc` after `regmove`. So the pre-RA scheduler sees the pseudo c1 as a normal pseudo, and hard regs for pinned vars.

So: in the target, c1 is $3 (hard) → the scheduler can hoist `li $3,-160` freely.
In the unpinned version, c1 is a pseudo → the scheduler must consider conflicts with other pseudos → it placed the li late.

In gcc 2.7 local_alloc: the allocation order is by priority; `allocno_priority` in local-alloc.c (gcc 2.x):

```
static int
allocno_priority (n, a, rtx, reg)
{
  int reg_class_size = regclass_num_regs[reg_class];
  int size = 1;
  int weight = 0;

  /* Compute the number of hard registers used by the pseudo. */
  ...
  /* Compute the number of references. */
  ...
  weight += 2 * size;  
  ...
  /* Prefer to allocate a pseudo to a register that is not used ... */
  weight += REG_LIVE_LENGTH (reg) * 4;  ??
```

I recall in local-alloc.c (gcc 2.7):
```
  /* Compute the number of references to the pseudo.  */
  ...
  /* Add the number of refs to the weight. */
  weight += 4 * size;  /* ? */
```
Hmm honestly I recall:
```
  weight += REG_LIVE_LENGTH (reg) * 4;
  weight += REG_FREQ (reg) * 4;  /* ? */
```
Not certain. The other important part: local-alloc assigns colors in order of decreasing priority; the FIRST allocno to be considered gets the "best" reg. It also has a "hard reg" preference: allocnos whose live range is confined get cheaper regs.

Actually in gcc 2.7 local_alloc, there's the notion: allocnos are processed in priority order, and for each, `find_reg` picks a hard reg (from the class) not conflicting. The "conflict" is determined by `not_preferred_regs` and `reg_equiv` etc. Actually the crucial part in gcc 2.x local-alloc: it uses "live range" conflicts computed via `not at the same time` using the "reg_equiv" and cross-jump information. Two pseudos conflict if their live ranges overlap (computed in `allocate_no_pseudo`? no, in `find_reg` it uses `hard_reg_pressure` and the "conflict" info from `equiv`).

Honestly, empirical iteration is the way. GCC 2.7's local-alloc: allocation order is by priority which is computed as:

```
  /* Prefer to allocate a pseudo to a register that is not used ... */
  weight = 1000 * (REG_LIVE_LENGTH (reg) < ...);
```

Let me just try many variants. Since each score takes ~1s, I can try 30-60 variants per item.

Key variants to try for func_8017E4E0:
A) Reorder the s16 store block so c1's stores come first (before 0xA0's).
B) Reorder so c1's stores come last.
C) Use a do-while(0) block around the constant stores (like the G06 MATCH for func_8017CE7C used do-while to shape live ranges).
D) Make the constants go through a variable each (e.g. s16 x = 0xA0; ...) to give them more refs/higher priority.
E) Write -0xA0 as literal twice (m07 = 11, so no).
F) Use a temp for the byte value? Not possible (aliasing forces reloads, but I could write `u8 b = ((Unkstruct*)a0)->unk1C; *(u8*)(p+0x10) = b;` — then only ONE load, wrong).
G) Change the declaration order (c1 declared after p/ot/tp).
H) Make c1 volatile? No — that's a barrier (a lever) → not allowed.
I) Change the type of c1 to s16/u8 etc. (tried: 11).
J) Use `p` as a typed pointer (e.g. s16 *q) so the stores are typed.

Note the target's `sh v1,20(s0)` — the s16 stores are to p+0x14 and p+0x24 with value -160.

Another thought: in the target, the -160 is in $3 and the constants in $2. What if in my unpinned version I introduce a *second* variable so that the constants get $2 and something else gets... no.

Hmm, what about the "ot" variable: `ot` is in s2 (global alloc). And tp is in a3/v0.

Wait, actually — maybe the crucial thing is the *priority* of c1 vs the constants. If I make the constants have MORE refs (e.g. assign 0xA0 to a variable used twice, -0x78 to another variable used twice), they might outrank c1. But c1 also has 2 uses.

Alternatively make c1 have FEWER refs: but it needs 2 uses (two stores).

Hmm, what if I write c1's value into a variable of type s16 and use it twice, but write it as `-0xA0` — the RTL would be `li $N,-160` (or addiu). The number of refs: 1 set + 2 uses = 3. The constants: 0xA0 has 1 set + 2 uses = 3 refs. -0x78: 3 refs. 0x78: 1 set + 1 use = 2 refs. So c1 ties with 0xA0 and -0x78.

The tie-break in local_alloc: allocnos are sorted by priority; for equal priority, the order is by allocno number (creation order = order in the RTL after local-alloc's renumbering). In gcc 2.7 local_alloc, `allocno` order comes from `reg_equiv`/`pseudo_regs` ordering = the order the pseudos appear in the RTL (roughly the order of the first occurrence).

In the target, the constants appear in the RTL before c1's set? The target's RTL order (pre-alloc) is roughly the source order: 0xA0 set, 0xA0 use, -0x78 set, -0x78 use, c1 set, c1 use, c1 use, 0x78 set, 0x78 use. If the allocno order is by first appearance, then 0xA0's allocno < c1's allocno. And if the priority ties, 0xA0 is allocated first → gets $2, c1 gets $3?

But in my unpinned version, c1 got $2 and 0xA0 also $2 (they don't conflict). So no conflict → sharing. For c1 to get $3, they must conflict.

So: make c1 conflict with 0xA0 (or with -0x78) while keeping c1's priority ≤ theirs.

Options for conflict: overlap their live ranges in the pre-alloc RTL. E.g., set c1 BEFORE 0xA0's uses:

```
c1 = -0xA0;
*(s16*)(p+0x1C) = 0xA0;
*(s16*)(p+0x2C) = 0xA0;    <- 0xA0's range overlaps c1's
...
*(s16*)(p+0x14) = c1;
*(s16*)(p+0x24) = c1;
```
Now c1's range is longer → higher priority → c1 allocated first → c1 gets $2 and 0xA0 gets $3. Wrong direction, unless priority is dominated by something else.

Alternatively set c1 = -0xA0 between 0xA0's set and its use:
```
*(s16*)(p+0x1C) = 0xA0;   // set 0xA0
c1 = -0xA0;                 // set c1
*(s16*)(p+0x2C) = 0xA0;     // use 0xA0 (conflicts with c1)
*(s16*)(p+0x14) = c1;
*(s16*)(p+0x24) = c1;
```
c1's range: from its set to its uses (2 uses, spanning 0xA0's use and the two c1 stores) — medium length. 0xA0's range: set → use (short, 1 store apart). So 0xA0 has a SHORTER live range but 3 refs; c1 has 3 refs and a longer range.

In gcc 2.7's local_alloc, priority is (I believe):
```
  weight = (REG_LIVE_LENGTH (reg) < 3 ? 2000 : 0) ... 
```
Hmm! I now recall gcc 2.x local-alloc had a special case: "Prefer to allocate a pseudo to a register that is not used at the same time" and there's a heuristic giving very high priority to pseudos whose live range is short (confined to one block):

From gcc 2.7 local-alloc.c:
```
static int
allocno_priority (n, a, rtx, reg)
{
  int reg_class_size = regclass_num_regs[reg_class];
  int size = 1;
  int weight = 0;

  /* Compute the number of registers needed... */
  ...
  /* Prefer to allocate a pseudo to a register that is not used elsewhere */
  ...
  /* Add in the number of references, and give a large weight to
     pseudos that are not live at the function's entry.  */
  weight += REG_LIVE_LENGTH (reg) * 4;  /* ? */
```

I really don't recall exactly. Let me instead check the actual gcc source if available in the repo? The moves.md mentions "gcc 2.7.2 source" in a comment. Maybe there's a copy of gcc source in .run/P36? Let me check for local-alloc.c in the repo.

That would be very helpful: read gcc 2.7.2's local-alloc.c allocno_priority.

Let me search.
