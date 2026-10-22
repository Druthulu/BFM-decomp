---
ts: 2026-10-22T00:46:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_HKw6YCW9P7tCkcByQDO6
---
Interesting. The residual is a register-shift (a3 vs a2) in the vol computation, and the ORDER of the magic-multiply chain differs.

Target sequence (from the diff):
```
sra a2,v0,0x10
bgez a2,...
move a1,a2
negu a1,a2
lui a0,0x6666
ori a0,a0,0x6667
(nop at 63? target has nothing at 63-65?)
mult v1,a0
mfhi t1
addiu v0,a2,160
nop
mult v0,a0
sra a0,t1,0x6
subu a1,a0,v1
sra v0,v0,0x1f
mfhi a2
sra v1,a2,0x3
subu a2,v1,v0
```
Mine:
```
sra a3,v0,0x10
bgez a3
move a1,a3
negu a1,a3
lui a2,0x6666
ori a2,a2,0x6667
addiu a0,a3,160
mult a0,a2
mfhi a3
mult v1,a2
sra a0,a0,0x1f
sra v0,a3,0x3
subu a3,v0,a0
mfhi t1
sra v0,t1,0x6
subu a1,v0,v1
```

So the target computes: magic mult FIRST (mult v1,a0 with a0=0x66666667), then the division sequence; and importantly the target's structure is the *signed division by 0xA0* pattern: vol = ((0xA0 - ax) * 0x7F) / 0xA0.

Hmm, in the target, the `addiu v0,a2,160` (0xA0 - ax) comes AFTER `mult v1,a0` and `mfhi t1`. So the target computes the magic multiply of v1 (which is 0x7F?) first, then the numerator, then the division.

Wait, in the target: `mult v1,a0` — v1 = 0x7F presumably, a0 = 0x66666667 (magic). Then `mfhi t1` → t1 = high part. Then `addiu v0,a2,160` = 0xA0 - ax. Then `nop` (delay slot), then `mult v0,a0` (numerator * magic), `sra a0,t1,0x6`, `subu a1,a0,v1`, `sra v0,v0,0x1f`, `mfhi a2`, `sra v1,a2,0x3`, `subu a2,v1,v0`.

So the target's order: the magic mult of the CONSTANT 0x7F happens early (that's the "birth boost" of a single-set const), then the numerator, then the divide.

Mine: `lui a2,0x6666; ori a2,a2,0x6667; addiu a0,a3,160; mult a0,a2; mfhi a3; mult v1,a2; ...` — the magic mult of the numerator comes first, then the mult of 0x7F.

So in the target, the constant 0x7F's magic-mult is scheduled BEFORE the numerator's multiply. That's the classic "birth boost": a single-set const gets boosted.

The launder `__asm__("" : "=r"(vol) : "0"(vol));` after vol's computation creates a 2nd set of vol → kills the birth boost of... hmm, the launder is AFTER the vol computation, so it kills the boost of the *use* of vol.

Hmm. Actually in the target, the order of the two `mult`s is: `mult v1,a0` (0x7F*magic) first, then `mult v0,a0` (numerator*magic). In mine, the numerator's mult comes first. The vol computation's whole chain in mine is contiguous.

Wait, actually where does the launder come in? Let's think about what the launder does in the target: it forces `vol` (the result of the division) to be a separate pseudo from the division's chain. Without the launder, gcc might merge the division result directly into the `or` expression.

But the observed residual is about the *internal* order of the division chain. Hmm, mine has 110 ins vs target 111 — mine is 1 shorter (the launder cost 0 bytes but maybe the target has a nop).

The key difference: in the target, `mult v1,a0` (the 0x7F multiply) is scheduled before `addiu v0,a2,160` (the numerator). This is the birth-boost of the constant multiply: the constant 0x7F is a single-set value, so gcc boosts it (it has no dependencies → scheduled early).

In mine, the order is different because... hmm, in mine `mult v1,a2` comes after `mfhi a3`. So mine schedules the numerator mult first.

What makes the target hoist the 0x7F mult? The magic number 0x66666667 is used by both mults (same a0). In the target, `lui a0,0x6666; ori a0,a0,0x6667` then `mult v1,a0` — the first use of the magic. In mine: `lui a2,0x6666; ori a2,a2,0x6667; addiu a0,a3,160; mult a0,a2`.

