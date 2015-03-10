#include <iostream>

#include "TFile.h"
#include "TH1.h"

#include "NSigmaFitter.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 5) {
        cout << "Usage: " << argv[0] << " nsigma infile sm_histname"
            << "sig_histname0 [sig_histname1 ...]" << endl;
        return 1;
    }

    double nsigma = atof(argv[1]);

    TFile *fin = new TFile(argv[2]);

    TH1D *background = (TH1D *) fin->Get(argv[3]);
    TH1D *signal = NULL;

    vector<string> v;
    v.assign(argv+4, argv+argc);

    NSigmaFitter nsf;
    nsf.SetBackground(*background);
    nsf.SetNSigma(5);

    for (size_t i = 0; i < v.size(); i++) {
        signal = (TH1D *) fin->Get(v.at(i).c_str());
        if (!signal) {
            cout << "cannot find signal histogram " << v.at(i) <<
                endl;
            continue;
        }

        signal->Add(background, -1);
        nsf.SetSignal(*signal);

        nsf.Solve();

        cout << endl;
        cout << v.at(i) << endl;
        cout << "nevents: " << nsf.GetNEvents() << endl;
    }

    fin->Close();

    cout << "Done analyzing histograms." << endl;

    return 0;
}
