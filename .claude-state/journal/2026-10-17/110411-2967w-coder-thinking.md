---
ts: 2026-10-17T17:04:11.435Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm realizing the andi persists because MIPS's PROMOTE_MODE zero-extends u8 locals to SImode when stored in registers, which explains that behavior. But for a signed 16-bit local kept in s0, the compiler instead uses explicit sll/sra shifts rather than relying on sign-extended promotion, suggesting gcc 2.7 handles that promotion differently.

I'm trying to find a way to compute the narrowed index without introducing an extra variable — something like casting the result of an arithmetic expression directly to u8 so the truncation happens inline rather than via a separate assignment. The issue is that convert_to_integer only narrows PLUS/MINUS/MULT expressions under certain conditions on operand types, so whether the sign-extension gets shared with the index computation depends on exactly how the narrowing conversion is applied during assignment versus inline casting.

Let me try testing a handful of these expression spellings directly in the store statements, without the intermediate variable.
