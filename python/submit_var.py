def  SetUpParserVar(soptions, number_of_cores, setjobs, setnumber_of_cores, tmp_filename, sample, channel, cycle, sendmail, logstep, loglevel, runnp, runtau, runcf, queue, tagger, useremail, tree, number_of_events_per_job, skipev, dataType, totalev, xsec, tar_lumi, eff_lumi, data_lumi, catversion, Finaloutputdir, remove_workspace, useskinput, runevent, tmplist_of_extra_lib, DEBUG, useskim, skflag, usebatch, runinbkg, quick_draw, tmpsubmit_allfiles, submit_allfiles ):

    options = soptions
    
    print options.jobs + "sss"
    number_of_cores = int(options.jobs)

    setjobs         = options.setnjobs
    setnumber_of_cores=False
    if setjobs== "true":
        setnumber_of_cores=True

    tmp_filename=options.tmpfilename
    if options.tmpfilename =="":
        tmp_filename="None"
    sample = options.period
    channel = options.stream
    cycle = options.cycle
    sendmail=options.sendmail
    logstep = int(options.logstep)
    loglevel = options.loglevel
    runnp = options.runnp
    runtau = options.runtau
    runcf = options.runcf
    queue = options.queue
    tagger= options.tagger
    useremail=options.useremail
    tree = options.tree
    number_of_events_per_job= int(options.nevents)
    skipev = int(options.skipevent)
    dataType = options.datatype
    totalev = int(options.totalev)
    xsec = float(options.xsec)
    tar_lumi = float(options.targetlumi)
    eff_lumi = float(options.efflumi)
    data_lumi = options.data_lumi
    catversion = options.catversion
    Finaloutputdir = options.outputdir
    remove_workspace=options.remove
    useskinput=options.skinput
    runevent= options.runevent
    tmplist_of_extra_lib=options.LibList
    DEBUG = options.debug
    useskim = options.useskim
    skflag = options.skflag
    usebatch =options.usebatch
    runinbkg=options.bkg
    quick_draw=options.drawhists
    tmpsubmit_allfiles=options.submitallfiles
    submit_allfiles=False
