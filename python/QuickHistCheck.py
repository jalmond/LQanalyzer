from ROOT import * 
import ROOT,sys


def QuickDrawHist(inputfilename,histname):

    f = ROOT.TFile(inputfilename)

    t = f.Get(histname)
    t.SetDirectory(0)
    t.AddDirectory(kFALSE)
    return t
def QuickDraw(inputfilename,histname, cutname):

    f = ROOT.TFile(inputfilename)
    
    t = f.Get(histname+"/"+cutname)
    t.SetDirectory(0)
    t.AddDirectory(kFALSE)
    #t.Draw()
    #c1.SaveAs("test.pdf")
    #os.system("display test.pdf")
    return t
import ROOT

def getall(d, basepath="/"):
    "Generator function to recurse into a ROOT file/dir and yield (path, obj) pairs"
    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            # TODO: -> "yield from" in Py3
            for i in getall(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)

def plotallhist(filename,outputfilename):
    # Demo
    ROOT.gROOT.SetBatch(True)
    f = ROOT.TFile(filename)
    
    c1 = TCanvas( 'summary'+filename, 'hist'+filename ,1600,1200)
    c1.cd()
    initial=True
    for k, o in getall(f):
        if "TH1"  in o.ClassName():
            histname= k
            histname=histname.replace("/"," ")
            splithist=histname.split()
            
            if len(splithist) == 2:
                continue
            if len(splithist) == 0:
                continue
            print filename + " " + splithist[0]
            hist=QuickDrawHist(filename, splithist[0])
            print type(hist)
            if not hist:
                sys.exit()
            hist.Draw()
            if initial:
                c1.Print(outputfilename+"(","pdf");
                initial=False
            else:
                c1.Print(outputfilename,"pdf");
                
    c1.Print(outputfilename+")","pdf");

