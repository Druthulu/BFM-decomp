---
ts: 2026-10-17T13:50:11.230Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
That base.c output is a bit confusing, but I'll set it aside since the score there is presumably zero anyway. The key thing is the target loads D_80126B78 twice, reloading it after the store to obj+0x14 — the barrier forces that reload, while without it the compiler would just reuse the cached value via CSE.

So the question is whether gcc 2.7's CSE treats a store through a non-symbol pointer as invalidating a load from a fixed symbol address. The store here is a u16 write to obj+0x14, and since there's no type-based aliasing in this compiler, I'd expect any pointer store to potentially clobber all memory, including loads of D_80126B78 — but the actual behavior suggests CSE might special-case symbol-based addresses differently from register-based ones when checking aliasing.

In my output, the load of D happens once early and gets reused twice, but the target reloads D twice — once before the store and once after. I need to figure out how to force a genuine reload of D_80126B78's value after the store, maybe by expressing the second access through a different address form that CSE can't recognize as the same expression, even though it resolves to the same symbol_ref memory location.

What's stopping CSE from invalidating that cached value after the u16 store happens? I'm thinking it may be because CSE treats the store address as "varying" (register-based) while the cached memory reference is tied to a fixed symbol, and under GCC 2.7's memory classification rules, a store into a struct field might not be considered aliasing with a scalar reference, which would explain why the stale value survives.
