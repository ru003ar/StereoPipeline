// __BEGIN_LICENSE__
// Copyright (C) 2006-2010 United States Government as represented by
// the Administrator of the National Aeronautics and Space Administration.
// All Rights Reserved.
// __END_LICENSE__


/// \file IsisInterface.h
///
/// Generic Interface with ISIS
///
#ifndef __ASP_ISIS_INTERFACE_H__
#define __ASP_ISIS_INTERFACE_H__

// VW & ASP
#include <string>
#include <vw/Math/Vector.h>
#include <vw/Math/Quaternion.h>

// Isis
#include <Pvl.h>
#include <Camera.h>

namespace asp {
namespace isis {

  // The IsisInterface abstract base class
  // -------------------------------------------------------

  class IsisInterface {
  public:
    IsisInterface( std::string const& file );
    virtual ~IsisInterface();

    virtual std::string type() = 0;
    static IsisInterface* open( std::string const& filename );

    // Standard Methods
    //------------------------------------------------------

    // These are the standard camera request; IsisInterface allows for
    // them to be customized for the type of camera so that they are
    // fast and not too full of conditionals.

    virtual vw::Vector2
      point_to_pixel( vw::Vector3 const& point ) const = 0;
    virtual vw::Vector3
      pixel_to_vector( vw::Vector2 const& pix ) const = 0;
    virtual vw::Vector3
      camera_center( vw::Vector2 const& pix = vw::Vector2(1,1) ) const = 0;
    virtual vw::Quaternion<double>
      camera_pose( vw::Vector2 const& pix = vw::Vector2(1,1) ) const = 0;

    // General information
    //------------------------------------------------------
    int lines(void) const { return m_camera->Lines(); }
    int samples(void) const { return m_camera->Samples(); }
    std::string serial_number(void) const;

  protected:
    // Standard Variables
    //------------------------------------------------------
    Isis::Pvl m_label;
    Isis::Camera* m_camera;
  };

}}

#endif//__ASP_ISIS_INTERFACE_H__
