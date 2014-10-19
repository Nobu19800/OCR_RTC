// -*- C++ -*-
/*!
 * @file  OCR.cpp
 * @brief OCR Component
 * @date $Date$
 *
 * $Id$
 */

#include "OCR.h"

// Module specification
// <rtc-template block="module_spec">
static const char* ocr_spec[] =
  {
    "implementation_id", "OCR",
    "type_name",         "OCR",
    "description",       "OCR Component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "TES",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	"conf.default.file_path", "sample.jpg",
	"conf.default.input_type", "DataPort",
	"conf.default.languages", "Japanese",
	"conf.__widget__.file_path", "text",
	"conf.__widget__.input_type", "radio",
	"conf.__widget__.languages", "radio",
	"conf.__constraints__.input_type", "(DataPort,Configuration)",
	"conf.__constraints__.languages", "(Japanese,English)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
OCR::OCR(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_imageIn("image", m_image),
    m_wordListOut("wordList", m_wordList),
    m_stringOut("string", m_string)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
OCR::~OCR()
{
}



RTC::ReturnCode_t OCR::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("image", m_imageIn);
  
  // Set OutPort buffer
  addOutPort("wordList", m_wordListOut);
  addOutPort("string", m_stringOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports

  bindParameter("file_path", file_path, "sample.jpeg");
  bindParameter("input_type", input_type, "DataPort");
  bindParameter("languages", languages, "Japanese");
  
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t OCR::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OCR::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OCR::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t OCR::onActivated(RTC::UniqueId ec_id)
{
	m_imageBuff = NULL;
	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t OCR::onDeactivated(RTC::UniqueId ec_id)
{
	if(m_imageBuff != NULL)
   {
     
     cvReleaseImage(&m_imageBuff);
     
   }
  return RTC::RTC_OK;
}


RTC::ReturnCode_t OCR::onExecute(RTC::UniqueId ec_id)
{
	MODI::Document ^doc = gcnew MODI::Document();

	if(input_type == "DataPort")
	{
		if(m_imageIn.isNew())
		{
			m_imageIn.read();
			
				
 
				 
			if(m_imageBuff != NULL)
			{
				cvReleaseImage(&m_imageBuff);
         
			}
 
				 
			m_imageBuff = cvCreateImage(cvSize(m_image.width, m_image.height), IPL_DEPTH_8U, 3);
    
			
 
			
			memcpy(m_imageBuff->imageData,(void *)&(m_image.pixels[0]),m_image.pixels.length());
 
			cvSaveImage("m_imageBuff.jpg", m_imageBuff);
			
			

			doc->Create("m_imageBuff.jpg");

			
		}
		else
		{
			return RTC::RTC_OK;
		}
	}
	else
	{
		doc->Create(gcnew System::String(file_path.c_str()));
	}
	

	if(languages == "Japanese")
		doc->OCR(MODI::MiLANGUAGES::miLANG_JAPANESE, false, false);
	else
		doc->OCR(MODI::MiLANGUAGES::miLANG_ENGLISH, false, false);

	try
	{
		
		for (int i = 0; i < doc->Images->Count; i++)
		{
			MODI::Image ^img = (MODI::Image ^)doc->Images[i];
			MODI::Layout ^layout = img->Layout;

			

			m_string.data = MarshalString(layout->Text).c_str();
			m_stringOut.write();
			System::Console::WriteLine(layout->Text);

			
			m_wordList.data.length(layout->Words->Count);
			
			for (int j = 0; j < layout->Words->Count; j++)
			{
				MODI::Word ^word = (MODI::Word ^)layout->Words[j];
				m_wordList.data[j] = MarshalString(word->Text).c_str();
				
			}
			
			m_wordListOut.write();
		}
	}
	catch(...)
	{
		return RTC::RTC_ERROR;
	}

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t OCR::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OCR::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OCR::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OCR::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OCR::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void OCRInit(RTC::Manager* manager)
  {
    coil::Properties profile(ocr_spec);
    manager->registerFactory(profile,
                             RTC::Create<OCR>,
                             RTC::Delete<OCR>);
  }
  
};


