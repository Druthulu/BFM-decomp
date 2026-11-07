---
ts: 2026-11-06T12:16:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vr79ip8VDlurhTbJahxv
---
Now I understand the target fully:

```
move t2,a0        # arg0 -> t2 (self copy)
move t3,a1        # arg1 -> t3  (a1v? or arg1 copy)
andi a1,a1,0x1    # test arg1
bnez a1, b48
move t4,a2        # arg2 -> t4 (pos)
```
So target has:
- arg0 copy to t2 (because arg0 used many times later)
- arg1 copied to t3 AND arg1 used for the first test
- arg2 copied to t4 at the delay slot

Interesting: `move t3,a1` then `andi a1,a1,0x1`. The source with launder: `a1v` in $5 (a1), launder ties to arg1's reg. Hmm, then a1v IS a1. But there's a copy t3 = a1. Where from? pos? No.

Wait: maybe the pin is $5 for a1v, and the launder forces the move. Then gcc sees a1v as a fresh value in $5 after the asm; but arg1 also in $5. The `if (!(a1v & 1))` uses a1v → andi a1,a1,1. So no move needed.

The `move t3,a1`... maybe it's `pos`? pos = arg2 though, move t4,a2.

Unless the compiler is copying arg1 into t3 for later uses (arg1 used at 0x8000 and 0x1 tests later). Because a1v occupies $5 (same reg as arg1) and is considered a distinct value, the compiler cannot keep arg1 in $5 for later uses — it must save arg1 elsewhere! That's exactly the launder trick: the launder makes a1v "own" $5, so arg1's later uses (at `arg1 & 0x8000`, `arg1 & 1`) need a copy in another register — t3.

And the first test uses a1v (in a1). Yes: `andi a1,a1,0x1` is a1v & 1. Then later `andi v0,t3,0x8000` and `andi v0,t3,0x1` use the t3 copy of arg1.

So target semantics: a1v is a copy of arg1 living in $5; arg1's later uses read from t3. That's an anti-coalescing launder: the asm operand forces a1v to $5, and arg1 (still live) gets a separate reg.

To do this lever-free with real C... We need a "real 2nd set": e.g. compute something so that the value in $5 is a distinct value from arg1.

Hmm, look at the moves catalog: "launder->pv=*p; pv&=mask split (real 2nd set)" — i.e., replace launder with a real second computation of the value. Here we need a1v = f(arg1) where f is identity-ish but real.

Options: `s32 a1v = arg1 & 0xFFFF;`? No, that changes value (arg1 may have high bits). Actually arg1 is used as `arg1 & 0x8000`, `arg1 & 1`, and a1v & 1. Only low 16 bits matter in all uses! a1v is used only in `a1v & 1`. So a1v could be `s32 a1v = (s16)arg1;` or `a1v = arg1 & 0xFFFF`? But that would emit extra insns (andi/sll+sra). The target has no extra insns — just `move t3,a1` (the copy of arg1 for later).

Alternatively make arg1's later uses go through a distinct C variable: 
```
s32 a1v = arg1;
...
if (!(a1v & 1)) ...
...
if (a1v & 0x8000) ...
if (a1v & 1) ...
```
That's just arg1 coalesced.

Hmm. But the register allocation problem: we want `a1v` (used for the first test) in $5 = a1, and the later uses in t3. With plain C, `a1v = arg1` coalesces, so all uses read a1 directly. To split, we need two variables with a real computation between them, or use arg1 after the value has been "clobbered".

What if we write `s32 a1v = arg1;` and then modify arg1? Can't modify a param without changing semantics? Actually we can: the later uses are `arg1 & 0x8000` and `arg1 & 1`. If we assign `arg1 = arg1;`... no.

What about: `s32 a1v = arg1 & 1;`? Then `if (!a1v)`. And later `if (arg1 & 0x8000)`, `if (arg1 & 1)`. Then a1v is computed by andi. Target: `andi a1,a1,0x1` writes to a1 — that's exactly a1v = arg1 & 1 in $5! And then `move t3,a1` must happen BEFORE the andi (it's at insn 2, before andi at insn 3). So the order: move t3,a1; andi a1,a1,1. That is: the compiler copies arg1 to t3 (for later uses) then computes a1v = arg1&1 into a1 (reusing a1's register since arg1's value is dead in a1 after the copy... but arg1 is still used later, from t3).

