#include "FingerLayoutModule.h"

#include <cassert>
#include <limits>

namespace {

using CFinger = NSApplication::NSKernel::CFinger;
using CKeyPosition = NSApplication::NSKeyboard::CKeyPosition;
using CLayoutContainer =
    std::map<CFinger, std::set<CKeyPosition>, CFinger::CStandardOrder>;

CLayoutContainer
toLayoutContainer(const NSApplication::NSKernel::CFingerLayout& src) {
  CLayoutContainer result;
  for (CKeyPosition pos = 0;; ++pos) {
    const CFinger finger = src.find(pos);
    if (finger.id() != CFinger::EFingerEnum::Undefined)
      result[finger].insert(pos);
    if (pos == std::numeric_limits<CKeyPosition>::max())
      break;
  }
  return result;
}

// думаю тебе это не понравиться, но пока функционал
// NSApplication::NSKernel::CFingerLayout такой, я не вижу как это более красиво
// сделать
CLayoutContainer getDefaultLayout() {
  return toLayoutContainer(
      NSApplication::NSKernel::CFingerLayout::getDefault());
}

} // namespace

namespace NSApplication {
namespace NSFingers {

CFingerLayoutModule::CFingerLayoutModule()
    : Layout_(getDefaultLayout()), InitialLayout_(Layout_),
      CurrentFinger_(CFinger::LeftPinky()),
      FingerLayoutKernelInput_([this](const NSKernel::CFingerLayout& layout) {
        Layout_ = toLayoutContainer(layout);
        InitialLayout_ = Layout_;
        FingerLayoutOutput_.set(
            CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
      }) {
  FingerLayoutOutput_.set(
      CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
}

void CFingerLayoutModule::changeCurrentFinger(CFinger new_finger) {
  CurrentFinger_ = new_finger;
  FingerLayoutOutput_.set(
      CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
}

void CFingerLayoutModule::changeButton(CKeyPosition button_for_change) {
  for (auto& [_, buttons_for_finger] : Layout_) {
    if (buttons_for_finger.count(button_for_change) == 0) {
      continue;
    }
    buttons_for_finger.erase(button_for_change);
    Layout_[CurrentFinger_].insert(button_for_change);

    FingerLayoutOutput_.set(
        CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
    return;
  }
}

void CFingerLayoutModule::resetLayout() {
  Layout_ = InitialLayout_;
  FingerLayoutOutput_.set(
      CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
}

void CFingerLayoutModule::sendLayout() {
  FingerLayoutSaveOutput_.set(NSKernel::CFingerLayout::make(Layout_));
}

void CFingerLayoutModule::subscribeToSaveLayout(
    CFingerLayoutSaveObserver* obs) {
  assert(obs);
  FingerLayoutSaveOutput_.subscribe(obs);
}

CFingerLayoutModule::CFingerLayoutKernelObserver*
CFingerLayoutModule::fingerLayoutInput() {
  return &FingerLayoutKernelInput_;
}

void CFingerLayoutModule::setKeyboardType(KeyboardType type) {
  CurrentKeyboardType_ = type;
  FingerLayoutOutput_.set(
      CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
}

void CFingerLayoutModule::subscribeToFingerLayout(
    CFingerLayoutObserver* observer) {
  assert(observer);
  FingerLayoutOutput_.subscribe(observer);
}

} // namespace NSFingers
} // namespace NSApplication