Hmm, the difference might be about the *dependency* structure: in the target, `mult v1,a0` uses v1 = 0x7F (constant) so it's ready immediately → scheduled first. In mine, the numerator's mult is also ready... but mine computed `addiu a0,a3,160` first (the numerator) since it feeds the mult.

Hmm, actually both are "ready". sched1 picks by priority: the birth-boost. In mine, the numerator mult was born first? Hmm.

Actually the deeper difference: in the target, the division is computed as `(x * 0x7F) / 0xA0` where gcc's expansion for signed division by 0xA0 uses the magic number. The target's sequence computes `mult v1, magic` where v1 = 0x7F, then `mfhi t1` (t1 = magic>>6 part?), then `addiu v0,a2,160` (numerator), `mult v0, magic`, `sra a0,t1,6`, `subu a1,a0,v1` (a1 = t1*... - 0x7F), etc.

So the target computes `((0xA0 - ax) * 0x7F) / 0xA0` with a shared magic: the multiply of 0x7F by magic is used for the "magic shift" correction? Actually for division by 0xA0 (160): the standard GCC magic division: M = 0x66666667, shift 6, and the "add" variant: q = (mulhi(n, M) >> 6) - n ... The 0x7F multiply: hmm, `mult v1,a0` where v1=0x7F gives 0x7F*0x66666667 = high part used as an offset?

Actually for signed division by 160: GCC uses the "magic number" method with an add: q = ((mulhi(n, M) + add) >> s) where add = (n < 0 ? ... ). Hmm, but here we see `subu a1,a0,v1` where v1 = 0x7F.

Wait: (0xA0 - ax) * 0x7F / 0xA0. Hmm, GCC might transform this. Note 0x7F = 127 and 0xA0 = 160.

Whatever. The point: mine and target differ in the *scheduling* of the division chain, plus a register swap (a3 vs a2).

The launder's role: `__asm__("" : "=r"(vol) : "0"(vol));` — a non-volatile asm with output tied to input. This creates a new pseudo for vol (the asm output) — a "2nd set". In cse/expand, this splits vol into two: vol (the division result) and the asm output pseudo. The asm has priority 1 (per cookbook §373) and its consumer... hmm.

Since the asm is a scheduling barrier-ish point? No, non-volatile asm is not a barrier but it has a low priority.

The lever here: we need the target's instruction order. The launder is what creates it. To reproduce it in plain C we need a "real 2nd set" of vol — e.g. `vol = vol | 0`? or per the G11 pattern: a compound assignment that creates a 2nd set.

Hmm, but the residual is not about vol's set; it's about the ORDER of the division chain's internals. Interesting: the target's chain has the 0x7F mult first (a "birth boost" of a single-set constant mult).

What in the source determines that order? The source order: `vol = ((0xA0 - ax) * 0x7F) / 0xA0;` — the numerator (0xA0-ax)*0x7F is computed first, then divided by 0xA0. GCC expands the division: it needs mulhi(numerator * M). The magic M is shared.

Target order:
1. mult v1, M       (v1 = 0x7F, so this is 0x7F * M — used for the "add" correction? no...)
2. mfhi t1
3. addiu v0, a2, 160   (numerator = 0xA0 - ax)
4. mult v0, M
5. sra a0, t1, 6
6. subu a1, a0, v1
...

Hmm, steps 1-2 and 5-6: a1 = (t1>>6) - v1 where v1 = 0x7F*M>>32? That looks like the "add" variant of magic division: for n/160 with negative n handled by adding (M*n)...

Hmm, actually this looks like the *unsigned* division idiom? Let's think: gcc's magic for 160: M=0x66666667, shift 6, and "add" indicator. The sequence `mulhi(n, M) >> 6` then subtract...

Actually, the sequence with `subu a1,a0,v1` where v1 = 0x7F*M (high) suggests: the division is of (n) by 160 where n = 0xA0 - ax, and there's a correction `(hi(M*0x7F)>>6) - 0x7F`? That doesn't look right either.

Hmm — maybe gcc transformed `(0xA0 - ax) * 0x7F / 0xA0` into something else entirely, e.g. `0x7F - ax*0x7F/0xA0`. Indeed! (160-ax)*127/160 = 127 - ax*127/160 = 127 - (ax*127)/160. So gcc might do: t = ax*127; q = t/160; result = 127 - q. That matches: `mult v1,M` with v1 = 0x7F?? no, v1 would be ax.

