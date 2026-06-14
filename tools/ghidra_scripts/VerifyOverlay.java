// VerifyOverlay.java — read-only R9 check that the imported overlay/resident bytes persisted.
//   analyzeHeadless ... -process SLUS_007.26 -noanalysis -readOnly -postScript VerifyOverlay.java
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;

public class VerifyOverlay extends GhidraScript {
    public void run() throws Exception {
        String[][] t = { {"residentBlob","0x800CEDF8"}, {"ovl_tutForest","0x80128158"} };
        for (String[] e : t) {
            Address a = toAddr(e[1]);
            byte[] c = new byte[8];
            currentProgram.getMemory().getBytes(a, c);
            StringBuilder sb = new StringBuilder();
            for (byte x : c) sb.append(String.format("%02x", x));
            boolean init = currentProgram.getMemory().getBlock(a).isInitialized();
            println("BFMVERIFY " + e[0] + " @" + a + " init=" + init + " first8=" + sb);
        }
    }
}
