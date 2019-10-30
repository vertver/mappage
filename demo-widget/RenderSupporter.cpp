#pragma once
#include "ImGuiRenderer.h"
#include "khrplatform.h"

typedef void*(vkGetInstanceProcAddr)(void*, const char*);
typedef int(vkCreateInstance)(void*, void*, void**);
typedef void(vkDestroyInstance)(void*, void*);
int glVer = 0;
int countOfLayers = 0;
vkGetInstanceProcAddr* pvkGetInstanceProcAddr = nullptr;
vkCreateInstance* pvkCreateInstance = nullptr;
vkDestroyInstance* pvkDestroyInstance = nullptr;
void* vulkanInstance = nullptr;
static void* libGL = {};

typedef enum VkStructureType {
	VK_STRUCTURE_TYPE_APPLICATION_INFO = 0,
	VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO = 1,
	VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO = 2,
	VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO = 3,
	VK_STRUCTURE_TYPE_SUBMIT_INFO = 4,
	VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO = 5,
	VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE = 6,
	VK_STRUCTURE_TYPE_BIND_SPARSE_INFO = 7,
	VK_STRUCTURE_TYPE_FENCE_CREATE_INFO = 8,
	VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO = 9,
	VK_STRUCTURE_TYPE_EVENT_CREATE_INFO = 10,
	VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO = 11,
	VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO = 12,
	VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO = 13,
	VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO = 14,
	VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO = 15,
	VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO = 16,
	VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO = 17,
	VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO = 18,
	VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO = 19,
	VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO = 20,
	VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO = 21,
	VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO = 22,
	VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO = 23,
	VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO = 24,
	VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO = 25,
	VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO = 26,
	VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO = 27,
	VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO = 28,
	VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO = 29,
	VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO = 30,
	VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO = 31,
	VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO = 32,
	VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO = 33,
	VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO = 34,
	VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET = 35,
	VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET = 36,
	VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO = 37,
	VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO = 38,
	VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO = 39,
	VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO = 40,
	VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO = 41,
	VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO = 42,
	VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO = 43,
	VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER = 44,
	VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER = 45,
	VK_STRUCTURE_TYPE_MEMORY_BARRIER = 46,
	VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO = 47,
	VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO = 48,
	VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR = 1000001000,
	VK_STRUCTURE_TYPE_PRESENT_INFO_KHR = 1000001001,
	VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR = 1000002000,
	VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR = 1000002001,
	VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR = 1000003000,
	VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR = 1000004000,
	VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR = 1000005000,
	VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR = 1000006000,
	VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR = 1000007000,
	VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR = 1000008000,
	VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR = 1000009000,
	VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT = 1000011000,
	VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD = 1000018000,
	VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT = 1000022000,
	VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT = 1000022001,
	VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT = 1000022002,
	VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV = 1000026000,
	VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV = 1000026001,
	VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV = 1000026002,
	VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV = 1000056000,
	VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV = 1000056001,
	VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV = 1000057000,
	VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV = 1000057001,
	VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV = 1000058000,
	VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT = 1000061000,
	VK_STRUCTURE_TYPE_BEGIN_RANGE = VK_STRUCTURE_TYPE_APPLICATION_INFO,
	VK_STRUCTURE_TYPE_END_RANGE = VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO,
	VK_STRUCTURE_TYPE_RANGE_SIZE = (VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO - VK_STRUCTURE_TYPE_APPLICATION_INFO + 1),
	VK_STRUCTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} VkStructureType;

typedef uint32_t VkFlags;
typedef VkFlags VkInstanceCreateFlags;

typedef struct VkApplicationInfo {
	VkStructureType    sType;
	const void* pNext;
	const char* pApplicationName;
	uint32_t           applicationVersion;
	const char* pEngineName;
	uint32_t           engineVersion;
	uint32_t           apiVersion;
} VkApplicationInfo;

typedef struct VkInstanceCreateInfo {
	VkStructureType             sType;
	const void* pNext;
	VkInstanceCreateFlags       flags;
	const VkApplicationInfo* pApplicationInfo;
	uint32_t                    enabledLayerCount;
	const char* const* ppEnabledLayerNames;
	uint32_t                    enabledExtensionCount;
	const char* const* ppEnabledExtensionNames;
} VkInstanceCreateInfo;

VkInstanceCreateInfo CurrentVulkanInfo = {};

