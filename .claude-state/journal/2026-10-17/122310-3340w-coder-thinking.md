---
ts: 2026-10-17T18:23:10.058Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a52573749b6b447df
model: claude-opus-5-5[1m]
effort: medium
turnId: 4acf539d-de7f-427e-9730-d2f03f4cf395
---
I'm comparing register allocation differences between my version and the reference, particularly how v1 versus a3 gets assigned for the shifted value in that multiply sequence.

I'm now considering whether a second "launder" copy of divisor into v1 could trip up CSE in the right way, trying to figure out how CSE in this older gcc chooses between pseudo and hard register equivalences when substituting divisor for v1.

Actually, it looks more like combine is the culprit, not CSE—combine is folding the copy from a0 into v1 directly into the multiply because v1 dies right after that use. I'm trying to find a way to give v1 a genuine second use so combine can't merge the copy away, but any real second use would alter the generated code, so I'm stuck on whether there's a trick involving v1's liveness across the loop.

I'm wondering if divisor is loaded via a sign-extend that combine could misinterpret as a move, though that doesn't match a multiply operation. Maybe the pin on the divisor register is actually forcing this combine behavior, and since I'm only allowed to launder (not add) pins, I could try removing that pin to see if it changes the outcome. Now I'm checking the a3 pin to see how it connects to v0.

I'm wondering whether combine can track the sign-bit copies of a hard register like $4 across basic blocks, since reg_sign_bit_copies is usually only computed for pseudos set once. If it can't, the cast would just emit explicit shift instructions instead of folding into a move, so I'm sketching a few variants to test: casting divisor to s16 directly, storing it into a separate s16 temp first, or casting inline at the multiply site.
