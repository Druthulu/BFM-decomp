---
ts: 2026-11-06T05:22:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RN41EBSc9xMmn9WBUJqs
---
Not obviously. Let me check `function.c: get_frame_size()` and whether the frame includes `current_function_pretend_args_size`. Hmm.

Actually, maybe I should look at this from a totally different angle: check the *build* object's `.frame` for all 5 target functions, and check whether the frame artifact is present in each. If all 5 have asm-artifact frames, then all 5 are likely walls (or require a C construct producing the same frame). The brief expects evidence from gcc passes.

Actually — hold on! Maybe the frame artifact is not from the memory clobber but from the **`!FAKE` barrier being the *only* statement in a block with a label**? No.

Let me just test: does an empty asm with memory clobber inside a function that has *no other asm and no locals* produce a frame? My probe said no (frame 0 for g). So the clobber alone doesn't. What's different in the real function? Let me bisect: take the nobar body, add `__asm__("" ::: "memory");` at the same position (that's orig) → frame 16. Add it at a different position → ? Add `__asm__("" ::: "memory")` to a simplified function with an extern struct array and pointer store → ?

Let me test with a small function that mimics: extern u8 D_8011F7A8; extern u16 D_800B9A02; extern struct {u32 *f0;} A[]; s32 f(void){ u8*p=(u8*)&D_8011F7A8; u16*q=(u16*)&D_800B9A02; u32*ptr=A[*q].f0; u32 old=ptr[2]; ptr[2]=old; __asm__("":::"memory"); ptr=A[*q].f0; return 0;}

Let me test with the probe harness (needs 200 lines padding). Actually the probe harness compiles a standalone .c; I can include the struct decl. Let me do it.
