#include "BTagCalibrationStandalone.h"
#include <iostream>
#include <exception>
#include <algorithm>
#include <sstream>


BTagEntry::Parameters::Parameters(
				  OperatingPoint op,
				  std::string measurement_type,
				  std::string sys_type,
				  JetFlavor jf,
				  float eta_min,
				  float eta_max,
				  float pt_min,
				  float pt_max,
				  float discr_min,
  float discr_max
				  ):
  operatingPoint(op),
  measurementType(measurement_type),
  sysType(sys_type),
  jetFlavor(jf),
  etaMin(eta_min),
  etaMax(eta_max),
  ptMin(pt_min),
  ptMax(pt_max),
  discrMin(discr_min),
  discrMax(discr_max)
{}

BTagEntry::BTagEntry(const std::string &csvLine)
{
  // make tokens

  std::stringstream buff(csvLine);
  std::vector<std::string> vec;
  std::string token;
  while (std::getline(buff, token, ","[0])) {
    token = BTagEntry::trimStr(token);
    if (token.empty()) {
      continue;
    }
    vec.push_back(token);
  }

  if (vec.size() != 11) {
    std::cerr << "ERROR in BTagCalibration: "
	      << "Invalid csv line; num tokens != 11: "
	      << csvLine;
    throw std::exception();
  }

  // clean string values
  char chars[] = " \"\n";
  for (unsigned int i = 0; i < strlen(chars); ++i) {
    vec[1].erase(remove(vec[1].begin(),vec[1].end(),chars[i]),vec[1].end());
    vec[2].erase(remove(vec[2].begin(),vec[2].end(),chars[i]),vec[2].end());
    vec[10].erase(remove(vec[10].begin(),vec[10].end(),chars[i]),vec[10].end());
  }

  // make formula
  formula = vec[10];
  TF1 f1("", formula.c_str());  // compile formula to check validity
  if (f1.IsZombie()) {
    std::cerr << "ERROR in BTagCalibration: "
	      << "Invalid csv line; formula does not compile: "
	      << csvLine;
    throw std::exception();
  }



  // make parameters
  std::vector<int> vec_i;
  for(unsigned int istoi=0; istoi < vec.size(); istoi++)
    { 
      std::istringstream stoi_x(vec[istoi]);
      int i_stoi_x;
      stoi_x >> i_stoi_x;
      vec_i.push_back(i_stoi_x);
  }
  std::vector<int> vec_f;
  for(unsigned int istof=0; istof < vec.size(); istof++){
    std::istringstream stof_x(vec[istof]);
    int i_stof_x;
    stof_x >> i_stof_x;
    vec_f.push_back(i_stof_x);
  }

  if ((vec_i[0]) > 3) {
    std::cerr << "ERROR in BTagCalibration: "
	      << "Invalid csv line; OperatingPoint > 3: "
	      << csvLine;
    throw std::exception();
  }
  if ((vec_i[3]) > 2) {
    std::cerr << "ERROR in BTagCalibration: "
	      << "Invalid csv line; JetFlavor > 2: "
	      << csvLine;
    throw std::exception();
  }
  params = BTagEntry::Parameters(
				 BTagEntry::OperatingPoint((vec_i[0])),
				 vec[1],
				 vec[2],
				 BTagEntry::JetFlavor((vec_i[3])),
				 (vec_f[4]),
				 (vec_f[5]),
				 (vec_f[6]),
				 (vec_f[7]),
				 (vec_f[8]),
				 (vec_f[9])
				 );
}

BTagEntry::BTagEntry(const std::string &func, BTagEntry::Parameters p):
  formula(func),
  params(p)
{}

BTagEntry::BTagEntry(const TF1* func, BTagEntry::Parameters p):
  formula(std::string(func->GetExpFormula("p").Data())),
  params(p)
{}

// Creates chained step functions like this:
// "<prevous_bin> : x<bin_high_bound ? bin_value : <next_bin>"
// e.g. "x<0 ? 1 : x<1 ? 2 : x<2 ? 3 : 4"
BTagEntry::BTagEntry(const TH1* hist, BTagEntry::Parameters p):
  params(p)
{
  int nbins = hist->GetNbinsX();

  // overwrite bounds with histo values
  if (params.operatingPoint == BTagEntry::OP_RESHAPING) {
    params.discrMin = hist->GetXaxis()->GetBinLowEdge(1);
    params.discrMax = hist->GetXaxis()->GetBinUpEdge(nbins);
  } else {
    params.ptMin = hist->GetXaxis()->GetBinLowEdge(1);
    params.ptMax = hist->GetXaxis()->GetBinUpEdge(nbins);
  }

  std::stringstream buff;
  buff << "x<" << hist->GetXaxis()->GetBinLowEdge(1) << " ? 0. : ";  // default value
  for (int i=1; i<nbins+1; ++i) {
    char tmp_buff[100];
    sprintf(tmp_buff,
            "x<%g ? %g : ",  // %g is the smaller one of %e or %f
            hist->GetXaxis()->GetBinUpEdge(i),
            hist->GetBinContent(i));
    buff << tmp_buff;
  }
  buff << 0.;  // default value
  formula = buff.str();
}

std::string BTagEntry::makeCSVHeader()
{
  return "OperatingPoint, "
         "measurementType, "
         "sysType, "
         "jetFlavor, "
         "etaMin, "
         "etaMax, "
         "ptMin, "
         "ptMax, "
         "discrMin, "
         "discrMax, "
    "formula \n";
}

