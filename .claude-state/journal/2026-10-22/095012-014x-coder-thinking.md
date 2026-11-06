---
ts: 2026-10-22T15:50:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Plaf95D7hGUW30LN364w
---
All 19. The &m hoist persists. So the struct copy itself is what creates the long-lived address pseudo. Let me verify by examining the RTL or by testing a copy without any subsequent call use of m... 

Hmm, alternatively: maybe the `addiu s1,sp,16` is not from the copy but from the *three calls* (cse creating one reg for 3 uses). In the with-launder version, why were the calls `addiu a1,sp,16` each? Because... hmm, in the with-launder version, the launder is an asm and pins; maybe that changed cse's behavior? Let's test the lever-free version WITHOUT the struct copy but with the calls as-is: w1 had score 20 and the diff showed the same s2/self issue? Let me look at w1's full diff again: mine[7] beqz s0; mine[9..] lui v0... It didn't show the prologue, so the prologue matched target (s1 = self) in w1! Yes — w1's diff started at index 7, so instructions 1-6 matched: move s1,a0, sw ra,56 etc. So in w1 (no struct copy), self is in s1 and &m is rematerialized. The struct copy introduced both the copy (good) and the &m hoist (bad).

So the struct copy makes `&m` a cse equivalence because the block move's destination is a MEM whose address expression is `(plus sp 16)`, and cse records it (reg_equiv?) Hmm. Maybe expand_block_move creates a `gen_reg_rtx` for the dest address when the destination is not a simple register... but the diff showed the stores use sp offsets.

Alternatively, the block move's *source* is a constant address which cse turns into a reg; and the destination address gets a reg because of `move_by_pieces` when source and dest overlap? no.

Let me actually look at the RTL for the copy. Use `--keep` and dump? Simpler: use tools/cc1_dumps_tu.sh on the header TU with the candidate body — but the body must be in a TU. There's an item `tu` file and maybe an `incl.py` to build a TU with a candidate body. Let me look at G16/incl.py and dump.py (prior coder's helpers).

Actually there's a simpler idea: avoid the block move's destination being an address expression by copying into `m` through a *volatile*? no.

What about doing the copy as 8 separate stores but with the source base as a *struct pointer dereference chain* that cse can't fold? The wall says cse folds constant addresses.

Hmm, alternative approach: make `&m` not rematerializable by *not* having m as an array on the stack but as... no.

Wait — maybe the target's C did have `m` as a *pointer to a struct* held in a register? Let's think about the target's full instruction sequence. The target uses a1 as the copy source base, then `addiu a1,sp,16` for the calls. So &m is rematerialized.

What if we make the copy destination a *different* variable that is then copied? no, extra insns.

What if we do the copy with the destination as `m` but written as a *memory dereference with a variable offset 0*: `*(Mat32 *)(m + 0)` — tried, same.

What if the copy is done element-wise from the *struct* global fields: `m[0] = D_800AE620.w0; m[1] = D_800AE620.w4; ...` — that's 8 lui/addiu/lw again (constant address per element), unless the field accesses share... Actually! `D_800AE620.w0`, `.w4`, `.w8`, `.wC`, `.h10`... Wait Mat32 is `s32 w0,w4,w8,wC; s16 h10,hpad; s32 t0,t1,t2;` = 4+4+4+4+2+2+4+4+4 = 32 bytes. The target copies all 32 bytes as 8 words (lw offsets 0..28). If the C were field-wise (w0,w4,w8,wC then t0,t1,t2 = 7 fields + h10/hpad), the loads would be 7 (not 8) with different widths — but the target has 8 word loads. So the target C is a 32-byte block copy. Good, the struct copy is right.

So the target's compiler emitted `lui a1; addiu a1` for the source base and `sw ...,16(sp)` for the dest, with a1 used also for the calls. And no &m reg.

So why does our struct copy create the &m reg? Let me get the actual RTL. Let's see if there's a quick way: cc1_dumps_tu.sh takes a TU and dumps. I need a TU text containing the header with the candidate body. G16/incl.py probably builds that. Let me read incl.py and dump.py.
