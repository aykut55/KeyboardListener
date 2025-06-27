
#pragma once

class Aircraft {
public:
    Aircraft();

    void RollLeft();
    void RollRight();

    void PitchUp();
    void PitchDown();
    
    void YawLeft();
    void YawRight();
    
    void ThrottleUp();
    void ThrottleDown();

    void StartRollLeft();
    void StartRollRight();
    void StopRolling();

    void StartPitchUp();
    void StartPitchDown();
    void StopPitching();

    void StartYawLeft();
    void StartYawRight();
    void StopYawing();

    void StartThrottleUp();
    void StartThrottleDown();
    void StopThrottle();

    void NeutralizeAll();

    void PrintStatus();

    void IncIterCount();

    void Update();

private:
    int roll;
    int pitch;
    int yaw;
    int throttle;

    int iterCount;

    bool isRollingLeft = false;
    bool isRollingRight = false;

    bool isPitchingUp = false;
    bool isPitchingDown = false;

    bool isYawingLeft = false;
    bool isYawingRight = false;

    bool isThrottlingUp = false;
    bool isThrottlingDown = false;
};
