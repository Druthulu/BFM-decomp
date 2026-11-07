---
ts: 2026-11-06T11:50:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pitTOisGjmrlLkptBNtH
---
The cse dump shows:
- insn 30: store QI to mem (arg0+6) of (subreg:QI reg 75).
- insn 33: `(set (reg:QI 83) (subreg:QI (reg/v:SI 75) 0))` — this is cse forwarding! It replaced the load `lbu` with a subreg of reg 75.
- insn 34: `(set (reg/v:SI 75) (zero_extend:SI (reg:QI 83)))` → andi 0xff.

So cse replaced the memory load with `(subreg:QI (reg:SI 75) 0)` because it knew mem[(arg0+6)] == subreg of reg75 from the store.

Wait, insn 33 was created by cse (a new insn). Then insn 34 zero-extends.

Hmm, so cse forwarded. In the target (with barrier), insn 33 wouldn't exist.

To prevent cse from forwarding, I need the store value's mode/expression to not be a simple subreg, or make cse lose track.

Idea: make the stored value come from a memory location or an expression that cse can't represent as a reg subreg. But the target stores v0 (a reg).

Idea: what if the store is `*(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;` but cse sees the *store* as a full-mode store? No.

Hmm, what if I make the store happen through a different base register? E.g., compute `u8 *p = (u8*)arg0;` and store `p[6]`, load `((u8*)arg0)[6]` — cse equates the addresses anyway (same value).

What if the load is through a pointer loaded from memory? e.g. `temp_v0 = *(u8*)((u8*)arg0 + 6)` where the base is a pointer variable that cse can't prove unchanged? The store also uses arg0.

Real idea: use `memcpy`-like access or a union? No.

Alternative: maybe the original C read the byte through a **different typed pointer** that cse treats as a different alias set. E.g., store via `*(u8*)` (QI) and load via `*(s8*)`? Same mode QI, cse forwards.

What about load via a `char` array vs `u8` pointer? Same.

Hmm, let me think about cse's store-forwarding condition in gcc 2.7.2. In `cse_insn`, for a store `(set (mem) (subreg:QI (reg) 0))`, it calls `record_jump_equiv`/`invalidate_memory`. For a load, `cse_insn` checks the hash table for an equivalent expression. The store sets the table entry for `(mem:QI addr)` to the value `(subreg:QI (reg) 0)`. Then the load `(zero_extend:SI (mem:QI addr))` — cse looks up the inner `(mem:QI addr)` and finds the value `(subreg:QI (reg) 0)`. Since the value is not a REG but a SUBREG, cse might still substitute it.

In the target (barrier), the barrier's memory clobber invalidates the table entry, so no forwarding.

So how did the ORIGINAL avoid this? Maybe the original's store value was NOT a subreg of a reg — e.g., the original stored `temp_v0` which was a **u8-typed variable**? If temp_v0 were QI, the store value would be a plain `(reg:QI)` and the load would forward to it directly (lbu→move). Not matching either.

Wait, maybe the original store was `*(u8 *)(arg0 + 6) = temp_v0 & 0xFF;` where combine produced `andi` + `sb`? No, target has no andi before sb.

Hmm, let me reconsider: maybe the original's reload is NOT cse-able because the store address and load address use different register forms. E.g., the store uses `(plus (reg arg0) (const 6))` and the load uses `(plus (reg arg0) (const 6))` — same.

Unless the original computed the address differently: `arg0 + 6` vs `arg0[6]` — same RTL.

OK, what if the original code had the reload BEFORE the store in source but the store got moved after by sched1? No, sched1 doesn't move stores across loads of the same address (dependency). Hmm, actually the dependency store→load is a true dependency (load after store). sched1 wouldn't move the store after the load.

Wait! What if the original had the reload BEFORE the store, and the store AFTER? That would give `lbu` then `sb`. But target has `sb` then `lbu`. Unless the store's value comes from... hmm.

Actually, wait. Look at the target:
```
11 sb v0,6(s0)
12 lbu v0,6(s0)
```
If the source had:
```
temp_v0 = byte[6] - temp_a0;   // lbu a0? 
temp_v1 = ...
byte[6] = temp_v0;             // sb
temp_v0 = byte[6];             // lbu
```
that's w1.