#if defined(_WIN32) || defined(_WIN64)
typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
#endif

typedef void glGetIntegerv_t(GLenum pname, GLint* data);
typedef GLubyte* glGetStringi_t(GLenum name, GLuint index);
typedef GLubyte* glGetString_t(GLuint index);
glGetIntegerv_t* pglGetIntegerv = nullptr;
glGetStringi_t* pglGetStringi = nullptr;
glGetString_t* pglGetString = nullptr;

static PFNWGLGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;

/*
	Return codes:
	0 - success
	-1 - Vulkan drivers are corrupted or not installed.
	-2 - Vulkan drivers installed and exists, but current video drivers doesn't support it.
*/
int GetVulkanInstanceStruct(char**& pVkExts, int& extsCount)
{
#if defined(_WIN32) || defined(_WIN64)
	int res = 0;
	void* hModule = LoadLibraryA("vulkan-1.dll");
	if (hModule == INVALID_HANDLE_VALUE || !hModule) return -1;

	/* Get procs of Vulkan functions */
	pvkGetInstanceProcAddr = (vkGetInstanceProcAddr*)GetProcAddress((HMODULE)hModule, "vkGetInstanceProcAddr");
	if (!pvkGetInstanceProcAddr) return -1;
	pvkCreateInstance = (vkCreateInstance*)pvkGetInstanceProcAddr(0, "vkCreateInstance");
	if (!pvkCreateInstance) return -1;
	pvkDestroyInstance = (vkDestroyInstance*)pvkGetInstanceProcAddr(0, "vkDestroyInstance");
	if (!pvkCreateInstance) return -1;

	/* 
		Try to initialize Vulkan instances, get extensions, and after that destroy 
		Vulkan instance.
	*/
	res = pvkCreateInstance(&CurrentVulkanInfo, nullptr, &vulkanInstance);
	if (!res || res != 0) return -2;

	countOfLayers = CurrentVulkanInfo.enabledLayerCount;
	extsCount = CurrentVulkanInfo.enabledExtensionCount;
	if (CurrentVulkanInfo.ppEnabledExtensionNames && extsCount) {
		pVkExts = (char**)malloc(sizeof(char*) * (extsCount + 1));
		for (size_t i = 0; i < extsCount; i++) {
			pVkExts[i] = strdup(CurrentVulkanInfo.ppEnabledExtensionNames[i]);
		}
	}

	pvkDestroyInstance(vulkanInstance, nullptr);

	return 0;
#else
	/* macOS has MoltenVK, which use Metal API. */
	return 0;
#endif
}

bool GetOpenGLInstance()
{
#if defined(_WIN32) || defined(_WIN64)
	libGL = LoadLibraryW(L"opengl32.dll");
	if (libGL != INVALID_HANDLE_VALUE && libGL) {
		void (*tmp)(void);
		gladGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE)(GetProcAddress((HMODULE)libGL, "wglGetProcAddress"));
		return gladGetProcAddressPtr != nullptr;
	}
#else
	static const char* NAMES[] = {
	"../Frameworks/OpenGL.framework/OpenGL",
	"/Library/Frameworks/OpenGL.framework/OpenGL",
	"/System/Library/Frameworks/OpenGL.framework/OpenGL",
	"/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
	};

	unsigned int index = 0;
	for (index = 0; index < (sizeof(NAMES) / sizeof(NAMES[0])); index++) {
		libGL = dlopen(NAMES[index], RTLD_NOW | RTLD_GLOBAL);
	
		if (libGL != NULL)  return true;
	}
#endif

	return false;
}

void* GetFuncProc(const char* name)
{
	void* ret = nullptr;

	if (gladGetProcAddressPtr) {
		ret = gladGetProcAddressPtr(name);
	}

	if (!ret) {
#if defined(_WIN32) || defined(_WIN64)
		ret = GetProcAddress((HMODULE)libGL, name);
#else
		ret = dlsym(libGL, name);
#endif
	}

	return ret;
}

