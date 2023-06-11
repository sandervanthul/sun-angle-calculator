#include <cmath>
#include <iostream>

constexpr double PI = 3.1415926535897932384626433832795;

double CalculateHourAngle(double longitude, double dayOfYear, double timeZone, double hours, double minutes)
{
    double LSTM = 15 * timeZone;

    double B = 360.0 / 365.0 * (dayOfYear - 81) * PI / 180;
    double EoT = 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B);

    double TC = 4 * (longitude - LSTM) + EoT;

    double LST = (hours + minutes / 60) + TC / 60;

    double HRA = 15 * (LST - 12);

    return HRA;
}

double CalculateDeclinationAngle(double dayOfYear)
{
    return -23.44 * cos(360.0 / 365.0 * (dayOfYear + 10.0) * PI / 180);
}

double CalculateElevationAngle(double latitude, double longitude, double dayOfYear, double timeZone, double hours, double minutes)
{
    double delta = CalculateDeclinationAngle(dayOfYear) * PI / 180;
    double phi = latitude * PI / 180;
    double HRA = CalculateHourAngle(longitude, dayOfYear, timeZone, hours, minutes) * PI / 180;

    double elevation_angle = asin(sin(delta) * sin(phi) + cos(delta) * cos(phi) * cos(HRA));

    return elevation_angle * 180 / PI;
}

double CalculateAzimuth(double latitude, double longitude, double dayOfYear, double timeZone, double hours, double minutes)
{
    double delta = CalculateDeclinationAngle(dayOfYear) * PI / 180;
    double phi = latitude * PI / 180;
    double HRA = CalculateHourAngle(longitude, dayOfYear, timeZone, hours, minutes) * PI / 180;
    double alpha = CalculateElevationAngle(latitude, longitude, dayOfYear, timeZone, hours, minutes) * PI / 180;

    double azimuth = acos((sin(delta) * cos(phi) - cos(delta) * sin(phi) * cos(HRA)) / cos(alpha));

    if (HRA > 0)
        azimuth = 2 * PI - azimuth;

    return azimuth * 180 / PI;
}

int main(int argc, char* argv[])
{
    std::cout << CalculateElevationAngle(-70.3125, -51.17934, 118, -3, 8, 32) << std::endl;

    std::cout << CalculateAzimuth(-70.3125, -51.17934, 118, -3, 8, 32) << std::endl;
}