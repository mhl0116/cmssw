#include "RecoParticleFlow/PFRootEvent/interface/GPFGenParticleUpgrade.h"
#include "RecoParticleFlow/PFRootEvent/interface/DisplayManagerUpgrade.h"
#include "TObject.h"
#include "TPad.h"

//________________________________________________________________
GPFGenParticleUpgrade::GPFGenParticleUpgrade(DisplayManagerUpgrade * display,
                               int view,int ident,
                               double x,double y,double e, double pt,int barcode,
                               TAttMarker *attm,std::string name, std::string latexName)
  :  GPFBaseUpgrade(display,view,ident, attm ),
     TMarker(x,y,1),
     TLatex(x,y,latexName.c_str()),
     en_(e),pt_(pt),name_(name),barcode_(barcode),
     barcodeMother_(0),
     line_(0) {
    
  //ResetBit(kCanDelete);
  SetMarkerColor(markerAttr_->GetMarkerColor());
  SetMarkerStyle(markerAttr_->GetMarkerStyle());
  SetMarkerSize(markerAttr_->GetMarkerSize());
}   
//________________________________________________________________
GPFGenParticleUpgrade::GPFGenParticleUpgrade(DisplayManagerUpgrade * display,
                               int view,int ident,
                               double *x,double *y,
                               double e, double pt,int barcode,int barcodeMother,
                               TAttMarker *attm,std::string name, std::string latexName)
  :  GPFBaseUpgrade(display,view,ident, attm ),
     TMarker(x[1],y[1],1),
     TLatex(x[1],y[1],latexName.c_str()),
     en_(e),pt_(pt),name_(name),barcode_(barcode),
     barcodeMother_(barcodeMother),
     line_(0) {
    
  //ResetBit(kCanDelete);
  SetMarkerColor(markerAttr_->GetMarkerColor());
  SetMarkerStyle(markerAttr_->GetMarkerStyle());
  SetMarkerSize(markerAttr_->GetMarkerSize());
  line_ = new TLine(x[0],y[0],x[1],y[1]);
  line_->SetLineColor(markerAttr_->GetMarkerColor());
}
   
//_________________________________________________________________
void GPFGenParticleUpgrade::Print()
{
  display_->printGenParticleInfo(name_,barcode_,barcodeMother_);
}
//_________________________________________________________________
void GPFGenParticleUpgrade::ExecuteEvent(Int_t event, Int_t px, Int_t py)
{
  // Execute action corresponding to a mouse click 

  gPad->SetCursor(kHand);
  switch (event) {
  case kButton1Down:
    Print();
    break;
  default:break;
  }    
}
//_________________________________________________________________ 
void GPFGenParticleUpgrade::draw()
{
  TMarker::Draw();
  SetTextFont(42);
  SetTextSize(0.05);
  TLatex::Draw();
  if(line_) line_->Draw();
}  
//_________________________________________________________________
void GPFGenParticleUpgrade::setColor()
{
  SetMarkerColor(markerAttr_->GetMarkerColor());
}
//_________________________________________________________________
void GPFGenParticleUpgrade::setColor(int newcol)
{
  SetMarkerColor(newcol);
}
//_________________________________________________________________
void GPFGenParticleUpgrade::setInitialColor()
{
  SetMarkerColor(markerAttr_->GetMarkerColor());
}
//_________________________________________________________________
void GPFGenParticleUpgrade::setNewStyle()
{
  SetMarkerStyle(markerAttr_->GetMarkerStyle());
}
//_________________________________________________________________
void GPFGenParticleUpgrade::setNewSize()
{
  SetMarkerSize(markerAttr_->GetMarkerSize());
}

