/*
  Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
 */

#ifndef TFCSShapeValidation_H
#define TFCSShapeValidation_H

#include "CLHEP/Random/RandomEngine.h"
#include "TFCSAnalyzerBase.h"
#include "TFCSSimulationRun.h"
#include "CaloGeometryFromFile.h"
#include "ISF_FastCaloSimEvent/TFCSTruthState.h"
#include "ISF_FastCaloSimEvent/TFCSExtrapolationState.h"
#include "ISF_FastCaloSimEvent/TFCSSimulationState.h"

class TFCSShapeValidation: public TFCSAnalyzerBase
{
public:
   TFCSShapeValidation(long seed = 42);
   TFCSShapeValidation(TChain *chain, int layer, long seed = 42);
   ~TFCSShapeValidation();

   void LoadGeo();
   ICaloGeometry* get_geometry() {return m_geo;};
   
   void LoopEvents(int pcabin);

   TFCSTruthState& get_truthTLV(int ievent) {return m_truthTLV[ievent];};
   TFCSExtrapolationState& get_extrapol(int ievent) {return m_extrapol[ievent];};
   
   std::vector<TFCSSimulationRun>& validations() {return m_validations;};
   int add_validation(TFCSParametrizationBase* sim) {m_validations.emplace_back(sim);return m_validations.size()-1;};
   int add_validation(const char* name, const char* title,TFCSParametrizationBase* sim) {m_validations.emplace_back(name,title,sim);return m_validations.size()-1;};
   
   void set_firstevent(int n) {m_firstevent=n;};
   void set_nprint(int n) {m_nprint=n;};
   
   int get_layer() const {return m_layer;};
   
private:
   CLHEP::HepRandomEngine *m_randEngine;

   TChain *m_chain;
   std::string m_output;
   int m_layer;
   int m_nprint;
   int m_firstevent;
   CaloGeometryFromFile* m_geo;
   
   std::vector<TFCSTruthState> m_truthTLV;
   std::vector<TFCSExtrapolationState> m_extrapol;
   
   std::vector<TFCSSimulationRun> m_validations;


   ClassDef(TFCSShapeValidation, 1);
};

#if defined(__MAKECINT__)
#pragma link C++ class TFCSShapeValidation+;
#endif

#endif
