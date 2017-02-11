/* These Efficiencies have been derived for Summer15ttbar events and should 
   be used only for the same MC samples or for events with similar topology */  


float BTagSFUtil::TagEfficiencyB(float JetPt, float JetEta) {
  
  
  if (TaggerOP=="CSVv2M") { 
    if (JetPt > 20.00000 && JetPt <= 40.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.59234 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.57961;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.52772;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.43535;  
    } 
    else if (JetPt > 40.00000 && JetPt <= 60.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.66022 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.64971;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.60206;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.52218;  
    } 
    else if (JetPt > 60.00000 && JetPt <= 80.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.68184 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.67571;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.62020;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.53328;  
    } 
    else if (JetPt > 80.00000 && JetPt <= 100.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.68998 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.68509;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.63066;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.53861;  
    } 
    else if (JetPt > 100.00000 && JetPt <= 120.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.68730 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.68463;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.61622;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.52498;  
    } 
    else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.66520 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.66545;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.59499;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.51355;  
    } 
  } 
  if (TaggerOP=="CSVv2T") { 
    if (JetPt > 20.00000 && JetPt <= 40.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.59234 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.57961;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.52772;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.43535;  
    } 
    else if (JetPt > 40.00000 && JetPt <= 60.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.66022 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.64971;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.60206;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.52218;  
    } 
    else if (JetPt > 60.00000 && JetPt <= 80.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.68184 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.67571;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.62020;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.53328;  
    } 
    else if (JetPt > 80.00000 && JetPt <= 100.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.68998 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.68509;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.63066;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.53861;  
    } 
    else if (JetPt > 100.00000 && JetPt <= 120.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.68730 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.68463;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.61622;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.52498;  
    } 
    else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.66520 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.66545;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.59499;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.51355;  
    } 
  } 
  return 1.;
}

float BTagSFUtil::TagEfficiencyC(float JetPt, float JetEta) {
  
  
  if (TaggerOP=="CSVv2M") { 
    if (JetPt > 20.00000 && JetPt <= 40.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.12617 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.11974;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.11290;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.08717;  
    } 
    else if (JetPt > 40.00000 && JetPt <= 60.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.12341 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.11844;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.11937;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.09907;  
    } 
    else if (JetPt > 60.00000 && JetPt <= 80.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.12777 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.12588;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.12337;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.10186;  
    } 
    else if (JetPt > 80.00000 && JetPt <= 100.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.13114 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.13176;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.12900;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.10778;  
    } 
    else if (JetPt > 100.00000 && JetPt <= 120.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.13586 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.13863;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.12548;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.10638;  
    } 
    else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.13414 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14295;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.13146;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.12254;  
    } 
  } 
  if (TaggerOP=="CSVv2T") { 
    if (JetPt > 20.00000 && JetPt <= 40.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.12617 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.11974;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.11290;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.08717;  
    } 
    else if (JetPt > 40.00000 && JetPt <= 60.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.12341 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.11844;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.11937;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.09907;  
    } 
    else if (JetPt > 60.00000 && JetPt <= 80.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.12777 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.12588;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.12337;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.10186;  
    } 
    else if (JetPt > 80.00000 && JetPt <= 100.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.13114 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.13176;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.12900;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.10778;  
    } 
    else if (JetPt > 100.00000 && JetPt <= 120.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.13586 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.13863;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.12548;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.10638;  
    } 
    else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.13414 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14295;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.13146;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.12254;  
    } 
  } 
  return 1.;
}
float BTagSFUtil::TagEfficiencyLight(float JetPt, float JetEta) {
  
  if (TaggerOP=="CSVv2M") { 
    if (JetPt > 20.00000 && JetPt <= 40.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00953 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01103;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01286;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01357;  
    } 
    else if (JetPt > 40.00000 && JetPt <= 60.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00690 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00841;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01088;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01451;  
    } 
    else if (JetPt > 60.00000 && JetPt <= 80.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00656 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00807;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.00992;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01298;  
    } 
    else if (JetPt > 80.00000 && JetPt <= 100.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00685 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00847;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01069;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01411;  
    } 
    else if (JetPt > 100.00000 && JetPt <= 120.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00675 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00837;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.00987;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01367;  
    } 
    else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00816 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01119;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01543;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.02225;  
    } 
  } 
  
  if (TaggerOP=="CSVv2T") { 
    if (JetPt > 20.00000 && JetPt <= 40.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00953 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01103;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01286;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01357;  
    } 
    else if (JetPt > 40.00000 && JetPt <= 60.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00690 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00841;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01088;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01451;  
    } 
    else if (JetPt > 60.00000 && JetPt <= 80.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00656 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00807;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.00992;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01298;  
  } 
    else if (JetPt > 80.00000 && JetPt <= 100.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00685 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00847;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01069;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01411;  
    } 
    else if (JetPt > 100.00000 && JetPt <= 120.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00675 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00837;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.00987;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01367;  
    } 
    else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
      if      (fabs(JetEta) > 0.00000   && fabs(JetEta) <= 0.60000) return 0.00816 ;  
      else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01119;  
      else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01543;  
      else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.02225;  
    } 
  } 
  return 1.;
}
