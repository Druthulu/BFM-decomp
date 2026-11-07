---
ts: 2026-11-06T05:17:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rsr6cCvtf9qkMwQtlv0Q
---
The asm is `(asm_operands ("") ("") 0[ ] ... (clobber (mem:BLK (scratch))))`. That's the memory clobber. `(mem:BLK (scratch))` — the `scratch` address! In GCC, `(mem:BLK (scratch))` is a special "everything" memory reference. Maybe its handling in `get_frame_size` or stack slot allocation creates a 16-byte slot? Hmm, the scratch is not a stack slot.

Wait, let me look at the full insn 53 in orig and compare to nobar. Let me view lines 11562+120 to 11562+145.
