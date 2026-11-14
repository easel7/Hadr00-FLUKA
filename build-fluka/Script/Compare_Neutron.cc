void Compare_Neutron()
{
    auto file1 = TFile::Open("/Users/xiongzheng/software/Hadr00/build/proton_BGO.root");
    auto hist6 = (TH1D*)file1->Get("h1");
    auto file2 = TFile::Open("/Users/xiongzheng/software/Hadr00/build/neutron_BGO.root");
    auto hist7 = (TH1D*)file2->Get("h1");


    double KN_Energy[60] = {0};
    double p_n_ratio[60] = {0};
    double KN_Neutron[60] = {0}; 
    double KN_Proton[60] = {0};

    int Nbins = hist6->GetNbinsX();
    for (int ii = 0 ; ii < Nbins ; ii++)
    {
        KN_Energy[ii]   = pow(10,hist6->GetBinCenter(ii+1)-3);
        file1->cd(); KN_Proton[ii]  = hist6->GetBinContent(ii+1)*1e3;
        file2->cd(); KN_Neutron[ii] = hist7->GetBinContent(ii+1)*1e3;
        p_n_ratio[ii] = KN_Proton[ii] / KN_Neutron[ii];
    }

    auto gre6 = new TGraph(Nbins,KN_Energy, p_n_ratio);     gre6->SetLineColor(kRed);

    
    auto c1 = new TCanvas("c1","c1",1200,900);
    c1->cd();
    gPad->SetLogx();
    gre6->Draw("AL");
}