#pragma once

#ifdef _WIN32

	//PROJECTTEMPLATEDLL_EXPORTS
	#ifdef ProjectTemplate_EXPORTS 
		#define libProjectTemplate __declspec(dllexport)
	#else
		#define libProjectTemplate __declspec(dllimport)
	#endif
	#ifdef debugDefines
		#ifdef ProjectTemplate_EXPORTS 
			#define libPvtProjectTemplate __declspec(dllexport)
		#else
			#define libPvtProjectTemplate __declspec(dllimport)
		#endif
	#else
		#define libPvtProjectTemplate
	#endif
#else
	#define libProjectTemplate
	#define libPvtProjectTemplate
#endif