std::string BTagEntry::makeCSVLine() const
{
  std::stringstream buff;
  buff << params.operatingPoint
       << ", " << params.measurementType
       << ", " << params.sysType
       << ", " << params.jetFlavor
       << ", " << params.etaMin
       << ", " << params.etaMax
       << ", " << params.ptMin
       << ", " << params.ptMax
       << ", " << params.discrMin
       << ", " << params.discrMax
       << ", \"" << formula
       << "\" \n";
  return buff.str();
}

std::string BTagEntry::trimStr(std::string str) {
  size_t s = str.find_first_not_of(" \n\r\t");
  size_t e = str.find_last_not_of (" \n\r\t");

  if((std::string::npos == s) || (std::string::npos == e))
    return "";
  else
    return str.substr(s, e-s+1);
}

#include <fstream>
#include <sstream>



BTagCalibration::BTagCalibration(const std::string &taggr):
  tagger_(taggr)
{}

BTagCalibration::BTagCalibration(const std::string &taggr,
                                 const std::string &filename):
  tagger_(taggr)
{
  std::ifstream ifs(filename.c_str());
  readCSV(ifs);
  ifs.close();
}

void BTagCalibration::addEntry(const BTagEntry &entry)
{
  data_[token(entry.params)].push_back(entry);
}

const std::vector<BTagEntry>& BTagCalibration::getEntries(
							  const BTagEntry::Parameters &par) const
{
  if (!data_.count(token(par))) {
    std::cerr << "ERROR in BTagCalibration: "
	      << "(OperatingPoint, measurementType, sysType) not available: "
	      << token(par);
    throw std::exception();
  }
  return data_.at(token(par));
}

void BTagCalibration::readCSV(const std::string &s)
{
  std::stringstream buff(s);
  readCSV(buff);
}

void BTagCalibration::readCSV(std::istream &s)
{
  std::string line;

  // firstline might be the header
  getline(s,line);
  if (line.find("OperatingPoint") == std::string::npos) {
    addEntry(BTagEntry(line));
  }

  while (getline(s,line)) {
    line = BTagEntry::trimStr(line);
    if (line.empty()) {  // skip empty lines
      continue;
    }
    addEntry(BTagEntry(line));
  }
}

void BTagCalibration::makeCSV(std::ostream &s) const
{
  s << BTagEntry::makeCSVHeader();
  for (std::map<std::string, std::vector<BTagEntry> >::const_iterator i = data_.begin(); i != data_.end(); ++i) {
    
    for (std::vector<BTagEntry>::const_iterator j = i->second.begin(); j != i->second.end(); ++j) {
      s << j->makeCSVLine();
    }
  }
}

std::string BTagCalibration::makeCSV() const
{
  std::stringstream buff;
  makeCSV(buff);
  return buff.str();
}

std::string BTagCalibration::token(const BTagEntry::Parameters &par)
{
  std::stringstream buff;
  buff << par.operatingPoint << ", "
       << par.measurementType << ", "
       << par.sysType;
  return buff.str();
}


BTagCalibrationReader::BTagCalibrationReader(const BTagCalibration* c,
                                             BTagEntry::OperatingPoint op,
                                             std::string measurementType,
                                             std::string sysType):
  params(BTagEntry::Parameters(op, measurementType, sysType)),
  useAbsEta(true)
{
  setupTmpData(c);
}

double BTagCalibrationReader::eval(BTagEntry::JetFlavor jf,
                                   float eta,
                                   float pt,
                                   float discr) const
{
  bool use_discr = (params.operatingPoint == BTagEntry::OP_RESHAPING);
  if (useAbsEta[jf] && eta < 0) {
    eta = -eta;
  }

  // search linearly through eta, pt and discr ranges and eval
  // future: find some clever data structure based on intervals

  for (unsigned i=0; i<  tmpData_.at(jf).size(); ++i) {
    const BTagCalibrationReader::TmpEntry &e =  tmpData_.at(jf).at(i);
    if (
	e.etaMin <= eta && eta < e.etaMax                   // find eta
	&& e.ptMin <= pt && pt < e.ptMax                    // check pt
	){
      if (use_discr) {                                    // discr. reshaping?
        if (e.discrMin <= discr && discr < e.discrMax) {  // check discr
          return e.func.Eval(discr);
        }
      } else {
        return e.func.Eval(pt);
      }
    }
  }

  return 0.;  // default value
}

void BTagCalibrationReader::setupTmpData(const BTagCalibration* c)
{
  useAbsEta = std::vector<bool>(4, true);

  for (unsigned i=0; i< c->getEntries(params).size(); ++i) {
    const BTagEntry &be =  c->getEntries(params)[i];
    BTagCalibrationReader::TmpEntry te;
    te.etaMin = be.params.etaMin;
    te.etaMax = be.params.etaMax;
    te.ptMin = be.params.ptMin;
    te.ptMax = be.params.ptMax;
    te.discrMin = be.params.discrMin;
    te.discrMax = be.params.discrMax;

    if (params.operatingPoint == BTagEntry::OP_RESHAPING) {
      te.func = TF1("", be.formula.c_str(),
                    be.params.discrMin, be.params.discrMax);
    } else {
      te.func = TF1("", be.formula.c_str(),
                    be.params.ptMin, be.params.ptMax);
    }

    tmpData_[be.params.jetFlavor].push_back(te);
    if (te.etaMin < 0) {
      useAbsEta[be.params.jetFlavor] = false;
    }
  }
}
