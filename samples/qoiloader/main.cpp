// Sample to exercise the qoi loader

#include <string>

#include "graphics/loaders/qoi_loader.hpp"

static constexpr std::string ASSET_PATH = "../../assets";

void RunQoiLoader(){
  KissShock::QoiLoader qld{ASSET_PATH + "/mero_head.qoi"};
  qld.PrintBuffer();
  qld.PrintDetails();
  qld.Decode();
  auto bitmap = qld.GenerateBitmap();

  if(bitmap){
    bitmap->PrintData();
    bitmap->DumpAsPpm("yes.ppm");
  }
}

int main(){
  RunQoiLoader();
}
