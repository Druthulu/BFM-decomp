---
ts: 2026-11-06T08:58:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l8Y4hbbYJHP3XmYUl6hs
---
No MATCH for flow-unused-result in moves.md. Line 194 is very similar: "the asms materialise a dead constant into v0; a void function drops the value, so plain C cannot keep the 5 instructions (G14)" — a WALL.

Our case is a dead product, same family. But let me try a couple of ideas before declaring a wall. The brief requires ≥20 min and ≥30 scored tries for a WALL. That's a lot. Let me first try a few plausible real-C forms:

Idea A: assign the product to a variable that IS used later but in a way that cancels? e.g. `t = (a[2]-z)*buf[5];` then later use `t*0`? no, adds.

Idea B: The product could be used as the value stored into a **dead stack slot that the target doesn't show**? no.

Idea C: Use `z` in a self-update: `z -= 0x80;` — target does `z -= 0x80` later (after the if block? line 3231: `z -= 0x80;` before v[0].vy). Hmm! In the target, is the `z -= 0x80` computed? Let me look: source:
```c
v[0].vy = v[1].vy = z;      // uses z
v[2].vy = v[3].vy = *(u16*)((s32)a + 0x8);
func_8017E410(mode1, buf);
asm((a[2]-z)*buf[5]);
gte_ldv3c(&v[0]);
```
and before that `z -= 0x80;`.

So z is used in the asm expression.

Idea D: maybe the product can be *the value of a variable that is conditionally assigned and later overwritten*: `s32 t = (a[2]-z)*buf[5]; ... t = something;` — the first set is dead unless used.

Idea E: **Make the product feed the GTE macro in a way that's a no-op**: e.g., gte_ldv3c(&v[0]) — no.

Idea F: Use the product in a `?:` as the *unused* branch: `x = cond ? product : x;` no.

Hmm. Let me look at the source context more carefully — maybe there's a natural place where the product could be used. Let me look at the first if block's original C again (lines 3207-3280). The product `(a[2]-z)*buf[5]`: a[2] is the "y" value; z is a depth. buf[5] might be a scale factor. This looks like it could be a *Z/depth* computation for sorting — maybe used as `otz` or for the tag.

Actually! Look at the target: `gte_stszotz(&otz)` computes otz, then `if (otz > 0 && cull == 0)`. And `idx = otz; if (a[8]) idx -= 0x40;`. The product (a[2]-z)*buf[5] might be an alternative depth used somewhere.

But the binary shows it dead.

Idea G: maybe flow doesn't delete the multiply if it's a *mult* (HI/LO) — in GCC 2.7.2, the multiply is `(set (reg t1) (mult ...))`? The mult/mflo are separate insns; flow's dead-code elimination might not handle multi-insn patterns? But our c1 compile (no asm) DID delete it, so flow handles it.

Idea H: use the product as a **function argument** to a function that ignores it? adds a call.

Idea I: What if the product is used in the *second* loop too? No.

Let me consider: is there any chance the value is used as a *return value*? The function returns 0 at the end. If the product were returned in some path... adds code.

OK, at this point the item looks like a genuine flow-unused-result wall. But the brief demands ≥30 scored tries and ≥20 min for a WALL. Hmm, that's expensive. Let me re-read: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". Hmm, 30 scored tries. The dt.sh each run takes maybe 10-20s. 30 tries = ~10 min. Plus writing candidates.

Wait, but maybe there IS a crack. Let me think harder about what real C keeps a dead result in GCC 2.7.2.

In GCC 2.7.2, dead code elimination is in flow.c (`flow_analysis` + `delete_dead_insns`?). Actually, GCC 2.7.2's dead code elimination is in `dce.c`? No — 2.7.2 has `flow.c` computing liveness and `local-alloc`/`global-alloc`; dead stores are removed by `delete_dead_insns` in flow.c? There's also `jump.c` and `combine`. The removal of dead code in a block is done by `flow_analysis`... Hmm, in old GCC, dead code elimination of sets to dead registers happens in `flow.c`'s `delete_dead_insns`? Actually I recall `dce` is part of `flow.c` in 2.7.2: `insn_dead_p` used by `delete_dead_insns`? Let me check: tools/reference/gcc-2.7.2/flow.c exists? The brief lists jump.c, cse.c, combine.c, reorg.c, sched.c. Let me check for flow.c/dce.c.

