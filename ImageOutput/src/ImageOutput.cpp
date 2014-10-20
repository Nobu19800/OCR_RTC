// -*- C++ -*-
/*!
 * @file  ImageOutput.cpp
 * @brief Image Output Component
 * @date $Date$
 *
 * $Id$
 */

#include "ImageOutput.h"

// Module specification
// <rtc-template block="module_spec">
static const char* imageoutput_spec[] =
  {
    "implementation_id", "ImageOutput",
    "type_name",         "ImageOutput",
    "description",       "Image Output Component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "TES",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.file_path", "sample.jpg",
    // Widget
    "conf.__widget__.file_path", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ImageOutput::ImageOutput(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_imageOut("m_image", m_image)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ImageOutput::~ImageOutput()
{
}



RTC::ReturnCode_t ImageOutput::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("m_image", m_imageOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("file_path", m_file_path, "sample.jpg");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ImageOutput::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageOutput::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageOutput::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ImageOutput::onActivated(RTC::UniqueId ec_id)
{
  m_imageBuff = cvLoadImage(m_file_path.c_str());
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ImageOutput::onDeactivated(RTC::UniqueId ec_id)
{
  if(m_imageBuff != NULL)
   {
     
     cvReleaseImage(&m_imageBuff);
     
   }
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ImageOutput::onExecute(RTC::UniqueId ec_id)
{
  m_image.width = m_imageBuff->width;
  m_image.height = m_imageBuff->height;
  int len = m_imageBuff->nChannels * m_imageBuff->width * m_imageBuff->height;
  m_image.pixels.length(len);
  memcpy((void *)&(m_image.pixels[0]),m_imageBuff->imageData,len);

  m_imageOut.write();

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ImageOutput::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageOutput::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageOutput::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageOutput::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageOutput::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ImageOutputInit(RTC::Manager* manager)
  {
    coil::Properties profile(imageoutput_spec);
    manager->registerFactory(profile,
                             RTC::Create<ImageOutput>,
                             RTC::Delete<ImageOutput>);
  }
  
};


