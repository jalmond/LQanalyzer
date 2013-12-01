{
  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();
  gStyle->SetPalette(1);
  gROOT->ProcessLine(".L multiplot.C++");
  multiplot();
}
