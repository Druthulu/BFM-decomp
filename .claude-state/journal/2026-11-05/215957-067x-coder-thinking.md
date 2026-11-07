---
ts: 2026-11-06T04:59:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eiQztnIGMBGl3NAPytNc
---
Key insight: `last_mem_set` is cleared when a register mentioned in the last store's address is written, or by a call. So if I insert a store whose address uses a register that is then modified... hmm.

Alternative simpler idea: a store whose MEM equals a later store's MEM will be deleted if last_mem_set matches. The equality check `rtx_equal_p(r, last_mem_set)`. Both MEMs must be structurally equal. If the dead store and the target sh are the same MEM (mem:HI (plus (reg X) 26)), the dead one is deleted. And for cse, this MEM has addr PLUS and mode HI → nonscalar only. Doesn't invalidate scalar D_80127524. BUT: the store's address register X — if X is a *register mentioned in the address of the last store*, it clears last_mem_set... irrelevant.

Hmm. Wait, maybe we can invalidate the cse entry differently: cse's table entry for D_80127524 is a *scalar* MEM. What if the load for the call arg is in a different basic block so cse1 can't forward? The forwarding is happening across the conditional jump, which suggests cse follows the fall-through. What if we restructure the C so the call-arg load is behind an additional unconditional jump or a block that cse doesn't follow? cse's `flag_cse_follow_jumps` and `flag_cse_skip_blocks` are on at -O2. cse1 follows jumps when profitable.

What if the `if (v0 != 0)` becomes a loop or a more complex structure that cse doesn't follow? E.g., `if (v0 == 0) goto done; ...` with a goto label — cse may still follow.

Alternatively, put the load of *p into a variable *before* the store and use it after? E.g.:
```
s32 v = *p;  // load before store? 
```
No, target loads after the store (to get the new value).

Hmm wait. Actually the call arg in target is `lw a0,0(a0)` — loading the *new* value (just stored). Since the stored value equals the loaded value, cse forwarding is semantically correct; target just doesn't do it because the barrier. The barrier is essentially an artificial obstacle. To reproduce in real C without a barrier, we need an obstacle that survives.

Idea: make the store's source and the load's result differ in cse's view by using a *different mode* for the load and converting. Target loads a full word (lw) and passes as s32. If we load via a `u8` and cast, that's lbu — different instruction.

Idea: use a struct member access for the load and a plain pointer store: `((S *)p)->x` vs `*p`. cse's hash of MEM: it hashes the address and the mode; MEM_IN_STRUCT_P doesn't affect the hash? Actually `hash` for MEM includes MEM_IN_STRUCT_P (line 1951: hash_arg_in_struct). The hash includes `(unsigned) MEM` plus the address hash; MEM_IN_STRUCT_P is tracked separately for invalidation, not hashed into the key? Let me check `hash` function: for MEM it adds the address hash and sets hash_arg_in_memory. The MEM_IN_STRUCT_P is a flag used in note_mem_written. The table lookup uses the hash and rtx_equal_p. rtx_equal_p on two MEMs with the same address and mode returns true regardless of MEM_IN_STRUCT_P. So struct vs plain doesn't matter.

Idea: make the load's address a different but equal expression that rtx_equal_p rejects? rtx_equal_p compares structurally; cse's fold_rtx canonicalizes both to the same form.

Hmm. What if the load for the call arg goes through a *second* pointer variable q that cse assigns a different REG_EQUAL... cse replaces q with its equivalent constant if known. If q is loaded from memory (e.g., `s32 *q = (s32 *)D_80127524;` — that's a value load, and q's value is the pointer, not the address). Hmm.

Wait! What if we make the call arg `*p` where p is a *different* pointer that is derived from D_80127524's value: e.g., the target's call is `func_80138C30(*p)` and the sh is `*(s16*)(D_80127524 + 0x1A)`. What if we rewrite the call arg as `*(s32 *)D_80127524`? No, D_80127524 is the s32 at the symbol, not a pointer.

Let me re-read the C: 
```
extern s32 D_80127524;    // a global s32
s32 *p = &D_80127524;
...
if (*p == s0) {
   v0 = D_80127528;
   D_80127528 = 0;
   *p = v0;
   if (v0 != 0) {
       *(s16 *)(D_80127524 + 0x1A) = 1;   // uses the VALUE of D_80127524 as an address
       ((void (*)(s32))func_80138C30)(*p);
   }
}
```
So D_80127524 holds a pointer value. The sh address = (value of D_80127524) + 0x1A. The call arg = value of D_80127524 (i.e., *p).

Target reloads *p twice. Mine forwards the call-arg load to the stored reg.

