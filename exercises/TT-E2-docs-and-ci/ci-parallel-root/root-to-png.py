import os
import sys
import ROOT

# Usage:
#   python3 root-to-png.py plots/merged_histograms_<name>.root
#
# Output:
#   plots/merged_histograms_<name>.png

if len(sys.argv) < 2:
    raise ValueError("Pass a ROOT file path as argv[1].")

infile = sys.argv[1]
if not os.path.exists(infile):
    raise FileNotFoundError(f"Input ROOT file not found: {infile}")

outpng = os.path.splitext(infile)[0] + ".png"

f = ROOT.TFile.Open(infile)
if not f or f.IsZombie():
    raise RuntimeError(f"Failed to open ROOT file: {infile}")

# In merged output, histogram name stays the same (h_M_Hyy)
hist = f.Get("h_M_Hyy")
if not hist:
    raise RuntimeError("Histogram 'h_M_Hyy' not found in merged ROOT file.")

c = ROOT.TCanvas("c", "merged", 900, 700)
hist.Draw("E")
c.SetLogy()
c.SaveAs(outpng)

print(f"Wrote {outpng}")
