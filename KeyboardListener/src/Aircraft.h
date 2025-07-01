#ifndef AircraftH
#define AircraftH

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <thread>
#include <mutex>
#include <chrono>

class CAircraft 
{
public:
    virtual ~CAircraft();
             CAircraft();

    virtual void    RollLeft(void);
    virtual void    RollRight(void);

    virtual void    PitchUp(void);
    virtual void    PitchDown(void);

    virtual void    YawLeft(void);
    virtual void    YawRight(void);

    virtual void    ThrottleUp(void);
    virtual void    ThrottleDown(void);

    virtual void    StartRollLeft(void);
    virtual void    StartRollRight(void);
    virtual void    StopRolling(void);
            
    virtual void    StartPitchUp(void);
    virtual void    StartPitchDown(void);
    virtual void    StopPitching(void);
            
    virtual void    StartYawLeft(void);
    virtual void    StartYawRight(void);
    virtual void    StopYawing(void);
            
    virtual void    StartThrottleUp(void);
    virtual void    StartThrottleDown(void);
    virtual void    StopThrottle(void);

    virtual void    SetRollCmd(double rollCmd);
    virtual double  GetRollCmd(void);

    virtual void    SetPitchCmd(double pitchCmd);
    virtual double  GetPitchCmd(void);

    virtual void    SetYawCmd(double yawCmd);
    virtual double  GetYawCmd(void);

    virtual void    SetThrottleCmd(double throttleCmd);
    virtual double  GetThrottleCmd(void);

    virtual void    SetRollCmdIncrement(double rollCmdIncrement);
    virtual double  GetRollCmdIncrement(void);

    virtual void    SetPitchCmdIncrement(double pitchCmdIncrement);
    virtual double  GetPitchCmdIncrement(void);

    virtual void    SetYawCmdIncrement(double yawCmdIncrement);
    virtual double  GetYawCmdIncrement(void);

    virtual void    SetThrottleCmdIncrement(double throttleCmdIncrement);
    virtual double  GetThrottleCmdIncrement(void);

    virtual void    SetRollCmdUpperLimit(double rollCmdUpperLimit);
    virtual double  GetRollCmdUpperLimit(void);

    virtual void    SetRollCmdLowerLimit(double rollCmdLowerLimit);
    virtual double  GetRollCmdLowerLimit(void);

    virtual void    SetPitchCmdUpperLimit(double pitchCmdUpperLimit);
    virtual double  GetPitchCmdUpperLimit(void);

    virtual void    SetPitchCmdLowerLimit(double pitchCmdLowerLimit);
    virtual double  GetPitchCmdLowerLimit(void);

    virtual void    SetYawCmdUpperLimit(double yawCmdUpperLimit);
    virtual double  GetYawCmdUpperLimit(void);

    virtual void    SetYawCmdLowerLimit(double yawCmdLowerLimit);
    virtual double  GetYawCmdLowerLimit(void);

    virtual void    SetThrottleCmdUpperLimit(double throttleCmdUpperLimit);
    virtual double  GetThrottleCmdUpperLimit(void);

    virtual void    SetThrottleCmdLowerLimit(double throttleCmdLowerLimit);
    virtual double  GetThrottleCmdLowerLimit(void);

    virtual void    SetRollCmdResetValue(double rollCmdResetValue);
    virtual double  GetRollCmdResetValue(void);

    virtual void    SetPitchCmdResetValue(double pitchCmdResetValue);
    virtual double  GetPitchCmdResetValue(void);

    virtual void    SetYawCmdResetValue(double yawCmdResetValue);
    virtual double  GetYawCmdResetValue(void);

    virtual void    SetThrottleCmdResetValue(double throttleCmdResetValue);
    virtual double  GetThrottleCmdResetValue(void);

    virtual void    SetRoll(double rollDeg);
    virtual double  GetRoll(void);

    virtual void    SetPitch(double pitchDeg);
    virtual double  GetPitch(void);

    virtual void    SetYaw(double yawDeg);
    virtual double  GetYaw(void);

    virtual void    SetThrottle(double value);
    virtual double  GetThrottle(void);

    virtual void    SetHeading(double headingDeg);
    virtual double  GetHeading(void);

    virtual void    SetLatitude(double latDeg);
    virtual double  GetLatitude(void);

    virtual void    SetLongitude(double lonDeg);
    virtual double  GetLongitude(void);

    virtual void    SetAltitude(double altMeter);
    virtual double  GetAltitude(void);

    virtual void    SetSpeed(double speedMPS);
    virtual double  GetSpeed(void);

    virtual void    SetIterCount(int value);
    virtual int     GetIterCount(void);

    virtual void    NeutralizeAll(void);

    virtual void    PrintFlighData(void);

    virtual void    PrintStatus(void);

    virtual void    Update(void);

protected:

private:
    double headingDeg;
    double latDeg;
    double lonDeg;
    double altMeter;
    double speedMPS;
    double rollDeg;
    double pitchDeg;
    double yawDeg;
    double throttle;

    double rollCmd;
    double pitchCmd;
    double yawCmd;
    double throttleCmd;

    double rollCmdIncrement;
    double pitchCmdIncrement;
    double yawCmdIncrement;
    double throttleCmdIncrement;

    double rollCmdUpperLimit;
    double rollCmdLowerLimit;
    double pitchCmdUpperLimit;
    double pitchCmdLowerLimit;
    double yawCmdUpperLimit;
    double yawCmdLowerLimit;
    double throttleCmdUpperLimit;
    double throttleCmdLowerLimit;

    double rollCmdResetValue;
    double pitchCmdResetValue;
    double yawCmdResetValue;
    double throttleCmdResetValue;

    int iterCount;

    bool isRollingLeft;
    bool isRollingRight;

    bool isPitchingUp;
    bool isPitchingDown;

    bool isYawingLeft;
    bool isYawingRight;

    bool isThrottlingUp;
    bool isThrottlingDown;

    void incIterCount(void);

    std::chrono::time_point<std::chrono::steady_clock> lastPrintTime;
    std::chrono::time_point<std::chrono::steady_clock> currentTime;
};

#endif
