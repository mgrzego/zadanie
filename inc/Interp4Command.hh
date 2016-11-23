#ifndef  INTERP4COMMAND_HH
#define  INTERP4COMMAND_HH

#include <iostream>
#include "DronPose.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Command
 *
 * Plik zawiera definicję klasy Interp4Command ...
 */

/*!
 * \brief Modeluje abstrakcyjne polecenie dla drona
 *
 *  Klasa modeluje ...
 */
 class Interp4Command {
  public:
   /*!
    * \brief Destruktor wirtualny ze wzgledu na klasy pochodne
    *
    *  
    */
   virtual ~Interp4Command() {}
   /*!
    * \brief
    */
   virtual void PrintCmd() const = 0;
   /*!
    * \brief
    */
   virtual void PrintSyntax() const = 0;
   /*!
    * \brief
    */
   virtual const char* GetCmdName() const = 0;
   /*!
    * \brief
    */
   virtual bool ExecCmd( DronPose  *pRobPose ) const = 0;
   /*!
    * \brief
    */
   virtual bool ReadParams(std::istream& Strm_CmdsList) = 0;
 };

#endif