If the dead-set deletion happens per basic block, a set whose value is used only... no.

Important nuance: GCC's dead-code elimination for sets with side effects: a MULT inside a `(set (reg) (mult ...))`? In 2.7.2, `(mult)` is an unspec-like; the insn is `(set (reg:SI t1) (mult:SI ...))` with the mult being a special RTL. `insn_dead_p` might consider `mult` as having side effects? No, ours got deleted.

Hmm, wait — did it? In c1, the 5 insns are absent, so yes deleted.

Let me look at the wall evidence from G14 line 194: "the asms materialise a dead constant into v0; a void function drops the value, so plain C cannot keep the 5 instructions". So this class is a known wall.

But before concluding, let me consider a different angle: maybe we can make the product *not dead* by using it in a real computation that the target already has, without adding instructions. The target computes `v[0].vy = v[1].vy = z;` where z was decremented. The product uses (a[2]-z). Hmm.

What if the original source was:
```c
v[2].vy = v[3].vy = *(u16 *)((s32)a + 0x8);
```
a[2] = *(s16*)(a+8)? The source at 3233 uses `*(u16 *)((s32)a + 0x8)`.

Could the product be part of a **comma expression** in an assignment that's later unused? e.g. `x = (product, y);` — the comma's left operand is evaluated for side effects only; gcc would drop it at tree level (no side effects).

Hmm.

What about a *conditional* whose branches are identical: `cond ? product : 0`? adds branch.

What if the product is assigned to a variable that is used in a *dead* branch... flow would delete the whole branch.

OK here's one more idea: **the target's t1 might be used as a scratch for the GTE macro**? Let me check the GTE macros: gte_ldv3c, gte_rtpt, gte_stsxy3, gte_ldv0, gte_rtps, gte_stsxy, gte_stszotz. These are asm macros. Maybe one of them uses $9 (t1) as a clobber/input? No.

Let me look at whether the *original* C could have the product in an `if` whose condition was `(a[2]-z)*buf[5] == something` that folded to a constant... no branch in target.

Alright, let me try a handful of real-C attempts, then if they all fail, do the WALL with 30 tries. But 30 tries on a hopeless item is wasteful; the brief explicitly says a WALL needs 30 scored tries. Let me try systematically:

Attempt list (each scored):
1. orig (0)
2. c1 asm removed
3. t = (a[2]-z)*buf[5]; as a statement (dead) → deleted.
4. t = ...; then use t in a later expression that's an identity? e.g. add `t` to something multiplied by 0? no.
5. `z = z - (a[2]-z)*buf[5]*0;`? adds.
6. assign to otz before gte_stszotz.
7. assign to a new variable used in the uv computation? changes code.
8. `if ((a[2]-z)*buf[5]) {}` — adds branch.
9. `while ((a[2]-z)*buf[5]) {}` — loop.
10. `switch ((a[2]-z)*buf[5]) {}` — switch on a value: gcc might compute the value and emit a jump table? adds.
11. `(void)((a[2]-z)*buf[5]);` — deleted.
12. Use it as a *volatile* temp: `volatile s32 t = ...;` — store.
13. `p->unkX = product`? adds store.
14. Return it? adds.
15. Store to a *dead* stack slot via a pointer whose address escapes: e.g. `s32 t; s32 *q = &t; ... *q = product;` — adds store; flow may keep it because q escapes? But it's a store to the stack that the target doesn't have.

Hmm.

Actually — wait. Let me reconsider the target. Maybe t1 IS used! `mflo t1` puts the result in $9. What if a later instruction reads $9? Let me check the target listing for "$9" or the register t1 in GTE instructions. GTE instructions don't take MIPS registers. But `sw t1,...`? Let me grep the target listing for t1/t9/$9 more carefully — my earlier grep on the listing found only line 88. So dead.

OK so flow kept a dead multiply. How?! Let me check the flow.c of 2.7.2: maybe dead-code elimination only removes insns in a block if the register is dead *at the end of the block*, and `t1` ($9) is a caller-saved register that is... hmm, t1 is dead.

