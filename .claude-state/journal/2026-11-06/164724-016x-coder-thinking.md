---
ts: 2026-11-06T23:47:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DxIDawdSxkvXKIUN6TSR
---
pri = floor_log2(n_refs) * n_refs / live_length * 10000 * size.

For base: n_refs ~10 (well, more, refs includes all uses). For mode: n_refs 4. If live_length of base is much longer, base's priority could be lower. base lives from top to the end (long), mode lives from its set to the end too.

Hmm, base live_length is huge (whole function ~160 insns), mode also long. Let's compute: base n_refs maybe 11, floor_log2(11)=3, pri = 3*11/live_len. mode n_refs=4? floor_log2(4)=2, 2*4/live=8/live_len.

If base live = 160: 33/160 = 0.206; mode live = 60: 8/60 = 0.133. So base wins → s3. In target with pin, base is allocated... hmm wait, with the pin, mode is a hard reg and doesn't participate, base gets s4? Why not s3? Because s3 is reserved by the pinned hard reg (global.c's `find_reg` skips hard regs used by fixed pseudos? Actually the pinned variable is a hard reg used in the function; global_conflicts marks conflicts with hard regs, so base can't take s3).

Hmm, so lever-free we need mode to beat base. Could we make mode's live_length shorter and refs higher? Or make base's priority lower (longer live range)?

But wait — maybe there's another path: what if mode is not callee-saved-worthy? Both s3/s4 are callee-saved. global-alloc's find_reg prefers... the order of hard regs considered. If both are eligible, the first allocated gets the lowest available reg in the preferred order. Actually the register order for s regs: global.c's `alloc_regs` order comes from `regs_allocated`? The order in which hard regs are tried is determined by `reg_class_contents` / `reg_alloc_order`? For MIPS, the `REG_ALLOC_ORDER` might be s0..s7 then t... Actually find_reg scans `regs_allocated` and tries regs in `reg_alloc_order`? Let me not go too deep.

Alternatively: maybe the natural way is that base and mode swap because of *how many refs each has* — the extra copy insn in target adds a ref to... no, the copy is in a different block.

Hmm. Actually, wait. Let me reconsider. Maybe it's local-alloc, not global-alloc. If base and mode are both assigned in a single block? No, base is set at top, used everywhere.

Actually, maybe the difference is that in the target, `q` (the launder pseudo) occupies v0, and p is a3 — that's fine. The register swap s3/s4 might resolve itself if the body changes.

Let me approach empirically: try candidate bodies. First, the copy issue.

Candidate idea for the copy: use a `s32 *q` with a real second set via a branch:
```
s32 *q;
q = &D_800C7C60;
p = q;
*q = val;
```
Hmm.

What about declaring q as `u32` and casting: 
```
u32 q = (u32)&D_800C7C60;
p = (s32 *)q;
*p = val;
```
The compiler will still fold.

Let me think about what makes cc1 emit a copy: if the destination and source are different pseudos after cse, and combine can't merge because the dest has >1 use, then the copy remains. In mine there's NO copy at all, meaning the frontend/cse folded `p = q` (p and q same pseudo). The asm output forces q into a new register because asm outputs are new pseudos.

A real C way to force a new pseudo: assign q through a construct cse treats as opaque... e.g., call a function that returns the pointer? No.

Hmm, what about making p not a copy but computed:
```
p = &D_800C7C60;
*p = val;
```
and separately q used for something? no.

Alternative approach: maybe we don't need the copy if we can make the target's extra insn appear differently — e.g., we could add a different real insn. But score 0 requires exact bytes.

OK here's another thought: the asm output `"=r"(q)` with `"0"(q)` — gcc treats it as q_new = q_old but a *new* pseudo. Value-preserving real 2nd set: the C equivalent used elsewhere in these shards is e.g.:

From moves: "launder->real 2nd set `pv = pv & 0xFF000000;`". For a pointer copy, an analogous real 2nd set that is value-preserving but not an identity statement: `q = (s32 *)((u32)q & 0xFFFFFFFC);`? That's a value-preserving mask (address is aligned), but it's an identity-statement launder by the brief's definition ("identity address spellings"). Hmm, `& 0xFFFFFFFC` is a mask, arguably an identity spelling.

What about `q = q + 0;`? identity.

What about a real 2nd set with a *different value* on a path: e.g.
```
s32 *q = &D_800C7C60;
if (some_cond) q = q;  // identity again
```

Hmm. Let's think about C0414 dead-reset more concretely: `q = 0;` after the copy. This is a real 2nd set (value 0 ≠ address). Does it break cse? cse processes forward: at `p = q`, it records p≡q. Then at `q = 0`, it invalidates q's class. p remains. But the issue is whether `p = q` is emitted as a copy at all. If cse made them equivalent, the copy is deleted. The reset comes after, so it doesn't help the copy before it.

Unless the reset is placed BEFORE:
```
q = &D_800C7C60;
q = 0;
q = &D_800C7C60;
p = q;
```
Silly.

OK, different idea: what if q and p are the SAME variable but we need a copy anyway. Actually, in the target, is it possible that the move is not `p=q` but rather `D_800C7C64 = &D_800A2E20`? Let's look at the target insns around 107-110 more carefully. Actually `lui v0; addiu v0; move a3,v0` — the lui/addiu is an address of a symbol. Which symbol? Could be D_800C7C60 or D_800A2E20. `move a3,v0` then... p = q. And then `*p = val` → sw val,0(a3). Then `D_800C7C64 = &D_800A2E20` would be another lui/addiu + sw. Hmm, but the diff at 107: mine has lui a3/addiu a3 and target has lui v0/addiu v0/move a3,v0. The offset alignment: mine[107:109] vs target[107:110]. So the rest aligns after.

Let me get the actual target disassembly. There's a tool to dump the target. Let me check dt.sh / delever_search for a way to print the target around an insn. Maybe `bin/chk.sh`? Let me look at tools/delever_search.py options.
