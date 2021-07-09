#pragma once

template<typename... Args>
void debug_print(const Args&... args) {
    ((Serial.print(args), Serial.print(" ")), ...);
    Serial.println();
}