Hmm: `addiu v0,a2,160` = 160 - ax → so the numerator form (160-ax) is used, and the *other* multiply is by 0x7F... wait `mult v1,a0` with v1 = 0x7F: where does 0x7F come from? It must be from the *other* multiplication in the expression: (0xA0-ax)*0x7F. So the numerator n = (0xA0 - ax) * 0x7F? But then `mult v0,a0` would be n*M, requiring n = (160-ax)*0x7F computed first — but we only see `addiu v0,a2,160` then `mult v0,a0`. So n = (160-ax), and the *0x7F* multiply is separate: `mult v1,a0` = 0x7F*M.

So gcc rewrote: ((160-ax)*127)/160. Since ax ∈ [0, 0x9F?], maybe gcc knows something. Hmm, (160-ax)*127/160 — maybe gcc distributes: = 127 - (ax*127)/160, so it computes ax*127 (needs mult) then divides by 160... but we see 0xA0-ax.

Alternatively, gcc's expansion for `(a*b)/c` with constant b: it computes the magic division of (a*b) where a*b = 127*(160-ax). Then n = 127*(160-ax) requires a mult by 127: `mult v1,a0`?? no, that multiplies by M.

Hmm, wait. Maybe I mis-assume which register holds what. `mult v1,a0` — a0 = 0x66666667 (M). v1 = ? If v1 = 0x7F then result = 0x7F*M. Hmm, but maybe v1 = ax (from the earlier `move a1,a3`/`negu a1,a3` → the absolute value of ax is in a3/a2?). Look: mine[56] `sra a3,v0,0x10` — v0 holds L.sxy[0] (x), sign-extended to 16 bits → ax = x. So ax is in a3 (mine) / a2 (target). Then `move a1,a3; negu a1,a3` computes abs. So ax (absolute) is in a3/a2.

Then in the target: `addiu v0,a2,160` → v0 = 160 - ax (numerator!). So the expression is (160-ax)*127/160 where gcc computes 127 - (ax*127)/160? Then the mult by 127 would be `mult v1, 127`... but we see `mult v1,a0` where a0 = M = 0x66666667.

Unless... gcc's magic-division expansion for dividing by 160 with the numerator (160-ax)*127:
q = mulhi(n, M) >> 6; with correction.
where n = (160-ax)*127. But then n must be computed as a mult by 127 first. We don't see that... unless `mult v1,a0` IS the mult by 127? No, a0 = M.

Hmm, alternatively gcc turned it into: (160-ax)*127/160 = 127 - ax*127/160 → q = (ax*127)/160 computed via magic: needs ax*127 (a mult) then mulhi by M.

The instruction `mult v1,a0` = v1 * M. If v1 = ax*127 then... where's ax*127? Maybe `negu a1,a3` was the abs, and then `mult v1,a0` — hmm, v1 ≠ a3.

OK, I mis-assume: maybe a0 (M) and v1: v1 could be 127 (a constant loaded earlier, e.g. `li v1,127`). Then `mult v1,a0` = 127*M = high → used for the "add" correction: q = (mulhi(n,M) + (mulhi(127*M)>>6)) ... hmm, no.

Let me look at the actual gcc magic-division-by-constant expansion for 160:
M = 0x66666667 (or 0x66666667 with the "add" bit), shift = 6.
For signed division by 160 with the "add" indicator, gcc computes:
  q = mulhi(n, M) >> 6;  q += (n < 0) ? 1 : 0 → the add variant computes t = mulhi(n, M); q = (t + (n>>31)) >> s...

The sequence in the target:
```
mult v1, a0     ; a0 = M
mfhi t1
addiu v0, a2, 160
nop
mult v0, a0     ; v0 = n = 160-ax
sra a0, t1, 6
subu a1, a0, v1
sra v0, v0, 0x1f
mfhi a2
sra v1, a2, 3
subu a2, v1, v0
```
Hmm: `sra a0,t1,6` where t1 = hi(v1*M). `subu a1,a0,v1` → a1 = (hi(v1*M)>>6) - v1.

If v1 = 0x7F: hi(0x7F*M) = hi(127 * 0x66666667) = 127*1717986919 / 2^32 = 218186138713/4294967296 = 50.79 → 50 (0x32). 50>>6 = 0. So a1 = 0 - 127 = -127. Then `mfhi a2` = hi(n*M) (n = 160-ax), `sra v1,a2,3`... wait v1 was 127 already. Hmm, v1 gets overwritten: `sra v1,a2,3` → v1 = hi(n*M)>>3.

