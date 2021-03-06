#ifndef L1GCTNULLJETFINDER_H_
#define L1GCTNULLJETFINDER_H_

#include "L1Trigger/GlobalCaloTrigger/interface/L1GctJetFinderBase.h"

#include <boost/cstdint.hpp> //for uint16_t
#include <vector>

/*! \class L1GctNullJetFinder
 * \brief no-op jet finder for test purposes.
 *
 * For use with hardware testing where not all leaf cards are present
 *  
 */
/*
 * \author Greg Heath
 * \date March 2010
 */



class L1GctNullJetFinder : public L1GctJetFinderBase
{
 public:

  /// id is 0-8 for -ve Eta jetfinders, 9-17 for +ve Eta, for increasing Phi.
  L1GctNullJetFinder(int id);
                 
  ~L1GctNullJetFinder();
   
  /// Overload << operator
  friend std::ostream& operator << (std::ostream& os, const L1GctNullJetFinder& algo);

  /// get input data from sources
  virtual void fetchInput();

  /// process the data, fill output buffers
  virtual void process();

 protected:

  // Each jetFinder must define the constants as private and copy the
  // function definitions below.
  virtual unsigned maxRegionsIn() const { return MAX_REGIONS_IN; }
  virtual unsigned centralCol0() const { return CENTRAL_COL0; }
  virtual unsigned nCols() const { return N_COLS; }

private:

  /// The real jetFinders must define these constants
  static const unsigned int MAX_REGIONS_IN; ///< Dependent on number of rows and columns.
  static const unsigned int N_COLS;
  static const unsigned int CENTRAL_COL0;

  void findJets();  

};

std::ostream& operator << (std::ostream& os, const L1GctNullJetFinder& algo);

#endif /*L1GCTNULLJETFINDER_H_*/
