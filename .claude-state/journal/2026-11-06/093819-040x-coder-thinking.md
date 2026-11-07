---
ts: 2026-11-06T16:38:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kDWkH0YsgxmXd2PIZi4s
---
All 5. (h08 identical to c38 probably.)

Time 09:37:48. Need 09:47. Let me do a few more probes to genuinely explore, then write up. 

One more idea for the cross-jump: what if the two blocks differ in the *delay slot* of one call? In target all delay slots are nops except `move a0,zero`. The sched1 fills `move a0,zero` into the last call's slot. What if in block A we reorder the *arguments* so that a different insn fills a slot... changes bytes.

Another: what if we make block A's `func_800D2D44(0)` call use a different function with the same address via a cast of a symbol? no.

Let me test whether the merge is sensitive to a *line note* difference: put a blank line or comment inside block A (comments don't reach RTL; line notes are skipped by cross-jump: `prev_nonnote_insn`). Already no effect.

What about a `#pragma`? no.

I'll now consider the possibility that the target was compiled with cross-jumping *disabled* for this function, e.g., because the function is large? No, other parts of the function show cross-jump behavior? Actually maybe cross-jump doesn't merge because of the *function's size*: cross-jump compares at most... `find_cross_jump` has no size limit, but `do_cross_jump`... Hmm.

Wait, actually: maybe in the target the two blocks are NOT identical because the register allocator assigned a *different* register in one of them? Let me check the target bytes exactly for both blocks. From target.s:
A: 158 jal, 15c move a0,zero, 160 jal, 164 nop, 168 jal, 16c nop, 170 jal, 174 move a0,zero, 178 j, 17c nop
B: 198 jal, 19c move a0,zero, 1a0 jal, 1a4 nop, 1a8 jal, 1ac nop, 1b0 jal, 1b4 move a0,zero, 1b8 j, 1bc nop

Identical except the j target (both 0x554). So the original binary has them unmerged. With gcc 2.7.2 -O2 and cross-jump on, identical blocks merge. Unless... cross-jump only runs at `-O2` with `cross_jump=2`, and maybe this TU is compiled at `-O1`? But then our barrier wouldn't matter either. Our test shows removing the barrier merges them, so cross-jump IS on in the recipe. Therefore the original source had a blocker. The blocker is invisible in bytes → an asm or something that emits an RTL insn with no bytes. In gcc 2.7.2, `asm("")` emits an `asm_operands` insn with no output → zero bytes. That's exactly our barrier. So the original source likely had `asm("")` there too — meaning the "lever" is actually part of the original code! In that case the barrier is NOT a fake; it's a genuine source feature. But the task defines it as a lever to remove.

Hmm, interesting: if the original had an asm, then this function cannot be lever-free. WALL confirmed with strong evidence.

Actually wait — another zero-byte RTL insn in gcc 2.7.2: a `(void)` cast of a volatile? No. Or a `NOTE_INSN_...`? Notes are skipped by cross-jump. Or a `USE`/`CLOBBER`? Those are inside patterns.

There's also `__builtin_constant_p`? folds. 

And there's the "empty statement" — nothing.

So yes: an empty asm in the original. The task's premise (that all levers are fakes) fails for this one. WALL.

Let me also double-check the keepalive: `li v0,1` at the end. If the original source had `return 1;` with an int return, the caller would use it. The caller (func_800D1E58) ignores the return. The extern decl is `void`. So the decomp author chose void. The original probably returned s32. So both the barrier and the keepalive are genuine source features. This is a "not plain C" item. Good.

Time: 09:38. Need 9 more minutes. Let me start preparing item 2's fresh check and orig while I wait? That's allowed — I'm still within item 1's time budget but working ahead is fine; the rule is a minimum per item, not exclusive. Actually, better to be honest: the 20-min rule is to prevent premature walls. I've done 65 tries and found a solid mechanism. Let me do a couple more genuinely new attempts, then at 09:47 write up.

New attempt idea: what if we block cross-jump by making the two `goto ret` jumps go to labels with *different* addresses by putting `ret2:` one instruction *earlier*, e.g., before the `func_80059658(1)` in the `after:` block? That would make block B jump to an earlier address that then falls through the after-block — changes semantics/bytes. No.

Another: make block B's goto a `goto after;` and duplicate the tail? Changes bytes.

Another idea: make the two blocks' *call targets* differ in RTL by calling one through a local function pointer initialized to the function? Emits indirect call (jalr) — bytes differ.

Another: exploit that cross-jump compares CALL_INSN_FUNCTION_USAGE. If in block A we cast the callee to a *different prototype* that changes the FUNCTION_USAGE (e.g., `((void (*)(s32)) func_800D2D44)(0)` vs `func_800D2D44(0)`), the usage list is the same (a0 used). Tried d01 → merged.

What if the prototype difference changes the *argument mode* (e.g., `((void (*)(s16)) func_800D2D44)(0)`)? The arg is const 0 in HImode vs SImode → the call setup might emit `move a0,zero` either way (0 is 0). But the FUNCTION_USAGE would have `(use (reg:HI 4))` vs `(use (reg:SI 4))` → different RTL → cross-jump blocked! And the bytes might be identical (`move a0,zero`). Let's test this! In gcc, passing an s16 argument in a register: the arg is promoted to int? For a K&R/old-style call through a prototype `void (*)(s16)`, the arg is converted to s16 (HImode) then passed in a SImode register with sign extension... Actually MIPS O32 passes s16 in a0 as SImode after sign-extension; the RTL would be `(sign_extend:SI (reg:HI ...))` or a HImode use. The emitted `move a0,zero` is the same for 0.

Let me try:
- i01: block A: `((void (*)(s16)) func_800D2D44)(0);`
- i02: block A: `((void (*)(u8)) func_800D2D44)(0);`
- i03: block A: `((void (*)(s32)) func_800D2D44)(0);` (control)
- i04: same for func_800D2AA0 with `((void (*)(s16)) func_800D2AA0)(0)`
- i05: `((void (*)(u8*)) func_800D2AA0)(0)` control

If i01 blocks the merge and emits identical bytes → score 1! Let's test. This is a real-C cast (no lever).

Also for func_800D2AA0 (u8* arg), casting to (s16) changes mode.

Let me run.
