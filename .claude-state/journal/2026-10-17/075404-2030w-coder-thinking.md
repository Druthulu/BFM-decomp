---
ts: 2026-10-17T13:54:04.335Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm drafting the function from scratch, starting by extracting the object pointer and calling the setup function before checking a conditional flag.

Looking at how the compiled code shares the sign-extension logic between branches, I suspect the original source assigns the angle variable inside each branch separately (either from a loaded u16 field or from masking a packed field value), then applies a shared `(s16)` cast after the if/else join, which explains why the shift instructions appear duplicated across both arms.

I'm reconstructing the field extraction (angle and shift masked from the loaded word), then working out the cosine/sine computation shifted by that value, with the sign and axis assignment depending on the mode flag, before storing the results back into the x/z offset fields. I'm testing a couple of equivalent phrasings to match the original register allocation.

Now I'm digging into a CSE-forwarding issue: the compiler is reusing the halfword store value across adjacent fields, and I'm checking whether changing the store/load types (signed vs unsigned halfword) would prevent that forwarding and match the expected codegen.

I'm wondering if cse forwards the store-to-load even when the address is expressed differently, since RTL canonicalization would still treat them as equivalent after the pointer gets reloaded into the same base register.

Actually, maybe cross-jump tail merging explains it better: if each arm stores a different value to the same offset right before converging, the compiler could merge those divergent stores into a single instruction at the join point, with the differing value set just beforehand in each arm's delay slot.

I'll write S12 modeled on the target shape: an `(s16)` narrowing after the if/else join, an `fld` local to its arm, if/else for the sign choice, and the `0x18` store duplicated in each arm so CSE can't forward it.
