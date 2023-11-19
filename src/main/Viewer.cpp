// File: Viewer.cpp
// Author: mankyu sung

#include <iostream>
#include "Viewer.hpp"
#include "glm/gtc/quaternion.hpp"

static float DEFAULT_TRANSLATE_SPEED = 0.5;
static float DEFAULT_ZOOM_FRACTION = 2.5;
static float DEFAULT_ROTATE_SPEED = 2.0;

using namespace std;

Viewer::Viewer(
    const glm::vec3&viewPoint, const glm::vec3&viewCenter, const glm::vec3&upVector,
    float fieldOfView, float aspectRatio
) : viewPoint(viewPoint),
    viewCenter(viewCenter),
    upVector(upVector),
    fieldOfView(fieldOfView),
    aspectRatio(aspectRatio),
    translateSpeed(DEFAULT_TRANSLATE_SPEED),
    zoomFraction(DEFAULT_ZOOM_FRACTION),
    rotateSpeed(DEFAULT_ROTATE_SPEED),
    viewDir(0.0f, 0.0f, 0.0f),
    imagePlaneHorizDir(0.0f, 0.0f, 0.0f),
    imagePlaneVertDir(0.0f, 0.0f, 0.0f),
    displayWidth(0),
    displayHeight(0),
    lastDesired{0.0f, 0.0f, 0.0f}
{
    this->upVector = glm::normalize(upVector);

    getFrustrumInfo();
}

void Viewer::translate(float changeHoriz, float changeVert, bool inImagePlane)
{
    glm::vec3 translateVec;

    if (inImagePlane)
        translateVec = (imagePlaneHorizDir * (displayWidth * changeHoriz)) + (imagePlaneVertDir * (changeVert * displayHeight));
    else
        translateVec = (viewCenter - viewPoint) * changeVert;
    translateVec *= translateSpeed;

    viewPoint += translateVec;
    viewCenter += translateVec;
}

void Viewer::zoom(float changeVert)
{
    float scaleFactor = powf(2.0, -changeVert * zoomFraction);
    viewPoint = viewCenter + (viewPoint - viewCenter) * scaleFactor;

    getFrustrumInfo();
}

const float pi = glm::pi<float>();

glm::quat setFromAxisAngle(glm::vec3&axis, float angle)
{
    float cosAng = cosf(angle / 2.0f);
    float sinAng = sinf(angle / 2.0f);
    float norm = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);

    glm::quat res;

    res.x = axis.x / norm;
    res.y = axis.y / norm;
    res.z = axis.z / norm;

    res.w = cosAng; //w

    res.x *= sinAng; //x
    res.y *= sinAng; //y
    res.z *= sinAng; //z

    return res;
}

void makeOrthogonalTo(glm::vec3&vec1, glm::vec3&vec2)
{
    float length = glm::length(vec2);

    if (length == 0) {
        std::cout << "Warning: called MathVec3D::makeOrthogonalTo with zero vector as the argument.  Doing nothing." << std::endl;
    }
    else {
        float scale = (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z) / (length * length);
        vec1.x -= scale * vec2.x;
        vec1.y -= scale * vec2.y;
        vec1.z -= scale * vec2.z;
    }
}

void Viewer::rotate(float changeHoriz, float changeVert)
{
    float horizRotAngle = rotateSpeed * changeVert;
    float vertRotAngle = -rotateSpeed * changeHoriz;

    glm::quat horizRot;
    horizRot = setFromAxisAngle(imagePlaneHorizDir, horizRotAngle);

    glm::quat vertRot;
    vertRot = setFromAxisAngle(imagePlaneVertDir, vertRotAngle);

    glm::quat totalRot = horizRot * vertRot;

    glm::vec3 viewVec = viewPoint - viewCenter;
    viewVec = totalRot * viewVec;

    viewPoint = viewCenter + viewVec;

    getFrustrumInfo();
}

void Viewer::centerAt(const glm::vec3&pos)
{
    viewPoint += (pos - viewCenter);
    viewCenter = pos;
    getFrustrumInfo();
}

void Viewer::lookFrom(const glm::vec3&pos)
{
    viewPoint = pos;
    getFrustrumInfo();
}

glm::vec3 Viewer::getViewPoint() const
{
    return (viewPoint);
}

glm::vec3 Viewer::getViewCenter() const
{
    return (viewCenter);
}

glm::vec3 Viewer::getUpVector() const
{
    return (upVector);
}

float Viewer::getFieldOfView() const
{
    return (fieldOfView);
}

float Viewer::getAspectRatio() const
{
    return (aspectRatio);
}

glm::vec3 Viewer::getViewDir() const
{
    return (viewDir);
}

glm::vec3 Viewer::getImagePlaneHorizDir() const
{
    return (imagePlaneHorizDir);
}

glm::vec3 Viewer::getImagePlaneVertDir() const
{
    return (imagePlaneVertDir);
}

void Viewer::setAspectRatio(float aspectRatio)
{
    if (this->aspectRatio != aspectRatio) {
        this->aspectRatio = aspectRatio;
        getFrustrumInfo();
    }
}

void Viewer::setFieldOfView(float fieldOfView)
{
    if (this->fieldOfView != fieldOfView) {
        this->fieldOfView = fieldOfView;
        getFrustrumInfo();
    }
}

void Viewer::setTranslateSpeed(float translateSpeed)
{
    this->translateSpeed = translateSpeed;
}

void Viewer::setZoomFraction(float zoomFraction)
{
    this->zoomFraction = zoomFraction;
}

void Viewer::setRotateSpeed(float rotateSpeed)
{
    this->rotateSpeed = rotateSpeed;
}

void Viewer::getFrustrumInfo()
{
    // Get the viewing direction

    viewDir = viewCenter - viewPoint;
    viewDir = glm::normalize(viewDir);

    // Get the vertical image-plane direction (the projection of the up vector into the view plane)
    imagePlaneVertDir = upVector;
    makeOrthogonalTo(imagePlaneVertDir, viewDir);
    imagePlaneVertDir = glm::normalize(imagePlaneVertDir);

    // Get the horizontal image-plane direction
    imagePlaneHorizDir = glm::cross(viewDir, imagePlaneVertDir);
    imagePlaneHorizDir = glm::normalize(imagePlaneHorizDir);

    // Get the view plane width and height at the view center.
    displayHeight = 2.0 * glm::length(viewCenter - viewPoint) * tan(glm::radians(0.5 * fieldOfView));
    displayWidth = displayHeight * aspectRatio;
}
