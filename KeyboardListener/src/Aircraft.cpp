
#include "Aircraft.h"
#include <iostream>
#include <iomanip>

Aircraft::Aircraft() : roll(0), pitch(0), yaw(0), throttle(0), iterCount(0) {}

void Aircraft::RollLeft()      { roll--;        }
void Aircraft::RollRight()     { roll++;        }
void Aircraft::PitchUp()       { pitch++;       }
void Aircraft::PitchDown()     { pitch--;       }
void Aircraft::YawLeft()       { yaw--;         }
void Aircraft::YawRight()      { yaw++;         }
void Aircraft::ThrottleUp()    { throttle++;    }
void Aircraft::ThrottleDown()  { throttle--;    }

void Aircraft::StartRollLeft()      { isRollingLeft = true;  isRollingRight = false;        }
void Aircraft::StartRollRight()     { isRollingRight = true; isRollingLeft = false;         }
void Aircraft::StopRolling()        { isRollingLeft = false; isRollingRight = false;        }

void Aircraft::StartPitchUp()       { isPitchingUp = true;   isPitchingDown = false;        }
void Aircraft::StartPitchDown()     { isPitchingDown = true; isPitchingUp = false;          }
void Aircraft::StopPitching()       { isPitchingUp = false;  isPitchingDown = false;        }

void Aircraft::StartYawLeft()       { isYawingLeft = true;   isYawingRight = false;         }
void Aircraft::StartYawRight()      { isYawingRight = true;  isYawingLeft = false;          }
void Aircraft::StopYawing()         { isYawingLeft = false;  isYawingRight = false;         }

void Aircraft::StartThrottleUp()    { isThrottlingUp = true;   isThrottlingDown = false;    }
void Aircraft::StartThrottleDown()  { isThrottlingDown = true; isThrottlingUp = false;      }
void Aircraft::StopThrottle()       { isThrottlingUp = false;  isThrottlingDown = false;    }

void Aircraft::Update() {
    if (isRollingLeft)     roll--;
    if (isRollingRight)    roll++;
    if (isPitchingUp)      pitch++;
    if (isPitchingDown)    pitch--;
    if (isYawingLeft)      yaw--;
    if (isYawingRight)     yaw++;
    if (isThrottlingUp)    throttle++;
    if (isThrottlingDown)  throttle--;
}

void Aircraft::NeutralizeAll() {
    roll = pitch = yaw = throttle = 0;
}

void Aircraft::PrintStatus() {
    std::cout << "iterCount: " << std::setw(4) << iterCount
        << "  [Aircraft Status] "
        << "  Roll: " << std::setw(4) << roll
        << ", Pitch: " << std::setw(4) << pitch
        << ", Yaw: " << std::setw(4) << yaw
        << ", Throttle: " << std::setw(4) << throttle
        << std::endl;
}

void Aircraft::IncIterCount() {
    iterCount++;
}