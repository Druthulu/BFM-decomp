// DumpFunctionSignatures.java — headless, READ-ONLY: dump a per-function fingerprint
// for cross-binary correspondence (Phase 3.5 proto<->retail diff). Three tiers so the
// match count is bracketed and trustworthy even if the middle tier is imperfect:
//
//   h_exact : SHA1 of the raw instruction bytes (strict; same bytes, usually same addr).
//   h_norm  : SHA1 of a MIPS-normalized instruction stream that neutralizes ONLY the
//             address/relocation-sensitive fields (j/jal absolute targets, lui high
//             halves, %lo / gp-relative address immediates detected via Ghidra's
//             analyzed references) and rewrites branch targets as PC-relative offsets,
//             while KEEPING registers (regalloc matters) and true constants. This is the
//             "same source compiled to a different address" workhorse.
//   h_seq   : SHA1 of the mnemonic-only sequence (loose; same ops, any regalloc/consts).
//
// Also emits nins, nbytes, ncalls and the ORDERED list of direct-call target addresses
// (for the T4 anchor-bootstrap call-graph BFS). The PSX loader emits no relocations, so
// normalization is derived from the analyzed disassembly, not a reloc table.
//
//   analyzeHeadless ~/bfm-decomp/ghidra bfm -process <PROG> -noanalysis -readOnly \
//     -scriptPath ~/bfm-decomp/tools/ghidra_scripts -postScript DumpFunctionSignatures.java
//
// Output: ~/bfm-decomp/.run/sig.<PROG>.jsonl  (gitignored; R12 — never /tmp).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.RefType;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.util.ArrayList;

public class DumpFunctionSignatures extends GhidraScript {

    private static String hex(byte[] b) {
        StringBuilder sb = new StringBuilder(b.length * 2);
        for (byte x : b) sb.append(Character.forDigit((x >> 4) & 0xF, 16)).append(Character.forDigit(x & 0xF, 16));
        return sb.toString();
    }

    private static String jsonEsc(String s) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '"' || c == '\\') sb.append('\\').append(c);
            else if (c < 0x20) sb.append(String.format("\\u%04x", (int) c));
            else sb.append(c);
        }
        return sb.toString();
    }

    // Normalized token for one instruction: mnemonic + per-operand canonical form.
    private String normToken(Instruction ins) {
        StringBuilder sb = new StringBuilder();
        String m = ins.getMnemonicString();
        sb.append(m);
        String ml = m.toLowerCase();
        boolean isAbsJump = ml.equals("j") || ml.equals("jal");   // J-type absolute target
        int nops = ins.getNumOperands();
        for (int i = 0; i < nops; i++) {
            sb.append('|');
            Reference[] refs = ins.getOperandReferences(i);
            boolean flowRef = false, dataRef = false;
            Address flowTgt = null;
            for (Reference r : refs) {
                RefType rt = r.getReferenceType();
                if (rt.isFlow()) { flowRef = true; flowTgt = r.getToAddress(); }
                if (rt.isData() || rt.isRead() || rt.isWrite()) dataRef = true;
            }
            Object[] objs = ins.getOpObjects(i);
            boolean hasGp = false;
            for (Object o : objs)
                if (o instanceof Register && ((Register) o).getName().equals("gp")) hasGp = true;

            // Direct flow target operand.
            if (flowRef && flowTgt != null) {
                if (isAbsJump) sb.append("@J");                                  // absolute j/jal -> neutralize
                else sb.append("rel").append(flowTgt.subtract(ins.getAddress())); // PC-relative branch -> keep offset
                continue;
            }
            // lui: the immediate is the high half of an address (PSX convention) -> neutralize.
            if (ml.equals("lui")) {
                for (Object o : objs) {
                    if (o instanceof Register) sb.append(((Register) o).getName()).append(',');
                    else if (o instanceof Scalar) sb.append("@HI,");
                    else sb.append("?,");
                }
                continue;
            }
            // Generic operand: keep registers + true constants; neutralize address immediates.
            for (Object o : objs) {
                if (o instanceof Register) {
                    sb.append(((Register) o).getName()).append(',');
                } else if (o instanceof Scalar) {
                    if (dataRef || hasGp) sb.append("@LO,");                     // %lo / gp-relative address
                    else sb.append(Long.toString(((Scalar) o).getValue())).append(','); // true constant
                } else if (o instanceof Address) {
                    sb.append("@A,");                                            // resolved absolute address operand
                } else {
                    sb.append(o.toString()).append(',');
                }
            }
        }
        return sb.toString();
    }

    @Override
    public void run() throws Exception {
        Listing listing = currentProgram.getListing();
        String prog = currentProgram.getName();
        Path out = Paths.get(System.getProperty("user.home"), "bfm-decomp", ".run", "sig." + prog + ".jsonl");
        Files.createDirectories(out.getParent());

        StringBuilder file = new StringBuilder();
        FunctionIterator fns = currentProgram.getFunctionManager().getFunctions(true);
        int nfuncs = 0;
        while (fns.hasNext()) {
            Function f = fns.next();
            if (f.isExternal() || f.isThunk()) continue;
            MessageDigest mdE = MessageDigest.getInstance("SHA-1");
            MessageDigest mdN = MessageDigest.getInstance("SHA-1");
            MessageDigest mdS = MessageDigest.getInstance("SHA-1");
            int nins = 0, nbytes = 0;
            ArrayList<String> calls = new ArrayList<>();
            for (Instruction ins : listing.getInstructions(f.getBody(), true)) {
                byte[] raw;
                try { raw = ins.getBytes(); } catch (Exception e) { raw = new byte[0]; }
                mdE.update(raw);
                mdN.update(normToken(ins).getBytes("UTF-8"));
                mdN.update((byte) '\n');
                mdS.update(ins.getMnemonicString().getBytes("UTF-8"));
                mdS.update((byte) ' ');
                nins++;
                nbytes += ins.getLength();
                if (ins.getFlowType() != null && ins.getFlowType().isCall()) {
                    for (Reference r : ins.getReferencesFrom())
                        if (r.getReferenceType().isCall()) calls.add(r.getToAddress().toString());
                }
            }
            String src = (f.getSymbol() != null) ? f.getSymbol().getSource().toString() : "UNKNOWN";
            StringBuilder cj = new StringBuilder();
            for (int i = 0; i < calls.size(); i++) {
                if (i > 0) cj.append(',');
                cj.append('"').append(calls.get(i)).append('"');
            }
            file.append("{\"addr\":\"0x").append(f.getEntryPoint().toString())
                .append("\",\"name\":\"").append(jsonEsc(f.getName()))
                .append("\",\"src\":\"").append(src)
                .append("\",\"nins\":").append(nins)
                .append(",\"nbytes\":").append(nbytes)
                .append(",\"ncalls\":").append(calls.size())
                .append(",\"h_exact\":\"").append(hex(mdE.digest()))
                .append("\",\"h_norm\":\"").append(hex(mdN.digest()))
                .append("\",\"h_seq\":\"").append(hex(mdS.digest()))
                .append("\",\"calls\":[").append(cj).append("]}\n");
            nfuncs++;
        }
        Files.write(out, file.toString().getBytes("UTF-8"));
        println("BFMSIG wrote " + nfuncs + " function signatures -> " + out);
    }
}