/*
	Return codes:
	0 - success
	-1 - OpenGL instance can't be created because GL library is not founded or it corrupted
	-2 - OpenGL library corrupted
	-3 - OpenGL doesn't supported by this system
*/
int GetOpenGLInstanceStruct(char**& pGLExts, int& extsCount)
{
	int major, minor;
	const char* version = nullptr;
	const char* prefixes[] = {
		"OpenGL ES-CM ",
		"OpenGL ES-CL ",
		"OpenGL ES ",
		nullptr
	};

	if (!GetOpenGLInstance()) return -1;
	pglGetIntegerv = (glGetIntegerv_t*)GetFuncProc("glGetIntegerv");
	pglGetStringi = (glGetStringi_t*)GetFuncProc("glGetStringi");
	pglGetString = (glGetString_t*)GetFuncProc("glGetString");
	if (!pglGetIntegerv ||  !pglGetString) return -2;

	if (!pglGetString(GL_VERSION)) -3;

	if (pglGetStringi) {
		pglGetIntegerv(0x821D, &extsCount);
		if (!extsCount) return -3;

		/* Get all extensions names and allocate */
		pGLExts = (char**)malloc(sizeof(char*) * (extsCount + 1));
		for (size_t i = 0; i < extsCount; i++) {
			const char* ptemp = (const char*)pglGetStringi(GL_EXTENSIONS, i);
			pGLExts[i] = strdup(ptemp);
		}
	}

	version = (const char*)pglGetString(GL_VERSION);
	if (version) {
		for (size_t i = 0; prefixes[i]; i++) {
			const size_t lengthOfstring = strlen(prefixes[i]);
			if (!strncmp(version, prefixes[i], lengthOfstring)) {
				version += lengthOfstring;
				break;
			}
		}

#ifdef _MSC_VER
		sscanf_s(version, "%d.%d", &major, &minor);
#else
		sscanf(version, "%d.%d", &major, &minor);
#endif
	}

	glVer = major + minor;
	return 0;
}

CRenderSupporter::CRenderSupporter()
{
	int ret = 0;
	if (!(ret = GetVulkanInstanceStruct(ppVkExtensions, extsVk))) {
		VulkanStruct.isSupported = true;
		VulkanStruct.LayersCount = countOfLayers;
		VulkanStruct.isSupported = extsVk;
		VulkanStruct.MaxVersion = 1;	
	} else {
		switch (ret) {
		case -1: REDEBUGOUTPUT("Vulkan drivers are corrupted or not installed."); break;
		case -2: REDEBUGOUTPUT("Vulkan drivers installed and exists, but current video drivers doesn't support it."); break;
		default: REDEBUGOUTPUT("Vulkan unknown error"); break;
		}
	}

	if (!(ret = GetOpenGLInstanceStruct(ppGLExtensions, extsGl))) {
		OpenGLStruct.isSupported = true;
		OpenGLStruct.MaxVersion = glVer;
	} else {
		switch (ret) {
		case -1: REDEBUGOUTPUT("OpenGL instance can't be created because GL library is not founded or it corrupted."); break;
		case -2: REDEBUGOUTPUT("OpenGL library is corrupted."); break;
		case -3: REDEBUGOUTPUT("OpenGL doesn't supported by this system."); break;
		default: REDEBUGOUTPUT("OpenGL unknown error"); break;
		}
	}
}

CRenderSupporter::~CRenderSupporter()
{
	if (ppVkExtensions) {
		for (size_t i = 0; i < extsVk; i++) {
			if (ppVkExtensions[i]) free(ppVkExtensions[i]);
		}
		free(ppVkExtensions);
	}

	if (ppGLExtensions) {
		for (size_t i = 0; i < extsGl; i++) {
			if (ppGLExtensions[i]) free(ppGLExtensions[i]);
		}
		free(ppGLExtensions);
	}
}

void CRenderSupporter::GetVulkanStruct(VulkanSupportStruct& Struct)
{
	memcpy(&Struct, &VulkanStruct, sizeof(VulkanSupportStruct));
}

void CRenderSupporter::GetOpenGLStruct(OpenGLSupportStruct& Struct)
{
	memcpy(&Struct, &OpenGLStruct, sizeof(VulkanSupportStruct));
}

char* CRenderSupporter::GetVulkanExtensionName(dword_t id)
{
	return ppVkExtensions[id];
}

char* CRenderSupporter::GetOpenGLExtensionName(dword_t id)
{
	return ppGLExtensions[id];
}

bool CRenderSupporter::IsVulkanSupported()
{
	if constexpr (false) {
		return !!VulkanStruct.isSupported;
	} else {
	return false;
	}
}

bool CRenderSupporter::IsOpenGLSupported()
{
	return !!OpenGLStruct.isSupported;
}
