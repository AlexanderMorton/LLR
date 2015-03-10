#ifndef __LLR_h__
#define __LLR_h__

class TH1;

// calculate the log likelihood of the data given the prediction in
// the iBinth bin.
double BinLogLikelihood(const TH1 *data, const TH1 *pred, int iBin);

// calculate the log likelihood of the data histogram given the
// prediction histogram
double LogLikelihood(const TH1 *data, const TH1 *pred);

// calculate the log likelihood ratio of the data histogram given the
// background prediction and the data given the signal+background
// prediction.
double LLRatio(const TH1 *d, const TH1 *b, const TH1 *sb);

// calculate the nsigma deviation of the data histogram given the
// background prediction and the signal+background prediction assuming
// gaussian fluctuations.
double NSigma(const TH1 *d, const TH1 *b, const TH1 *sb);

#endif
