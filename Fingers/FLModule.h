#pragma once

#include "FingerLayoutController.h"
#include "FingerLayoutModule.h"
#include "FingerLayoutView.h"
#include "Library/Observer2/Observer.h"
#include "Local/Localizer.h"

#include <QMainWindow>

#include <memory>

namespace NSApplication {
namespace NSFingers {

class CFLModule {
public:
  using CLocalizerObserver =
      NSLibrary::CObserver<NSLocal::CFingerLayoutLocalizer>;
  using CFingerLayoutSaveObserver =
      CFingerLayoutModule::CFingerLayoutSaveObserver;
  using CFingerLayoutKernelObserver =
      CFingerLayoutModule::CFingerLayoutKernelObserver;

  CFLModule();
  ~CFLModule() = default;

  CLocalizerObserver* localizerInput();
  void show();

  void subscribeToSaveLayout(CFingerLayoutSaveObserver* obs);
  CFingerLayoutKernelObserver* fingerLayoutInput();

  using CShowObserver = NSLibrary::CObserver<bool>;
  CShowObserver* showInput();

private:
  using CShowInput = NSLibrary::CColdInput<bool>;

  std::unique_ptr<QMainWindow> MainWindow_;
  CFingerLayoutModule FingerLayout_;
  CFingerLayoutView FingerLayoutView_;
  CFingerLayoutController FingerLayoutController_;
  CShowInput ShowInput_;
};
} // namespace NSFingers
} // namespace NSApplication
