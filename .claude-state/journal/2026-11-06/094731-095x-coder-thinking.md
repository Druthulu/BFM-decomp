---
ts: 2026-11-06T16:47:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p0QIFrqOEYLCJurD58mt
---
No change. The fp allocation is robust to these tweaks. The pin $16 forces s0; without it the allocation differs structurally.

Let me check what register fp actually gets in no_fp and why. In no_fp's asm, fp = s0? The diff showed `addiu s5,s3,46` vs target `addiu s0,s4,46`: mine computes fp = s3+46 (s5), i.e., prim is s3 and fp is s5. Target: prim=s3, fp=s0.

Mine's loop: prim=s3, fp=s5, buf=s4, table=s6, cbase=s7? and extra s7 save.

Target: prim=s3, fp=s0, buf=s4, table=s5, cbase=s6? (target addu v0,v0,s5 for table). So mine has table=s6, cbase=s7, fp=s5; target table=s5, cbase=s6, fp=s0.

The pin fp=s0 shifts everything: with fp pinned to s0, the others get s5,s6 and no s7. Without, fp takes s5 (high priority?) and cbase takes s7.

So if we can make fp the *first* allocated (highest priority) among {fp, table, cbase}, it would take s0 (the first callee-saved assigned). fp's priority = floor_log2(refs)*refs*size/life.

fp: defined once (fp = prim+0x22), used many times in the loop (12+ uses), live across the loop. table: defined once, used 4 times in the loop. cbase: defined once, used 8 times.

Hmm, fp has the most refs. But local-alloc allocates per basic block; the loop body is one block. All three are live in the loop. Priority = f(refs)/life. fp: refs ~13, life from before loop to end. table: refs 4. cbase: refs 8.

floor_log2(13)=3 → 39/life; table floor_log2(4)=2 → 8/life; cbase floor_log2(8)=3 → 24/life. If lives are similar, fp wins → should get the first free callee-saved. Why doesn't it?

Maybe because s0 is already taken by something else in mine: D_800AF648 address? In target, s0 is ALSO the D_800AF648 address (`lui s0,0x0; addiu s0,s0,0`) and then later fp is ALSO s0! Because the D_800AF648 address dies before the loop (used only for the two func_8004914C/AC calls). So s0 is reused: first for &D_800AF648, then for fp.

In mine, s0 is used for something else (maybe &D_800AF648), and fp goes to s5. The reuse depends on the ordering of allocations (s0 is allocated to fp only if the D_800AF648 pseudo is dead by then...).

Since local-alloc is per-block, s0 is a hard reg; the pseudo for &D_800AF648 is in block0 (entry), and fp in the loop block (block N). local-alloc allocates per block, so s0 should be free in the loop block. Unless the entry block and the loop are in the same... The loop is after the buf allocation call and the primPtrs stores — many blocks.

Hmm, why would fp get s5 then? Because the callee-saved registers are allocated by *global* alloc (they're live across calls!). fp/table/cbase are live across the calls inside the loop (AddPrim? no, AddPrim is a macro). The loop contains no calls. But fp is born after func_80010A08 and lives to the end; it crosses no calls after birth. Hmm, but the loop body contains no calls, so these are block-local to the loop block → local-alloc.

In local-alloc, the allocation order within the block by priority. First free callee-saved regs: s0? s0 holds &D_800AF648 in block0 only; but is s0 considered live at the loop block start? No (dead after the calls).

Hmm, but the order of *hard regs* chosen: find_free_reg scans registers from 0 up, preferring the qty's preferred class. So the first free one would be v0/v1/t0..., then s0.. So fp should get s0 if it's the first allocated in the block... unless other pseudos in the block are allocated first and take s0.

In mine, which pseudo got s0? Let me dump no_fp's lreg to see the block allocations.