Real-C idea: force the reload by using a *different type/mode* load that cse can't forward but codegen-wise is still lw. E.g., load as `u32` and pass as s32: `func_80138C30((s32)*(u32 *)p)` — same SImode, forwarded.

What if we load via a struct pointer: `((Unk *)p)->field`? Same.

What if we write the call arg as `D_80127524` (direct symbol) and the store as `*p` (via reg)? cse folds p to the symbol, so both hash the same → forwarded (h4 tested 12, same).

What if the store is `*p = v0` and the load is `D_80127524`, but we *reassign p* between them so cse loses the REG_EQUAL? e.g. `p = &D_80127524;` again — same. Reassign p to itself via a different expression that cse can't fold: `p = (s32 *)((u8 *)p);` identity launder (not allowed). 

What if we declare `p` as a `void *` and cast at each use? cse folds.

OK, different angle: maybe use a *call* as the memory barrier but a call that emits nothing. Is there a way in C to force a call that gcc later removes? No.

What about the "asm" alternative — we're told no asm. 

What about `setjmp`/`longjmp`? No.

Hmm, what about `alloca`? no.

Let me reconsider: maybe the crack doesn't need to prevent the forwarding. Perhaps a different C structure yields the same target naturally. The target has two reloads because in the original C the *source* has two separate loads of *p: one in `*(s16 *)(D_80127524 + 0x1A)` (well, that's a load of D_80127524) and one in the call arg. Both are loads of the same memory. Without the barrier, cse forwards both? It forwarded only the call arg (the sh base load stayed because it's a load used as an address and cse... hmm).

Wait, why did the sh-base load at insn 57 survive? Maybe because it's the *first* load after the store and cse's table lookup failed due to the intervening jump, but the *second* load at 64 found the entry created by insn 57 (which is reg 84). But then the call arg would be reg 84, not 76. The dump says 76. So cse's lookup for insn 64 found 76 — the *store's* source. That means the store's entry survived the jump AND the load at 57 didn't override it (cse prefers the entry with lower cost/reg). And the load at 57 also should have been forwarded to 76 then... unless at insn 57 the store's entry was not valid *because the address register 75 differs from the symbol*? No, the store's dest is (mem (reg 75)) and the load is (mem (symbol D_80127524)); fold_rtx uses REG_EQUAL on reg 75 to fold the load's address to the symbol, and the store's dest too? The store's dest at insn 50 is (mem (reg/v 75)) — not folded (REG_EQUAL on reg 75 exists: insn 35 has REG_EQUAL symbol). cse would fold the store dest to the symbol as well. Hmm.

Then the entry is (mem (symbol D_80127524)) -> 76. At insn 57 (in the next EBB after the jump), cse's table was reset at the jump? If reset, no forward → real load. Then the load creates entry (mem symbol) -> 84. Then insn 61 store (varying, HI, PLUS) invalidates nonscalar entries only, so both entries (76 and 84) for the same MEM... cse's table has a chain of equivalents; lookup returns the cheapest. Both 76 and 84 have the same hash. At insn 64, lookup finds the entry whose... maybe the first one (76, from before the jump) is still in the table because the table wasn't reset but the load at 57 was somehow not forwarded? Contradiction.

Let me actually check the cse1 dump before insn 57 for the table state — hard. Let me instead check whether the .cse dump shows insn 64 forwarded and insn 57 not — yes. Maybe cse's cse_basic_block starts a new block at the label after the jump, but it processes the *fall-through* block too and the table persists partially.

This is getting deep. Let me try a more empirical approach: insert a *dead store that cse sees as all=1* and check whether flow deletes it. The easiest deletable store with a varying QI address... hmm.

Alternative: a store to a *register* doesn't invalidate memory. A store to a MEM whose address is a bare register (not PLUS) → all=1, and flow can't delete it. But what if the store is to a MEM through a register that is a *known stack slot* after cse? cse's fold_rtx would fold the register to the stack address if it has REG_EQUAL. If we store to a local through a pointer variable that cse can fold to a fixed stack slot, the address becomes fixed (not varying) → doesn't invalidate all. Ugh.

What if the address is a bare register whose value cse can't determine but which is *dead* after the store, and flow deletes the store because... insn_dead_p doesn't delete MEM stores except last_mem_set. So no.

Hmm, but maybe flow isn't the only deleter; combine might remove a store to a dead stack slot? No.

What about making the extra store *not emit an instruction* because it's optimized away by cse/combine themselves? E.g., a store of a constant 0 that gets merged? no.

New idea: Use a **call to a function pointer that is the same function**? no.

Let me step back and consider the WALL possibility. The brief says a WALL needs ≥20 min and ≥30 scored tries on that item. We have maybe 15 tries on item 3 so far. Time: started item 3 around 21:52; now probably 22:05. Let me keep trying a bit.

Another idea: the barrier is between the sh store and the call. What if we put the *call* first (before the sh) in source and then the sh? Target order is sh then call-arg-load then call. If source is:
```
func_80138C30(*p);
*(s16 *)(D_80127524 + 0x1A) = 1;
```
that changes semantics? The target does the store then the call. Semantically, if the call reads the stored field, order matters. Target: store then call. So can't reorder.

What about making the call arg load depend on the store in a *real* way: the call arg is `*p` (new value). The store wrote v0. If we write the call arg as `(*p = v0, *p)`? same.

What if the call arg is a *different expression* that requires a reload: e.g., `*((s32 *)((u8 *)p))` no.

Hmm, what if we make the store's source a *constant-ish* expression that cse can't record, e.g., `*p = D_80127528` (load) then `D_80127528 = 0`? Then the store's src is a MEM (do_not_record for the src? cse's `do_not_record` is set when the source contains a MEM — line 1942: `if (MEM_VOLATILE_P) do_not_record`; a plain MEM in src sets hash_arg_in_memory but not do_not_record). Hmm.

