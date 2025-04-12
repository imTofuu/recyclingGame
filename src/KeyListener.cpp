#include "KeyListener.h"

namespace RecyclingGame {

    bool KeyListener::getKeyEnabledState(Key key) const {
        return m_enabledKeys.contains(key);
    }

    void KeyListener::setKeyEnabledState(Key key, bool state) {
        if (state) {
            m_enabledKeys.insert(key);
        } else {
            m_enabledKeys.erase(key);
        }
    }


}