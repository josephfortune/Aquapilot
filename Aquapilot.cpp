#include "Aquapilot.h"
#include <cmath>

Aquapilot::Aquapilot() {
  curr_wp = nWaypoints = l_motor = r_motor = rudderAngle = 0;
}

void Aquapilot::updateCompass(double heading) {
  Waypoint w = waypoints[curr_wp];
  double bearing = calcBearing(latitude, longitude, w.lat, w.lon);
  double relBearing = bearing - heading;

  // Left motor
  if (relBearing > 0)
    l_motor = 255 * w.speed;
  else
    l_motor = (1.4167 * relBearing + 255) * w.speed;

  // Right motor
  if (relBearing < 0)
    r_motor = 255 * w.speed;
  else
    r_motor = (-1.4167 * relBearing + 255) * w.speed;

  // Rudder
  rudderAngle = (relBearing + 180) / 360 * 255;

  #ifdef DEBUG
  cout << "------------------------------\n";
  //cout << "Distance: " << dist << "\n";
  cout << "Bearing: " << bearing << "\n";
  cout << "Relative Bearing: " << relBearing << "\n";
  cout << "Motors: " << l_motor << " " << r_motor << "\n";
  cout << "------------------------------\n";
  #endif
}


void Aquapilot::updateGPS(double lat, double lon, bool hasFix) {
  // If we lose the GPS fix
  if (!hasFix) {
    l_motor = r_motor = 0; // Shutdown motors
    return;
  }

  // Update the object's lat/lon for future use by the compass
  latitude = lat;
  longitude = lon;

  // Current waypoint
  Waypoint w = waypoints[curr_wp];

  // Have we reached the waypoint yet?
  double dist = distance(lat, lon, w.lat, w.lon);
  if (dist < WAYPOINT_RADIUS) {

    // Are there more waypoints remaining?
    if (curr_wp < nWaypoints) {
      w = waypoints[++curr_wp];
    }
    else {
      l_motor = r_motor = 0;
    }
  }
}

void Aquapilot::addWaypoint(double lat, double lon, double speedFactor) {
  waypoints[nWaypoints].lat = lat;
  waypoints[nWaypoints].lon = lon;
  waypoints[nWaypoints].speed = speedFactor;
  nWaypoints++;
}

double Aquapilot::calcBearing(double lat1, double lon1, double lat2, double lon2) {
  double y = sin(lon2 - lon1) * cos(lat2);
  double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(lon2 - lon1);
  
  return atan2(y, x) * 180 / 3.141592654;
}

double Aquapilot::distance(double lat1, double lon1, double lat2, double lon2)
{
  // Conversion factor from degrees to radians (pi/180)
  const double toRadian = 0.01745329251;

  // First coordinate (Radians)
  double lat1_r = lat1 * toRadian;
  double lon1_r = lon1 * toRadian;

  // Second coordinate (Radians)
  double lat2_r = lat2 * toRadian;  
  double lon2_r = lon2 * toRadian;

  // Delta coordinates 
  double deltaLat_r = (lat2 - lat1) * toRadian;
  double deltaLon_r = (lon2 - lon1) * toRadian;

  // Distance
  double a = sin(deltaLat_r/2)*sin(deltaLat_r/2) + cos(lat1_r) * cos(lat2_r) * sin(deltaLon_r/2) * sin(deltaLon_r/2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  double distance = 6371 * c * 1000;

  return distance;
}

int Aquapilot::leftMotorSpeed() {
  return l_motor;
}

int Aquapilot::rightMotorSpeed() {
  return r_motor;
}

int Aquapilot::singleMotorSpeed() {
  return waypoints[curr_wp].speed * 255;
}

int Aquapilot::rudder() {
  return rudderAngle;
}


#ifdef DEBUG
void Aquapilot::printWaypoints() {
  for (int i = 0; i < nWaypoints; i++) {
    Waypoint w = waypoints[i];
    cout << "[" << i << "] Lat: " << w.lat << " Lon: " << w.lon << " Speed: " << w.speed << "\n";
  }
}
#endif