Hmm, that doesn't fit a division by 160 (shift should be 6).

Let me redo: maybe M is for division by 0x14 (20)? no, `lui 0x6666, ori 0x6667` = 0x66666667 → that's the magic for /160? Let's compute: 2^35/160 = 214748364.8 → magic for /160 with shift 6: M = ceil(2^(32+6)/160) = ceil(274877906944/160) = 1717986918.4 → 1717986919 = 0x66666667. Yes! M = 0x66666667 for /160, shift 6.

So the division by 160 has shift 6: q = mulhi(n, M) >> 6 with correction.

In the target: `mfhi a2` = mulhi(n, M) where n = 160-ax (in v0), `sra v1,a2,3`?? that's >>3, not >>6. Hmm, then `subu a2,v1,v0` where v0 = n>>31 (sign). Hmm, that gives q = (mulhi>>3) - (n>>31).

Hmm, maybe there are TWO divisions: /0xA0 and /0x14 (20). Note the source also has `x = (x + 0xA0) / 0x14;` — division by 20! Magic for /20: 2^(32+5)/20 = 1717986918.4 → 0x66666667 with shift 5! So the same magic 0x66666667 is used for both /160 (shift 6) and /20 (shift 5)? For /20: M = ceil(2^37/20) = 1717986918.4 → 1717986919 = 0x66666667, shift 5. Yes! Both divisions share the magic constant 0x66666667.

So the target's chain:
- `mult v1,a0` (v1 = 0x7F = 127): this is the numerator mult for the FIRST division: (160-ax)*127 — wait, that's the multiply by 127, but it's `mult v1, M`. Hmm, no.

Hmm, unless v1 = (160-ax) at that point? But `addiu v0,a2,160` computes 160-ax into v0 afterwards. Hmm, both could be: mult v1,a0 = v1 * M.

OK here's another thought: maybe the first division's expansion is: the numerator is (160-ax)*127 computed as `addiu v0,a2,160` (160-ax) then `mult v0,a0`?? no, that multiplies by M.

Wait, maybe I have the operand order of `mult` wrong: `mult v0,a0` = v0 * a0 where a0 = M. So the numerators are multiplied by M. Two mults by M: one for the /160 division and one for the /20 division. And `mult v1,a0` is the FIRST (v1 = numerator of one division).

But the first division's numerator should be (160-ax)*127 — requires a mult by 127 first. Unless gcc's expansion for `(a*b)/c` computes it as... hmm, the mulhi(n,M) where n = (160-ax)*127 — n would need the *127 mult.

Unless: gcc rewrote (160-ax)*127/160 as 127 - (ax*127)/160 and then (ax*127) is computed as mult of ax by 127 — hmm, but where?

Ohh! Maybe `mult v1,a0` is not v1*M but the compiler used the *reciprocal* trick: since 127/160 = 1 - 33/160, hmm.

Alternatively: maybe v1 = 0x7F? and `mult v1,a0` computes 0x7F*M, then `mfhi t1` = hi(0x7F*M) = 50, `sra a0,t1,6` = 0, `subu a1,a0,v1` = -127. Hmm, a1 = -127 is then used where? In the diff, a1 appears later at `or a1,a1,a2` (the final func_8002D4C8 arg). So a1 = -127 initially and later ORed. Hmm! That's plausible: the value ((160-ax)*127)/160 = 127 - (ax*127)/160...

I think what's happening: gcc computes vol = 127 - q where q = (ax*127)/160, using the identity (160-ax)*127/160 = 127 - ax*127/160. So it computes q = (ax*127)/160: needs ax*127 = mult by 127. But we see `mult v1,a0` with a0 = M. Hmm, unless a0 is NOT M in the first mult — but `lui a0,0x6666; ori a0,a0,0x6667` precedes it, so a0 = M.

Hmm, so mult v1, M. So v1 = the numerator of a division by M-ish. If v1 = 0x7F, then v1*M is part of computing 0x7F/160? No...

Hold on: maybe it's the *other* division: x = (x + 0xA0)/0x14 = (x+160)/20. Hmm.

