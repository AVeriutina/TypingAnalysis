#include "FLModule.h"

namespace NSApplication {
namespace NSFingers {

CFLModule::CFLModule()
    : MainWindow_(std::make_unique<QMainWindow>()), FingerLayout_(),
      FingerLayoutView_(MainWindow_.get()),
      FingerLayoutController_(&FingerLayout_),
      ShowInput_([this](bool) { show(); }) {

  FingerLayout_.subscribeToFingerLayout(FingerLayoutView_.FingerLayoutInput());
  FingerLayoutView_.subscribeToKeyPress(
      FingerLayoutController_.keyPressInput());
  FingerLayoutView_.subscribeToFingerChange(
      FingerLayoutController_.fingerChangeInput());
  FingerLayoutView_.subscribeToKeyboardType(
      FingerLayoutController_.keyboardTypeInput());
  FingerLayoutView_.subscribeToAction(FingerLayoutController_.actionInput());
}

CFLModule::CLocalizerObserver* CFLModule::localizerInput() {
  return FingerLayoutView_.localizerInput();
}

void CFLModule::show() {
  MainWindow_->show();
}

void CFLModule::subscribeToSaveLayout(CFingerLayoutSaveObserver* obs) {
  FingerLayout_.subscribeToSaveLayout(obs);
}

CFLModule::CFingerLayoutKernelObserver* CFLModule::fingerLayoutInput() {
  return FingerLayout_.fingerLayoutInput();
}

CFLModule::CShowObserver* CFLModule::showInput() {
  return &ShowInput_;
}

} // namespace NSFingers
} // namespace NSApplication
