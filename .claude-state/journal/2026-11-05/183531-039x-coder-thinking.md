---
ts: 2026-11-06T01:35:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1GBQwqpZdkDoh3Mq3uKt
---
Note: `if (GET_CODE (p1) != USE && GET_CODE (p1) != CLOBBER) { ... --minimum; }` — so minimum starts at 1 and each matched insn decrements; after 1 match minimum=0 → merge. Yes.

So to prevent, the single matched insn must not match. Since regs are hard at jump2, we need the *instructions* to differ. But target has them identical... 

Unless! In the target, the epilogue label's preceding real insn at jump2 is not zero's sw. What if in the target build, zero's block's `sw` is followed by a `barrier` or the label is at a different place? Actually, the target's zero block might not fall through into the epilogue label in the RTL sense: maybe zero's block ends with an explicit jump too, which reorg later converts to fallthrough by deleting the jump when the target is the next block! Yes! That's the key: In the target source, both zero and dec end with explicit `j .Lepilogue` (the C compiler emits a jump at the end of each return block). Then reorg (or jump2's jump-to-next optimization) deletes zero's jump because the epilogue is the next block, leaving fall-through. At jump2 time, zero's block ends with `sw; j .Lepilogue`, and dec's block ends with `sw; j .Lepilogue`. Now find_cross_jump compares e1 (dec's jump) with the label: i1 = sw (prev of dec's jump), i2 = prev of label = ... the insn before the label is zero's *jump*, not its sw! Because zero's jump is between its sw and the label. So i1=sw vs i2=jump → differ. Then the "jump_chain" loop: it tries other jumps to the same label: target = zero's jump, find_cross_jump(insn=dec's jump, target=zero's jump, minimum=2). Compare i1 = prev of dec's jump = sw; i2 = prev of zero's jump = sw → match (minimum 2→1), continue: i1 = addiu, i2 = sh → differ. minimum=1 > 0 → no merge! 

So the real-C shape: zero's block must end with an explicit jump (i.e., the epilogue must not be the fall-through *at jump2 time*, or zero must not be the physical predecessor). In C, `return;` at the end of the zero block emits a jump to the epilogue. Our current C also has `return;` at the end of zero (the code is `...; unk1C = 0x1D;` then `}` — the function's closing brace? No! In the current C, the `zero:` block does NOT have a return; it falls off the end of the function (the function ends right after the zero block's statements). Let me re-read:

```
zero:
    if (func_80185D3C(a0,1) == 0) {
        func_8012B178(...);
        func_8012CBA4(a0);
    }
    func_8012B200((u8*)a0);
    CAST_WIDTH(s16,a0,0xF4)=0;
    ((Unk*)a0)->unk1C = 0x1D;
    /* barrier */
}
```

Yes — zero falls through to the function end. All other paths `return;`. So zero has no explicit jump; it's the last block. dec has `return;` → jump to the epilogue (shared function exit). At jump2: dec's jump, label = function epilogue; i2 = prev of label = zero's sw (since zero falls through) → match → merge.

So the real-C shape likely has zero ALSO end with a `return;`! i.e., add `return;` after the unk1C store. Then zero's block ends with `j epilogue` too. At jump2, both blocks end with a jump, and the label's prev is zero's jump, so the first call (minimum 1) fails (sw vs jump), then the jump_chain call with minimum=2 compares sw/sw (1 match, minimum 1) and then addiu vs sh differ → no merge. Then reorg/jump-to-next deletes zero's jump (since epilogue follows) → fall-through, and dec's jump gets its delay slot filled with the store.

That's exactly the target! And the added `return;` at the end of zero produces no extra instruction after the jump-to-next deletion. 

But wait: would adding `return;` change the source semantics? No, zero is at the end of the function; adding return is equivalent.

However, will the compiler emit a jump for a `return;` at the end of a void function? Yes, expand_return emits a jump to the epilogue label (in gcc 2.7.2, returns jump to the common exit label). Actually for a void function with `return;`, expand_null_return emits `emit_jump (return_label)` unless it's the last statement... Let me check: in gcc, a `return;` at the very end of the function body is optimized: "expand_null_return_1" has code: if this is the last statement of the function, it might not emit a jump? There's a check `if (this_function... )`. Actually in stmt.c expand_null_return_1: it emits a jump to return_label. And the epilogue is placed at return_label. So there will be a jump even at the end? Let me check gcc 2.7.2 stmt.c.

But note other blocks in this function end with `return;` and they DO get jumps to the epilogue (e.g., the first blocks' `return;` compile to j 180c). And the last block zero currently falls through. If we add `return;`, will it emit j 180c? Likely yes (it's not smart enough to know it's last, or it is but the return label placement makes it a jump anyway).

Let's test this hypothesis right away. Variant vA: add `return;` after the store in zero.

Let me create it and score.
