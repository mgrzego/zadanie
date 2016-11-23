#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include "Interp4Fly.hh"
#include "math.h"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Fly::CreateCmd();
}


/*!
 *
 */
Interp4Fly::Interp4Fly(): _HSpeed_mmS(0), _VSpeed_mmS(0), _Length_mm(0)
{}


/*!
 *
 */
void Interp4Fly::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _HSpeed_mmS  << " " << _VSpeed_mmS << " " << _Length_mm << endl;
}


/*!
 *
 */
const char* Interp4Fly::GetCmdName() const
{
  return "Fly";
}


/*!
 *
 */
bool Interp4Fly::ExecCmd( DronPose     *pRobPose) const
{

   Wektor3D wsp;
   double x, y, z, a; 
/*
   *  Normalizacja wektora predkosci.
   */
   double SVectorLength = sqrt(pow(_HSpeed_mmS, 2) + pow(_VSpeed_mmS, 2));
   double NHorizontal = _HSpeed_mmS / SVectorLength;
   double NVertical = _VSpeed_mmS / SVectorLength;

   double angleXZ = acos(NHorizontal * 1 + NVertical * 0);
   angleXZ = 90 - (angleXZ/M_PI*180);


   wsp=pRobPose->GetPos_m();
   pRobPose->GetAngle_deg(a);

if(_VSpeed_mmS == 0 && _HSpeed_mmS == 0){
  	x = wsp.x();
  	y = wsp.y();
  	z = wsp.z();
  }
else if (_VSpeed_mmS == 0){
  	x = wsp.x() + round(((_HSpeed_mmS/abs(_HSpeed_mmS))*(_Length_mm*cos(a*M_PI/180)*sin(angleXZ*M_PI/180))) * 1000.0) / 1000.0;
	  y = wsp.y() + round(((_HSpeed_mmS/abs(_HSpeed_mmS))*(_Length_mm*sin(a*M_PI/180)*sin(angleXZ*M_PI/180))) * 1000.0) / 1000.0;
  	z = wsp.z();
  }
else if (_HSpeed_mmS == 0){
  	x = wsp.x();
  	y = wsp.y();
  	z = wsp.z() + round(((_VSpeed_mmS/abs(_VSpeed_mmS))*(_Length_mm*cos(angleXZ*M_PI/180))) * 1000.0) / 1000.0;
  }
else
  {
  	x = wsp.x() + round(((_HSpeed_mmS/abs(_HSpeed_mmS))*(_Length_mm*cos(a*M_PI/180)*sin(angleXZ*M_PI/180))) * 1000.0) / 1000.0;
	  y = wsp.y() + round(((_HSpeed_mmS/abs(_HSpeed_mmS))*(_Length_mm*sin(a*M_PI/180)*sin(angleXZ*M_PI/180))) * 1000.0) / 1000.0;
  	z = wsp.z() + round(((_VSpeed_mmS/abs(_VSpeed_mmS))*(_Length_mm*cos(angleXZ*M_PI/180))) * 1000.0) / 1000.0;
  }

a = fmod(a, 360);
  pRobPose->SetPos_m(x,y,z);
  pRobPose->SetAngle_deg(a);
return true;
}
  

/*!
 *
 */
bool Interp4Fly::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return Strm_CmdsList >> _HSpeed_mmS >> _VSpeed_mmS >> _Length_mm;
}


/*!
 *
 */
Interp4Command* Interp4Fly::CreateCmd()
{
  return new Interp4Fly();
}


/*!
 *
 */
void Interp4Fly::PrintSyntax() const
{
  cout << "   Fly  hor_speed[m/s]  ver_speed[m/s]  dist[m]" << endl;
}
