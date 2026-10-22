---
ts: 2026-10-21T23:43:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_SUtc7aeGZRo6zrBoDscL
---
So the tool dumps with objdump -drz, real instructions. So the ROM function truly ends with `move v0,zero; nop; nop`? That means no `jr $ra` in the listing — impossible for a function.

Unless the ROM's function ends with a jump to a shared epilogue? Hmm, at +0x90: `move v0,zero` then +0x94 `nop`, +0x98 `nop`. Branches to +0x94 → lands on a nop?! Then falls through to +0x98 nop and then... continues into the next function's code? That would be a "tail call" style: the ROM's function might end by falling through into a common epilogue in the next function's space? That's a known decomp trick in some ROMs (functions sharing epilogues) — but unusual.

Hmm, wait. Maybe the addresses: the label "+0x94" refers to func_8014C308+0x94 = ins 37 (nop). And the branches go there. Falling through to +0x98 (nop) then to the next function's start +0x9C. Hmm, that means the "return" is a fall-through into the next function, which begins with `jr $ra`? That's the classic "tail-call/shared epilogue" pattern in some MIPS ROMs.

Actually! I recall in these overlays (decomp of Breath of Fire), functions are packed and the last few instructions of a function may be shared. But more likely: the tool's extraction of the function label ends at the NEXT label, and the ROM's next label starts at +0x9C. The instructions at +0x90..+0x98 belong to this function. So indeed the return happens by falling through to the next function's `jr $ra`? That can't be — the next function would clobber.

Alternatively the ROM function ends with:
+0x90: move v0,zero   (return 0 path)
+0x94: jr $ra
+0x98: move v0,v0  (delay slot, nop-ish)
And the objdump prints `jr $ra` as "jr" and `move v0,v0`... but we see "nop" at both.

Hmm, maybe the tool's _INS_RE only captures certain mnemonics? No.

Let me just directly look at the objdump of the baseline object. I can't run objdump (not allowed). But maybe tools/ has a wrapper: `tools/asm-differ/diff.py`? or `tools/objdump`? Let me check for a python tool that dumps an object: tools/objdump*.py?

Hmm, alternatively the ROM asm is available in the repo as .s files: "splat .s" — the ROM disassembly might be in the repo (e.g. .run/P36/... or decomp-architect/corpus). Let me look for the function's asm in the repo: grep -rn "func_8014C308" --include=*.s . | head.

Let me try that.