So if we write:
```
s32 a1v = arg1 & 1;
...
if (!a1v) ...
... 
if (arg1 & 0x8000) ...
if (arg1 & 1) ...
```
gcc would need arg1 live across, so it keeps arg1 in a1 and computes a1v in another reg (v0), and the andi would be `andi v0,a1,1`. Target instead does `andi a1,a1,1` — a1v in a1. Hmm, gcc local-alloc might reuse a1 if it thinks arg1 is dead... but arg1 is used later, so not dead.

Unless the compiler decides to copy arg1 to t3 and free a1. Which is a global-alloc choice: arg1's later uses are far away (after many insns), and a1 is caller-saved; holding it in t3 (also caller-saved, but less used?) Hmm.

Alternatively, restructure: make the later tests use a different variable `a1w = arg1` (a copy). Then gcc must copy arg1 to a1w anyway; where does the copy land? It could coalesce the copy with arg1 (a1w in a1) if arg1 dies. But arg1 also used for a1v's computation.

Let me think about what real-C shape produces: `move t3,a1; andi a1,a1,1`.

Consider:
```
s32 a1v = arg1;
s32 m = arg1 & 1;
if (!m) ...
```
No.

What about using the copy in a way that forces a1v to be the one in $5: e.g., call a function with arg1? No.

Alternative: swap roles — the first test is the "a1v" one, later tests use "arg1". If we write:

```
s32 a1v = arg1;
...
if (!(a1v & 1)) ...
...
if (a1v & 0x8000) ...
```
all same var → coalesced, no copy.

Hmm, but wait: maybe the simplest real-C is to not have a1v at all and accept arg1 in a1, but then the later uses read a1 directly: that's my a1.c which has `move t4,a1`?? Wait mine had `move t4,a1` at insn1 and `andi v0,t4,0x1`. Hmm, mine copies arg1 into t4 and tests t4. Because arg1 is used many times, gcc copied it into a temp? Interesting: mine: move t4,a1; andi v0,t4,1. So gcc DID make a copy of arg1 into t4, and uses t4 everywhere (probably). And it copied arg2 into t3.

So mine: arg1→t4, arg2→t3. Target: arg1→t3, arg2→t4 (swap!), and target's first test uses a1 directly while later uses t3.

Interesting: in mine, the `andi v0,t4,0x1` is `temp = t4 & 1` then bnez v0. In target, `andi a1,a1,1; bnez a1`. So target uses the copy-in-place (a1v = arg1&1 in a1) whereas mine has a separate andi into v0 from t4.

So the difference at top: target computes a1v = arg1&1 in $5 and copies arg1 to t3. Mine copies arg1 to t4 (and uses t4 for all arg1 uses).

Now what determines t3 vs t4? Global alloc priority/order. In target, arg2's copy got t4 and arg1's copy t3. In mine, arg1's copy got t4, arg2's copy t3. It's the order of allocation. Both copies are born around the same place.

Idea: if I can make the first test be `arg1 & 1` computed in a1 (i.e., have a real a1v that occupies a1), then arg1's copy would be a separate reg and likely t3, and arg2's pos would take t4. The allocator assigns regs in order of priority: the first temp to be allocated gets... local-alloc assigns t3? Actually temps get t3..t9, etc.

Target: t3 = arg1 copy, t4 = arg2 copy. Mine: t4 = arg1 copy, t3 = arg2 copy. So the allocation ORDER differs: target allocates arg1-copy first (gets t3), mine allocates arg2-copy first (gets t3)? Or the birth times.

Hmm wait — in mine, where does `move t4,a1` come from? gcc created a copy of arg1 because arg1 is used 3 times and maybe the first `&1` test then later... Actually why copy at all? Because the andi needs to not destroy a1? `andi v0,t4,0x1` — it computes from t4 into v0. It could have done `andi v0,a1,1` directly. The copy t4=arg1 exists because arg1 (a1) is used multiple times and... hmm.

Actually maybe the copy is `pos`? No, pos=arg2 is `move t3,a2` in mine.

Let me get my candidate's listing to compare properly. Dump cand.o.
