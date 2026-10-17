---
ts: 2026-10-17T06:20:11.426Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm classifying several addresses as scratch registers written by assembly output rather than incoming parameters, including the mfhi output at 80029E30, the pm output at 800CEF50, and the triplicated arg1 copy-in at 80136824.

Several more are tricky: 8017E210's $7 appears to be used in a macro reading an uninitialized param while callers load a global, suggesting a possibly 4-param signature I need to verify later; the asm-written $5 cases at 8018C000, 80188C68, 80189540, and 80189240 are clear scratch writes; 8017BF14's $4 is likely scratch via the CLAMP80S macro; and 8017F0AC and 80180FA4 both involve reads of registers that callers set from values or constants, which need more investigation before I can classify them confidently.

Now I'm checking 8018107C, where the pinned temp just mirrors the existing third parameter, so the fix is to drop the redundant pin and use the parameter directly. Then I note that 8014E048 and several other addresses (80166054, 80178004, 8017EF50, 80188A18, 801ADF5C, 80015D4C) are straightforward scratch writes, and I'm starting a new list of confirmed real missing parameters beginning with 800CC024 and 800CD1A8.

There's still a long batch of uncertain addresses to classify — including possible scratch pins around a2v in func_8013B6A0 and several more functions like 8018C730, 80182334, 80151664, 80157D20 twice — plus 17 NODEF rows that need resolving. I should go check the current background status before continuing.