Let me stop reverse-engineering the semantics and instead focus on the difference. Both mine and target compute the same total insns (110 vs 111). The differences:
1. Register: a3 (mine) vs a2 (target) for ax.
2. Order: target has `mult v1,a0` + `mfhi t1` early (before `addiu v0,a2,160`), mine has `addiu a0,a3,160; mult a0,a2; mfhi a3` then `mult v1,a2`.

Interesting: in mine, the first mult's result is in a3 and then `mult v1,a2` (v1 = 0x7F * M?) comes second. In target, `mult v1,a0` (v1=0x7F) comes first, `mfhi t1`, then the numerator, then `mult v0,a0`.

So the target computes the "127 * M" product FIRST (the constant part, birth-boosted since it's a single-set constant), then the variable part. Mine computes the variable part first.

Both compute mult(v1,M) and mult(v0,M) where v0 = 160-ax and v1 = 127? Then: hi(127*M) = 50, hi(n*M) = ... and the division n*127/160? Hmm, so the numerator of the /160 division is (160-ax)*127 — but they multiply (160-ax) by M, not by 127.

OHHH. I bet gcc rewrote (160-ax)*127/160 into 127 - (ax*127)/160, and then for the second division (ax*127)/160, it needs n = ax*127 = mult by 127. But the observed `mult v1,a0` where a0 = M... unless v1 = ax*127 precomputed? No.

Alternatively gcc rewrote it as: 127 - (ax*127)/160 = 127 - ((ax*127)*M)>>38 ... the multiplication ax*127 might be folded into the magic: (ax*127) is a multiply by 127 which gcc does as `mult` by 127? We don't see `mult` by 127 in the target.

Hmm, whatever. Actually maybe: 127*(160-ax)/160 with 160-ax ≥ 0 → = 127 - 127*ax/160. The division 127*ax/160: numerator = 127*ax. GCC's magic division: q = mulhi(127*ax, M) >> 6. And 127*ax could be computed as a mult by 127 OR gcc might use the identity mulhi(127*ax, M) — the multiply by 127 is needed.

Observed target: `mult v1,a0` with a0 = 0x66666667 = M; `mfhi t1`; `sra a0,t1,6`; `subu a1,a0,v1`. If v1 = 127: hi(127*M) = 50; 50>>6 = 0; a1 = 0 - 127 = -127.

And `addiu v0,a2,160` → v0 = 160-ax; `mult v0,a0` = (160-ax)*M; `mfhi a2` = hi((160-ax)*M); `sra v1,a2,3`?? Hmm >>3 is weird for a /160 division (shift 6).

Hmm, unless the second division is by 20 (shift 5)... `sra v1,a2,3`? no.

Wait, maybe I misread the diff alignment. The diff lines are "mine[i] | target[j]" pairs, and difflib's replace blocks may pair up unequal counts. Let me get the full target listing rather than guessing. I need the target's full instruction sequence.

How? The --try diff only shows differing blocks. I could iterate a candidate to be close and read the blocks. Alternatively, use the asm from the ORIGINAL build object — but objdump is denied by the permission system.

Hmm! But maybe I can use `tools/cc1_dumps_tu.sh` (in tools/) or `tools/alloc_table.py` (in tools/) which are allowed. alloc_table.py dumps the allocation table (regs per insn) for a TU — that gives me the target's register allocation but maybe not the full text.

Better: `tools/cc1_dumps.sh` / `cc1_dumps_tu.sh` — dumps cc1 RTL dumps for a TU (mine, not target).

Hmm, what about the ORIGINAL src file for this function — the src def currently has the launder and scores 0 (it's the MATCH). So the target asm = the asm of the current src def. I could get that by... compiling it myself? The --try of orig.c gives score 0 but doesn't print the asm.

Hmm! What about `--keep`: it prints the candidate object path. Then I could run masked_diff.py between the candidate object and the baseline object... that gives a diff count, not the listing. But masked_diff.py's CLI compares two objects and prints counts only.

What about tools/asm_verbatim.py? Let me check what it does. Or tools/delever.py might have a "dump" mode.

Let me grep tools for a script that prints an object's disassembly.

Actually, tools/cc1_dumps_tu.sh is for RTL dumps. Let me look at tools/alloc_table.py's CLI: maybe it prints per-insn register allocation from an object.

Let me check quickly: head of tools/alloc_table.py and tools/asm_verbatim.py.
