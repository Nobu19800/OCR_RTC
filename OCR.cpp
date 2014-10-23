// -*- C++ -*-
/*!
 * @file  OCR.cpp
 * @brief OCR Component
 * @date $Date$
 *
 * $Id$
 */

#include "OCR.h"
#include "ImageDataCom.h"
#include <windows.h>
#include <wchar.h>
#include <tchar.h>


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
	"conf.default.languages", "JAPANESE",
	"conf.default.tmp_directory_path", "%TMP%",
	"conf.__widget__.file_path", "text",
	"conf.__widget__.input_type", "radio",
	"conf.__widget__.languages", "radio",
	"conf.__widget__.tmp_directory_path", "text",
	"conf.__constraints__.input_type", "(DataPort,Configuration)",
	"conf.__constraints__.languages", "(CZECH,DANISH,GERMAN,GREEK,ENGLISH,SPANISH,FINNISH,FRENCH,HUNGARIAN,ITALIAN,JAPANESE,KOREAN,DUTCH,NORWEGIAN,POLISH,PORTUGUESE,RUSSIAN,SWEDISH,TURKISH,CHINESE_TRADITIONAL,CHINESE_SIMPLIFIED,SYSDEFAULT)",
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
  bindParameter("languages", languages, "JAPANESE");
  bindParameter("tmp_directory_path", tmp_directory_path, "%TMP%");
  
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

			m_imageBuff = GetCameraImage(&m_image);
			
			std::string tmp = tmp_directory_path + "\\m_imageBuff.jpg";
			wchar_t CheckFileName[100];
			mbstowcs(CheckFileName, tmp.c_str(), 100);

			wchar_t CheckFileName2[100];
			ExpandEnvironmentStrings(  CheckFileName ,CheckFileName2,sizeof( CheckFileName2 ));
			char CheckFileName3[100];
			wcstombs(CheckFileName3,CheckFileName2,100);
			
			
			cvSaveImage(CheckFileName3, m_imageBuff);
			

			
			
			

			doc->Create(gcnew System::String(CheckFileName2));

			
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
	

	if(languages == "CZECH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_CZECH, false, false);
	else if(languages == "DANISH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_DANISH, false, false);
	else if(languages == "GERMAN")
		doc->OCR(MODI::MiLANGUAGES::miLANG_GERMAN, false, false);
	else if(languages == "GREEK")
		doc->OCR(MODI::MiLANGUAGES::miLANG_GREEK, false, false);
	else if(languages == "ENGLISH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_ENGLISH, false, false);
	else if(languages == "SPANISH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_SPANISH, false, false);
	else if(languages == "FINNISH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_FINNISH, false, false);
	else if(languages == "FRENCH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_FRENCH, false, false);
	else if(languages == "HUNGARIAN")
		doc->OCR(MODI::MiLANGUAGES::miLANG_HUNGARIAN, false, false);
	else if(languages == "ITALIAN")
		doc->OCR(MODI::MiLANGUAGES::miLANG_ITALIAN, false, false);
	else if(languages == "JAPANESE")
		doc->OCR(MODI::MiLANGUAGES::miLANG_JAPANESE, false, false);
	else if(languages == "KOREAN")
		doc->OCR(MODI::MiLANGUAGES::miLANG_KOREAN, false, false);
	else if(languages == "DUTCH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_DUTCH, false, false);
	else if(languages == "NORWEGIAN")
		doc->OCR(MODI::MiLANGUAGES::miLANG_NORWEGIAN, false, false);
	else if(languages == "POLISH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_POLISH, false, false);
	else if(languages == "PORTUGUESE")
		doc->OCR(MODI::MiLANGUAGES::miLANG_PORTUGUESE, false, false);
	else if(languages == "RUSSIAN")
		doc->OCR(MODI::MiLANGUAGES::miLANG_RUSSIAN, false, false);
	else if(languages == "SWEDISH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_SWEDISH, false, false);
	else if(languages == "TURKISH")
		doc->OCR(MODI::MiLANGUAGES::miLANG_TURKISH, false, false);
	else if(languages == "CHINESE_TRADITIONAL")
		doc->OCR(MODI::MiLANGUAGES::miLANG_CHINESE_TRADITIONAL, false, false);
	else if(languages == "CHINESE_SIMPLIFIED")
		doc->OCR(MODI::MiLANGUAGES::miLANG_CHINESE_SIMPLIFIED, false, false);
	else if(languages == "SYSDEFAULT")
		doc->OCR(MODI::MiLANGUAGES::miLANG_SYSDEFAULT, false, false);
	



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


