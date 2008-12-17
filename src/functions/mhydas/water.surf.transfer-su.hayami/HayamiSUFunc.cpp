/**
  \file HayamiSUFunc.h
  \brief header of HayamiSUFunction

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/


#include "HayamiSUFunc.h"
#include <iostream>
#include "math.h"

#include "HayamiTools.h"

// =====================================================================
// =====================================================================

DEFINE_FUNCTION_HOOK(HayamiSUFunction);



// =====================================================================
// =====================================================================

BEGIN_SIGNATURE_HOOK

  DECLARE_SIGNATURE_ID(wxT("water.surf.transfer-su.hayami"));
  DECLARE_SIGNATURE_NAME(wxT("water transfer on surface units using hayami propagation method"));
  DECLARE_SIGNATURE_DESCRIPTION(wxT(""));
  DECLARE_SIGNATURE_DOMAIN(wxT("hydrology"));

  DECLARE_SIGNATURE_STATUS(openfluid::base::BETA);

  DECLARE_SIGNATURE_SDKVERSION;

  DECLARE_SIGNATURE_AUTHORNAME(wxT("Moussa R., Fabre J.-C."));
  DECLARE_SIGNATURE_AUTHOREMAIL(wxT("moussa@supagro.inra.fr, fabrejc@supagro.inra.fr"));

  DECLARE_SU_PRODUCED_VAR("water.surf.Q.downstream-su",wxT("output volume at the outlet of the SUs"),wxT("m3/s"));

  DECLARE_SU_REQUIRED_VAR("water.surf.H.runoff",wxT("runoff on the surface of the unit"),wxT("m/s"));

  DECLARE_SU_REQUIRED_PROPERTY("nmanning",wxT("Manning roughness coefficient"),wxT("s/m^(-1/3)"));


  DECLARE_FUNCTION_PARAM("maxsteps",wxT("maximum hayami kernel steps"),wxT(""));
  DECLARE_FUNCTION_PARAM("meancel",wxT("wave mean celerity"),wxT("m/s"));
  DECLARE_FUNCTION_PARAM("meansigma",wxT("mean diffusivity on SUs"),wxT("m2/s"));

END_SIGNATURE_HOOK

// =====================================================================
// =====================================================================



HayamiSUFunction::HayamiSUFunction()
                : PluggableFunction()
{


  // default values
  m_MaxSteps = 100;
  m_MeanCelerity = 0.045;
  m_MeanSigma = 500;
  m_MeanSlope = 0;
  m_MeanManning = 0;

}


// =====================================================================
// =====================================================================


HayamiSUFunction::~HayamiSUFunction()
{

}


// =====================================================================
// =============================================)========================


bool HayamiSUFunction::initParams(openfluid::core::ParamsMap Params)
{

  OPENFLUID_GetFunctionParameter(Params,wxT("maxsteps"),&m_MaxSteps);
  OPENFLUID_GetFunctionParameter(Params,wxT("meancel"),&m_MeanCelerity);
  OPENFLUID_GetFunctionParameter(Params,wxT("meansigma"),&m_MeanSigma);

  return true;
}


// =====================================================================
// =====================================================================

bool HayamiSUFunction::prepareData()
{

  return true;
}


// =====================================================================
// =====================================================================



bool HayamiSUFunction::checkConsistency()
{

  return true;
}

// =====================================================================
// =====================================================================


bool HayamiSUFunction::initializeRun(const openfluid::base::SimulationInfo* SimInfo)
{
  openfluid::core::SurfaceUnit* SU;
  float Cel, Sigma;
  openfluid::core::UnitID ID;
  openfluid::core::ScalarValue TmpValue;

  DECLARE_SU_ORDERED_LOOP;


  BEGIN_SU_ORDERED_LOOP(SU)
    ID = SU->getID();

    m_Input[ID] = new openfluid::core::SerieOfScalarValue();
    m_CurrentInputSum[ID] = 0;

    m_MeanSlope = m_MeanSlope + SU->getUsrSlope();
    OPENFLUID_GetProperty(SU,wxT("nmanning"),&TmpValue);
    m_MeanManning = m_MeanManning + TmpValue;
  END_LOOP

  m_MeanSlope = m_MeanSlope / mp_CoreData->getSpatialData()->getSUsCollection()->size();
  m_MeanManning = m_MeanManning / mp_CoreData->getSpatialData()->getSUsCollection()->size();

  BEGIN_SU_ORDERED_LOOP(SU)
    OPENFLUID_GetProperty(SU,wxT("nmanning"),&TmpValue);
    Cel = m_MeanCelerity * (m_MeanManning / TmpValue) * (sqrt((SU->getUsrSlope() / m_MeanSlope)));
    Sigma = m_MeanSigma * (TmpValue / m_MeanManning) * (m_MeanSlope / SU->getUsrSlope());

    m_SUKernel[SU->getID()] = t_HayamiKernel();

    ComputeHayamiKernel(Cel, Sigma,SU->getDownstreamDistance(),m_MaxSteps,SimInfo->getTimeStep(), &m_SUKernel[SU->getID()]);

  END_LOOP


  return true;
}



// =====================================================================
// =====================================================================


bool HayamiSUFunction::runStep(const openfluid::base::SimulationStatus* SimStatus)
{

  int ID;
  int CurrentStep;
  int TimeStep;
  openfluid::core::ScalarValue QOutput;
  openfluid::core::ScalarValue QInput;
  openfluid::core::ScalarValue TmpValue;


  openfluid::core::SurfaceUnit* SU;

  TimeStep = SimStatus->getTimeStep();
  CurrentStep = SimStatus->getCurrentStep();

  DECLARE_SU_ORDERED_LOOP;
  BEGIN_SU_ORDERED_LOOP(SU)

    ID = SU->getID();

    OPENFLUID_GetVariable(SU,wxT("water.surf.H.runoff"),CurrentStep,&TmpValue);

    QInput = TmpValue * SU->getUsrArea() / TimeStep;
    m_CurrentInputSum[ID] = m_CurrentInputSum[ID] + QInput;
    m_Input[ID]->push_back(QInput);

    QOutput = 0;
    if (m_CurrentInputSum[ID] > 0)
    {
      QOutput = DoHayamiPropagation(m_SUKernel[ID], CurrentStep, m_Input[ID], m_MaxSteps, TimeStep);
    }


    OPENFLUID_AppendVariable(SU,wxT("water.surf.Q.downstream-su"),QOutput);

  END_LOOP



  return true;

}


// =====================================================================
// =====================================================================


bool HayamiSUFunction::finalizeRun(const openfluid::base::SimulationInfo* SimInfo)
{

  return true;
}