Wait, maybe the multiply is NOT deleted because of the `mult` instruction's implicit use of HI/LO — the `mult` sets HI/LO (a hard register pair) which is not tracked; GCC treats the mult as having side effects on HI/LO, so `insn_dead_p` might not delete a `(set (reg) (mult ...))` because mult clobbers HI/LO? But our c1 shows it WAS deleted.

Unless in c1 it was deleted because the whole expression was removed at the tree level (the asm was the only use). Yes — c1 has no product in the C at all.

So the question is: what C construct makes gcc emit a mult+mflo that survives to the final code?

What if the product is assigned to a variable that is **used in a later block that is unreachable but not deleted until after flow**? Hmm.

What if the product is used in an **asm-like GTE macro that takes a value**? The GTE macros in this project might be C macros with asm. E.g., `gte_ldv3c(p)` uses `*(u32*)p` etc. No.

What about the macro `gte_stszotz(&otz)`: it does `mfc2` and stores. If we pass the product as the *address*? no.

Hmm, what about `D_800A5E60 = (u8 *)p;` at the end — no.

Let me look at the source around the product for a hint of what the original might compute. Actually, maybe the product's *result* is used as `otz`! Look: `gte_stszotz(&otz); if (otz > 0 && cull == 0)`. What if the original was:

```c
otz = (a[2] - z) * buf[5];
gte_stszotz(&otz);
```
Then otz is assigned, then gte_stszotz overwrites it → dead set. But because &otz escapes, flow might keep the assignment! Let's test. In the target, is there a store to otz's stack slot before the mfc2? The target at 1c64: mfc2 t4,$19; sra t4; sw t4,0(v0) where v0=sp+72. So otz is at sp+0x48 and is stored after mfc2. Is there an earlier store to sp+0x48? Let me check the target listing around insns 80-95: no store to 72(sp) before. So no.

Test anyway (cheap): if flow keeps it, we'd see an extra store → score > 0.

Hmm, what if the product is used in a *comparison whose result is stored in a flag that's later used*? e.g. `cull = ((a[2]-z)*buf[5]) != 0;` — but cull is set later: `cull = 0; if (...) cull = 1;`. Adding an assignment to cull before would be overwritten → dead store, but cull is a local; flow deletes.

What if the product is used in the *cull* condition: `if (mx < -0xA0 || ...)` — changing the condition would change code.

Let me look at the actual target: after the product, the code loads the vectors and does GTE. The product sits between the func_8017E410 call and the gte_ldv3c. In source terms, between `func_8017E410(mode1, buf);` and `gte_ldv3c(&v[0]);`. The only statements there in the decompiled body are the asm.

Could the original have been `v[0].vy = ...` using the product? Let me see: `v[0].vy = v[1].vy = z;` is before the call. The target's v[] loads (lwc2 from sp+16) happen after. The v[] stores to the stack are at 1bd0-1bf0 region (before the call). So no.

Hmm, what if the product was used to compute the address of `buf` for the call? No, the call already happened.

Let me try the simplest hypothesis: the original source was
```c
s32 t;
...
t = (a[2] - z) * buf[5];
```
with t used *nowhere*, and GCC 2.7.2 kept it because dead-store elimination doesn't remove sets to pseudos that are... no, it does.

Wait, maybe GCC 2.7.2's dead code elimination is `flow.c`'s `delete_dead_insns` which only runs on *dead stores* to registers that are dead AND not used — and it might miss a `(set (reg) (mult ...))` because the mult is an insn with `insn_can_trap`? Let me check the c1 case more carefully: in c1, the expression is not in the source at all, so no data.

Let me TEST the simplest: `s32 t; t = (a[2]-z)*buf[5];` as a dead statement, then score. If it scores 0, great! (GCC might keep it.) Let me test that first — it's the most direct.

Also test with `(void)` and with `buf[5]` usage.

Let me create candidates:
c2: insert `t = (a[2] - z) * buf[5];` after the call, with `s32 t;` declared.
c3: same but `t` declared at function scope and used in a later dead context? start with c2.

Let me also think about the "temps" catalog: adding a temp variable is allowed.

Test c2 now.
