/**
  \file SurfaceUnit.h
  \brief

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/

#ifndef __SURFACEUNIT_H__
#define __SURFACEUNIT_H__


#include <list>
#include "HydroObject.h"
#include "GroundwaterUnit.h"



namespace openfluid { namespace core {


class GroundwaterUnit;



/**
  \brief Enumerates possible flow types from a surface unit

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/
enum SUDownstreamCode
{
  SUDownstream,
  RLatDownstream,
  RSrcDownstream,
  UnknownDownstreamCode
};



/**
  \brief Class definition for Surface Units (SUs)

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/
class SurfaceUnit : public HydroObject
{


  private:

    double m_UsrArea;
    double m_UsrSlope;
    SUDownstreamCode m_DownstreamCode;
    UnitID m_DownstreamID;
    HydroObject *mp_DownstreamObject;
    double m_DownstreamDistance;
    UnitID m_GUExchangeID;
    GroundwaterUnit *mp_GUExchange;
    std::list<SurfaceUnit*>* mp_UpstreamSUs;

  public:

	/**
	  Default constructor
	*/
    SurfaceUnit();

    /**
      Constructor
    */
    SurfaceUnit(UnitID ID, int ProcessOrder,
	            double UsrArea, double UsrSlope,
	            SUDownstreamCode DSCode, UnitID DownstreamID, double DSDistance, UnitID GUExchangeID);
    ~SurfaceUnit();

    /**
      Returns the area of the SU
     */
    double getUsrArea() const;

    /**
      Returns the slope of the SU
     */
    double getUsrSlope() const;

    SUDownstreamCode getDownstreamCode() const;

    UnitID getDownstreamID() const;

    /**
      Returns the distance to the downstream Unit
     */
    double getDownstreamDistance() const;

    UnitID getGUExchangeID() const;

    /**
      Returns the GU exchanging with this SU
     */
    GroundwaterUnit* getGUExchange() { return mp_GUExchange; };

    /**
      Returns the list of GUs exchanging with this SU
     */
    std::list<SurfaceUnit*>* getUpstreamSUs() { return mp_UpstreamSUs; };

    void setUsrArea(double Area);

    void setUsrSlope(double Slope);

    void setDownstreamCode(SUDownstreamCode Code);

    void setDownstreamID(UnitID ID);

    void setDownstreamDistance(double Distance);

    void setGUExchangeID(UnitID ID);

    void setGUExchange(GroundwaterUnit *GHU);

    void setDownstreamObject(HydroObject *HObject);


};


} } // namespace openfluid::core


#endif
