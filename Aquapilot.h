#ifndef AQUAPILOT_H
#define AQUAPILOT_H

#define MAX_WAYPOINTS 32
#define WAYPOINT_RADIUS 5 // 5 meter radius

class Waypoint {
  public:
  double lat;
  double lon;
  double speed;
};

class Aquapilot {
  public:
  Aquapilot();
  void updateGPS(double lat, double lon, bool hasFix);
  void updateCompass(double heading);
  void addWaypoint(double lat, double lon, double speedFactor);
  int leftMotorSpeed();
  int rightMotorSpeed();
  int singleMotorSpeed();
  int rudder();

  private:
  int curr_wp, nWaypoints, l_motor, r_motor, rudderAngle;
  double latitude, longitude;
  Waypoint waypoints[MAX_WAYPOINTS];
  double calcBearing(double lat1, double lon1, double lat2, double lon2);
  double distance(double lat1, double lon1, double lat2, double lon2);
  
};

#endif