Alternatively, the source could be:
```
temp_v0 = byte[6] - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
temp_v0 = byte[6];             // lbu (before the store!)
byte[6] = (u8)temp_v0;         // sb -- but this stores the NEW temp_v0, wrong
```
No.

Hmm, what if the reload and the store use different variables such that cse's forwarding is invalidated by the intervening `temp_v1` computation? No, temp_v1 doesn't touch memory.

Let me look at the target again: `andi v1,v0,0xff; negu v1,v1; sb v0,6(s0); lbu v0,6(s0)`. The andi/negu use v0 before the sb. Fine.

What if the original code was:
```
temp_a0 = byte[5];
temp_v0 = byte[6] - temp_a0;
byte[6] = (u8)temp_v0;     // sb
temp_v0 = byte[6];         // lbu
temp_v1 = -(temp_v0 & 0xFF);  // but target has andi before sb
```
No: target computes temp_v1 (andi/negu) BEFORE the sb. So source order: temp_v1 = -(temp_v0 & 0xFF); then store; then reload.

So it's exactly w1's order.

OK so the original must have had some construct that blocks cse. What real C blocks cse store-forwarding without volatile/asm? 

Possibility: the original used a **different address expression** that cse can't equate. For example:
```
*(u8 *)(arg0 + 6) = (u8)temp_v0;
temp_v0 = *(u8 *)(arg0 + 6);
```
where `arg0` is `void *`. The pointer arithmetic on void* is a GNU extension (byte arithmetic). Same.

What if the original stored via `((u8 *)arg0)[6]` and loaded via `*(u8 *)((u8 *)arg0 + 6)`? Same RTL.