Let me test h3-like variants where the store source is a load: `*p = D_80127528;` before zeroing. We need v0 = D_80127528 for the if. Try:
```
v0 = D_80127528;
*p = v0;
D_80127528 = 0;
if (v0 != 0) {...}
```
h2 tested this = 12.

What if we don't keep v0 but re-read for the if: `*p = D_80127528; D_80127528 = 0; if (*p != 0) {...}` — the if test loads *p (forwarded to the store src?). Might produce different code (the if test would be forwarded).

Let me look at the actual difference between mine and target more concretely. Mine (a1): 
- `sw a0,0(v1)` (store value)
- reload `lw v1,0(v1)` for sh base
- `jal` with a0 = value (forwarded)
Target:
- `sw v0,0(a0)` 
- reload `lw v1,0(v1)` for sh base
- `lw a0,0(a0)` for call arg
- `jal`

If we could make the call arg load not forwardable by giving the stored value a different register than a0... The forward is a *register copy* `(set (reg:SI 4 a0) (reg/v:SI 76))` — that's cse replacing the load with reg 76. Then global-alloc assigns a0 = the call arg. Since reg 76 is the stored value, and the store already used it, this is one insn.

What if the stored value register is *dead* after the store (it's used in the if test before)? The if test uses it. 

Idea: store a *different variable* than the one tested: 
```
v0 = D_80127528;
D_80127528 = 0;
*p = v0;
if (v0 != 0) { ... }
```
What if we store `D_80127528` via a separate temp: `s32 t = v0; *p = t;`? Then the store's source is t, and the call arg load would be forwarded to t. Still a register.

What if the store's source is an expression with a REG_EQUAL note rather than a register? cse records the *src expression*; if src is `(plus v0 0)` folded to v0.

Hmm.

What if we make the store value a `u32` variable while the load is s32? Mode SImode both; cse mode-sensitive lookup uses SImode. Forwarded.

What if the load is `s16`? Changes instruction.

Let me try yet another structural approach: make the call arg load happen in a block that cse doesn't follow by adding a `goto`/label. For instance:

```
if (v0 != 0) {
    *(s16 *)(D_80127524 + 0x1A) = 1;
    goto do_call;
}
...
do_call:
    func_80138C30(*p);
```
This changes control flow and codegen; likely worse.

Alternatively invert: 
```
if (v0 == 0) return/... 
```
The function continues after the if (the else path is the code after). Target structure: `if (v0 != 0) { sh; call; }` then falls to the `if ((*(s32*)(s0+8) & 0x8000) == 0)` block. Inverting could change block layout.

Hmm, let me look at whether cse1's forwarding survives if there's an intervening *unconditional* jump. What if we use a `while(0)`-style loop? A do-while(0) around the sh+call? cse doesn't cross loops (cse_around_loop). Let's try wrapping the `if (v0 != 0)` body in a do-while(0). That might stop cse from forwarding the load (loop boundaries reset the table), and flow/loop.c removes the empty loop. Target might keep the same code.

Let me test:
i1: do { sh; call(*p); } while(0); inside the if.
i2: do { sh; } while(0); then call(*p);
i3: do { call(*p); } while(0); after sh? order changes.
i4: `while (0) {}` no.

Actually, do-while(0) is a loop construct; cse_around_loop handles loops conservatively (it invalidates). This could work.

Let me test i1 and i2 on includer 0.
