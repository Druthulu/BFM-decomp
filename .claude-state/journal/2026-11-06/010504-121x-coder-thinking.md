---
ts: 2026-11-06T08:05:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PcjPnIySZkxMpxHzmhA9
---
Target mapping:
- s2 = obj->unk4C (76)
- s3 = obj->unk20 (32)
- beqz s2
- func_80015954(D_800CC290, obj+4): a0=lui/addiu D_800CC290, a1=s0+4
- lhu v0,96(s0) = v (unk60)
- lhu v1,10(s0) = t (unkA)
- andi a0,v0,0x1f = m
- sll s1,a0,0x7 = m << 7  (computed early, kept in s1)
- addiu v1,v1,-16 = t-0x10
- sh v1,10(s0) = unkA
- lw v1,80(s0) = obj->unk50
- addiu v0,v0,1 = v+1
- bnez v1 → if unk50
- sh v0,96(s0) = unk60 (delay slot)
- jal func_80047948 with `sll a0,a0,0x7` in delay slot — wait, `sll a0,a0,0x7` uses a0 (m) and produces m<<7 for the arg. But s1 already has m<<7. So the target computes m<<7 TWICE: once into s1 early, once into a0 for the call. Interesting: the early `sll s1,a0,0x7` computes the argument value and stores it in s1 for the ELSE branch? Let me see: in the if-branch, `jal; sll a0,a0,0x7` (call with m<<7). In the else-branch, `jal; sll a0,a0,0x7; li v1,4096; subu v0,v1,v0` (0x1000 - func(...)). So both branches compute m<<7 at the call. The early `sll s1,a0,0x7` — what uses s1? Later: `jal func_8004787C; move a0,s1` — s1 is the argument to func_8004787C! But the source calls `func_8004787C(ang)`, not m<<7! 

Wait: `move a0,s1` before `jal` (the func_8004787C call) — s1 = m<<7?? That would pass m<<7 as ang. But the source passes `ang = ((m << 8) & 0x7F00) >> 1`. Let me compute: ((m << 8) & 0x7F00) >> 1. m is v & 0x1F (0..31). m<<8 = m*256; & 0x7F00 keeps bits 8..14; >>1 = ... Hmm, `sll s1,a0,0x7` = m << 7 = m*128. And ang = ((m<<8)&0x7F00)>>1 = ((m*256) & 0x7F00) / 2. For m in 0..31, m*256 & 0x7F00 = (m & 0x7F)*256? m*256 <= 7936 < 0x7F00? 31*256 = 7936 = 0x1F00, & 0x7F00 = 0x1F00. >>1 = 0xF80 = 3968 = 31*128. So ang = m*128 = m << 7! Yes! ang == m << 7 mathematically (for m in 0..31, since the mask is redundant). So the compiler folded ang to m<<7 and s1 holds ang, used for func_8004787C(ang). And `sll a0,a0,0x7` at the call is m<<7 for func_80047948(m<<7). Both are m<<7, computed twice (or s1 reused?).

So the target: m in a0, ang (m<<7) in s1 computed early. The early `sll s1,a0,0x7` is ang, computed at its source position (`ang = ...` before the stores). Then the call's `sll a0,a0,0x7` is m<<7 (a separate computation, cse might have merged but the asm keepalive blocked? no).

Hmm, in mine, the register pairs v1->a0 x2: the call arg is a0 in target vs v1 in mine. Mine computes m into v1 and does `sll a0,v1,0x7`. Target computes m into a0 and `sll a0,a0,0x7`.

So the natural C: `m` and `ang` are computed before the stores. Mine sinks them. The keepalive forces them.

Real-C idea: name `ang` as a variable and use it. The source already does `ang = ((m << 8) & 0x7F00) >> 1;` and uses `func_8004787C(ang)` later. The compiler folded ang to m<<7 and keeps it in s1 (target). Mine also has s1 for the sll at insn 25 (`sll s1,v1,0x7`), but computed late. So the issue is scheduling: the target computes ang early, mine late.

What real-C forces ang's computation early? A use of ang before the stores. Hmm, ang's only use is the func_8004787C call after. The target computes it early because sched1's birthing priority hoisted it (the sll has a long latency? no). The keepalive forced it.

Maybe the original source has a use of ang in the stores? No.

