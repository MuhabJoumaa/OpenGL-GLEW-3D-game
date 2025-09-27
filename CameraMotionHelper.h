#pragma once

#define MOUSE_SENSITIVITY 0.2f
#define WHEEL_SENSITIVITY 0.2f

class CameraMotionHelper
{
private:
    bool leftButtonDown;
    int currentPosition[2];
    int lastPosition[2];
    float rotationY;
    float rotationXZ;
    float distance;

public:
    float getRotationY()
    {
        return rotationY;
    }
    float getRotationXZ()
    {
        return rotationXZ;
    }
    float getDistance()
    {
        return distance;
    }

public:
    void startMove(int x, int y)
    {
        leftButtonDown = true;
        lastPosition[0] = x;
        lastPosition[1] = y;
        currentPosition[0] = x;
        currentPosition[1] = y;
    }

    void move(int x, int y)
    {
        if (leftButtonDown)
        {
            lastPosition[0] = currentPosition[0];
            lastPosition[1] = currentPosition[1];
            currentPosition[0] = x;
            currentPosition[1] = y;
            rotationY += (currentPosition[0] - lastPosition[0]) * MOUSE_SENSITIVITY;
            rotationXZ += (currentPosition[1] - lastPosition[1]) * MOUSE_SENSITIVITY;
        }
    }

    void endMove()
    {
        leftButtonDown = false;
    }

    void increaseDistance()
    {
        distance += WHEEL_SENSITIVITY;
    }
    void decreaseDistance()
    {
        distance -= WHEEL_SENSITIVITY;
    }
public:
    CameraMotionHelper()
    {
        leftButtonDown = false;
        lastPosition[0] = 0;
        lastPosition[1] = 0;
        currentPosition[0] = 0;
        currentPosition[1] = 0;
        rotationY = 0.0f;
        rotationXZ = 0.0f;
        distance = 13.0f;
    }
};
