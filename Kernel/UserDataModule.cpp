#include "UserDataModule.h"

namespace NSApplication {
namespace NSKernel {
namespace NSUserDataModuleDetail {

CUserDataModuleImpl::CUserDataModuleImpl()
    : FingerLayoutOutput_(CFingerLayout::getDefault()),
      FingerLayoutSetInput_([this](CFingerLayout layout) {
        setFingerLayout(std::move(layout));
      }) {
}

void CUserDataModuleImpl::subscribeToFingerLayout(CFingerLayoutObserver* obs) {
  assert(obs);
  FingerLayoutOutput_.subscribe(obs);
}

void CUserDataModuleImpl::setFingerLayout(CFingerLayout&& FingerLayout) {
  FingerLayoutOutput_.set(std::move(FingerLayout));
}

CUserDataModuleImpl::CFingerLayoutObserver*
CUserDataModuleImpl::fingerLayoutInput() {
  return &FingerLayoutSetInput_;
}

} // namespace NSUserDataModuleDetail
} // namespace NSKernel
} // namespace NSApplication
