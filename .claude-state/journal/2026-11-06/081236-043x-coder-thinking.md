---
ts: 2026-11-06T15:12:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PwpQCC2xUcje0e2UfONs
---
SO CLOSE: only `li a0,2715` is one slot later in mine (it's at 222 instead of 221). Pure ORDER of one insn: mine has li a0 after something, target before.

The instruction sequence: mine ... [221]? Let me see: mine[221] insert point: target has li a0,2715 at 221 and mine has it at 222. So mine has one extra insn before it at 221.

The target order: `ori a1,a1,0x3000; or a1,a1,a2; jal; andi` with `li a0,2715` before the ori. Mine: probably `ori; li a0; or` — i.e. li a0 after ori.

Hmm, need the exact lines. The diff only shows the insert/delete. Mine at 221 must be `ori a1,a1,0x3000`? and target at 221 = li a0,2715, at 222 = ori?

Let me dump c_i1's tail with --keep, or just get a bigger diff context. The tool prints only changed lines. Let me reason: 

target (from the earlier disasm):
```
4b90 li a0,2715
4b94 ori a1,a1,0x3000
4b98 or a1,a1,a2
4b9c jal
4ba0 andi a1,a1,0xffff
```
mine (c_i1): 221 = ? (insert point means target has li a0 at 221 and mine doesn't), 222 = li a0,2715 in mine, and mine 223 = ori? So mine:
```
221 ori a1,a1,0x3000   (aligned with target's 221 li a0? no—)
222 li a0,2715
223 or a1,a1,a2
```
So mine = ori, li, or; target = li, ori, or. sched1 ordered the ori before the li.

To flip: the ori comes from `vol = vol | 0x3000;` and the li from the call's first arg (0xA9B). Source order: `vol = vol | 0x3000;` then the call. Target has li first (the call's arg const materialised before the ori).

Hmm, sched1 orders by priority. If I move `vol = vol | 0x3000;` INTO the call expression, it's the same as before (c_u16-like). But now vol needs a 2nd set elsewhere...

Options to flip the order:
- Put `vol = vol | 0x3000;` BEFORE `sx = sx << 8;`:
```
vol = vol | 0x3000;
sx = sx << 8;
func_8002D4C8(0xA9B, (vol | sx) & 0xFFFF);
```
Then the ori is earlier in source; sched1 might still order it after li.

- Or use a temp: `vol = vol | 0x3000;` placed right after the if.

Actually the target's order li a0,2715 THEN ori. The li is the call's first argument (independent). sched1 puts it first probably because it's on the critical path to the jal (an arg). Mine puts ori first.

What if I make the ori's input later? E.g. put the `vol | 0x3000` INSIDE the call arg but keep a 2nd set of vol elsewhere (e.g. the u16 cast at the vol division — c_u16 shape) → that's the c_u16 problem again (delay slot).

Hmm, combine: `vol = (u16)vol;` at the division AND `vol = vol | 0x3000;`? That's 2 extra insns.

Alternative: make the ori come from a *separate variable*: 
```
s32 v3 = vol | 0x3000;
sx = sx << 8;
func_8002D4C8(0xA9B, (v3 | sx) & 0xFFFF);
```
Hmm, then vol has 1 set again.

We need vol to have 2 sets. The 2nd set must be the `| 0x3000`. If it's a separate var, vol has 1 set.

OK so the question: how to get `li a0,2715` before `ori a1,a1,0x3000`?

The li is the first call argument (0xA9B). It's an independent constant. sched1 orders insns by priority = distance to the end of the block (weighted by dependencies). Both feed the jal. The ori feeds `or` which feeds the andi which feeds the jal (longer chain) → higher priority → scheduled first. Target has li first, which means in target's RTL the ori is later in the block... 

In the target, the ori is part of the arg expression `vol | (0x3000|sx)`. The `(0x3000|sx)` part: fold made `ori a1,a1,0x3000` where a1 = vol. Hmm, so in target: `ori a1,a1,0x3000` (vol|0x3000) then `or a1,a1,a2`.

Interesting: in the target, the ori comes from the fold of `vol | (0x3000 | sx)` → the inner `0x3000 | sx`... no, it produced ori on vol.

Anyway, target's order = li a0, ori, or.

Mine's = ori, li, or.

Since the ori in mine is a statement (`vol = vol | 0x3000;`) whose result is used later, its priority is high.

What if I place the `vol = vol | 0x3000;` AFTER the call? Not possible.

What if the 2nd set of vol is the `& 0xFFFF` mask instead of the or? E.g.:
```
sx = sx << 8;
vol = (vol | 0x3000) & 0xFFFF;   -- no, that's 2 ops
```

Hmm, what about making the 2nd set `vol = vol | 0x3000;` but placed BEFORE the if (i.e. before `sx = (sx+0xA0)/0x14`)? Then the ori is earlier in the block; sched1 might place it before li a0. But then the arg becomes `(vol | sx) & 0xFFFF`.

Wait, but if the ori is placed earlier (before the branch), we might get the same "stolen into delay slot" problem! Hmm, the ori is a strong candidate for the delay slot too.

Let me just try placing it at various points:
1. right after the vol division (before the sx division)
2. right after the if, before the shift
3. after the shift (current, score 2 ORDER)

Try 2: after the if, before the shift.

Also try: keep it after the shift but write the call as `func_8002D4C8(0xA9B, vol | sx)` (drop the mask, since vol|0x3000|sx ≤ 0xFFFF? vol ≤ 0x7F, |0x3000 → ≤0x307F, sx ≤ 0xF00 → ≤ 0x3F7F; so the mask is a no-op value-wise, but gcc doesn't know → it would emit the andi anyway? If we drop it, we lose the andi → 236.

Let me try variant 2 and 1.
