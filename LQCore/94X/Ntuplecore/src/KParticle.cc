#include "KParticle.h"

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace snu;

ClassImp(KParticle)

/**
 * Construct using the default TLorentzVector constructor and set the charge to
 * 0.  From now on prefer to use initialiser lists in order to cut out an
 * additional assignment to the member variables (probably not so important in
 * this constructor).  This is the constructor used by ROOT when reading objects
 * from a file.
 */
KParticle::KParticle() :
  TLorentzVector(),
  //partType_( NOPARTICLE),
    //k_index(0),
    //k_mindex(0),
    //k_mother_pdgid(0),
    //k_dindex(0),
    m_charge(0)
{  
}

/**
 * Copy constructors should be defined in terms of references.  GCC wasn't
 * always seeing the pointer variants correctly.  Set the TLorentzVector and the
 * particle charge.
 */
KParticle::KParticle(const KParticle& p) :
    TLorentzVector(p),
    //partType_(p.GetType()),
    //k_index(p.ParticleIndex()),
    //k_mindex(p.MotherIndex()),
    //k_mother_pdgid(p.MotherPdgId()),
    //k_dindex(p.NDaughter()),
    m_charge(p.Charge())
 {
 }

KParticle::KParticle(const TLorentzVector& p) :
    TLorentzVector(p),
    //partType_( NOPARTICLE),
    //k_index(0),
    //k_mindex(0),
    //k_dindex(0),
    //k_mother_pdgid(0),
    m_charge(0)
{
}

KParticle::KParticle(Float_t px, Float_t py, Float_t pz, Float_t e) :
    TLorentzVector(px, py, pz, e),
    //partType_( NOPARTICLE),
    //k_index(0),
    //k_mindex(0),
    //k_dindex(0),
    //k_mother_pdgid(0),
    m_charge(0)
{
}



/**
 * Added for the sake of completeness, since we have our own copy
 * constructors.
 */
KParticle::~KParticle()
{
}

/**
 * The electric charge is stored as an integer.  This method allows public
 * access.
 */
Int_t KParticle::Charge() const {
    return m_charge;
}

/*KParticle::PartType KParticle::GetType() const {
  return partType_;
}

KParticle::LooseTight KParticle::looseTight() const {
  return looseTight_;
}

int KParticle::ParticleIndex() const {
  return k_index;
}

int KParticle::MotherIndex() const {
  return k_mindex;
}

int KParticle::MotherPdgId() const {
  return k_mother_pdgid;
}

int KParticle::NDaughter() const {
  return k_dindex;
}
*/
/**
 * Reset the private member variables of this instance.
 */
void KParticle::Reset()
{
    m_charge = 0;
    //  k_index=0;
    //k_mindex=0;
    //k_dindex=0;
    //k_mother_pdgid=0;
}

void KParticle::SetCharge(Int_t c)
{
    m_charge = c;
}


/**
 * At run time we may have a vector<KParticle*> which could for example
 * contain both electrons and muons.  This function lets you know which
 * particle it is.
 */
string KParticle::Type() const
{
    return "KParticle";
}

ostream& KParticle::PrintContent(ostream& os) const
{
    const int w = 8;
    return os << setw(10) << Type() <<
      " ch=" << setw(w) << Charge() <<
            " px=" << setw(w) << Px() <<
            " py=" << setw(w) << Py() <<
            " pz=" << setw(w) << Pz() <<
            " E=" << setw(w) << E() <<
            " pt=" << setw(w) << Pt() <<
            " m=" << setw(w) << M();
}

/**
 * Assignment operator.  Since we have copy constructor we should also define
 * the assignment operator (and the destructor).  Calls
 * TLorentzVector::operator= and also assigns the charge.  Also checks for self
 * assignment.
 */
KParticle& KParticle::operator=(const KParticle& p)
{
    if (this != &p) {
        TLorentzVector::operator=(p);
	m_charge = p.m_charge;	 
	//partType_= p.GetType();
	//k_index= p.ParticleIndex();
	//k_mindex= p.MotherIndex();
	//k_mother_pdgid= p.MotherPdgId();
	//k_dindex =p.NDaughter();
    }

    return *this;
}

/**
 * Worrying about the number of temporaries created by the previous operator+.
 */
KParticle& KParticle::operator+= (const KParticle& p)
{
    TLorentzVector::operator+=(p);
    m_charge += p.m_charge;
    return *this;
}

/**
 * Comparison works based on transverse momentum.
 */
bool KParticle::operator< (const KParticle& p) const
{
    return Pt() < p.Pt();
}

/**
 * Just invert the operator<.  Avoids the branch condition in the previous
 * version.
 */
bool KParticle::operator> (const KParticle& p) const
{
    return !(*this < p);
}

/**
 * Since this calls o.PrintContent(stuff) any class that derives from KParticle
 * can also be redirected by this function.
 */
ostream& operator<< (ostream& os, const KParticle& o)
{
    return o.PrintContent(os);
}

/**
 * Allows two KParticle instances to be added together.  Might even be exception
 * safe.
 */
const KParticle operator+ (const KParticle& lhs, const KParticle& rhs)
{
    KParticle ret(lhs);
    ret += rhs;
    return ret;
}

/*
void KParticle::SetType(PartType type){
  partType_ = type;
}

void KParticle::SetLooseTight(LooseTight istight){
  looseTight_ = istight;
}

void KParticle::SetTruthParticleIndex(int index){
  k_index = index;
}


void KParticle::SetMotherIndex(int index){
  k_mindex = index;
}

void KParticle::SetMotherPdgId(int mp){
  k_mother_pdgid = mp;
}


void KParticle::SetNDaughter(int index){
  k_dindex = index;
}
*/
