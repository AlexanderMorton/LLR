#include "LLR.h"

#include <iostream>

#include <TMath.h>
#include <TH1.h>

double BinLogLikelihood(const TH1 *data, const TH1 *pred, int iBin) {
    double lambda = pred->GetBinContent(iBin);
    double n = data->GetBinContent(iBin);

    return n*TMath::Log(lambda) - lambda - TMath::LnGamma(n+1);
}

double LogLikelihood(const TH1 *data, const TH1 *pred) {
    int nbins = data->GetNbinsX()*data->GetNbinsY()*data->GetNbinsZ();

    double ll = 0, l;
    for (int iBin = 1; iBin < nbins+1; iBin++) {
        l = BinLogLikelihood(data, pred, iBin);
        ll += l;
    }

    return ll;
}

double LLRatio(const TH1 *d, const TH1 *b, const TH1 *sb) {
    return LogLikelihood(d, b) - LogLikelihood(d, sb);
}

double NSigma(const TH1 *d, const TH1 *b, const TH1 *sb) {
    double llr = LLRatio(d, b, sb);
    return llr > 0 ? 0 : sqrt(-2*llr);
}


