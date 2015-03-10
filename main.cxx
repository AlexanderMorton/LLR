#include "LLR.h"

#include <iostream>

#include <TFile.h>
#include <TH1.h>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 4) {
        cout << "Usage: " << argv[0] << " infile sm_histname"
            << "bsm_histname0 [bsm_histname1 ...]" << endl;
        return 1;
    }

    TFile *fin = new TFile(argv[1]);

    TH1D background = *(TH1D *) fin->Get(argv[2]);

    vector<string> v;
    v.assign(argv+3, argv+argc);

    TH1D *signalbackground;

    for (size_t i = 0; i < v.size(); i++) {
        signalbackground = (TH1D *) fin->Get(v.at(i).c_str());
        if (!signalbackground) {
            cout << "cannot find signal histogram " << v.at(i) <<
                endl;
            continue;
        }

        cout << endl;
        cout << v.at(i) << endl;
        cout << "NSigma: " << NSigma(signalbackground,
                &background, signalbackground) << endl;
    }

    fin->Close();

    return 0;
}
