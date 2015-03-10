// NSigmaFitter.h
// Chris Pollard
// Duke University

#ifndef __NSIGMAFITTER_H__
#define __NSIGMAFITTER_H__

#include <vector>

#include "TH1.h"
#include "Minuit2/FCNBase.h"
#include "TFitterMinuit.h"
#include "TError.h"

class NSigmaFitter : public ROOT::Minuit2::FCNBase {
    protected:
        double m_norm;
        double m_nsigma;

        TH1D m_background;
        TH1D m_signal;

        TFitterMinuit m_fitter;

    public:
        NSigmaFitter() {
            m_fitter.SetPrintLevel(0);
            m_fitter.CreateMinimizer();
            m_fitter.SetMinuitFCN(this);
        }

        ~NSigmaFitter() {
        }

        double operator () (const std::vector<double> &params) const;
        void Solve(const double nsigma=-1);
        double Up() const;

        void SetBackground(const TH1D &background);
        void SetSignal(const TH1D &signal);
        void SetNSigma(const double nsigma);

        TH1D GetBackground() const;
        TH1D GetSignal() const;
        double GetNSigma() const;
        double GetNEvents() const;
};

#endif
