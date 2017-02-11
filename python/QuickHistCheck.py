from ROOT import * 
import ROOT,sys


def QuickDrawHist(inputfilename,histname, col):

    f = ROOT.TFile(inputfilename)

    t = f.Get(histname)
    t.SetDirectory(0)
    t.AddDirectory(kFALSE)
    if "cutflow" in histname:
        t.SetLineColor(col)
    else:
        t.SetLineColor(0)
        t.SetFillColor(col)
    f.Close()

    return t
def QuickDraw(inputfilename,histname, cutname):

    f = ROOT.TFile(inputfilename)
    
    t = f.Get(histname+"/"+cutname)
    t.SetDirectory(0)
    t.AddDirectory(kFALSE)
    f.Close()
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



###### MAKE PLOTS FOR JOBS: Cutflow
def plotallhist(filenames,outputfilename,collist,jobid):
    # Demo                                                                                                                                                                 
    ROOT.gROOT.SetBatch(True)
    filename=filenames[0]
    histlist= plotallhist_individual(filename,"tmp")    
    initialhist=True
    print len(histlist)
    ihist=0
    for h in histlist:
        ihist+=1
        isample=-1
        initialsample=True
        hists =[]
        for s in filenames:
            isample=isample+1
            histname= h
            print h + " "  + s
            hist=QuickDrawHist(s, histname,collist[isample])
            if not hist:
                sys.exit()
            hists.append(hist)

        c1 = TCanvas( 'summary_'+str(jobid)+h, 'hist_'+str(jobid)+h ,1600,1200)
        c1.cd()
        stack = THStack (h, h)
       
        for x in range(0,len(hists)): 
            if "cutflow" in h:
                hists[x].SetLineColor(collist[x])
            else:
                hists[x].SetFillColor(collist[x])
            stack.Add(hists[x])
        if "cutflow" in h:
            stack.Draw("histtext")
        else:
            stack.Draw("hist")

        if initialhist:
            c1.Print(outputfilename+"(","pdf");
            initialhist=False
        elif ihist < len(histlist):
            c1.Print(outputfilename,"pdf");
        else:
            c1.Print(outputfilename+")","pdf");

def plotallhist_individual(filename,outputfilename):
    # Demo
    ROOT.gROOT.SetBatch(True)
    f = ROOT.TFile(filename)
    
    c1 = TCanvas( 'summary'+filename, 'hist'+filename ,1600,1200)
    c1.cd()
    initial=True
    listhists=[]
    for k, o in getall(f):
        if "TH1"  in o.ClassName():
            histname= k
            histname=histname.replace("/"," ")
            splithist=histname.split()
            
            if len(splithist) == 2:
                continue
            if len(splithist) == 0:
                continue
            listhists.append(splithist[0])
            continue
            hist=QuickDrawHist(filename, splithist[0],1)
            if not hist:
                sys.exit()
            hist.Draw()
            if initial:
                c1.Print(outputfilename+"(","pdf");
                initial=False
            else:
                c1.Print(outputfilename,"pdf");
    f.Close()            
    return listhists            
    c1.Print(outputfilename+")","pdf");