Alternatively, maybe the original computes `m << 7` once into a variable:
```
s32 m7 = m << 7;   // or ang
```
Then the variable is used in both the call arg and func_8004787C? No, the call arg is m<<7 and func_8004787C takes ang=m<<7. They're the same value! If the source computed `ang = m << 7` (folded) and used ang for BOTH the func_80047948 arg and func_8004787C, then there'd be ONE computation. But target computes it twice (`sll s1` early and `sll a0` at the call). Hmm, cse could have merged them but didn't (the keepalive? no).

Wait, maybe the two slls are: `sll s1,a0,0x7` = ang (from m<<8>>1 folded), and `sll a0,a0,0x7` = m<<7 for the call. The source has two different expressions that fold to the same value; cse might merge them if it can prove m is unchanged. It didn't merge, so maybe the source's expressions are genuinely different in the IR.

Let me look at the source: `ang = ((m << 8) & 0x7F00) >> 1;` → the compiler folds to `m << 7`? The target's sll s1,a0,0x7 confirms. And `func_80047948(m << 7)` → sll a0,a0,0x7. cse should CSE these two (same value m<<7) — but it didn't because between them there are asm/stores? The `sh v1,10(s0)` store and `lw v1,80(s0)` etc. The m value is unchanged, so cse could. Unless the slls are in different basic blocks (the call is inside the if/else blocks). Yes! The `sll a0,a0,0x7` at the call is inside the if/else blocks; the `sll s1,a0,0x7` is in the entry block. cse1 doesn't propagate across blocks (or the value in a0 isn't available). So two computations.

Now, the keepalive forces m and ang to be computed in the entry block. The natural C must cause the same. The `ang = ...` assignment IS in the entry block, so the compiler should compute it there (at its definition) unless sched1 sinks it to its use in the else block. Mine sinks it (insn 25 in the entry block? Let me check mine's full listing). Actually mine has `sll s1,v1,0x7` at insn 25, which is still in the entry block (before the bnez at 24? no, after). Let me look at mine's full listing.

Actually, the diff shows mine[22:26] = `lw v0,80(s0); nop; bnez v0; sll s1,v1,0x7` and target[25] = nothing. So mine has the sll AFTER the bnez (in the delay slot!). Target has the sll early (insn 18). So mine sank the sll into the branch delay slot. The target computes it early.

Real-C fix: compute `ang` into a named variable used before the branch. It is. Hmm.

What if the original computes `m` and `ang` via separate statements AND uses `ang` in the `func_8004787C(ang)` call which is in the ELSE path? The compiler sinks ang to the delay slot (mine). To prevent, the source might use `ang` earlier, e.g. store it or use it in the d[1] computation before the branch? No, d[1] is after.

Maybe the natural C has `ang` used in a way that forces it: e.g., `s16 d[2]; ... d[1] = func_8004787C(ang) / 512;` — after.

The keepalive is at a specific point (after t=unkA, before the stores). It forces m and ang live there. What real-C value is live there? m and ang are used after the stores/branch. Their live ranges already span the stores! The compiler could keep them. The keepalive's real effect is to force them into registers *at that point* so sched1 computes them there. Without it, sched1 sinks the computations.

Maybe the natural C has the two stores AFTER the if/else? No, target stores unkA/unk60 before the branch.

Hmm, what if the source computes `m` and `ang` with the stores in between differently:
```
v = obj->unk60;
m = v & 0x1F;
ang = ((m << 8) & 0x7F00) >> 1;
obj->unkA = obj->unkA - 0x10;
obj->unk60 = v + 1;
```
That's the same.

Let me try real-C variants:
1. Name `m << 7` as a variable `m7` used for the call, and `ang` separately.
2. Compute ang as `m << 7` directly.
3. Use `s32 ang = m << 7;` (folds to the same).
4. Reorder: compute ang after the stores? No.
5. Use `d[1] = func_8004787C(ang) / 512;` earlier? no.

Let me also check: mine's register pairs v1->a0 x2 — after fixing the order, m should be in a0. Let me try naming the arg:
```
s32 m7 = m << 7;
...
r = func_80047948(m7);
else r = 0x1000 - func_80047948(m7);
...
d[1] = func_8004787C(ang) / 512;
```
Hmm, if m7 is named, the compiler computes it once and keeps it; but the target computes it twice. Might not match.

Let me just try a batch. First, let me see mine's full listing to understand the delay slot.
