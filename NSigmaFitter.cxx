// NSigmaFitter.cxx
// Chris Pollard
// Duke University

#include "NSigmaFitter.h"
#include "LLR.h"

double NSigmaFitter::operator () (const std::vector<double> &params) const {
    TH1D signalbackground(m_signal);
    signalbackground.Scale(params.at(0)/signalbackground.Integral(0,
                signalbackground.GetNbinsX()+2));

    signalbackground.Add(&m_background);

    double x = m_nsigma - NSigma(&signalbackground, &m_background, &signalbackground);

    return x*x;
}

void NSigmaFitter::Solve(const double nsigma) {
    if (nsigma > 0)
        m_nsigma = nsigma;

    m_fitter.SetParameter(0, "norm", 1, 1, 0, 99999999);

    m_fitter.Minimize();

    m_norm = m_fitter.GetParameter(0);

    return;
}

void NSigmaFitter::SetBackground(const TH1D &background) {
    m_background = background;

    return;
}

void NSigmaFitter::SetSignal(const TH1D &signal) {
    m_signal = signal;

    return;
}

void NSigmaFitter::SetNSigma(const double nsigma) {
    m_nsigma = nsigma;

    return;
}

TH1D NSigmaFitter::GetBackground() const {
    return m_background;
}

TH1D NSigmaFitter::GetSignal() const {
    return m_signal;
}

double NSigmaFitter::GetNSigma() const {
    return m_nsigma;
}

double NSigmaFitter::GetNEvents() const {
    return m_norm;
}

double NSigmaFitter::Up() const {
    return 1.0;
}
