---
ts: 2026-11-06T06:32:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nlVrXN063skLCS0gjIFn
---
Big diff. The launder's memory clobber clearly matters a lot (it forces the D_800A5E60 load and ordering, and it keeps mulc in a register).

Note the target has an interesting tail: `lui at,0x1; addu at,t1,at; lhu v0,-23598(at)` — a non-folded address (t1 = base?). That's the `*(u16 *)(base + 0xA3D2)` load where base is in a register.

Let me look at the target's full asm to understand. Let me dump the target function from build/.

Actually, let me first try the obvious real-C replacements for the launder:
1. `pkt = D_800A5E60;` — keep.
2. The asm forces mulc to be in a register and clobbers the memory of D_800A5E60.

A natural replacement: make `mulc` used in a way that keeps it live, and make D_800A5E60's load happen after the division.

Actually, what does the asm do at RTL? It's an asm with an output operand "=m"(D_800A5E60) — a memory write to D_800A5E60 (a pointer variable) — and an input "r"(mulc). Since the asm writes memory, it prevents the compiler from reordering the subsequent `pkt = D_800A5E60;` load before it. Without the asm, the compiler may hoist `pkt = D_800A5E60` earlier (before the division), which changes register allocation.

So a real-C replacement: make the D_800A5E60 load happen after mulc's computation in a way the compiler can't move... In C, `pkt = D_800A5E60;` is already after `mulc = mulc / (g.otz * 4);`. The compiler wouldn't hoist a load across... it could, since D_800A5E60 isn't written between.

Hmm, but the asm *writes* D_800A5E60 (out-only "=m"), which is a real store (zero bytes — the constraint is "=m" but the asm body is empty, so reload still allocates the operand as a memory location; with an empty asm, no actual store is emitted).

So the asm's RTL effect: an asm insn with a memory output operand (D_800A5E60) and a register input (mulc). At RTL it's `(set (mem D_800A5E60) (asm_operands ...))` — a *set of memory* that is dead (never used) but prevents reordering.

A real-C replacement: a store to D_800A5E60 that is dead but not deleted — e.g. `D_800A5E60 = D_800A5E60;`? That's a load+store (2 insns) and might be deleted by cse (dead store).

Hmm. Or the C0414 dead-reset: `D_800A5E60 = 0;` then `pkt = D_800A5E60;`? That changes pkt's value.

Wait — look at the code:
```
__asm__ ("" : "=m"(D_800A5E60) : "r"(mulc));
pkt = D_800A5E60;
D_800A5E60 = pkt + 0x28;
```
The asm "writes" D_800A5E60 (virtually), so the load `pkt = D_800A5E60` can't be hoisted above it. And the input "r"(mulc) forces mulc into a register at that point.

Real C alternative: what if we write
```
pkt = D_800A5E60;
D_800A5E60 = pkt + 0x28;
```
directly (no temp)? That's the same.

The issue is the ordering: the compiler may move the `lw` of D_800A5E60 up before the division. Let's see what w0's diff says around there. The diff at mine[124] etc. is about `sb a0,13(a3)` (pkt[0xD] = w2) and the w2/w assignment.

Let me look at the target asm to understand the structure. Let me dump the target function.