Hmm, what if the store was to `*(u8 *)((u8 *)arg0 + 6)` and the load from `*(u8 *)((u8 *)arg0 + 6)` but with a **different pointer variable** for the load that was assigned earlier:
```
u8 *p = (u8 *)arg0;
...
p[6] = (u8)temp_v0;
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
cse sees both as (reg p) and (reg arg0) — but it knows p == arg0? If p is just a copy, cse may equate them. If p is `(u8*)arg0 + 6` stored in a variable, then the store address is `(reg p)` and the load address is `(plus (reg arg0) 6)`. cse might not equate those! That could block forwarding while still producing the same code (a pointer in a register).

But the target doesn't show a separate pointer register: `sb v0,6(s0)` uses s0=arg0 directly with offset 6. If p were a separate variable, the store would be `sb v0,0(p)` where p = s0+6, requiring an addiu. Target has no addiu. So no.

Hmm, unless the compiler folds p back to (arg0+6). cse might then equate.

Let me try: `u8 *p = (u8 *)arg0;` and store `p[6]`, load `p[6]`. Same base, cse forwards.

What if the store uses a different *mode*: store as `*(u8*)` and load as part of an `s16` read? No.

Let me try something else: what if the store is done through a **volatile-free struct field** and the load through a plain pointer? cse tracks by address only.

Alternatively: what if the original used `temp_v0 = *(u8 *)((u8 *)arg0 + 6);` where temp_v0 is declared `s32` but the store is `*(u8 *)((u8 *)arg0 + 6) = temp_v0;` — the cast absent. I tried w4 (no cast) → still 1.

Let me check what w4's cse did — probably the same.

New idea: the target's `lbu` might be preserved because cse is run BEFORE the store is recognized as killing... no.

Let me look at the cse dump for the ORIGINAL (pinned+barrier) to see the barrier's effect and whether the pins matter. The pins shouldn't affect cse. The barrier does.

Since the barrier is the only thing blocking cse, and we can't use asm, we need a real-C memory clobber equivalent. In C, a function call clobbers memory. But there's no call there.

Hmm, what about a **store through a pointer that cse thinks may alias**? cse invalidates memory on any store to a potentially-aliasing address. The store at +5 happens AFTER the reload in target. If I move the +5 store BEFORE the reload, cse would still forward the +6 store (different address).

What if the +6 store is followed by another store to +6 with a different value? No.

Wait — here's a thought: cse's memory table is invalidated by any store to an address that may alias. If the store at +6 is followed by the store at +5, cse wouldn't invalidate the +6 entry (different offset). 

What if I reorder so the +5 store comes between the +6 store and the reload? Target has: sb +6, lbu +6, addiu a0, sb +5. So the +5 store is after. Can't reorder.

Hmm, but the ORDER of the final stores (sh) is flexible. What if I do the +5 store BEFORE the +6 store? Then: sb +5, sb +6, lbu +6 → still forwards.

What if I put a store to the SAME address +6 with a value that cse can't equate... no.

OK, maybe the answer is that this item is a WALL (`cse-store-forward`), and the barrier is genuinely needed. But score is 1 — one instruction. Let me try more real-C tricks:

Trick: make the reload address be `arg0 + 6` where `arg0` has been reassigned? No.

Trick: use a union/bitfield? 

Trick: the store value is `(u8)temp_v0`; if I instead store `temp_v0` into a `u8` variable and then use that variable's address... 

Trick: `*(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;` then `temp_v0 = *(u8 *)((u8 *)arg0 + 6);` — cse forwards. What if the reload is `temp_v0 = *(u8 *)((u8 *)arg0 + 6) | 0;`? combine might drop.

Trick: use an array: `((u8*)arg0)[6] = ...; temp_v0 = ((u8*)arg0)[6];` same.

Trick: store via a pointer-to-array type with a different alias set? In gcc, alias sets depend on the type. A store through `u8*` and a load through `s8*` are the same alias set (char types alias everything). What about store through `u8*` and load through `unsigned short*`? Different mode/alias → cse wouldn't forward? But the load would be `lhu` not `lbu`.

Hmm, what about store through `u8*` and load through `int*`? `lw` not `lbu`.

Trick: use a **volatile-free** memory barrier via a function call that's inlined? No.

Trick: `asm` is out. `volatile` is out (lever).

Hmm, wait. Is `volatile` really out? The kinds are barrier,pin. A `volatile` read would be a barrier-like lever. The brief: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind." So volatile is a new lever. Out.

Let me reconsider: maybe the original C didn't have the store and reload at the same address in a way cse can see, because the original used a **function** like `temp_v0 = *(u8*)(arg0+6);` where arg0 is passed through... no.

Let me look at the actual game function: func_80175590. It's a small state-update function. Maybe the original C is:
```
u8 a = p[5];
u8 b = p[6];
p[6] = b - a;
...
```
Hmm.

Actually, let me reconsider the target sequence:
```
lbu a0,5(s0)      ; a0 = p[5]
lbu v0,6(s0)      ; v0 = p[6]
nop
subu v0,v0,a0     ; v0 = p[6] - p[5]
andi v1,v0,0xff   ; v1 = v0 & 0xFF
negu v1,v1        ; v1 = -(v0 & 0xFF)
sb v0,6(s0)       ; p[6] = v0
lbu v0,6(s0)      ; v0 = p[6]
addiu a0,a0,255   ; a0 = p[5] - 1
sb a0,5(s0)       ; p[5] = a0
...
```
The reload p[6] after storing v0. Since v0's low byte is what was stored, the reload = v0 & 0xFF. The compiler could forward but the original didn't.

Why wouldn't the original compiler forward? Maybe because the original source stored `p[6] = (u8)(v0)` where the cast produced a **SUBREG**, and cse 2.7.2 only forwards when the stored value is a REG in the same mode... but our w1 shows it forwards.

Hold on — maybe in w1, the forwarding happened in **combine** or **cse2**, not cse1. The dump I looked at was `.cse` (cse1). It showed insn 33 = subreg. So cse1 did it.

What differs between orig and w1 at cse time? Only the barrier. The pins don't affect cse.

Unless... the original source had a *different* expression that cse couldn't forward. 

Let me look at the cse dump of orig (with barrier) to see the insn numbers, then think about what source produces the same cse output minus the barrier. Actually the barrier is an asm, which cse treats as a memory clobber → invalidates.

What if the original had TWO separate statements that read p[6] and the store was to a *copy*? 

New idea: what if the original used `p[6] = p[6] - a;` — a compound assignment! `*(u8*)(arg0+6) -= temp_a0;` This reads p[6], computes, and stores. Then a separate read `temp_v0 = *(u8*)(arg0+6);`.

RTL for `p[6] -= a`: `(set (mem:QI addr) (plus:QI (mem:QI addr) (subreg:QI a)))`. Hmm, then the store value is a PLUS, not a subreg. Then cse can't forward the store into the reload! And the target's `sb v0,6(s0)` stores v0 — but with a compound assignment, combine might produce the same.

Wait, target:
```
subu v0,v0,a0    ; v0 = p[6] - a0
andi v1,v0,0xff
negu v1,v1
sb v0,6(s0)      ; store v0's low byte
```
This is exactly `p[6] = p[6] - a0` where the subtraction result is in v0. If the source is `temp_v0 = p[6] - a0; ... p[6] = temp_v0;`, combine could produce the same.

But if the source is a compound assignment `p[6] -= a0;`, the value temp_v0 isn't available for temp_v1 = -(temp_v0 & 0xFF). The target uses v0 (the subtraction result) for the andi/negu. So temp_v0 must be a variable.

Hmm, but maybe the source is:
```
temp_v0 = p[6] - a0;
temp_v1 = -(temp_v0 & 0xFF);
p[6] -= a0;    // or p[6] = p[6] - a0 (recompute)
```
No, that recomputes.

Let me think about the RTL: in w1, the store value is `(subreg:QI (reg/v:SI 75) 0)` where reg 75 = temp_v0. cse forwards. If instead the source stored `(u8)(temp_v0 & 0xFF)`, the store value would be `(subreg:QI (and:SI (reg) (const)))` — but combine would simplify to the same reg (since sb only uses the low byte). Actually combine might turn `(subreg:QI (and:SI x 255))` into `(subreg:QI x)`. So same.

What if the store value is a different reg than the reload's expected? cse forwards any reg.

Hmm, what if I make the store value come from a **different pseudo** than the load's result would be, such that cse creates the equivalence but the scheduler... no, cse still removes the load.

OK here's another thought: what if the reload is at a **different address that cse can't prove equal** but the assembler still shows 6(s0)? E.g., if the base pointer is re-loaded or computed via a different expression. For instance:
```
u8 *base = (u8 *)arg0;
...
*(u8 *)(base + 6) = (u8)temp_v0;
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
If `base` and `arg0` are both in registers but cse knows base == arg0 (copy propagation), it equates.

What if `base` is obtained from memory? e.g. `u8 *base = *(u8**)&someglobal;` — changes code.

What if the reload uses `arg0` cast differently, e.g. `((u8 *)arg0)[6]` vs `*((u8 *)arg0 + 6)` — identical.

Let me try the **different alias type** idea: store through `u8*`, load through `s8*` and cast: `temp_v0 = (u8)*(s8 *)((u8 *)arg0 + 6);` → would give `lb` (sign-extend) then `andi`, not lbu. Target is lbu. No.

What if store through `s8*` and load through `u8*`? The store is the same sb. The load is lbu. Alias sets: both are QImode with the same alias set (char). cse likely still forwards.

Let me just test a batch of alias/type variants and see.

Actually, let me step back and look at what the previous worker did — maybe there's a note in the header: "NEEDED DIFFERS (P36 rung B headers1)". So this was a known-difficult header.

Let me try the compound-assignment idea in a way that keeps temp_v0:
```
temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)((u8 *)arg0 + 6) = temp_v0;
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
vs
```
temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)((u8 *)arg0 + 6) = temp_v0;
temp_v0 = *(u8 *)((u8 *)arg0 + 6) & 0xFF;   // no change
```

Hmm.

What about making the store use a QImode temporary and the reload a QImode temp, but with the store value being a **constant-folded** expression? no.

Let me look at the cse code for store forwarding to find the condition. tools/reference/gcc-2.7.2/cse.c. Search for how stores invalidate. Actually, cse's table entry for memory is set by `cse_insn` when it sees a store: it records the store as `(mem) = value` in the table (via `insert`). Then a later load of the same mem finds it.

The forwarding of a SUBREG value: cse's `cse_insn` for the load `(zero_extend:SI (mem:QI addr))` — the inner mem is looked up, found as `(subreg:QI (reg:SI 75) 0)`. Then cse substitutes. So it happens.

Is there a way cse would NOT insert the store into the table? In cse_insn, for a `set (mem) (value)`, it calls `insert` only if the value is not a MEM and not... Let me check the source.

Let me grep cse.c for the store handling.
