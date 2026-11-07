---
ts: 2026-11-06T21:09:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_97kqL1MoZLDEjq1WVQOI
---
All 4. Let me think harder.

The launder's key effect: e gets a 2nd def, making n_refs=4 and multi-set, which changes local-alloc. Actually, maybe more importantly, the launder's asm makes e *not* REG_EQUIV, so e is a normal pseudo. But mine still allocates e to a1, so REG_EQUIV didn't eliminate it.

Wait — maybe the effect of the launder is on the *global-alloc* or *reload* phase, not local. Let me look at where the a0/a1 assignment happens. The greg dump (after global-alloc) shows a0/a1. Global-alloc runs after local-alloc. So local-alloc set it. But maybe local-alloc didn't allocate (pseudos live across calls), and global-alloc did. off and e don't cross calls though.

Let me look at the actual local-alloc decision by checking whether off/e are in qty_order. Hard.

Let me try a different tack: change e's *type* to make its qty different. E.g., declare `e` as `void *e` and cast at use:
```
void *e;
e = D_801E8F78;
... *(s16*)((u8*)e + off + 2) ...
```
The condition already casts `(u8*)e`. If e is void*, `(u8*)e` is fine. Let me test. Width/mode same (SI). Might not matter.

Or declare e as `s32 e;` and cast. Same mode.

Hmm. What about the REG_EQUIV: if we prevent the REG_EQUIV note, e becomes a normal pseudo. REG_EQUIV is added when the set source is a MEM or constant? In local-alloc, a REG_EQUIV note is added if source is MEM and validate_equiv_mem. But our source is symbol_ref — REG_EQUIV was set earlier by cse? Actually the lreg dump showed REG_EQUIV on the symbol_ref set. So it's there.

To remove REG_EQUIV, make e's source not a plain symbol: e.g. `e = (s16 *)((u32)D_801E8F78);` — a cast, folded to symbol. Or `e = &D_801E8F78[0];`. Or compute via a volatile? no.

Alternatively, make e = (s16*)((u8*)D_801E8F78 + 0) → folded.

Hmm, what if we make e = D_801E8F78 but D_801E8F78 is declared differently... no.

Let me try the void* and s32 declarations, plus making e a `u8*` and casting the load.

Actually, here's a cleaner idea. The launder gave e TWO definitions. A real 2nd definition can be created by initializing e to something at declaration and reassigning it:
```
s16 *e = (s16 *)D_801E8F78;   // init at decl
...
e = (s16 *)D_801E8F78;         // reassign
```
The first is dead → removed.

What if the first def is used in a way that produces the SAME instruction? For example, use e for the lim load via a cast, then reassign e, then use it in the condition. But the lim-via-e changed instruction count.

Hmm, what if lim is loaded via e but we prevent the address sharing by making the condition use `(u8*)e + off + 2` where off is a separate variable — cse still shares e+off.

Unless... we use `e + off + 2` written as `e[off/2 + 1]`? e[off/2+1] = e + (off/2+1)*2 = e+off+2. If off is used as `off/2`, that's a shift... changes code.

Let me look at what the target's two addresses are again: lim uses at = sym+off (lui at). Condition uses v0 = e+off (addu). Note e = sym (a0, addiu). So sym+off via `lui at` (16-bit hi only, no addiu) because the low part goes in the load's offset? Actually `lh v1,0(at)` with R_MIPS_LO16 D_801E8F78 at offset 0. So the lim address = HI(sym)+off with LO applied at load. And e = lui+addiu (full address). This is the classic difference between using a symbol directly in an address (HI/LO split) vs materializing the full pointer.

So target: lim address uses symbol+off (a "plus sym off" expression), condition uses e (a materialized pointer) + off. If we write `lim = ((s16(*)[2])e)[idx][0]`, the compiler may use e+off (materialized) instead of sym+off → shares with condition → 146.

To get sym+off for lim AND have e used elsewhere, we need e to be a separate pseudo with its own materialization, which is what win.c does.

OK, let me think about the register allocation from the qty angle once more. Maybe the issue is that off and e are allocated in the SAME qty_order iteration but off is processed first because qty numbers tie-break. If priorities are equal? Let me compute with actual qty_birth/death as 2*insn:
- off: birth 2*54-1=107, death 2*81=162 → 55. n_refs: let me check if off's def counts. reg_n_refs in flow counts each reference (use and set). off: set at 54, use at 70, use at 81 → 3.
- e: birth 2*73-1=145, death 2*81=162 → 17. n_refs: set at 73, use at 81 → 2.

pri_off = floor_log2(3)*3*4/55 = 1*12/55 = 0.218*10000=2181
pri_e = floor_log2(2)*2*4/17 = 8/17=0.47*10000=4705

e > off → e first → a0. But actual is off=a0. So my model is wrong somewhere. Perhaps off's death is later than 81? Or e's birth earlier?

Wait, maybe off is ALSO used in the `if (idx >= 0)` block? Let me check: `p = D_801E8F98[idx]` uses idx, not off. No.

Maybe e's qty includes the REG_EQUIV symbol use in a way that extends... no.

Hmm, maybe the block is split such that e and off are in DIFFERENT basic blocks! The `if (t < lim)` creates a new basic block. The lim load (insn 70) and e def (73) and slt (76) and branch (77) are in block A; the condition (81-89) is in block B (the then-arm). If off and e are defined in block A but used in block B, they are NOT local to one block → handled by GLOBAL-alloc, not local! Because local-alloc only handles pseudos whose all references are in one block ("pseudos that die but once" in the block).

off: defined in block A (insn 54), used in block A (insn 70) and block B (insn 81). Crosses blocks → global-alloc.
e: defined block A (73), used block B (81) → global-alloc.

So this is GLOBAL-alloc! Global priority formula in global.c. Let me read global.c priority.

The moves log mentions greg-pri-refs etc. Global priority = floor_log2(n_refs) * n_refs / live_length or similar. Let me check global.c.
