#pragma once
#include <glm/vec3.hpp>
#include <random>

class BSpline
{
private:
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_real_distribution<float> m_uniformZeroToOne;
    glm::vec3 m_pMin;
    glm::vec3 m_pMax;
    glm::vec3 m_deCasteljau[4];
    int m_MaxInterCound = 100;

    glm::vec3 RayBoxIntersection(glm::vec3 p, glm::vec3 d);
    void DeCasteljau(glm::vec3 tab[], int n, float t);
public:
    glm::vec3 m_p0;
    glm::vec3 m_p1;
    glm::vec3 m_p2;
    glm::vec3 m_p3;
    
    BSpline();
    ~BSpline();

    BSpline(const BSpline&) = delete;
    BSpline(BSpline&&) = delete;
    BSpline& operator=(const BSpline&) = delete;
    BSpline& operator=(BSpline&&) = delete;

    BSpline(
        const glm::vec3 p0,
        const glm::vec3 p1,
        const glm::vec3 p2,
        const glm::vec3 p3,
        const glm::vec3 pMin,
        const glm::vec3 max
    );
    glm::vec3 GetCurvePosition(float t);
    glm::vec3 GetCurveTangent(float t);
    void GenerateSubsequentCurve();
};