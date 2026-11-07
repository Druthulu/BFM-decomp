---
ts: 2026-11-06T09:59:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UkeRHUMAXL2D4heYS2Ct
---
Confirmed: no move a0,s0 for the final call. That means GCC emitted a call with a0 unset — that's a bug... OR the final call's argument isn't s0 but something already in a0.

Wait, look at line 76: `addiu a0,a0,0` sets a0 = &D_800CD7A4 (for func_800233CC call at line 80). Then the call at 80 (func_800233CC). Then final call at 89 (func_80146C3C) with nop.

Hmm, but the lever-free body's last line is `((void (*)(s32))func_80146C3C)(s0);`. GCC would definitely emit a move. Unless GCC's dataflow thinks a0 still holds s0? No.

WAIT. Maybe `s0` is a `register` variable name in my nopin.c? I replaced `register s32 s0 __asm__("$16");` with `s32 s0;`. So s0 is a normal variable. Hmm.

Hold on, maybe the call is not the last statement in the generated function because the function ends with the call, and the move a0,s0 was scheduled into... the jal's delay slot would be ideal. Mine has nop.

Could the compiler have emitted `move a0,s0` but the disassembler shows nop because... the word at 920 is 00000000 nop. No.

Let me look at the source: `((void (*)(s32))func_80146C3C)(s0);`. In the ORIGINAL (with pin), target has move a0,s0. Without pin, the only change is s0 is no longer a hard reg. Could it be that the lever-free `s0` got allocated to $4 (a0) and the prologue `move s0,a0` is actually `move $4,$4`? But line 4 shows `00808021 move s0,a0` = addu $16,$4,$0. So $16.

I'm going in circles. Let me directly test a candidate variant where the last line is `func_80146C3C((u8 *)s0);` (plain call, no cast) and see. Actually the call cast is a lever (call-site return-type cast) — the brief says levers of other kinds may stay but never added. Removing it is fine (it's not required). Let me try plain `func_80146C3C((u8 *)s0);`.

Actually, maybe the reason is: the cast `((void (*)(s32))func_80146C3C)(s0)` with the pin made it a hard-reg move; without pin, GCC's expand_call sees the function as taking s32 and the arg s0... still needs move.

Hmm, let me reconsider: maybe the arg is passed in a0 because the variable `s0` was coalesced into a0 by the *global allocator*? No, $16 is saved/restored, so s0 is $16.

Let me just experiment. Let me try variants:
V1: separate `u` for unk50 (as reasoned) — should fix v0/v1.
V2: V1 + plain call `func_80146C3C((u8 *)s0);`.
V3: V1 + keep cast.

Let me generate and score V1 and V2.

Actually first, let me understand the missing move. Perhaps in mine, the last statement `((void(*)(s32))func_80146C3C)(s0)` is compiled such that the call is at 91c but the `move a0,s0` got deleted because... the compiler determined `s0` is dead and a0 was... 

You know what? Let me test whether the current nopin.c is semantically the same as orig by checking if the final call has the move when I keep the cast but remove only the barrier. Actually let me just look: does the target (build baseline, which has the pin) have `move a0,s0`? Yes per the diff. And in the original with pin, `s0` is `register ... __asm__("$16")`, so the move is `move a0,$16` = `move a0,s0`. Fine.

For the lever-free body, GCC has to move s0 ($16) to a0. It didn't. This strongly suggests GCC allocated the *argument pseudo* to a0 and the s0 variable to... no.

Let me look at the cc1 dump / RTL. Use tools/cc1_dumps_tu.sh? That dumps for a TU. Hmm.

Alternatively: maybe the call `((void (*)(s32))func_80146C3C)(s0)` is being optimized: since func_80146C3C is declared `extern void func_80146C3C(u8 *a0);`, the cast to `(void(*)(s32))` and call with s0... GCC 2.7.2 might handle it. But the move is required.

Wait wait. Let me re-read the disassembly: at 8fc `sw a1,48(s0)` then 900 jal func_800233CC with delay `andi a1,a1,0xffff`. Then 908 lw v0,28(s0); 910 addiu v0,v0,1; 914 j; 918 sw v0,28(s0) [delay]; 91c jal func_80146C3C; 920 nop; 924 epilogue.

Between 900 and 91c, is a0 set? At 8f0 `lui a0,0`, 8f4 `addiu a0,a0,0` — a0 = &D_800CD7A4 (arg to func_800233CC at 900). Then func_800233CC returns, a0 is caller-saved (clobbered by the callee). So at 91c, a0 is garbage. Mine passes garbage.

Unless... the callee func_800233CC's return keeps a0? No.

So the lever-free body is genuinely miscompiled? That would be a GCC bug triggered by the cast. Hmm, but score 7 means shape matches except regs — and a missing move vs nop is only 1 diff. If it's a miscompile, that's fine for scoring purposes; we just need shape.

But actually, could it be that the compiler DID move a0,s0 but the *disassembler* shows nop because the move was placed at 8fc's... no.

Let me test: remove the cast (plain call). Then GCC knows func_80146C3C(u8*). Let me try.

Let me create variants and score them with sc.sh.
