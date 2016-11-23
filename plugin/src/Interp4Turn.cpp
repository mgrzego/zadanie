#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include "Interp4Turn.hh"
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
  return Interp4Turn::CreateCmd();
}


/*!
 *
 */
Interp4Turn::Interp4Turn():  _Speed_mmS(0), _Length_mm(0), _Radius_mm(0)
{}


/*!
 *
 */
void Interp4Turn::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed_mmS  << " " << _Length_mm << " " << _Radius_mm << endl;
}


/*!
 *
 */
const char* Interp4Turn::GetCmdName() const
{
  return "Turn";
}


/*!
 *
 */
bool Interp4Turn::ExecCmd( DronPose     *pRobPose) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Wektor3D wsp;
  double x, y, z, a;

  double circ_mm = 2*_Radius_mm*M_PI;
  a = _Length_mm/circ_mm*360;
  wsp = pRobPose->GetPos_m();
  x = wsp.x() + round((_Radius_mm*cos(a*M_PI/180)*1000.0)) / 1000.0;
  if(_Radius_mm > 0){
  	y = wsp.y() + round((_Radius_mm*sin(a*M_PI/180)*1000.0)) / 1000.0;
  }
  else if (_Radius_mm < 0){
  	y = wsp.y() - round((_Radius_mm*sin(a*M_PI/180)*1000.0)) / 1000.0;
  }
  z = wsp.z();
  
  pRobPose->SetPos_m(x,y,z);
  return true;
}


/*!
 *
 */
bool Interp4Turn::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Funkcja odczytuje wprowadzone parametry
   */

  return Strm_CmdsList >> _Speed_mmS >> _Length_mm >> _Radius_mm;
}


/*!
 *
 */
Interp4Command* Interp4Turn::CreateCmd()
{
  return new Interp4Turn();
}


/*!
 *
 */
void Interp4Turn::PrintSyntax() const
{
  cout << "   Turn  speed[mm/s]  distance[m]  radius[mm]" << endl;
}
